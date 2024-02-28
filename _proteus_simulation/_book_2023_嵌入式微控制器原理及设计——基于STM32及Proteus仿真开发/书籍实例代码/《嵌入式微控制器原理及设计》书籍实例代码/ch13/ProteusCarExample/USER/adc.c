#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "adc.h"
volatile uint16_t adcConvVal[50];

static uint16_t adcSelChVal(void)
{
	uint8_t i;
	uint32_t sum = 0;

	for (i=0; i<50; i++)
	{
		sum += adcConvVal[i];
	}

	return (uint16_t)(sum/50);
}

static void adcDmaConfig(void)
{
	DMA_InitTypeDef DMA_InitStruct;

	// 使能外设时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;	// 外设基址ADC1的规则数据寄存器
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&adcConvVal;		// 存储器基址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;					// 将外设数据作为传输的来源
	DMA_InitStruct.DMA_BufferSize = 100;							// 传输数目
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// 失能外设基址增量
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;			// 使能存储器基址增量
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// 外设数据宽度为字
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// 存储器数据宽度为字
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;								// 传输模式为正常模式(一次传输)
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;						// 优先权最高
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;									// 失能存储器到存储器传输
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);									// 初始化DMA1通道1

	DMA_Cmd(DMA1_Channel1, ENABLE);												// DMA1通道1使能DMA传输
}
void ADC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	// 使能相应的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;					// 端口配置为模拟输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;			// PA4
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStruct) ;
  ADC_DeInit(ADC1);  
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);							// 配置ADC的时钟为APB2时钟6分频（72/6）

	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;				// 独立转换模式
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;					    // 使能扫描转换
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;				// 使能连续转换模式
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 不使用外部触发
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;			// 数据右对其
	ADC_InitStruct.ADC_NbrOfChannel = 1;						// 配置1个转换通道
	ADC_Init(ADC1, &ADC_InitStruct);							// 初始化ADC1

	// 配置ADC1通道4第一个转换采样周期为239.5
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);	

	ADC_Cmd(ADC1, ENABLE);										// 使能ADC1

	//ADC_ResetCalibration(ADC1);									// 重置ADC1校准
	//while(ADC_GetResetCalibrationStatus(ADC1));					// 等待重置校准完成
	ADC_StartCalibration(ADC1);									// 开始校准
	//while(ADC_GetCalibrationStatus(ADC1));						// 等待校准完成

	ADC_DMACmd(ADC1, ENABLE);									// 使能ADC的DMA

	adcDmaConfig();												// ADC的DMA配置

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);						// ADC1软件触发转换
}

uint16_t ADC_GetVoltageVal(void)
{
	return adcSelChVal();
}

