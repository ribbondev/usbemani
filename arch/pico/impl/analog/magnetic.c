// Jump table entry, used for process unrolling.
#define _ANALOG_JUMP_TABLE(x) case x: if (x < ANALOG_CHANNELS_ACTIVE) _impl_analog_processChannel(x); return;
const uint8_t _ANALOG_CHANNEL_ORDER[] = { ANALOG_CHANNEL_ORDER };

#if defined(ANALOG_CHANNELS_ACTIVE) && (ANALOG_CHANNELS_ACTIVE > 0)
_impl_magnetic_t _magnetic[ANALOG_CHANNELS_ACTIVE];
#endif

#define AVG_WINDOW 5

typedef struct {
  uint16_t buf[AVG_WINDOW];
  uint32_t sum;
  uint8_t index;
  uint8_t count; 
} analog_avg_t;

static analog_avg_t _avg[ANALOG_CHANNELS_ACTIVE];

volatile uint8_t _analogs_index = 0;

// Set calibration values for a specific analog channel.
void _impl_analog_setCalibration(int i, uint16_t up, uint16_t down) {
  if (i < 0 || i >= ANALOG_CHANNELS_ACTIVE) return;
  _settings.analog.min[i] = up < down ? up : down;
  _settings.analog.max[i] = up > down ? up : down;
  _settings.analog.invert |= (up > down) << i;
}

// Sets up the IRQ handler on the second core and begin the first conversion
int64_t _impl_analog_startConversion(alarm_id_t id, void *user_data) {
  hw_set_bits(&adc_hw->cs, ADC_CS_START_ONCE_BITS);
  return 0;
}

uint32_t mux_mask() {
  uint32_t mask = 0;
  mask = mask | (1 << MUX_S0);
  mask = mask | (1 << MUX_S1);
  mask = mask | (1 << MUX_S2);
  mask = mask | (1 << MUX_S3);
  return mask;
}

static void set_mux_gpio(uint8_t input) {
  uint32_t s0 = (input & (1 << 0)) >> 0;
  uint32_t s1 = (input & (1 << 1)) >> 1;
  uint32_t s2 = (input & (1 << 2)) >> 2;
  uint32_t s3 = (input & (1 << 3)) >> 3;

  uint32_t mask = mux_mask();

  uint32_t pins = 0;
  pins = pins | (s0 << MUX_S0);
  pins = pins | (s1 << MUX_S1);
  pins = pins | (s2 << MUX_S2);
  pins = pins | (s3 << MUX_S3);

  gpio_put_masked(mask, pins);
}

static inline void _impl_analog_processChannel(const uint8_t i) {
  // Read the raw value from the ADC FIFO.
  uint16_t raw = adc_fifo_get();

  // Rolling average. Subtract oldest sample, store newest sample, advance the index.
  analog_avg_t *a = &_avg[i];
  a->sum -= a->buf[a->index];
  a->buf[a->index] = raw;
  a->sum += raw;
  a->index = (a->index + 1) % AVG_WINDOW;
  if (a->count < AVG_WINDOW) {
    a->count++;
  }

  // Compute averaged value
  uint16_t avg = a->sum / a->count;
  _magnetic[i].raw = avg;

  // Clamp to pre-calibrated range.
  const uint16_t min = _settings.analog.min[i];
  const uint16_t max = _settings.analog.max[i];
  const bool invert = (_settings.analog.invert >> i) & 1;

  uint16_t clamped = avg;
  if (clamped < min) clamped = min;
  if (clamped > max) clamped = max;

  // Scale the raw value from 16-bit to 8-bit.
  uint8_t scaled = 0;
  if (max > min) {
    scaled = (clamped - min) * 255 / (max - min);
  }

  // inversion
  _analogs[i].raw = invert ? (255 - scaled) : scaled;

  // Switch the ADC to the next channel
  const uint8_t next_index = (_analogs_index + 1) % ANALOG_CHANNELS_ACTIVE;

  // Look up physical channel order based on config
  const uint8_t ordered_channel_number = _ANALOG_CHANNEL_ORDER[next_index];


  set_mux_gpio(ordered_channel_number);
  _analogs_index = next_index;

  // Flag the highest bit of the averaging index, to indicate a new ADC read is ready
  _analogs[i].average.index |= 0x80;

  // Start the next conversion after a brief delay
  alarm_pool_add_alarm_in_us(
    _impl_arch_alarmPool(),
    5,
    _impl_analog_startConversion,
    NULL,
    true
  );
}

// Interrupt handler after each conversion is completed.
void _impl_analog_interrupt(void) {
  switch(_analogs_index) {
    _ANALOG_JUMP_TABLE(0);
    _ANALOG_JUMP_TABLE(1);
    _ANALOG_JUMP_TABLE(2);
    _ANALOG_JUMP_TABLE(3);
    _ANALOG_JUMP_TABLE(4);
    _ANALOG_JUMP_TABLE(5);
    _ANALOG_JUMP_TABLE(6);
    _ANALOG_JUMP_TABLE(7);
    _ANALOG_JUMP_TABLE(8);
    _ANALOG_JUMP_TABLE(9);
    _ANALOG_JUMP_TABLE(10);
    _ANALOG_JUMP_TABLE(11);
    _ANALOG_JUMP_TABLE(12);
    _ANALOG_JUMP_TABLE(13);
    _ANALOG_JUMP_TABLE(14);
    _ANALOG_JUMP_TABLE(15);
  }
}

// Sets up the IRQ handler on the second core and begin the first conversion
int64_t _impl_analog_multicoreInit(alarm_id_t id, void *user_data) {
  adc_irq_set_enabled(true);

  irq_set_exclusive_handler(ADC_IRQ_FIFO, _impl_analog_interrupt);
  irq_set_enabled(ADC_IRQ_FIFO, true);

  hw_set_bits(&adc_hw->cs, ADC_CS_START_ONCE_BITS);
  return 0;
}

// Initializes the analog subsystem
void _impl_analog_init(void) {
  // Setup the analog subsystem
  adc_init();
  adc_fifo_setup(
    true,   // Write each conversion to the ADC FIFO
    false,  // Don't use DMA
    1,      // Threshold for interrupts
    false,  // Don't set the error flag
    false   // Raw 16-bit samples we'll convert to 8-bit later
  );
  adc_set_clkdiv(9600); // ~5000 samples/second to reduce noise

  // Setup ADC pin for analog usage
  adc_gpio_init(ANALOG_MAGNETIC_ADC_INPUT + ADC_BASE_PIN);
  adc_select_input(ANALOG_MAGNETIC_ADC_INPUT);

  // Setup switch pins
  gpio_init_mask(mux_mask());
  gpio_set_dir_out_masked(mux_mask());

  // Start the interupt handler on the second core. We'll use a single-fire timer to achieve this
  alarm_pool_add_alarm_in_us(
    _impl_arch_alarmPool(),
    1,
    _impl_analog_multicoreInit,
    NULL,
    true
  );
}