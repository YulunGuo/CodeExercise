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

extern vu16 ADC_DMA_IN[2];

int main(void){
	delay_ms(100); //�ϵ�ʱ�ȴ�������������
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ��
	// LED_Init();
	// KEY_Init();
	// BUZZER_Init();
	// USART1_Init(115200);
	USART3_Init(115200);
	RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //����ܳ�ʼ������
	ENCOODER_Init();//��ת��������ʼ��
	I2C_Configuration(); // I2C���߳�ʼ��
	OLED_Init();
	// RELAY_Init(); // �̵�����ʼ��
	STEP_MOTOR_Init(); // ���������ʼ��
	ADC_Config();
	MY1690_Init(); // MP3��ʼ��

	/*��ʼ��ҳ��*/
	OLED_DISPLAY_PIC();


	/* ���� */
	// ҳ��
	u8 page_flag = 0; // 0:��ʼ��ҳ�棻1:�������ҳ�棻2:MP3����ҳ�棻3:����������
	u8 redisplay_flag = 0; // ���¼���ҳ���־λ,��ֹ�ظ�ˢ��ҳ��
	// �������
	u8 step_motor_status = 0; // �������״̬: 0���رգ�1����ת��2����ת
	u8 step_motor_v = 0; // ��������ٶȣ�4 8��-> 0 1
	// ��ת������
	u8 encooder_status; // 1:������2��������3������ 
	// �¶�
	u8 temp[3];
	// MP3
	u8 volum = 0; // �����ȼ���Ĭ��Ϊ0
	u8 display_num = 1; // ��ǰ�������֣�Ĭ��Ϊ��һ��
	u16 music_num; // ��������
	music_num = MY1690_CHECK(0x25);
	u8 display_status = 0; // ���ֲ���״̬��Ĭ��Ϊ��ͣ

	while(1){
		/*ͨ����������A��Bʵ��ҳ���л���������ʼ��ͼƬҳ�桢�����������ҳ�桢MP3����ҳ���Լ�����������*/
		/*����Aʱʵ��ҳ�����л�*/
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
				if(page_flag == 0) page_flag = 4;
				page_flag--;
				redisplay_flag = 1;
				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1));
			}
		}
		/*����Bʱʵ��ҳ�����л�*/
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)){
				page_flag++;
				if(page_flag == 4) page_flag = 0;
				redisplay_flag = 1;
				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2));
			}
		}


		if(redisplay_flag == 1){
			switch (page_flag)
			{
			case 0:
				/*��ʼҳ��*/
				redisplay_flag = 0;
				OLED_DISPLAY_PIC();
				break;
			case 1:
				/*�������ҳ��*/
				redisplay_flag = 0;
				OLED_DISPLAY_CLEAR();
				OLED_DISPLAY_8x16_BUFFER(0,"  <StepMotor>");
				OLED_DISPLAY_8x16_BUFFER(3,"->Status: "); // ���״̬��Left or right or stop��
				OLED_DISPLAY_8x16_BUFFER(6,"->Speed: "); // ����ٶȣ�4 or 8��
				break;
			case 2:
				/*MP3����ҳ��*/
				redisplay_flag = 0;
				OLED_DISPLAY_CLEAR();
				OLED_DISPLAY_8x16_BUFFER(0,"  <Simple MP3>");
				OLED_DISPLAY_8x16_BUFFER(2,"->Status:");
				OLED_DISPLAY_8x16_BUFFER(4,"->Volumn:"); //�����ȼ�0����30
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:"); // ��ǰ������Ŀ
				break;
			case 3:
				/*�������ҳ��*/
				redisplay_flag = 0;
				OLED_DISPLAY_CLEAR();
				OLED_DISPLAY_8x16_BUFFER(0,"  <Environment>");
				OLED_DISPLAY_8x16_BUFFER(2,"->Time:"); // ʱ��
				OLED_DISPLAY_8x16_BUFFER(4,"->Temp:"); // �¶�
				OLED_DISPLAY_8x16_BUFFER(6,"->Light:"); // ����ǿ��
				break;
			}	
		}

		/*��ͬҳ��״̬��������*/
		switch (page_flag)
		{
		case 1:
			encooder_status = ENCOODER_READ(); // ��ת������״̬
			/*�������ҳ��*/
			/*ͨ����ת���������Ʋ�������رտ���*/
			switch (encooder_status)
			{
			case 1:
				/* ���� */
				OLED_DISPLAY_8x16(0,15*8,'R');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				step_motor_status = 1;
				step_motor_v = 0;
				break;
			case 2:
				/* ���� */
				OLED_DISPLAY_8x16(0,15*8,'L');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				step_motor_status = 2;
				step_motor_v = 0;
				break;
			case 3:
				/* ���� */
				OLED_DISPLAY_8x16(0,15*8,'D');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				step_motor_status = 0;
				break;
			default:
				break;
			}
			/*ͨ��C���л���������ٶ�*/
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
				delay_ms(20);
				if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
					step_motor_v = 1 - step_motor_v;
					while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3));
				}
			}
			/*���Ƶ������ʾ״̬��OLED��Ļ��*/
			if(step_motor_status == 0){
				STEP_MOTOR_OFF();
				//״̬
				OLED_DISPLAY_8x16(3,9*8,'S');
				OLED_DISPLAY_8x16(3,10*8,'T');
				OLED_DISPLAY_8x16(3,11*8,'O');
				OLED_DISPLAY_8x16(3,12*8,'P');
				OLED_DISPLAY_8x16(3,13*8,' ');
				//�ٶ�
				OLED_DISPLAY_8x16(6,8*8,'0');
			}else if(step_motor_status == 1){
				if(step_motor_v == 0){
						STEP_MOTOR_4R(4);
						//״̬
						OLED_DISPLAY_8x16(3,9*8,'R');
						OLED_DISPLAY_8x16(3,10*8,'I');
						OLED_DISPLAY_8x16(3,11*8,'G');
						OLED_DISPLAY_8x16(3,12*8,'H');
						OLED_DISPLAY_8x16(3,13*8,'T');
						//�ٶ�
						OLED_DISPLAY_8x16(6,8*8,'4');
					}else{
						STEP_MOTOR_8R(4);
						//״̬
						OLED_DISPLAY_8x16(3,9*8,'R');
						OLED_DISPLAY_8x16(3,10*8,'I');
						OLED_DISPLAY_8x16(3,11*8,'G');
						OLED_DISPLAY_8x16(3,12*8,'H');
						OLED_DISPLAY_8x16(3,13*8,'T');
						//�ٶ�
						OLED_DISPLAY_8x16(6,8*8,'8');	
					}
			}else if(step_motor_status == 2){
				if(step_motor_v == 0){
						STEP_MOTOR_4L(4);
						//״̬
						OLED_DISPLAY_8x16(3,9*8,'L');
						OLED_DISPLAY_8x16(3,10*8,'E');
						OLED_DISPLAY_8x16(3,11*8,'F');
						OLED_DISPLAY_8x16(3,12*8,'T');
						OLED_DISPLAY_8x16(3,13*8,' ');
						//�ٶ�
						OLED_DISPLAY_8x16(6,8*8,'4');
					}else{
						STEP_MOTOR_8L(4);
						//״̬
						OLED_DISPLAY_8x16(3,9*8,'L');
						OLED_DISPLAY_8x16(3,10*8,'E');
						OLED_DISPLAY_8x16(3,11*8,'F');
						OLED_DISPLAY_8x16(3,12*8,'T');
						OLED_DISPLAY_8x16(3,13*8,' ');
						//�ٶ�
						OLED_DISPLAY_8x16(6,8*8,'8');	
					}
			}
			break;
		case 2:
			/*MP3����ҳ��*/
			/*ͨ����ת������ʵ���������ڣ���ת������ת��С�����²���/ֹͣ*/
			/*C/D�������и�*/
			encooder_status = ENCOODER_READ();
			/*��������*/
			switch (encooder_status)
			{
			case 1:
				// �������� 
				if(volum == 0) volum = 1;
				volum--;
				OLED_DISPLAY_8x16(0,15*8,'-');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				break;
			case 2:
				// ��������
				volum++;
				if(volum == 31) volum = 30;
				OLED_DISPLAY_8x16(0,15*8,'+');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				break;
			case 3:
				// ���š�ֹͣ
				display_status = 1 - display_status;
				if(display_status == 0) {
					OLED_DISPLAY_8x16_BUFFER(6,"    --PAUSE--    ");
					delay_ms(500);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				}else{
					OLED_DISPLAY_8x16_BUFFER(6,"    --PLAY--    ");
					delay_ms(500);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
				}
				break;
			}
			/*����������*/
			// ��������
			MY1690_CMD2(0x31,volum);
			/*�л���Ŀ*/
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
				delay_ms(20);
				if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
					// ��һ��
					MY1690_PREV();
					if(display_num == 0) display_num = 1;
					display_num--;
					OLED_DISPLAY_8x16_BUFFER(6,"    --PREV--    ");
					delay_ms(500);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
					while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3));
				}
			}
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY4)){
				delay_ms(20);
				if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY4)){
					// ��һ��
					MY1690_NEXT();
					display_num++;
					if(display_num == music_num+1) display_num = music_num;
					OLED_DISPLAY_8x16_BUFFER(6,"    --NEXT--    ");
					delay_ms(500);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
					while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY4));
				}
			}
			/*OLED��ʾ*/
			// ����״̬
			if(display_status == 0){
				// ��ͣ
				MY1690_PAUSE();
				OLED_DISPLAY_8x16(2,9*8,'S');
				OLED_DISPLAY_8x16(2,10*8,'T');
				OLED_DISPLAY_8x16(2,11*8,'O');
				OLED_DISPLAY_8x16(2,12*8,'P');
			}else{
				// ����
				MY1690_PLAY();
				OLED_DISPLAY_8x16(2,9*8,'P');
				OLED_DISPLAY_8x16(2,10*8,'L');
				OLED_DISPLAY_8x16(2,11*8,'A');
				OLED_DISPLAY_8x16(2,12*8,'Y');
			}
			// ����
			OLED_DISPLAY_8x16(4,9*8,volum/10+0x30);
			OLED_DISPLAY_8x16(4,10*8,volum%10+0x30);
			// ��ǰ������Ŀ
			OLED_DISPLAY_8x16(6,12*8,display_num/10+0x30);
			OLED_DISPLAY_8x16(6,13*8,display_num%10+0x30);
			break;

		case 3:
			/*�������ҳ��*/
			// Time
			if(RTC_Get() == 0){
			OLED_DISPLAY_8x16(2,7*8,rmin/10+0x30);
			OLED_DISPLAY_8x16(2,8*8,rmin%10+0x30);
			OLED_DISPLAY_8x16(2,9*8,':');
			OLED_DISPLAY_8x16(2,10*8,rsec/10+0x30);
			OLED_DISPLAY_8x16(2,11*8,rsec%10+0x30);
			}
			// Temp
			LM75A_GetTemp(temp);
			if(temp[0] == 1) OLED_DISPLAY_8x16(4,7*8,'-');
			OLED_DISPLAY_8x16(4,8*8,temp[1]/10+0x30);
			OLED_DISPLAY_8x16(4,9*8,temp[1]%10+0x30);
			OLED_DISPLAY_8x16(4,10*8,'.');
			OLED_DISPLAY_8x16(4,11*8,temp[2]/10+0x30);
			OLED_DISPLAY_8x16(4,12*8,temp[2]%10+0x30);
			// Light
			OLED_DISPLAY_8x16(6,8*8,ADC_DMA_IN[0]/1000+0x30);
			OLED_DISPLAY_8x16(6,9*8,ADC_DMA_IN[0]%1000/100+0x30);
			OLED_DISPLAY_8x16(6,10*8,ADC_DMA_IN[0]%100/10+0x30);
			OLED_DISPLAY_8x16(6,11*8,ADC_DMA_IN[0]%10+0x30);
			// delay
			delay_ms(50);
			break;
		default:
			break;
		}
	}
}

