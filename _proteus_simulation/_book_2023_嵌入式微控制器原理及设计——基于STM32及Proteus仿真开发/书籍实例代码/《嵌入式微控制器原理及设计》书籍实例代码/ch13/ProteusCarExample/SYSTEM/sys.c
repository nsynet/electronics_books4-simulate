
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
Description:�������е��ж�����
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void NVIC_Configuration(void)
{

//    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	  NVIC_InitTypeDef NVIC_InitStructure;
//		/* Timer2 �ж�*/
//		#if 0
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//		#elif 0
//		/* Configure one bit for preemption priority */
//		/* Timer3 �ж�*/
//		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//		#elif 1
//		/* Timer4 �ж�*/
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
* Function Name : RCC_Configuration     ��λʱ�ӿ�������
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
	  uint8_t HSEStartUpStatus;
		/* system clocks configuration -----------------ϵͳʱ������-------------------*/
		/* RCC system reset(for debug purpose) */
		RCC_DeInit();                                    //������RCC�Ĵ�������Ϊȱʡֵ
		/* Enable HSE */
		RCC_HSEConfig(RCC_HSE_ON);                    //�����ⲿ���پ���HSE��
		/* Wait till HSE is ready */ 
		HSEStartUpStatus = RCC_WaitForHSEStartUp();    //�ȴ�HSE����
		if(HSEStartUpStatus == SUCCESS)               //���ɹ����񣬣�����Ϊϵͳ����ʱ�����ã�
		{
		    /* Enable Prefetch Buffer */
		    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //ʹ��FLASHԤȡָ����
		    /* Flash 2 wait state */
		    FLASH_SetLatency(FLASH_Latency_2);   //����FLASH�洢����ʱʱ��������(���ݲ�ͬ��ϵͳʱ��ѡȡ��ͬ��ֵ)
		     /* HCLK = SYSCLK */
		    RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHBʱ��=72 MHz
		    /* PCLK2 = HCLK/2 */
		    RCC_PCLK2Config(RCC_HCLK_Div2);   //����APB1ʱ��=36 MHz(APB1ʱ�����ֵ)
		    /* PCLK1 = HCLK/2 */
		    RCC_PCLK1Config(RCC_HCLK_Div1);   //����APB2ʱ��=72 MHz
		    /* Configure ADCCLK such as ADCCLK = PCLK2/2 */
		    RCC_ADCCLKConfig(RCC_PCLK2_Div2); //RCC_PCLK2_Div2,4,6,8
		    /* PLLCLK = 8MHz * 9 = 72 MHz */
		    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //PLL�������伤��ǰ������ã�����PLLʱ��Դ����Ƶϵ����
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
