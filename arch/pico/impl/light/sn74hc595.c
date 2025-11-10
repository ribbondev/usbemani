static const uint8_t _light_pidx[LIGHTS_ACTIVE]    = { LIGHT_CHANNELS };

void _impl_light_init(void) {
  // Set latch, clock, and data all to low
  // Note that this asserts the latch
  Pin_OutputLow(LIGHT_SN74HC595_LATCH);
  Pin_OutputLow(LIGHT_SN74HC595_CLOCK);
  Pin_OutputLow(LIGHT_SN74HC595_DATA);

#if defined(LIGHTS_ACTIVE) && (LIGHTS_ACTIVE > 0)
  _lights.mask = 0;
  _impl_light_render();
#endif
}

// TODO: Rework the send process to use alarms instead of sleeps
static inline void _impl_light_clock(void) {
  Pin_WriteHigh(LIGHT_SN74HC595_CLOCK);
  sleep_us(5);
  Pin_WriteLow(LIGHT_SN74HC595_CLOCK);
  sleep_us(5);
}

static inline void _impl_light_latch(void) {
  Pin_WriteHigh(LIGHT_SN74HC595_LATCH);
  sleep_us(5);
  Pin_WriteLow(LIGHT_SN74HC595_LATCH);
  sleep_us(5);
}


void _impl_light_render(void) {
#if defined(LIGHTS_ACTIVE) && (LIGHTS_ACTIVE > 0)
  static uint16_t prevMask = -1;

  if (!(prevMask ^ _lights.mask)) return;
  prevMask = _lights.mask;

  // Setup the mask to send to the shift registers
  register uint16_t sendMask = 0;
  for (int i = 0; i < LIGHTS_ACTIVE; i++) {
    register uint16_t bmask = (1 << _light_pidx[i]);
#if defined(LIGHTS_INVERT)
    if (_lights.mask & (1 << i))
      continue;

    sendMask |= bmask;
#else
    if (_lights.mask & (1 << i))
      sendMask |= bmask;
#endif
  }

  // Send the new light data, MSB first
  for (int i = 0; i < 16; i++) {
    if (sendMask & 0x8000)
      Pin_WriteHigh(LIGHT_SN74HC595_DATA);

    _impl_light_clock();
    Pin_WriteLow(LIGHT_SN74HC595_DATA);
    sendMask <<= 1;
  }
  _impl_light_latch();
#endif
}
