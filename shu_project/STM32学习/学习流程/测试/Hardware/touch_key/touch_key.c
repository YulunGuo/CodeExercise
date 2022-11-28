#include "touch_key.h"


void TOUCH_KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Pin = TOUCH_KEY1 | TOUCH_KEY2 | TOUCH_KEY3 | TOUCH_KEY4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(TOUCH_KEY_PORT,&GPIO_InitStruct);
}