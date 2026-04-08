#pragma once

// Physical analog channel order on mux
#define ANALOG_DRIVER magnetic
#define ANALOG_CHANNELS_AVAILABLE 7
#define DUALCONTROL_TRANSISTOR_PINS 24, 23, 25, 22, 26, 21, 27
#define ANALOG_CHANNEL_ORDER 5, 6, 11, 7, 10, 8, 9

#define BUTTON_DRIVER dualcontrol
#define DUALCONTROL
#define BUTTONS_AVAILABLE 11
#define BUTTON_PINS 20, 14, 19, 15, 18, 16, 17, 9, 8, 7, 6

// Set button type to DUALCONTROL to switch transistors so lamp holder always gets 5V
#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
#define ENCODER_PINS [0] = {46, 45}, [1] = {44, 43}

// shift which GPIO the PIO use (RP2530B specific, required if using PIO on pins >31, range changes from 0-31 to 16-48)
#define PIO0_BASE_SHIFT
#define PIO1_BASE_SHIFT

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 3
#define RGB_PINS 38, 37, 39
#define RGB_PIO pio0

#define LIGHT_DRIVER direct
#define LIGHTS_AVAILABLE 11
#define LIGHT_PINS 33, 33, 33, 33, 33, 33, 33, 10, 11, 12, 13

#define PSX_ACTIVE
#define PSX_DRIVER          pio
#define PSX_PIO             pio1
#define PSX_CMD_CLK_PINBASE 31
#define PSX_ATT_PIN         30
#define PSX_DAT_PIN         29
#define PSX_ACK_PIN         28

#define USB_CMD_REPORT_SIZE 64

#define FLASH_TARGET_OFFSET (1024 * 1024)

/*** Chain Inclusion ***/
#include_next "config.h"
