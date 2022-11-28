#ifndef __LM75A_H
#define __LM75A_H
#include "sys.h"
#include "i2c.h"

#define LM75A_ADD 0X9E

void LM75A_GetTemp(u8 *Tempbuffer); // 读取温度
void LM75A_POWERDOWN(void); // 掉电模式（低功耗省电）

#endif