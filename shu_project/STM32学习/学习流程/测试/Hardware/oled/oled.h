#ifndef __OLED_H
#define __OLED_H
#include "sys.h"
#include "i2c.h"



#define OLED_ADD 0x78
#define COM 0x00 // OLEDָ���ֹ�޸ģ�������ָ��
#define DAT 0x40 // OLEDָ���ֹ�޸ģ�����������

void OLED_Init(void);
void OLED_DISPLAY_ON(void);
void OLED_DISPLAY_OFF(void);
void OLED_DISPLAY_LTF(u8 x); // ������ʾ
void OLED_DISPLAY_CLEAR(void);
void OLED_DISPLAY_8x16(u8 x,u8 y,u16 w); // ��ʾ�����ַ�
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str); // ��ʾ8x16���ַ���


#endif