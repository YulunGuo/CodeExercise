#include "buzzer.h"
#include "delay.h"

void BUZZER_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BUZZER; //�˿ں�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUZZERPORT,&GPIO_InitStructure);
	
	GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); //д��ߵ�ƽ����ֹ������һֱ�죬������
}



void BUZZER_BEEP1(void){
	u16 i;
	for(i=0;i<200;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(500);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(500);
	}
} //��һ��


void BUZZER_BEEP2(void){
	u16 i;
	for(i=0;i>500;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(1000);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(1000);
	}
}

uc16 music1[78]={ //����1�����ݱ�����������(Ƶ��)��ż���ǳ���(��Ƶ��ִ�е�ʱ�䣬��λms)��
330,750,
440,375,
494,375,
523,750,
587,375,
659,375,
587,750,
494,375,
392,375,
440,1500,
330,750,
440,375,
494,375,
523,750,
587,375,
659,375,
587,750,
494,375,
392,375,
784,1500,
659,750,
698,375,
784,375,
880,750,
784,375,
698,375,
659,750,
587,750,
659,750,
523,375,
494,375,
440,750,
440,375,
494,375,
523,750,
523,750,
494,750,
392,750,
440,3000
};

void MIDI_PLAY(void){
	u16 i,j;
	for(i=0;i<39;i++){ // �����ĸ���
		for(j=0;j<music1[2*i]*music1[2*i+1]/1000;j++){ // ÿ�������Ĳ��ų���
			// ÿ��������Ƶ�ʣ�������
			GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
			delay_ms(500/music1[2*i]);
			GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
			delay_ms(500/music1[2*i]);
		}
	}

}