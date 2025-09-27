#pragma once

#define _KB_QUOTE(x)          #x
#define _KB(x)                _KB_QUOTE(x)
#define _KB_INCLUDE(x, y)     _KB(usb/descriptors/keyboard.x.y)

#define USB_STRING_VENDOR_KEYBOARD "LainHW"

#if defined(CONTROLLER_TYPE)
#include _KB_INCLUDE(CONTROLLER_TYPE, h)
#endif
