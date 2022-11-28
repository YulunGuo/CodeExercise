#ifndef __OLED_H
#define __OLED_H
#include "sys.h"
#include "i2c.h"



#define OLED_ADD 0x78
#define COM 0x00 // OLED指令（禁止修改），代表指令
#define DAT 0x40 // OLED指令（禁止修改），代表数据

void OLED_Init(void);
void OLED_DISPLAY_ON(void);
void OLED_DISPLAY_OFF(void);
void OLED_DISPLAY_LTF(u8 x); // 亮度显示
void OLED_DISPLAY_CLEAR(void);
void OLED_DISPLAY_8x16(u8 x,u8 y,u16 w); // 显示单个字符
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str); // 显示8x16的字符串


#endif