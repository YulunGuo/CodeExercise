/* MY1690为MP3播放芯片 */
#ifndef __MY1690_H
#define __MY1690_H
#include "sys.h"
#include "usart.h"


void MY1690_STOP(void); // 音乐停止

void MY1690_Init(void);

void MY1690_PLAY(void);
void MY1690_PREV(void); //播放上一首
void MY1690_NEXT(void);
void MY1690_PAUSE(void);
void MY1690_VUP(void); //调高音量
void MY1690_VDOWM(void); //调低音量


void MY1690_CMD1(u8 a);
void MY1690_CMD2(u8 a,u8 b);
void MY1690_CMD3(u8 a,u16 b);

// 通信查询命令
u16 MY1690_CHECK(u8 a);

#endif