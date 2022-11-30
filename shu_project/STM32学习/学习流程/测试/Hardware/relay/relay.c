#include "relay.h"

/*
	由于GPIOA中13，14上电后为JTAG功能
	需要在RCC程序中启动AFIO时钟，再在RELAY_Init中加入：
	GPIO_PinRemapConfig(gpio_remap_swj_disable,enable)
	即进行重映射
*/
void RELAY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = RELAY1 | RELAY2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RELAYPORT,&GPIO_InitStructure);
	//禁用JTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_ResetBits(RELAYPORT,RELAY1 | RELAY2);//低电平，初始为关继电器
}
void RELAY_1(u8 c) //c=0放开，c=1按动
{
	GPIO_WriteBit(RELAYPORT,RELAY1,(BitAction)(c));
}
void RELAY_2(u8 c)
{
		GPIO_WriteBit(RELAYPORT,RELAY2,(BitAction)(c));
}