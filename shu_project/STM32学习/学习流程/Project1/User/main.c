/*********************************************************************************************
ģ��������  ��������/���ҵ���
��Ʒ��		
��������	
��дʱ�䣺	201������
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

�޸���־������
1-	
	
							
˵����
 # ��ģ�������STM32F103�ڲ���RCCʱ�����ã������������õδ�ʱ������ʱ������
 # �ɸ����Լ�����Ҫ���ӻ�ɾ����

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"

#include "led.h"
#include "key.h"
#include "flash.h"
#include "buzzer.h"


//#define add 0x0801f000

int main (void){//������	
	
//	u8 a;
//	u16 date;
	
	RCC_Configuration(); //ʱ������
	
	LED_Init(); //led��ʼ��
	KEY_Init(); // ������ʼ��
	BUZZER_Init(); // ��������ʼ��
	
	
//	date = FLASH_R(add);
//	
//	GPIO_Write(LEDPORT,date);
	
//	a = 0;
	
	while(1){
		
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadInputDataBit(KEYPORT,KEY1))); //������
		
		
//		// ������
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			delay_ms(20); // ��������
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadOutputDataBit(LEDPORT,LED1))); // �ı�LED״̬
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //�ȴ������ɿ�
//			}
//		}
		
//		// ������Ķϵ籣��
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			delay_ms(20);
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//				a++;
//				if(a > 3){
//					a = 0;
//				}
//				GPIO_Write(LEDPORT,a);
//				FLASH_W(add,a); // д��FLASH�У��ϵ籣��
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//			}
//		}


//// ����KEY1,����������
//	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//		delay_ms(20);
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			BUZZER_BEEP1();
//		}
//		while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//		BUZZER_BEEP2();
//	}

//// ����KEY1,����MIDI����
//	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//		delay_ms(20);
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
//			MIDI_PLAY();
//		}
//		while(!GPIO_ReadInputDataBit(KEYPORT,KEY1));
//	}

		
	}
}


/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
/*

���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��
*/

