#pragma once
#include "button.h"
#include "encoder.h"
#include "config.h"

#include _LR2_INCLUDE(CONTROLLER_TYPE, 13k.h)


typedef struct __attribute__((packed)) {
          int8_t  turntable;
  const   int8_t _unused_1;
        uint16_t  buttons;
  const  uint8_t _unused_2;
} USB_InputReport_LR2_t;