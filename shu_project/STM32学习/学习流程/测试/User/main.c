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

#define KEY1_SPEED1 100//长按时间长度（单位10ms）
#define KEY1_SPEED2 10//双击时间长度（单位20ms）

extern vu16 ADC_DMA_IN[4];

int main(void){
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化
	// LED_Init();
	// KEY_Init();
	// BUZZER_Init();
	// USART1_Init(115200);
	// USART3_Init(115200);
	RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //数码管初始化函数
	// ENCOODER_Init();//旋转编码器初始化
	I2C_Configuration(); // I2C总线初始化
	OLED_Init();
	// RELAY_Init(); // 继电器初始化
	// STEP_MOTOR_Init(); // 步进电机初始化
	ADC_Config();

	while(1){

	}
}