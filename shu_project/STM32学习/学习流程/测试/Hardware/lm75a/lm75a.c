#include "lm75a.h"

//读出LM75A的温度值（-55--125摄氏度）
//温度正负号（0正1负），温度整数，温度小数点后两位依次放入*Tempbuffer（十进制）
void LM75A_GetTemp(u8 *Tempbuffer) // 读取温度
{
	u8 buf[2]; //2个字节，存放温度
	I2C_READ_BUFFER(LM75A_ADD,0x00,buf,2);
	u8 t = 0;
	u8 a = 0;
	t = buf[0]; //处理温度整数部分,0-125度
	*Tempbuffer = 0; //温度为正
	if(t & 0x80){
		// 判断温度是否为负数
		*Tempbuffer = 1;//负数
		// 计算补码（反码后加一）
		t = ~t;
		t++;
	}
	// 按位计算温度
	if(t & 0x01) a = a + 1;
	if(t & 0x02) a = a + 2;
	if(t & 0x04) a = a + 4;
	if(t & 0x08) a = a + 8;
	if(t & 0x10) a = a + 16;
	if(t & 0x20) a = a + 32;
	if(t & 0x40) a = a + 64;
	Tempbuffer++;
	*Tempbuffer = a;
	a = 0;
	t = buf[1]; //处理小数部分，取0.125精度前两位（12、25、37、、、、）
	if(t & 0x20) a = a + 12;
	if(t & 0x40) a = a + 25;	
	if(t & 0x80) a = a + 50;
	Tempbuffer++;
	*Tempbuffer = a;
}

// LM75进入掉电模式，再次调用LM75A_GetTemp()，即可正常工作
//建议只在低功耗情况下使用
void LM75A_POWERDOWN(void) // 掉电模式（低功耗省电）
{
	I2C_SAND_BYTE(LM75A_ADD,0x01,1); //操作配置寄存器，关断LM75A
}