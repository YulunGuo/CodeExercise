#include "oled.h"
#include "ASCII_8x16.h"

void OLED_Init(void)
{
	OLED_DISPLAY_OFF();
	OLED_DISPLAY_CLEAR();
	OLED_DISPLAY_ON();
}

void OLED_DISPLAY_ON(void)
{
	u8 buff[28] = {0xae,0x00,0x10,0xd5,0x80,0xa8,0x3f,0xd3,0x00,0XB0,0x40,0x8d,0x14,0xa1,0xc8,0xda,0x12,0x81,0xff,0xd9,0xf1,0xdb,0x30,0x20,0x00,0xa4,0xa6,0xaf};
	I2C_SAND_BUFFER(OLED_ADD,COM,buff,28);	
}

void OLED_DISPLAY_OFF(void)
{
	u8 buff[3] = {0xae,0x8d,0x10};
	I2C_SAND_BUFFER(OLED_ADD,COM,buff,3);
}
void OLED_DISPLAY_LTF(u8 x) // 亮度显示
{
	I2C_SAND_BYTE(OLED_ADD,COM,0x81);
	I2C_SAND_BYTE(OLED_ADD,COM,x);
}
void OLED_DISPLAY_CLEAR(void)
{
	for(u8 i=0xB0;i<0xB8;i++){
		I2C_SAND_BYTE(OLED_ADD,COM,i); // 组数
		// 128列,发送的起始列地址
		I2C_SAND_BYTE(OLED_ADD,COM,0x10);
		I2C_SAND_BYTE(OLED_ADD,COM,0x00);
		for(u8 j=0;j<132;j++){
			//128变成132，是由于芯片可以驱动132列，现在使用的是128列
			// 也可以写128
			I2C_SAND_BYTE(OLED_ADD,DAT,0x00);
		}
	}
}
void OLED_DISPLAY_8x16(u8 x,u8 y,u16 w) // 显示单个字符
{
	// x : 页坐标（0-7）；y:列坐标（0-128）；w:显示字符编号
	u8 c = 0;
	y = y + 2; // 由于OLED内置芯片从0x02作为最左一列，需要偏移量
	for(u8 t=0;t<2;t++){
		// 由于字符为8x16,因此循环两次
		I2C_SAND_BYTE(OLED_ADD,COM,0xB0+x);
		I2C_SAND_BYTE(OLED_ADD,COM,0x10+y/16); //起始列地址高位
		I2C_SAND_BYTE(OLED_ADD,COM,0x00+y%16); //起始列地址低位
		for(u8 i=0;i<8;i++){
			I2C_SAND_BYTE(OLED_ADD,DAT,ASCII_8x16[(w*16)+c-512]);
			c++;
		}
		x++;
	}
	
}
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str) // 显示8x16的字符串
{
	u8 r = 0;
	while(*str != '\0'){
		OLED_DISPLAY_8x16(row,r*8,*str++);
		r++;
	}
}