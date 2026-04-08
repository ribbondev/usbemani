#pragma once

/*** Buttons ***/
#define BUTTON_UP_THRESHOLD        (255 * 0.25) // Consider a button released at 25%
#define BUTTON_DOWN_THRESHOLD      (255 * 0.3) // Consider a button pressed at 30%

/*** Encoders ***/
#define ENCODER_CHANNELS_REVERSED
#define ENCODER_CHANNELS                0, 1
#define ENCODER_FREQUENCY               16000
#define ENCODER_SAMPLES_UNTIL_VALID     128
#define ENCODER_DIRECTION_THRESHOLD     1
#define ENCODER_DIRECTION_HOLD_TIMEOUT  100

/*** RGB ***/
#define RGB_CHANNELS          0, 1, 2
#define RGB_FRAMERATE_TARGET  120

/*** USB ***/
#define USB_ANALOGS_ACTIVE      11
#define USB_BUTTONS_ACTIVE      15
#define USB_ENCODER_AXES_ACTIVE 2
#define USB_ENCODER_AXES        USB_Axis_X, USB_Axis_Y
#define USB_GENERAL_AXES_ACTIVE 2
#define USB_GENERAL_AXES        USB_Axis_X, USB_Axis_Y
#define USB_RGB_ACTIVE          12

/*** Button Combinations ***/
#define BUTTON_COMBO_ARCH_RESET     0, 1
#define BUTTON_COMBO_KONAMI_CLOUD   7, 8
#define BUTTON_COMBO_KEYBOARD       9, 10
#define BUTTON_COMBO_LR2            1


/*** Additional Includes ***/
#include "usb_labels.h"
