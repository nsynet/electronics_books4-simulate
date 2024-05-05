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

	// ʹ������ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;	// �����ַADC1�Ĺ������ݼĴ���
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&adcConvVal;		// �洢����ַ
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;					// ������������Ϊ�������Դ
	DMA_InitStruct.DMA_BufferSize = 100;							// ������Ŀ
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	// ʧ�������ַ����
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;			// ʹ�ܴ洢����ַ����
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// �������ݿ��Ϊ��
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// �洢�����ݿ��Ϊ��
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;								// ����ģʽΪ����ģʽ(һ�δ���)
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;						// ����Ȩ���
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;									// ʧ�ܴ洢�����洢������
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);									// ��ʼ��DMA1ͨ��1

	DMA_Cmd(DMA1_Channel1, ENABLE);												// DMA1ͨ��1ʹ��DMA����
}
void ADC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	// ʹ����Ӧ������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;					// �˿�����Ϊģ������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;			// PA4
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStruct) ;
  ADC_DeInit(ADC1);  
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);							// ����ADC��ʱ��ΪAPB2ʱ��6��Ƶ��72/6��

	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;				// ����ת��ģʽ
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;					    // ʹ��ɨ��ת��
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;				// ʹ������ת��ģʽ
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// ��ʹ���ⲿ����
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;			// �����Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;						// ����1��ת��ͨ��
	ADC_Init(ADC1, &ADC_InitStruct);							// ��ʼ��ADC1

	// ����ADC1ͨ��4��һ��ת����������Ϊ239.5
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);	

	ADC_Cmd(ADC1, ENABLE);										// ʹ��ADC1

	//ADC_ResetCalibration(ADC1);									// ����ADC1У׼
	//while(ADC_GetResetCalibrationStatus(ADC1));					// �ȴ�����У׼���
	ADC_StartCalibration(ADC1);									// ��ʼУ׼
	//while(ADC_GetCalibrationStatus(ADC1));						// �ȴ�У׼���

	ADC_DMACmd(ADC1, ENABLE);									// ʹ��ADC��DMA

	adcDmaConfig();												// ADC��DMA����

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);						// ADC1�������ת��
}

uint16_t ADC_GetVoltageVal(void)
{
	return adcSelChVal();
}

