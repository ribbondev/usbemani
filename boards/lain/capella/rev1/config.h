#pragma once

#define ANALOG_DRIVER magnetic
#define ANALOG_CHANNELS_AVAILABLE 16
#define ANALOG_CHANNEL_ORDER 4, 5, 10, 6, 9, 7, 8, 0, 1, 2, 3

#define BUTTON_DRIVER magnetic
#define BUTTONS_AVAILABLE 11


#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
#define ENCODER_PINS [0] = {24,25}, [1] = {26,27}

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 1
#define RGB_PINS 22
#define RGB_PIO pio0

#define USB_CMD_REPORT_SIZE 64

#define FLASH_TARGET_OFFSET (1024 * 1024)

/*** Chain Inclusion ***/
#include_next "config.h"
