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

extern vu16 ADC_DMA_IN[2];

int main(void){
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化
	// LED_Init();
	// KEY_Init();
	// BUZZER_Init();
	// USART1_Init(115200);
	USART3_Init(115200);
	RTC_Config();
	TOUCH_KEY_Init();
	// TM1640_Init(); //数码管初始化函数
	ENCOODER_Init();//旋转编码器初始化
	I2C_Configuration(); // I2C总线初始化
	OLED_Init();
	// RELAY_Init(); // 继电器初始化
	STEP_MOTOR_Init(); // 步进电机初始化
	ADC_Config();
	MY1690_Init(); // MP3初始化

	/*初始化页面*/
	OLED_DISPLAY_PIC();


	/* 变量 */
	// 页面
	u8 page_flag = 0; // 0:初始化页面；1:步进电机页面；2:MP3控制页面；3:环境检测界面
	u8 redisplay_flag = 0; // 重新加载页面标志位,防止重复刷新页面
	// 步进电机
	u8 step_motor_status = 0; // 步进电机状态: 0：关闭；1：右转；2：左转
	u8 step_motor_v = 0; // 步进电机速度（4 8）-> 0 1
	// 旋转编码器
	u8 encooder_status; // 1:右旋；2：左旋；3：按下 
	// 温度
	u8 temp[3];
	// MP3
	u8 volum = 0; // 音量等级，默认为0
	u8 display_num = 1; // 当前播放音乐，默认为第一首
	u16 music_num; // 音乐总数
	music_num = MY1690_CHECK(0x25);
	u8 display_status = 0; // 音乐播放状态，默认为暂停

	while(1){
		/*通过触摸按键A、B实现页面切换，包括初始化图片页面、步进电机控制页面、MP3控制页面以及环境检测界面*/
		/*按下A时实现页面左切换*/
		if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
			delay_ms(20);
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1)){
				if(page_flag == 0) page_flag = 4;
				page_flag--;
				redisplay_flag = 1;
				while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY1));
			}
		}
		/*按下B时实现页面右切换*/
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
				/*初始页面*/
				redisplay_flag = 0;
				OLED_DISPLAY_PIC();
				break;
			case 1:
				/*步进电机页面*/
				redisplay_flag = 0;
				OLED_DISPLAY_CLEAR();
				OLED_DISPLAY_8x16_BUFFER(0,"  <StepMotor>");
				OLED_DISPLAY_8x16_BUFFER(3,"->Status: "); // 电机状态（Left or right or stop）
				OLED_DISPLAY_8x16_BUFFER(6,"->Speed: "); // 电机速度（4 or 8）
				break;
			case 2:
				/*MP3控制页面*/
				redisplay_flag = 0;
				OLED_DISPLAY_CLEAR();
				OLED_DISPLAY_8x16_BUFFER(0,"  <Simple MP3>");
				OLED_DISPLAY_8x16_BUFFER(2,"->Status:");
				OLED_DISPLAY_8x16_BUFFER(4,"->Volumn:"); //音量等级0——30
				OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:"); // 当前播放曲目
				break;
			case 3:
				/*环境检测页面*/
				redisplay_flag = 0;
				OLED_DISPLAY_CLEAR();
				OLED_DISPLAY_8x16_BUFFER(0,"  <Environment>");
				OLED_DISPLAY_8x16_BUFFER(2,"->Time:"); // 时间
				OLED_DISPLAY_8x16_BUFFER(4,"->Temp:"); // 温度
				OLED_DISPLAY_8x16_BUFFER(6,"->Light:"); // 光照强度
				break;
			}	
		}

		/*不同页面状态参数更新*/
		switch (page_flag)
		{
		case 1:
			encooder_status = ENCOODER_READ(); // 旋转编码器状态
			/*步进电机页面*/
			/*通过旋转编码器控制步进电机关闭开启*/
			switch (encooder_status)
			{
			case 1:
				/* 右旋 */
				OLED_DISPLAY_8x16(0,15*8,'R');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				step_motor_status = 1;
				step_motor_v = 0;
				break;
			case 2:
				/* 左旋 */
				OLED_DISPLAY_8x16(0,15*8,'L');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				step_motor_status = 2;
				step_motor_v = 0;
				break;
			case 3:
				/* 按下 */
				OLED_DISPLAY_8x16(0,15*8,'D');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				step_motor_status = 0;
				break;
			default:
				break;
			}
			/*通过C键切换步进电机速度*/
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
				delay_ms(20);
				if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
					step_motor_v = 1 - step_motor_v;
					while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3));
				}
			}
			/*控制电机并显示状态到OLED屏幕上*/
			if(step_motor_status == 0){
				STEP_MOTOR_OFF();
				//状态
				OLED_DISPLAY_8x16(3,9*8,'S');
				OLED_DISPLAY_8x16(3,10*8,'T');
				OLED_DISPLAY_8x16(3,11*8,'O');
				OLED_DISPLAY_8x16(3,12*8,'P');
				OLED_DISPLAY_8x16(3,13*8,' ');
				//速度
				OLED_DISPLAY_8x16(6,8*8,'0');
			}else if(step_motor_status == 1){
				if(step_motor_v == 0){
						STEP_MOTOR_4R(4);
						//状态
						OLED_DISPLAY_8x16(3,9*8,'R');
						OLED_DISPLAY_8x16(3,10*8,'I');
						OLED_DISPLAY_8x16(3,11*8,'G');
						OLED_DISPLAY_8x16(3,12*8,'H');
						OLED_DISPLAY_8x16(3,13*8,'T');
						//速度
						OLED_DISPLAY_8x16(6,8*8,'4');
					}else{
						STEP_MOTOR_8R(4);
						//状态
						OLED_DISPLAY_8x16(3,9*8,'R');
						OLED_DISPLAY_8x16(3,10*8,'I');
						OLED_DISPLAY_8x16(3,11*8,'G');
						OLED_DISPLAY_8x16(3,12*8,'H');
						OLED_DISPLAY_8x16(3,13*8,'T');
						//速度
						OLED_DISPLAY_8x16(6,8*8,'8');	
					}
			}else if(step_motor_status == 2){
				if(step_motor_v == 0){
						STEP_MOTOR_4L(4);
						//状态
						OLED_DISPLAY_8x16(3,9*8,'L');
						OLED_DISPLAY_8x16(3,10*8,'E');
						OLED_DISPLAY_8x16(3,11*8,'F');
						OLED_DISPLAY_8x16(3,12*8,'T');
						OLED_DISPLAY_8x16(3,13*8,' ');
						//速度
						OLED_DISPLAY_8x16(6,8*8,'4');
					}else{
						STEP_MOTOR_8L(4);
						//状态
						OLED_DISPLAY_8x16(3,9*8,'L');
						OLED_DISPLAY_8x16(3,10*8,'E');
						OLED_DISPLAY_8x16(3,11*8,'F');
						OLED_DISPLAY_8x16(3,12*8,'T');
						OLED_DISPLAY_8x16(3,13*8,' ');
						//速度
						OLED_DISPLAY_8x16(6,8*8,'8');	
					}
			}
			break;
		case 2:
			/*MP3控制页面*/
			/*通过旋转编码器实现音量调节，右转增大，左转减小，按下播放/停止*/
			/*C/D键左右切歌*/
			encooder_status = ENCOODER_READ();
			/*音量调节*/
			switch (encooder_status)
			{
			case 1:
				// 降低音量 
				if(volum == 0) volum = 1;
				volum--;
				OLED_DISPLAY_8x16(0,15*8,'-');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				break;
			case 2:
				// 增大音量
				volum++;
				if(volum == 31) volum = 30;
				OLED_DISPLAY_8x16(0,15*8,'+');
				delay_ms(500);
				OLED_DISPLAY_8x16(0,15*8,' ');
				break;
			case 3:
				// 播放、停止
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
			/*扬声器控制*/
			// 设置音量
			MY1690_CMD2(0x31,volum);
			/*切换曲目*/
			if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
				delay_ms(20);
				if(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY3)){
					// 上一首
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
					// 下一首
					MY1690_NEXT();
					display_num++;
					if(display_num == music_num+1) display_num = music_num;
					OLED_DISPLAY_8x16_BUFFER(6,"    --NEXT--    ");
					delay_ms(500);
					OLED_DISPLAY_8x16_BUFFER(6,"->Music Num:");
					while(!GPIO_ReadInputDataBit(TOUCH_KEY_PORT,TOUCH_KEY4));
				}
			}
			/*OLED显示*/
			// 播放状态
			if(display_status == 0){
				// 暂停
				MY1690_PAUSE();
				OLED_DISPLAY_8x16(2,9*8,'S');
				OLED_DISPLAY_8x16(2,10*8,'T');
				OLED_DISPLAY_8x16(2,11*8,'O');
				OLED_DISPLAY_8x16(2,12*8,'P');
			}else{
				// 播放
				MY1690_PLAY();
				OLED_DISPLAY_8x16(2,9*8,'P');
				OLED_DISPLAY_8x16(2,10*8,'L');
				OLED_DISPLAY_8x16(2,11*8,'A');
				OLED_DISPLAY_8x16(2,12*8,'Y');
			}
			// 音量
			OLED_DISPLAY_8x16(4,9*8,volum/10+0x30);
			OLED_DISPLAY_8x16(4,10*8,volum%10+0x30);
			// 当前播放曲目
			OLED_DISPLAY_8x16(6,12*8,display_num/10+0x30);
			OLED_DISPLAY_8x16(6,13*8,display_num%10+0x30);
			break;

		case 3:
			/*环境检测页面*/
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

