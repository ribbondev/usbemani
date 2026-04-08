// TODO: Contains subjective changes. Use `user.c` from mini-4 before committing.
#include "usbemani.h"

Effect_Rainbow_t rainbow = New_EffectRainbow(1, 0, CONTROLLER_RGB_LEDS_TURNTABLE, false);

RGB_Color_t getButtonColor(uint8_t button) {
  RGB_Color_t color = {0};
  const uint8_t value = Analog_Get(button);
  // Ignore really low values
  if (value < 5) {
    return color;
  }
  if (button >= 7) {
    // E1-E4
    color.red = value / 2;
    color.green = value / 2;
    color.blue = value / 2;
  } else if (button % 2 == 0) {
    // White keys (
    color.red = value / 2;
    color.green = value / 2;
    color.blue = value / 2;
  } else {
    // Black keys
    color.red = value / 2;
    color.green = value / 2;
    color.blue = value / 2;
  }
  return color;
}

void CALLBACK_OnRGBDrawFallback() {

    const RGB_Color_t TT = {.r=255,.g=255,.b=255};

  // Clear the channel
  
  RGB_ClearAll(0);
  // Draw the keys
  for (uint8_t i = 0; i < 11; i++) {
    const RGB_Color_t color = getButtonColor(i);
    if (Button_Get(i))
      RGB_SetRange(0, (i * CONTROLLER_RGB_LEDS_PER_KEY), CONTROLLER_RGB_LEDS_PER_KEY, color);
  }

  //Set turntable Color
  RGB_SetRange(1, 0, CONTROLLER_RGB_LEDS_TURNTABLE, TT);

}

void CALLBACK_OnRGBDrawUSB(USB_OutputReport_t *output) {
  RGB_ClearAll(0);
  // Draw the 7 keys
  for (int i = 0; i < 1; i++) {
    RGB_SetRange(0, (i * CONTROLLER_RGB_LEDS_PER_KEY), CONTROLLER_RGB_LEDS_PER_KEY, output->rgb[i]);
  }
  // Draw TT
  RGB_SetRange(1, 0, CONTROLLER_RGB_LEDS_TURNTABLE, output->rgb[7+4]);
}