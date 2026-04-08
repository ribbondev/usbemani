#include "usb/descriptors/keyboard.h"

#if defined(CONTROLLER_TYPE)
#include _KB_INCLUDE(CONTROLLER_TYPE, c)
#endif