#include "led.h"
#include "delay.h"
void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED1 | LED2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEDPORT,&GPIO_InitStruct);
}

void LED_Breathe(void){
	int i;
	int t;
	int flag;
	t = 1;
	flag = 1;
	if(flag == 1)
		{
			for(i=0;i<10;i++){
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
			delay_us(t);
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
			delay_us(501 - t);
			} // Öð½¥±äÁÁ
			t++;
			if(t == 500){
				flag = 0;
			}
		}else{
			for(i=0;i<10;i++){
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
				delay_us(t);
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
				delay_us(501 - t);
			}
			t--;
			if(t == 1){
				flag = 1;
			}
		} // Öð½¥±ä°µ
}