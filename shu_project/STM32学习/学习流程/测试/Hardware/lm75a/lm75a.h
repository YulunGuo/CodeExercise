#ifndef __LM75A_H
#define __LM75A_H
#include "sys.h"
#include "i2c.h"

#define LM75A_ADD 0X9E

void LM75A_GetTemp(u8 *Tempbuffer); // ��ȡ�¶�
void LM75A_POWERDOWN(void); // ����ģʽ���͹���ʡ�磩

#endif