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
	// RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //数码管初始化函数
	ENCOODER_Init();//旋转编码器初始化
	I2C_Configuration(); // I2C总线初始化
	OLED_Init();
	// RELAY_Init(); // 继电器初始化
	// STEP_MOTOR_Init(); // 步进电机初始化
	// ADC_Config();
	MY1690_Init(); // MP3初始化

	/* 变量 */
	u16 display_status = 0; // 当前播放状态
	u8 display_voice_status = 0; // 当前音量大小
	u8 ENCOODER_Status;
	u8 music_num;

	delay_ms(30);

	/* 初始化页面 */
	OLED_DISPLAY_PIC();
	MY1690_CMD2(0x31,display_voice_status); // 初始化音量
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
			/* 右旋UP */
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
			/* 右旋DOWN */
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
			/* 如果暂停则打开，打开则暂停 */
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

		/*通过触摸按键切换歌曲*/
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
				/*A键向后切歌曲*/
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
				/*B键向前切歌曲*/
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
		// 串口接收处理，1（STOP）,2(OK)
		if(USART3_RX_STA == 1){
			display_status = 0;
			USART3_RX_STA = 0;
		}else if(USART3_RX_STA == 2){
			USART3_RX_STA = 0;
		}
	}
}

