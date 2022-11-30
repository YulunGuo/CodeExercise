#ifndef __RELAY_H
#define __RELAY_H
#include "sys.h"

// ¼ÌµçÆ÷Çý¶¯³ÌÐò
#define RELAYPORT GPIOA
#define RELAY1 GPIO_Pin_14
#define RELAY2 GPIO_Pin_13

void RELAY_Init(void);
void RELAY_1(u8 c);
void RELAY_2(u8 c);

#endif