#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define ADD1_DR_ADDRESS ((uint32_t)0X4001244C) //ADC1外设地址，查手册可得

#define ADC_PORT GPIOA
#define ADC_CH4 GPIO_Pin_4 //电压电位器
#define ADC_CH5 GPIO_Pin_5 //光敏电阻
#define ADC_CH6 GPIO_Pin_6 //摇杆X轴
#define ADC_CH7 GPIO_Pin_7 //摇杆Y轴

void ADC_DMA_Init(void);
void ADC_GPIO_Init(void);
void ADC_Config(void);


#endif