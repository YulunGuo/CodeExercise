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

	while(1){

	}
}