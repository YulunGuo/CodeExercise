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

#define FLASH_START_ADDR 0x0801f000

#define KEY1_SPEED1 100//长按时间长度（单位10ms）
#define KEY1_SPEED2 10//双击时间长度（单位20ms）


int main(void){
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化
//	LED_Init();
//	KEY_Init();
//	BUZZER_Init();
		USART1_Init(115200);
//	RTC_Config();
//	TOUCH_KEY_Init();
		TM1640_Init(); //数码管初始化函数
		ENCOODER_Init();//旋转编码器初始化
		I2C_Configuration(); // I2C总线初始化
		OLED_Init();
	
		OLED_DISPLAY_8x16_BUFFER(0,"    Guoyulun");
		OLED_DISPLAY_8x16_BUFFER(4," Encooder Num:");
		OLED_DISPLAY_8x16_BUFFER(6,"  Temp:");
	
	u8 buff[3]; // 温度符号+整数+小数
	u8 status;
	u8 num = 99;
	OLED_DISPLAY_8x16(4,14*8,num/10+0x30);
	OLED_DISPLAY_8x16(4,15*8,num%10+0x30);
	
	TM1640_display(0,num/10);
	TM1640_display(1,num%10);
	TM1640_display(2,20);
	TM1640_display(3,20);
	TM1640_display(4,20);
	TM1640_display(5,20);
	TM1640_display(6,20);
	TM1640_display(7,20);
	while(1){
		LM75A_GetTemp(buff);
		if(buff[0]) OLED_DISPLAY_8x16(6,7*8,'-');
		OLED_DISPLAY_8x16(6,8*8,buff[1]/10+0x30);
		OLED_DISPLAY_8x16(6,9*8,buff[1]%10+0x30);
		OLED_DISPLAY_8x16(6,10*8,'.');
		OLED_DISPLAY_8x16(6,11*8,buff[2]/10+0x30);
		OLED_DISPLAY_8x16(6,12*8,buff[2]%10+0x30);
		status = ENCOODER_READ();
		switch(status){
			case 1:
				num++;
				if(num>99) num = 0;
				break;
			case 2:
				if(num == 0) num = 100;
				num--;
				break;
			case 3:
				num = 0;
		}
		if(status!=0){
			printf("num:%d\r\n",num);
			TM1640_display(0,num/10);
			TM1640_display(1,num%10);
			OLED_DISPLAY_8x16(4,14*8,num/10+0x30);
			OLED_DISPLAY_8x16(4,15*8,num%10+0x30);
		}
		delay_ms(10);
	}
}