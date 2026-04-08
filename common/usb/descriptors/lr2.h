#pragma once

#define _LR2_QUOTE(x)          #x
#define _LR2(x)                _LR2_QUOTE(x)
#define _LR2_INCLUDE(x, y)     _KC(usb/descriptors/lr2.x.y)

#define USB_STRING_VENDOR_LR2 "Lain HW"

#if defined(CONTROLLER_TYPE)
#include _LR2_INCLUDE(CONTROLLER_TYPE, h)
#endif
