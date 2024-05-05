#include "velocity.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
static   uint32_t Count=0;
uint32_t Buff_1;
struct Timer_  Timer_Count;

void velocity_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA端口时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //外部中断，需要使能AFIO时钟
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PC0 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB3
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);						 
}



void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                    //定义一个IO口配置的结构体
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    //PORTB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);           //外部中断，需要使能AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //设置成上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 	GPIO_Init(GPIOC, &GPIO_InitStructure);                  //初始化GPIOC0配置	
  
	
  /*根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器*/
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	  	      
 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			    //使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 		
}

//void EXTI0_IRQHandler(void)
//{ 		 
//	//if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
//	EXTI_ClearITPendingBit(EXTI_Line0);          //清除LINE1线路挂起位
//	Count++;
//}


/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint8_t k,uint16_t j)
* Description    : GPIO输出
* EntryParameter :
* ReturnValue    : 
**************************************************************************************/
void EXTI0_IRQHandler(void)
{ 
		Count++;
	  EXTI_ClearITPendingBit(EXTI0_IRQn); //清除LINE15线路挂起位
}





/**************************************************************************************************
Function:   void TIM2_Configuration(void)
Description:定时器4初始化
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void TIM2_Configuration(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
		/* TIM2 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		/* 基础设置*/
		TIM_TimeBaseStructure.TIM_Period = 5000; //计满值
		TIM_TimeBaseStructure.TIM_Prescaler = 72-1; //预分频,此值+1 为分频的除数
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		/*使能预装载*/
		TIM_ARRPreloadConfig(TIM2, ENABLE);
		/*预先清除所有中断位*/
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		/* 允许 TIM2 开始计数 */
		
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //TIM4中断
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //先占优先级0级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //从优先级3级
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ通道被使能
	 NVIC_Init(&NVIC_InitStructure);                             //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器					
	
	 TIM_Cmd(TIM2, ENABLE);
}






/*******************************************************************************
* Function Name : TIM4_IRQHandler
* Description : This function handles TIM4 global interrupt request.
* Input : None
* Output : None
* Return : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        
				Timer_Count.MSec++;	         //计时			
				if(Timer_Count.MSec>20)
				{
					 Timer_Count.MSec=0; 	
					 Buff_1=Count;
					 Count=0;
				}
		}
		//测速部分
}
