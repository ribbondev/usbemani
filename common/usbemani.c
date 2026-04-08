#include "usbemani.h"
#include "settings.h"

Settings_t _settings;

TimerTick_t _timer;
HSV_Color_t _effect_global;
USB_LightingHelper_t USB_LightingHelper = {
  .active = 0,
};

CommandReport_t _command = {
  .ready = false,
};

int main(void) {
  // Read & write settings
  Flash_Init();
  Flash_Read();

  // Initialize hardware
  
  //If PIO_BASE is defined shift the base GPIO for that PIO by 16
  //RP2350B which has an extra bank of GPIO, to use a PIO on the pins beyond 32 this must be set
#if defined(PIO0_BASE_SHIFT)
 pio_set_gpio_base(pio0, 16);
#endif

#if defined(PIO1_BASE_SHIFT)
 pio_set_gpio_base(pio1, 16);
#endif

  //DUAL CONTROL button boards need to get GND from the conventional button's GND spade connector. 
  //the transistor connected to GND must be open for it to work (in the conventional implementation)
  //can also be achieved in hardware by jumping switch ground to LED ground
#if defined(DUALCONTROL)
   const uint8_t _DUALCONTROL_TRANSISTOR_PINS[] = { DUALCONTROL_TRANSISTOR_PINS };
  for (uint8_t i = 0; i < ANALOG_CHANNELS_AVAILABLE; i++) {
      gpio_init(_DUALCONTROL_TRANSISTOR_PINS[i]);
      gpio_set_dir(_DUALCONTROL_TRANSISTOR_PINS[i], 1);
      gpio_put(_DUALCONTROL_TRANSISTOR_PINS[i], 1);
  }
#endif

  Arch_Init();
  Analog_Init();
  Button_Init();
  Encoder_Init();
  Light_Init();
  PSX_Init();
  RGB_Init();
  Timer_Init();

  // Wait a brief moment for initialized components to stabilize before initializing anything else
  Arch_Stabilize();
  // Initialize quirks
  Quirks_Init();

#if defined(ANALOG_CHANNELS_ACTIVE) && (ANALOG_CHANNELS_ACTIVE > 0)
  // HACK: Run the analog task a few times in case it's used in button readings
  //       otherwise the subsequent checks will never pass.
  for (int i = 0; i < 1000; i++)
    Analog_Task();
#endif

  // Check if bootloader entry is requested
  Arch_BootloaderCheck();
  // Check if Konami Cloud descriptors are requested
  HID_KonamiCloudCheck();
  // Check if Keyboard descriptors are requested
  HID_KeyboardCheck();
  // Check if LR2 descriptors are requested
  HID_LR2Check();

  // Call user hook when hardware is ready
  if (CALLBACK_OnHardwareReady)
    CALLBACK_OnHardwareReady();

  // Initialize HID/USB stack
  HID_Init();

  for(;;) {
    HID_Task();
    PSX_Task();
    Analog_Task();

    // If an RGB frame tick has passed, call user hook to update values
    if (RGB_ReadyToCalculate()) {
      if (CALLBACK_RGBCalculateNextFrame) {
        CALLBACK_RGBCalculateNextFrame();
      }
    }

    // If the framebuffer is free to draw, call user hooks to perform draws
    if (RGB_ReadyToDraw()) {
      if (CALLBACK_OnRGBDrawUSB && USB_LightingHelper.last_output) {
        CALLBACK_OnRGBDrawUSB(USB_LightingHelper.last_output);
      } else if (CALLBACK_OnRGBDrawFallback) {
        CALLBACK_OnRGBDrawFallback();
      }
      RGB_Render();
    }

    // If it's time to update lights, call user hooks to perform draws
    if (Light_ReadyToDraw()) {
      if (CALLBACK_OnLightingDrawUSB && USB_LightingHelper.last_output) {
        CALLBACK_OnLightingDrawUSB(USB_LightingHelper.last_output);
      } else if (CALLBACK_OnLightingDrawFallback) {
        CALLBACK_OnLightingDrawFallback();
      }
      Light_Render();
    }

    // Call user-defined tasks at the end
    if (CALLBACK_UserTask) {
      CALLBACK_UserTask();
    }
  }
}

// 8kHz timer
void CALLBACK_OnTimer() {
  // Increment the tick timer
  Timer_Tick();
  // Update the current status of RGB frame draws
  RGB_UpdateStatus();
  // Update the current status of traditional lighting frame draws
  Light_UpdateStatus();

  // Tick down our enumerated lighting timer.
  if (USB_LightingHelper.active) {
    USB_LightingHelper.active--;
  } else if (USB_LightingHelper.last_output) {
    USB_LightingHelper.last_output = NULL;
  }
}
