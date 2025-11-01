#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
#define BUTTONS_ACTIVE  11
#define BUTTON_INVERTED 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1

/*** Uncomment for Mini-4 with conventional E1-E4 switches ***/
//#define BUTTON_INVERTED 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1


//Button keyboard definitions represent BUTTONS_ACTIVE plus 2 per turntable, 15 total for an 11-key keypad with two turntables. See scan code definitions in /common/button/defs.h
#define BUTTONS_KEYBOARD_DEFINITION {KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_ENTER, KEY_BACKSPACE, KEY_PAGEUP, KEY_PAGEDOWN, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT} 

/*** Encoders ***/
#define ENCODERS_ACTIVE 1
#define ENCODER_PPR     72

/*** RGB ***/
#define RGB_CHANNELS_ACTIVE   1
#define RGB_LED_TYPE          WS2812
#define RGB_LEDS_PER_CHANNEL  (7 * CONTROLLER_RGB_LEDS_PER_KEY) + (4 * 1) + (CONTROLLER_RGB_LEDS_TURNTABLE)

/*** Chain Inclusion ***/
#include_next "config.h"
