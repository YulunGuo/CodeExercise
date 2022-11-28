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
void OLED_DISPLAY_LTF(u8 x) // ������ʾ
{
	I2C_SAND_BYTE(OLED_ADD,COM,0x81);
	I2C_SAND_BYTE(OLED_ADD,COM,x);
}
void OLED_DISPLAY_CLEAR(void)
{
	for(u8 i=0xB0;i<0xB8;i++){
		I2C_SAND_BYTE(OLED_ADD,COM,i); // ����
		// 128��,���͵���ʼ�е�ַ
		I2C_SAND_BYTE(OLED_ADD,COM,0x10);
		I2C_SAND_BYTE(OLED_ADD,COM,0x00);
		for(u8 j=0;j<132;j++){
			//128���132��������оƬ��������132�У�����ʹ�õ���128��
			// Ҳ����д128
			I2C_SAND_BYTE(OLED_ADD,DAT,0x00);
		}
	}
}
void OLED_DISPLAY_8x16(u8 x,u8 y,u16 w) // ��ʾ�����ַ�
{
	// x : ҳ���꣨0-7����y:�����꣨0-128����w:��ʾ�ַ����
	u8 c = 0;
	y = y + 2; // ����OLED����оƬ��0x02��Ϊ����һ�У���Ҫƫ����
	for(u8 t=0;t<2;t++){
		// �����ַ�Ϊ8x16,���ѭ������
		I2C_SAND_BYTE(OLED_ADD,COM,0xB0+x);
		I2C_SAND_BYTE(OLED_ADD,COM,0x10+y/16); //��ʼ�е�ַ��λ
		I2C_SAND_BYTE(OLED_ADD,COM,0x00+y%16); //��ʼ�е�ַ��λ
		for(u8 i=0;i<8;i++){
			I2C_SAND_BYTE(OLED_ADD,DAT,ASCII_8x16[(w*16)+c-512]);
			c++;
		}
		x++;
	}
	
}
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str) // ��ʾ8x16���ַ���
{
	u8 r = 0;
	while(*str != '\0'){
		OLED_DISPLAY_8x16(row,r*8,*str++);
		r++;
	}
}