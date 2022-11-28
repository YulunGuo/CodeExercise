/*********************************************************************************************
ģ��������  ��������/���ҵ���
��������	USART���ڷ��ͳ���
��д�ˣ�	����	
��дʱ�䣺	2018��1��9��
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

#include "usart.h"
#include "led.h"
#include "buzzer.h"

int main (void){//������
	//��ʼ������
	RCC_Configuration(); //ʱ������
	LED_Init(); //LED��ʼ��
	BUZZER_Init(); //��������ʼ��
	USART1_Init(115200); //���ڳ�ʼ���������ǲ����ʣ�

	USART1_RX_STA = 0xC000; //��ʼ��ʱ��ʾ��ӭ��
	//��ѭ��
	while(1){
		// �ж����ݴ��Ƿ�������
		if(USART1_RX_STA & 0xC000){
			// �ж��Ƿ񵥶��Ļس�
			if((USART1_RX_STA & 0x3FFF) == 0){
				printf("�����ն˿��Ƴ���/r/n");
			}else if((USART1_RX_STA & 0x3FFF) == 2 && USART1_RX_BUF[0] == '1' && USART1_RX_BUF[1] == 'y'){
				// 1y = led1��
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
			}else if((USART1_RX_STA & 0x3FFF) == 2 && USART1_RX_BUF[0] == '1' && USART1_RX_BUF[1] == 'n'){
				// 1n = led1��
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
			}else if((USART1_RX_STA & 0x3FFF) == 2 && USART1_RX_BUF[0] == '2' && USART1_RX_BUF[1] == 'y'){
				// 2y = led2��
				GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));
			}else if((USART1_RX_STA & 0x3FFF) == 2 && USART1_RX_BUF[0] == '2' && USART1_RX_BUF[1] == 'n'){
				// 2n = led2��
				GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
			}else{
				printf("�������/r/n");
			}
			USART1_RX_STA = 0;
		}
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



