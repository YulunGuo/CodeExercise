#include "lm75a.h"

//����LM75A���¶�ֵ��-55--125���϶ȣ�
//�¶������ţ�0��1�������¶��������¶�С�������λ���η���*Tempbuffer��ʮ���ƣ�
void LM75A_GetTemp(u8 *Tempbuffer) // ��ȡ�¶�
{
	u8 buf[2]; //2���ֽڣ�����¶�
	I2C_READ_BUFFER(LM75A_ADD,0x00,buf,2);
	u8 t = 0;
	u8 a = 0;
	t = buf[0]; //�����¶���������,0-125��
	*Tempbuffer = 0; //�¶�Ϊ��
	if(t & 0x80){
		// �ж��¶��Ƿ�Ϊ����
		*Tempbuffer = 1;//����
		// ���㲹�루������һ��
		t = ~t;
		t++;
	}
	// ��λ�����¶�
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
	t = buf[1]; //����С�����֣�ȡ0.125����ǰ��λ��12��25��37����������
	if(t & 0x20) a = a + 12;
	if(t & 0x40) a = a + 25;	
	if(t & 0x80) a = a + 50;
	Tempbuffer++;
	*Tempbuffer = a;
}

// LM75�������ģʽ���ٴε���LM75A_GetTemp()��������������
//����ֻ�ڵ͹��������ʹ��
void LM75A_POWERDOWN(void) // ����ģʽ���͹���ʡ�磩
{
	I2C_SAND_BYTE(LM75A_ADD,0x01,1); //�������üĴ������ض�LM75A
}