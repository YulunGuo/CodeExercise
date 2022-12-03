#include "my1690.h"


void MY1690_Init(void)
{
    USART3_Init(9600);
    MY1690_STOP();
}

void MY1690_PLAY(void)
{
    USART3_printf("\x7e\x03\x11\x12\xef");
}
void MY1690_PREV(void) //播放上一首
{
    USART3_printf("\x7e\x03\x14\x17\xef");
}
void MY1690_NEXT(void)
{
    USART3_printf("\x7e\x03\x13\x10\xef");
}
void MY1690_PAUSE(void)
{
    USART3_printf("\x7e\x03\x12\x11\xef");
}
void MY1690_VUP(void) //调高音量
{
    USART3_printf("\x7e\x03\x15\x16\xef");
}
void MY1690_VDOWM(void) //调低音量
{
    USART3_printf("\x7e\x03\x16\x15\xef");
}
void MY1690_STOP(void) // 音乐停止
{
    USART3_printf("\x7e\x03\x1e\x1d\xef");    
}

// 全部指令输入
void MY1690_CMD1(u8 a)
{
    // 无参数的指令发送 a操作码
    u8 i;
    i = 3^a; // 由于无参数指令为7E+03+操作码+校验码+EF，这里是校验码（异或得到）
    USART_SendData(USART3,0x7e); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0x03); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,a); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,i); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0xef); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
}
void MY1690_CMD2(u8 a,u8 b)
{
    // 8位HEX参数的指令发送 a为操作码，b为8位的参数
    u8 i;
    i = 4^a; 
    i = i^b;// 由于无参数指令为7E+04+操作码+参数+校验码+EF，这里是校验码（异或得到）
    USART_SendData(USART3,0x7e); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0x04); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,a); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,b); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,i); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0xef); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);    
}
void MY1690_CMD3(u8 a,u16 b)
{
    // 8位HEX参数的指令发送 a为操作码，b为8位的参数
    u8 i,h_8,d_8;
    h_8 = b/0x100; //高8位
    d_8 = b%100;
    i = 5^a;
    i = i^h_8;
    i = i^d_8;
    USART_SendData(USART3,0x7e); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0x05); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,a); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,h_8); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,d_8); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,i); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0xef); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET); 
}

// 通信查询指令
u16 MY1690_CHECK(u8 a)
{
    // 无参数的指令发送 a操作码
    u8 i;
    i = 3^a; // 由于无参数指令为7E+03+操作码+校验码+EF，这里是校验码（异或得到）
    USART_SendData(USART3,0x7e); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0x03); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,a); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,i); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3,0xef); while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
}