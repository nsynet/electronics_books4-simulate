
/**************************************************************************************************
Title: 				sys source program based on STM32F10 c
Current 			version: v1.0
Function:			
processor: 	                
Clock:				8-72M  Hz
Author:			
Company:			
Contact:			
E-MAIL:				
Data:				  
***************************************************************************************************/ 

/**************************************************************************************************
========================================Include Head===============================================
***************************************************************************************************/
#include "sys.h"

/**************************************************************************************************
========================================Program Start===============================================
***************************************************************************************************/

/**************************************************************************************************
Function:   void NVIC_Configuration(void)
Description:设置所有的中断允许
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void NVIC_Configuration(void)
{

//    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	  NVIC_InitTypeDef NVIC_InitStructure;
//		/* Timer2 中断*/
//		#if 0
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//		#elif 0
//		/* Configure one bit for preemption priority */
//		/* Timer3 中断*/
//		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//		#elif 1
//		/* Timer4 中断*/
//		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//		#elif 0
//		
//		/*UART1*/
//		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//		#endif

} 
/*******************************************************************************
* Function Name : RCC_Configuration     复位时钟控制配置
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
	  uint8_t HSEStartUpStatus;
		/* system clocks configuration -----------------系统时钟配置-------------------*/
		/* RCC system reset(for debug purpose) */
		RCC_DeInit();                                    //将外设RCC寄存器重设为缺省值
		/* Enable HSE */
		RCC_HSEConfig(RCC_HSE_ON);                    //开启外部高速晶振（HSE）
		/* Wait till HSE is ready */ 
		HSEStartUpStatus = RCC_WaitForHSEStartUp();    //等待HSE起振
		if(HSEStartUpStatus == SUCCESS)               //若成功起振，（下面为系统总线时钟设置）
		{
		    /* Enable Prefetch Buffer */
		    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //使能FLASH预取指缓存
		    /* Flash 2 wait state */
		    FLASH_SetLatency(FLASH_Latency_2);   //设置FLASH存储器延时时钟周期数(根据不同的系统时钟选取不同的值)
		     /* HCLK = SYSCLK */
		    RCC_HCLKConfig(RCC_SYSCLK_Div1);   //设置AHB时钟=72 MHz
		    /* PCLK2 = HCLK/2 */
		    RCC_PCLK2Config(RCC_HCLK_Div2);   //设置APB1时钟=36 MHz(APB1时钟最大值)
		    /* PCLK1 = HCLK/2 */
		    RCC_PCLK1Config(RCC_HCLK_Div1);   //设置APB2时钟=72 MHz
		    /* Configure ADCCLK such as ADCCLK = PCLK2/2 */
		    RCC_ADCCLKConfig(RCC_PCLK2_Div2); //RCC_PCLK2_Div2,4,6,8
		    /* PLLCLK = 8MHz * 9 = 72 MHz */
		    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //PLL必须在其激活前完成配置（设置PLL时钟源及倍频系数）
		    /* Enable PLL */
		    RCC_PLLCmd(ENABLE);
		    /* Wait till PLL is ready */
		    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		    {
		    }
		    /* Select PLL as system clock source */
		    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		    /* Wait till PLL is used as system clock source */
		    while(RCC_GetSYSCLKSource() != 0x08)
		    {
		    }   
	   }
}
