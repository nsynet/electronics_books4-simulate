#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void COMTIM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);         //设置定时器1时钟使能
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);       //使能GPIO外设时钟使能
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;                    //TIM_CH1，设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //设置为响应速度为50M
	GPIO_Init(GPIOA, &GPIO_InitStructure);                       //初始化该输出口

	TIM_TimeBaseStructure.TIM_Period = 256;                      //自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =7200-1;                      //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                 //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;            //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 100;                           //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);                     //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
  TIM_CtrlPWMOutputs(TIM1,ENABLE);	                           //MOE 主输出使能	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);            //CH1预装载使能	 
	TIM_ARRPreloadConfig(TIM1, ENABLE);                          //使能TIMx在ARR上的预装载寄存器
	TIM_Cmd(TIM1, ENABLE);                                       //使能TIM1 
	
	
	
	
	
	
//////	GPIO_InitTypeDef GPIO_InitStruct;
//////	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//////	TIM_OCInitTypeDef TIM_OCInitStruct;

//////	// 使能相应外设的时钟
//////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
//////	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//////	
//////	// 引脚重映射配置
//////	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
//////	// 初始化相应的引脚
//////	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;		// 复用推挽输出
//////	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 ;
//////	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//////	GPIO_Init(GPIOB, &GPIO_InitStruct);
//////	
//////	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;		// 复用推挽输出
//////	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 ;
//////	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//////	GPIO_Init(GPIOB, &GPIO_InitStruct);
//////	
//////	// 初始化相应的定时器
//////	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
//////	TIM_TimeBaseInitStruct.TIM_Period = 255;							// 计数值255
//////	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;				// 预分频值7200
//////	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct) ;

//////	// 输出比较相关的参数
//////	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;						// PWM1模式
//////	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;				// 极性配置为高
//////	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;			// 使能定时器输出状态s
//////	TIM_OCInitStruct.TIM_Pulse = 120;										// 输出比较值初始为0
//////	TIM_OC3Init(TIM3, &TIM_OCInitStruct);
//////	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);					// 使能通道1的预装载寄存器
//////	
//////	TIM_OCInitStruct.TIM_Pulse = 120;										// 输出比较值初始为0
//////	TIM_OC4Init(TIM3, &TIM_OCInitStruct);
//////	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);					// 使能通道1的预装载寄存器

//////	// 使能重装载寄存器
//////	TIM_ARRPreloadConfig(TIM3, ENABLE);									// 使能自动重装载寄存器
//////	TIM_Cmd(TIM3, ENABLE);												// 使能定时器3
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

