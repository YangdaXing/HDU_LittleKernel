#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "stm32f2xx.h"

void init_keyboard();      //
u8 time_1ms();              //����systick��ʱ1ms
u8 Keyboard_Scan();              //����ɨ�躯��
u8 Keyboard_Jitter();          //������������

#endif // !_KEYBOARD_H

