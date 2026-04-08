#include "usb/descriptors/keyboard.iidx.h"

const USB_REPORT USB_ATTRIBUTES Keyboard_Report[] = {
0x05, 0x01,           //     Usage Page (Generic Desktop Ctrls)
0x09, 0x07,           //     Usage (Keyboard)
0xA1, 0x01,           //     Collection (Application)
0x85, 0x02,           //     Report ID
0x75, 1,              //     Report Size (1) (bit)
0x95, 8,              //     Report Count (8)
0x05, 0x07,           //     Usage Page (Keyboard)
0x19, 224,            //     USAGE_MINIMUM 
0x29, 231,            //     USAGE_MAXIMUM 
0x15, 0x00,           //     LOGICAL_MINIMUM (0)
0x25, 0x01,           //     LOGICAL_MAXIMUM (1)
0x81, 0x02,           //     Input (Data,Var,Abs)
0x75, 1,              //     Report Size (1) (bit)
0x95, (31 * 8),       //     Report Count kk
0x15, 0x00,           //     LOGICAL_MINIMUM (0)
0x25, 0x01,           //     LOGICAL_MAXIMUM (1)
0x05, 0x07,           //     Usage Page (Keyboard)
0x19, 0,              //     USAGE_MINIMUM 
0x29, ((31 * 8) - 1), //     USAGE_MAXIMUM 
0x81, 0x02,           //     Input (Data,Var,Abs)
0xC0,                 //     End Collection
};

#include _KB_INCLUDE(CONTROLLER_TYPE, 13k.c)

WEAK void CALLBACK_OnKeyboardInputRequest(USB_InputReport_Keyboard_t *input) {
  uint16_t buttons = Button_GetAll();
  ENCODER_EMIT direction1 = Encoder_Direction(0);
  ENCODER_EMIT direction2 = Encoder_Direction(1);
  input->buttons = buttons | ((direction1 >> 4) << BUTTONS_ACTIVE) | ((direction2 >> 4) << (BUTTONS_ACTIVE + 2));
}