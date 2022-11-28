#include "buzzer.h"
#include "delay.h"
void BUZZER_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Pin = BUZZER;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(BUZZERPORT,&GPIO_InitStruct);
	GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
}
void BUZZER_BEEP1(void){
	u16 i;
	for(i=0;i<200;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(500);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(500);
	}
}

void BUZZER_BEEP2(void){
	u16 i;
	for(i=0;i<200;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(100);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(100);
	}
}