#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void COMTIM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);         //���ö�ʱ��1ʱ��ʹ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);       //ʹ��GPIO����ʱ��ʹ��
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;                    //TIM_CH1�����ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //����Ϊ��Ӧ�ٶ�Ϊ50M
	GPIO_Init(GPIOA, &GPIO_InitStructure);                       //��ʼ���������

	TIM_TimeBaseStructure.TIM_Period = 256;                      //�Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =7200-1;                      //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                 //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;            //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 100;                           //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);                     //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
  TIM_CtrlPWMOutputs(TIM1,ENABLE);	                           //MOE �����ʹ��	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);            //CH1Ԥװ��ʹ��	 
	TIM_ARRPreloadConfig(TIM1, ENABLE);                          //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM1, ENABLE);                                       //ʹ��TIM1 
	
	
	
	
	
	
//////	GPIO_InitTypeDef GPIO_InitStruct;
//////	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//////	TIM_OCInitTypeDef TIM_OCInitStruct;

//////	// ʹ����Ӧ�����ʱ��
//////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
//////	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//////	
//////	// ������ӳ������
//////	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
//////	// ��ʼ����Ӧ������
//////	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;		// �����������
//////	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 ;
//////	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//////	GPIO_Init(GPIOB, &GPIO_InitStruct);
//////	
//////	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;		// �����������
//////	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 ;
//////	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//////	GPIO_Init(GPIOB, &GPIO_InitStruct);
//////	
//////	// ��ʼ����Ӧ�Ķ�ʱ��
//////	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
//////	TIM_TimeBaseInitStruct.TIM_Period = 255;							// ����ֵ255
//////	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;				// Ԥ��Ƶֵ7200
//////	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct) ;

//////	// ����Ƚ���صĲ���
//////	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;						// PWM1ģʽ
//////	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;				// ��������Ϊ��
//////	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;			// ʹ�ܶ�ʱ�����״̬s
//////	TIM_OCInitStruct.TIM_Pulse = 120;										// ����Ƚ�ֵ��ʼΪ0
//////	TIM_OC3Init(TIM3, &TIM_OCInitStruct);
//////	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);					// ʹ��ͨ��1��Ԥװ�ؼĴ���
//////	
//////	TIM_OCInitStruct.TIM_Pulse = 120;										// ����Ƚ�ֵ��ʼΪ0
//////	TIM_OC4Init(TIM3, &TIM_OCInitStruct);
//////	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);					// ʹ��ͨ��1��Ԥװ�ؼĴ���

//////	// ʹ����װ�ؼĴ���
//////	TIM_ARRPreloadConfig(TIM3, ENABLE);									// ʹ���Զ���װ�ؼĴ���
//////	TIM_Cmd(TIM3, ENABLE);												// ʹ�ܶ�ʱ��3
}

void COMTIM_SetPwm(uint8_t pwmVal)
{
	

  /* Check the parameters */
  assert_param(IS_TIM_LIST8_PERIPH(TIM1));
  /* Set the Capture Compare1 Register value */
  TIM1->CCR1 =  pwmVal;

////	TIM_SetCompare3(TIM3, pwmVal);
////	TIM_SetCompare4(TIM3, pwmVal);
}

