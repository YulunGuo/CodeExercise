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

#define FLASH_START_ADDR 0x0801f000

#define KEY1_SPEED1 100//长按时间长度（单位10ms）
#define KEY1_SPEED2 10//双击时间长度（单位20ms）


int main(void){
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化
	// LED_Init();
	// KEY_Init();
	// BUZZER_Init();
	// USART1_Init(115200);
	RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //数码管初始化函数
	ENCOODER_Init();//旋转编码器初始化
	I2C_Configuration(); // I2C总线初始化
	OLED_Init();
	// RELAY_Init(); // 继电器初始化
	STEP_MOTOR_Init(); // 步进电机初始化

	u8 encooder_flag;
	u8 flag = 1;
	u8 buf[3];
	u8 step_motor_flag = 0;
	/* 开机显示图片 */
	OLED_DISPLAY_PIC();

	while(1){
		// 通过触摸按键控制步进电机
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)) {
			step_motor_flag = 1;
			while (!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)) STEP_MOTOR_4L(3);
			OLED_DISPLAY_CLEAR();
		}
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)) {
			step_motor_flag = 2;
			while (!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY2)) STEP_MOTOR_4R(3);
			OLED_DISPLAY_CLEAR();
		}
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)) {
			step_motor_flag = 3;
			while (!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)) STEP_MOTOR_8L(3);
			OLED_DISPLAY_CLEAR();
		}
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY4)) {
			step_motor_flag = 4;
			while (!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY4)) STEP_MOTOR_8R(3);
			OLED_DISPLAY_CLEAR();
		}
		else {
			STEP_MOTOR_OFF();
		}
		// 旋转编码器进行切换
		encooder_flag = ENCOODER_READ();
		if(encooder_flag == 1) {
			flag = 1;
			OLED_DISPLAY_CLEAR();
		}
		if(encooder_flag == 2) {
			flag = 2;
			OLED_DISPLAY_CLEAR();
		}
		if(encooder_flag == 3){
			flag = 3;
			OLED_DISPLAY_CLEAR();
		}
		if(flag == 1) OLED_DISPLAY_PIC();
		if(flag == 2){
			OLED_DISPLAY_8x16_BUFFER(0,"    Guoyulun");
			// 温度
			LM75A_GetTemp(buf);
			OLED_DISPLAY_8x16_BUFFER(2," Temp:");
			if(buf[0] == 1) OLED_DISPLAY_8x16(2,6*8,'-');
			OLED_DISPLAY_8x16(2,7*8,buf[1]/10+0x30);
			OLED_DISPLAY_8x16(2,8*8,buf[1]%10+0x30);
			OLED_DISPLAY_8x16(2,9*8,'.');
			OLED_DISPLAY_8x16(2,10*8,buf[2]/10+0x30);
			OLED_DISPLAY_8x16(2,11*8,buf[2]%10+0x30);
			// 时间
			RTC_Get();
			OLED_DISPLAY_8x16_BUFFER(4," Time:");
			OLED_DISPLAY_8x16(4,6*8,rday/10+0x30);
			OLED_DISPLAY_8x16(4,7*8,rday%10+0x30);
			OLED_DISPLAY_8x16(4,8*8,'.');
			OLED_DISPLAY_8x16(4,9*8,rhour/10+0x30);
			OLED_DISPLAY_8x16(4,10*8,rhour%10+0x30);
			OLED_DISPLAY_8x16(4,11*8,'.');
			OLED_DISPLAY_8x16(4,12*8,rsec/10+0x30);
			OLED_DISPLAY_8x16(4,13*8,rsec%10+0x30);
			// 电机状态
			OLED_DISPLAY_8x16_BUFFER(6," Motor:");
			switch (step_motor_flag)
			{
			case 0 :
				OLED_DISPLAY_8x16(6,7*8,'S');
				OLED_DISPLAY_8x16(6,8*8,'T');
				OLED_DISPLAY_8x16(6,9*8,'O');
				OLED_DISPLAY_8x16(6,10*8,'P');				
				break;
			case 1:
				OLED_DISPLAY_8x16(6,7*8,'L');
				OLED_DISPLAY_8x16(6,8*8,'E');
				OLED_DISPLAY_8x16(6,9*8,'F');
				OLED_DISPLAY_8x16(6,10*8,'T');
				break;
			case 2:
				OLED_DISPLAY_8x16(6,7*8,'R');
				OLED_DISPLAY_8x16(6,8*8,'I');
				OLED_DISPLAY_8x16(6,9*8,'G');
				OLED_DISPLAY_8x16(6,10*8,'H');
				OLED_DISPLAY_8x16(6,11*8,'T');
				break;	
			case 3:
				OLED_DISPLAY_8x16(6,7*8,'L');
				OLED_DISPLAY_8x16(6,8*8,'E');
				OLED_DISPLAY_8x16(6,9*8,'F');
				OLED_DISPLAY_8x16(6,10*8,'T');
				break;	
			case 4:
				OLED_DISPLAY_8x16(6,7*8,'R');
				OLED_DISPLAY_8x16(6,8*8,'I');
				OLED_DISPLAY_8x16(6,9*8,'G');
				OLED_DISPLAY_8x16(6,10*8,'H');
				OLED_DISPLAY_8x16(6,11*8,'T');
				break;
			}
		}
	}
}