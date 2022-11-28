#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LEDPORT GPIOB
#define LED1 GPIO_Pin_0
#define LED2 GPIO_Pin_1

void LED_Init(void);
void LED_Breathe(void);

#endif