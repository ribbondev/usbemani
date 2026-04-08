#pragma once
#include <stdint.h>
#include "impl/usb.h"

extern _usb_status_t _usb_status;

void HID_SetMode(USB_DeviceType_t new_mode);

static inline void HID_Init(void) {
  _impl_hid_init();
}

static inline void HID_Task(void) {
  _impl_hid_task();
}

// Check if a specific set of buttons is being held. If so, switch to Konami Cloud descriptors.
static inline void HID_KonamiCloudCheck(void) {
#if defined(BUTTON_COMBO_KONAMI_CLOUD)
   uint8_t  check_buttons[] = { BUTTON_COMBO_KONAMI_CLOUD };
  uint16_t required_buttons = 0;
  uint16_t     held_buttons = 0;

  for (uint8_t i = 0; i < sizeof(check_buttons); i++) {
    const uint16_t mask = (1 << check_buttons[i]);
    required_buttons |= mask;

    if (Button_GetRaw(check_buttons[i]))
      held_buttons |= mask;
  }

  if (held_buttons == required_buttons)
    HID_SetMode(USB_DeviceType_KonamiCloud);
#endif
}

// Check if a specific set of buttons is being held. If so, switch to LR2 descriptors.
static inline void HID_LR2Check(void) {
#if defined(BUTTON_COMBO_LR2)
   uint8_t  check_buttons[] = { BUTTON_COMBO_LR2 };
  uint16_t required_buttons = 0;
  uint16_t     held_buttons = 0;

  for (uint8_t i = 0; i < sizeof(check_buttons); i++) {
    const uint16_t mask = (1 << check_buttons[i]);
    required_buttons |= mask;

    if (Button_GetRaw(check_buttons[i]))
      held_buttons |= mask;
  }

  if (held_buttons == required_buttons)
    HID_SetMode(USB_DeviceType_LR2);
#endif
}

// Check if a specific set of buttons is being held. If so, switch to Keyboard descriptors.
static inline void HID_KeyboardCheck(void) {
#if defined(BUTTON_COMBO_KEYBOARD)
   uint8_t  check_buttons[] = { BUTTON_COMBO_KEYBOARD };
  uint16_t required_buttons = 0;
  uint16_t     held_buttons = 0;

  for (uint8_t i = 0; i < sizeof(check_buttons); i++) {
    const uint16_t mask = (1 << check_buttons[i]);
    required_buttons |= mask;

    if (Button_GetRaw(check_buttons[i]))
      held_buttons |= mask;
  }

  if (held_buttons == required_buttons)
    HID_SetMode(USB_DeviceType_Keyboard);
#endif
}