#pragma once

#define ONBOARD_LED 25

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 11
#define BUTTON_PINS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

#define ANALOG_DRIVER direct
#define ANALOG_CHANNELS_AVAILABLE 2
#define ANALOG_PINS 26, 27

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
#define ENCODER_PINS [0] = {26,27}, [1] = {20,21}

#define LIGHT_DRIVER sn74hc595
#define LIGHTS_AVAILABLE 8
#define LIGHT_SN74HC595_CLOCK 11
#define LIGHT_SN74HC595_LATCH 12
#define LIGHT_SN74HC595_DATA  13

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 2
#define RGB_PINS 14, 15
#define RGB_PIO pio0

#define PSX_DRIVER pio
#define PSX_PIO pio1
#define PSX_CMD_CLK_PINBASE 19 
#define PSX_ATT_PIN         21 
#define PSX_DAT_PIN         22
#define PSX_ACK_PIN         28

#define USB_CMD_REPORT_SIZE 64
#define FLASH_TARGET_OFFSET (1024 * 1024)

/*** Chain Inclusion ***/
#include_next "config.h"
