#include "buzzer.h"
#include "delay.h"

void BUZZER_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BUZZER; //端口号
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUZZERPORT,&GPIO_InitStructure);
	
	GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); //写入高电平，防止蜂鸣器一直响，损坏器件
}



void BUZZER_BEEP1(void){
	u16 i;
	for(i=0;i<200;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(500);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(500);
	}
} //响一声


void BUZZER_BEEP2(void){
	u16 i;
	for(i=0;i>500;i++){
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
		delay_us(1000);
		GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
		delay_us(1000);
	}
}

uc16 music1[78]={ //音乐1的数据表（奇数是音调(频率)，偶数是长度(该频率执行的时间，单位ms)）
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
	for(i=0;i<39;i++){ // 音符的个数
		for(j=0;j<music1[2*i]*music1[2*i+1]/1000;j++){ // 每个音符的播放长度
			// 每个音符的频率，即音调
			GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0));
			delay_ms(500/music1[2*i]);
			GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1));
			delay_ms(500/music1[2*i]);
		}
	}

}