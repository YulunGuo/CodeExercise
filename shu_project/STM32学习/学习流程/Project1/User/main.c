/*********************************************************************************************
模板制作：  杜洋工作室/洋桃电子
出品：		
程序名：	
编写时间：	201年月日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

修改日志：　　
1-	
	
							
说明：
 # 本模板加载了STM32F103内部的RCC时钟设置，并加入了利用滴答定时器的延时函数。
 # 可根据自己的需要增加或删减。

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"

#include "led.h"
#include "key.h"
#include "flash.h"
#include "buzzer.h"


//#define add 0x0801f000

int main (void){//主程序	
	
//	u8 a;
//	u16 date;
	
	RCC_Configuration(); //时钟设置
	
	LED_Init(); //led初始化
	KEY_Init(); // 按键初始化
	BUZZER_Init(); // 蜂鸣器初始化
	
	
//	date = FLASH_R(add);
//	
//	GPIO_Write(LEDPORT,date);
	
//	a = 0;
	
	while(1){
		
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadInputDataBit(KEYPORT,KEY1))); //无锁存
		
		
//		// 带锁存
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			delay_ms(20); // 按键消抖
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1))); // 改变LED状态
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //等待按键松开
//			}
//		}
		
//		// 带锁存的断电保护
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			delay_ms(20);
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//				a++;
//				if(a > 3){
//					a = 0;
//				}
//				GPIO_Write(LEDPORT,a);
//				FLASH_W(add,a); // 写入FLASH中，断电保护
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//			}
//		}


//// 按动KEY1,蜂鸣器发声
//	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//		delay_ms(20);
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			BUZZER_BEEP1();
//		}
//		while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//		BUZZER_BEEP2();
//	}

//// 按动KEY1,播放MIDI音乐
//	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//		delay_ms(20);
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			MIDI_PLAY();
//		}
//		while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//	}

		
	}
}


/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒
*/

