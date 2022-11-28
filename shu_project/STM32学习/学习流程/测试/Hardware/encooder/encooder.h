#ifndef __ENCOODER_H
#define __ENCOODER_H
#include "sys.h"
#include "delay.h"

#define ENCOODER_PORT_A GPIOA
#define ENCOODER_L GPIO_Pin_6
#define ENCOODER_D GPIO_Pin_7

#define ENCOODER_PORT_B GPIOB
#define ENCOODER_R GPIO_Pin_2

void ENCOODER_Init(void);
u8 ENCOODER_READ(void);

#endif