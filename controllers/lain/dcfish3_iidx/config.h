
#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE iidx

/*** Analogs ***/
#define ANALOG_CHANNELS_ACTIVE    7
#define MUX_S0 5
#define MUX_S1 4
#define MUX_S2 3
#define MUX_S3 2
#define ANALOG_MAGNETIC_ADC_INPUT 7    // GPIO pin 47 for ADC input (RP2350B Base pin is 40)

/*** Buttons ***/
#define BUTTONS_ACTIVE  11

//Button keyboard definitions represent BUTTONS_ACTIVE plus 2 per turntable, 15 total for an 11-key keypad with two turntables. See scan code definitions in /common/button/defs.h
#define BUTTONS_KEYBOARD_DEFINITION {KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_ENTER, KEY_BACKSPACE, KEY_PAGEUP, KEY_PAGEDOWN, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT} 

/*** Encoders ***/
#define ENCODERS_ACTIVE 2
#define ENCODER_PPR     72


/*** RGB ***/
#define RGB_CHANNELS_ACTIVE   3
#define RGB_LED_TYPE          WS2812
#define RGB_LEDS_PER_CHANNEL  (7 * CONTROLLER_RGB_LEDS_PER_KEY) + (4 * 7), 12, 12

/*** Lights ***/
#define LIGHTS_ACTIVE     11

/*** Chain Inclusion ***/
#include_next "config.h"