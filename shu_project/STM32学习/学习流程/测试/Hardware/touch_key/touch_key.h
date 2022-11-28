#ifndef __TOUCH_KEY_H
#define __TOUCH_KEY_H
#include "sys.h"

#define TOUCH_KEY_PORT GPIOA
#define TOUCH_KEY1 GPIO_Pin_0
#define TOUCH_KEY2 GPIO_Pin_1
#define TOUCH_KEY3 GPIO_Pin_2
#define TOUCH_KEY4 GPIO_Pin_3


void TOUCH_KEY_Init(void);

#endif