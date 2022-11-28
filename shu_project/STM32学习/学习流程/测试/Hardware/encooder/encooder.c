#include "encooder.h"

u8 KUP; //������������־��1Ϊ������
u16 cou; //ͨ�ü�����

void ENCOODER_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = ENCOODER_D | ENCOODER_L;
	GPIO_Init(ENCOODER_PORT_A,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ENCOODER_R;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENCOODER_PORT_B,&GPIO_InitStructure);
}

u8 ENCOODER_READ(void){
	u8 a; //��Ű���ֵ
	u8 kt;
	a = 0;
	if(GPIO_ReadInputDataBit(ENCOODER_PORT_A,ENCOODER_L)){
		KUP = 0;
	}
	if(!GPIO_ReadInputDataBit(ENCOODER_PORT_A,ENCOODER_L) && KUP == 0){
		delay_us(100);
		kt = GPIO_ReadInputDataBit(ENCOODER_PORT_B,ENCOODER_R);
		delay_ms(3);
		if(!GPIO_ReadInputDataBit(ENCOODER_PORT_A,ENCOODER_L)){
			if(kt == 0){
				a = 1; //����
			}else{
				a = 2;//����
			}
			cou = 0;
			while(!GPIO_ReadInputDataBit(ENCOODER_PORT_A,ENCOODER_L) && cou < 60000){
				cou++;
				KUP = 1;
				delay_us(20);
			}
		}
	}
	if(!GPIO_ReadInputDataBit(ENCOODER_PORT_A,ENCOODER_D)&&KUP == 0){
		delay_ms(20);
		if(!GPIO_ReadInputDataBit(ENCOODER_PORT_A,ENCOODER_D)){
			a = 3;
		}
	}
	return a;
}
