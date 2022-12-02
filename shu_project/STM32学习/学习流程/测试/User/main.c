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
	RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //����ܳ�ʼ������
	// ENCOODER_Init();//��ת��������ʼ��
	I2C_Configuration(); // I2C���߳�ʼ��
	OLED_Init();
	// RELAY_Init(); // �̵�����ʼ��
	// STEP_MOTOR_Init(); // ���������ʼ��
	ADC_Config();

	/*ҡ�˰���*/
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);


	// ��ʼ������
	OLED_DISPLAY_PIC();

	u8 flag = 0;
	u8 buf[3]; // �¶�
	u8 left_num = 0;
	u8 right_num = 0;
	while(1){
		LM75A_GetTemp(buf);
		RTC_Get();
		delay_ms(100);
		/* ͨ��ҡ�˿���ҳ����л� */
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)){
			OLED_DISPLAY_CLEAR();
			OLED_DISPLAY_PIC();
			flag = 0;
			while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2));
		}
		if(ADC_DMA_IN[2] >= 3000){
			//�ұ�
			flag = 2;
			while(ADC_DMA_IN[2] >= 3000);
			right_num = 0;
			left_num = 0;
			OLED_DISPLAY_CLEAR();
		}
		if(ADC_DMA_IN[2] <= 1000){
			//���
			flag = 1;
			while(ADC_DMA_IN[2] <= 1000);
			OLED_DISPLAY_CLEAR();
		}

		switch (flag)
		{
		case 1:
			OLED_DISPLAY_8x16_BUFFER(0,"  Environment");
			OLED_DISPLAY_8x16_BUFFER(3," Tem:");
			OLED_DISPLAY_8x16_BUFFER(6," Light:");
			if(buf[0] == 1) OLED_DISPLAY_8x16(3,5*8,'-');
			OLED_DISPLAY_8x16(3,6*8,buf[1]/10+0x30);
			OLED_DISPLAY_8x16(3,7*8,buf[1]%10+0x30);
			OLED_DISPLAY_8x16(3,8*8,'.');
			OLED_DISPLAY_8x16(3,9*8,buf[2]/10+0x30);
			OLED_DISPLAY_8x16(3,10*8,buf[2]%10+0x30);
			// Light
			OLED_DISPLAY_8x16(6,7*8,ADC_DMA_IN[1]/1000+0x30);
			OLED_DISPLAY_8x16(6,8*8,ADC_DMA_IN[1]%1000/100+0x30);
			OLED_DISPLAY_8x16(6,9*8,ADC_DMA_IN[1]%100/10+0x30);
			OLED_DISPLAY_8x16(6,10*8,ADC_DMA_IN[1]%10+0x30);
			break;
		
		case 2:
			OLED_DISPLAY_8x16_BUFFER(0,"     Clock");
			OLED_DISPLAY_8x16_BUFFER(3," Time:");
			OLED_DISPLAY_8x16_BUFFER(6," L:   R:");

			OLED_DISPLAY_8x16(3,6*8,rhour/10+0x30);
			OLED_DISPLAY_8x16(3,7*8,rhour%10+0x30);
			OLED_DISPLAY_8x16(3,8*8,':');
			OLED_DISPLAY_8x16(3,9*8,rmin/10+0x30);
			OLED_DISPLAY_8x16(3,10*8,rmin%10+0x30);
			OLED_DISPLAY_8x16(3,11*8,':');
			OLED_DISPLAY_8x16(3,12*8,rsec/10+0x30);
			OLED_DISPLAY_8x16(3,13*8,rsec%10+0x30);

			OLED_DISPLAY_8x16(6,3*8,right_num/10+0x30);
			OLED_DISPLAY_8x16(6,4*8,right_num%10+0x30);

			OLED_DISPLAY_8x16(6,8*8,left_num/10+0x30);
			OLED_DISPLAY_8x16(6,9*8,left_num%10+0x30);
			
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
				right_num++;
				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1));
			}
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)){
				left_num++;
				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2));
			}
			break;
		}

	}
}