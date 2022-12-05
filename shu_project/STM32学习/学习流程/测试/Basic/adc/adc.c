#include "adc.h"

vu16 ADC_DMA_IN[2]; //外部通道ADC数值存放

void ADC_DMA_Init(void){
    DMA_InitTypeDef DMA_InitStruture;
    DMA_DeInit(DMA1_Channel1); //复位DMA通道1，即使用DMA通道1
    DMA_InitStruture.DMA_PeripheralBaseAddr = ADD1_DR_ADDRESS;
    DMA_InitStruture.DMA_MemoryBaseAddr = (u32)&ADC_DMA_IN;
    DMA_InitStruture.DMA_DIR = DMA_DIR_PeripheralSRC; //定义外设作为源地址
    DMA_InitStruture.DMA_BufferSize = 2; // 缓冲区大小（为ADC采集通道数）
    DMA_InitStruture.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 当前外设地址不变
    DMA_InitStruture.DMA_MemoryInc = DMA_MemoryInc_Enable; // 存储器地址不变，由于只存储一个数据，因此存储器地址不会偏移
    DMA_InitStruture.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 外设数据宽度为16位
    DMA_InitStruture.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内部存储数据为16位
    DMA_InitStruture.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStruture.DMA_Priority = DMA_Priority_High;
    DMA_InitStruture.DMA_M2M = DMA_M2M_Disable; //禁止DMA通道存储器到存储器进行传输
    DMA_Init(DMA1_Channel1,&DMA_InitStruture);
    DMA_Cmd(DMA1_Channel1,ENABLE); //使能DMA通道1
}
void ADC_GPIO_Init(void){
    GPIO_InitTypeDef GPIO_InitStruture;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    GPIO_InitStruture.GPIO_Pin = ADC_CH4 | ADC_CH5;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(ADC_PORT,&GPIO_InitStruture);
}
void ADC_Config(void){
    ADC_InitTypeDef ADC_InitStruture;
    ADC_GPIO_Init();
    ADC_DMA_Init();
    ADC_InitStruture.ADC_Mode = ADC_Mode_Independent; //ADC1 ADC2工作在独立模式
    ADC_InitStruture.ADC_ContinuousConvMode = ENABLE; //ADC工作在连续扫描模式
    ADC_InitStruture.ADC_ScanConvMode = ENABLE; // 使能扫描
    ADC_InitStruture.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件控制转换
    ADC_InitStruture.ADC_DataAlign = ADC_DataAlign_Right; // 数据右对齐
    ADC_InitStruture.ADC_NbrOfChannel = 2; // 顺序进行转换的通道数
    ADC_Init(ADC1,&ADC_InitStruture);
    // 设置指定ADC规则组通道，设置采样顺序与采样时间
    ADC_RegularChannelConfig(ADC1,ADC_Channel_4,1,ADC_SampleTime_28Cycles5); // 光敏电阻
    ADC_RegularChannelConfig(ADC1,ADC_Channel_5,2,ADC_SampleTime_28Cycles5); // 电压调节
    // 开启ADC1 DMA
    ADC_DMACmd(ADC1,ENABLE);
    // 使能ADC1
    ADC_Cmd(ADC1,ENABLE);
    // 重置ADC校准寄存器
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)); // 等待重置完成
    // 开始ADC重置
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    // 使能ADC1软件开始转换,将通道中模拟量转换成数据
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}