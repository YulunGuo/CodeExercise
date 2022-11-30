#include "relay.h"

/*
	����GPIOA��13��14�ϵ��ΪJTAG����
	��Ҫ��RCC����������AFIOʱ�ӣ�����RELAY_Init�м��룺
	GPIO_PinRemapConfig(gpio_remap_swj_disable,enable)
	��������ӳ��
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
	//����JTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_ResetBits(RELAYPORT,RELAY1 | RELAY2);//�͵�ƽ����ʼΪ�ؼ̵���
}
void RELAY_1(u8 c) //c=0�ſ���c=1����
{
	GPIO_WriteBit(RELAYPORT,RELAY1,(BitAction)(c));
}
void RELAY_2(u8 c)
{
		GPIO_WriteBit(RELAYPORT,RELAY2,(BitAction)(c));
}