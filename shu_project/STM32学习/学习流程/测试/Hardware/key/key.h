#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEYPORT GPIOA
#define KEY1 GPIO_Pin_0
#define KEY2 GPIO_Pin_1

void KEY_Init(void);

#endif