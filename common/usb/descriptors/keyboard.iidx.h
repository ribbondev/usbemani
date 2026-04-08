#pragma once
#include "button.h"
#include "encoder.h"
#include "config.h"

#include _KB_INCLUDE(CONTROLLER_TYPE, 13k.h)


typedef struct __attribute__((packed)) {
        uint16_t  buttons;
} USB_InputReport_Keyboard_t;
