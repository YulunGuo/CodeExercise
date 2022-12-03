#include "stm32f10x.h"

#include "led.h"
#include "sys.h"
#include "delay.h"
#include "key.h"
#include "flash.h"
#include "buzzer.h"
#include "usart.h"
#include "rtc.h"
#include "touch_key.h"
#include "TM1640.h"
#include "encooder.h"
#include "lm75a.h"
#include "oled.h"
#include "relay.h"
#include "stepmotor.h"
#include "adc.h"
#include "my1690.h"

#define FLASH_START_ADDR 0x0801f000

#define KEY1_SPEED1 100//����ʱ�䳤�ȣ���λ10ms��
#define KEY1_SPEED2 10//˫��ʱ�䳤�ȣ���λ20ms��

extern vu16 ADC_DMA_IN[4];

int main(void){
	delay_ms(100); //�ϵ�ʱ�ȴ�������������
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ��
	// LED_Init();
	// KEY_Init();
	// BUZZER_Init();
	// USART1_Init(115200);
	// USART3_Init(115200);
	// RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //����ܳ�ʼ������
	ENCOODER_Init();//��ת��������ʼ��
	I2C_Configuration(); // I2C���߳�ʼ��
	OLED_Init();
	// RELAY_Init(); // �̵�����ʼ��
	// STEP_MOTOR_Init(); // ���������ʼ��
	// ADC_Config();
	MY1690_Init(); // MP3��ʼ��

	/* ���� */
	u16 display_status = 0; // ��ǰ����״̬
	u8 display_voice_status = 0; // ��ǰ������С
	u8 ENCOODER_Status;
	u8 music_num;

	delay_ms(30);

	/* ��ʼ��ҳ�� */
	OLED_DISPLAY_PIC();
	MY1690_CMD2(0x31,display_voice_status); // ��ʼ������
	delay_s(5);
	music_num = MY1690_CHECK(0x29);
	OLED_DISPLAY_CLEAR();
	OLED_DISPLAY_8x16_BUFFER(0,"   Simple MP3");
	OLED_DISPLAY_8x16_BUFFER(2,"->Voice:");
	OLED_DISPLAY_8x16_BUFFER(4,"->Statue:");
	OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
	// voice
	OLED_DISPLAY_8x16(2,8*8,display_voice_status/10+0x30);
	OLED_DISPLAY_8x16(2,9*8,display_voice_status%10+0x30);
	// display statue
	OLED_DISPLAY_8x16(4,9*8,display_status+0x30);
	// music num
	OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
	OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);

	while(1){
		ENCOODER_Status = ENCOODER_READ();
		music_num = MY1690_CHECK(0x29);
		delay_ms(50);
		switch (ENCOODER_Status){
		case 1:
			/* ����UP */
			display_voice_status++;
			if(display_voice_status>30) display_voice_status = 30;
			OLED_DISPLAY_8x16(2,8*8,display_voice_status/10+0x30);
			OLED_DISPLAY_8x16(2,9*8,display_voice_status%10+0x30);
			MY1690_VUP(); // up
			if (display_status==0) {
				OLED_DISPLAY_8x16_BUFFER(6,"    --STOP--   ");
				delay_ms(1000);
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
				delay_ms(50);
				OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
			}
			if (display_status==1) {
				OLED_DISPLAY_8x16_BUFFER(6,"  --DISPLAY--   ");
				delay_ms(1000);
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
				delay_ms(50);
				OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
			}
			break;
		case 2:
			/* ����DOWN */
			if(display_voice_status == 0) display_voice_status = 1;
			display_voice_status--;
			OLED_DISPLAY_8x16(2,8*8,display_voice_status/10+0x30);
			OLED_DISPLAY_8x16(2,9*8,display_voice_status%10+0x30);
			MY1690_VDOWM(); // down
			if (display_status==0) {
				OLED_DISPLAY_8x16_BUFFER(6,"    --STOP--   ");
				delay_ms(1000);
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
				delay_ms(50);
				OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
			}
			if (display_status==1) {
				OLED_DISPLAY_8x16_BUFFER(6,"  --DISPLAY--   ");
				delay_ms(1000);
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
				delay_ms(50);
				OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
			}
			break;
		case 3:
			/* �����ͣ��򿪣�������ͣ */
				if(display_status == 0){
					MY1690_PLAY();
					display_status = 1;
					OLED_DISPLAY_8x16(4,9*8,display_status+0x30);
					OLED_DISPLAY_8x16_BUFFER(6,"  --DISPLAY--   ");
					delay_ms(3000);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
					OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
					delay_ms(50);
					OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
				}
				else if(display_status == 1){
					MY1690_PAUSE();
					display_status = 0;
					OLED_DISPLAY_8x16(4,9*8,display_status+0x30);
					OLED_DISPLAY_8x16_BUFFER(6,"    --STOP--   ");
					delay_ms(1000);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
					OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
					delay_ms(50);
					OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
				}
			break;
		}

		/*ͨ�����������л�����*/
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
				/*A������и���*/
				MY1690_PREV();
				delay_ms(50);
				MY1690_STOP();
				OLED_DISPLAY_8x16_BUFFER(6,"    --PREV--   ");
				delay_ms(1000);
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
				delay_ms(50);
				OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);

				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1));
			}
		}
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)){
				/*B����ǰ�и���*/
				MY1690_NEXT();
				delay_ms(50);
				MY1690_STOP();
				OLED_DISPLAY_8x16_BUFFER(6,"    --NEXT--   ");
				delay_ms(1000);
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				OLED_DISPLAY_8x16(6,12*8,music_num/10+0x30);
				delay_ms(50);
				OLED_DISPLAY_8x16(6,13*8,music_num%10+0x30);
				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2));
			}
		}
		// ���ڽ��մ���1��STOP��,2(OK)
		if(USART3_RX_STA == 1){
			display_status = 0;
			USART3_RX_STA = 0;
		}else if(USART3_RX_STA == 2){
			USART3_RX_STA = 0;
		}
	}
}

