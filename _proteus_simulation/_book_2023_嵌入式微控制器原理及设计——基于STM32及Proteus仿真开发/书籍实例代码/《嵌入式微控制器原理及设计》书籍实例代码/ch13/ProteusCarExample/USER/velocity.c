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
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA�˿�ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PC0 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB3
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);						 
}



void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                    //����һ��IO�����õĽṹ��
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    //PORTBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);           //�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //���ó���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOC, &GPIO_InitStructure);                  //��ʼ��GPIOC0����	
  
	
  /*����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���*/
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	  	      
 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			    //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure); 		
}

//void EXTI0_IRQHandler(void)
//{ 		 
//	//if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
//	EXTI_ClearITPendingBit(EXTI_Line0);          //���LINE1��·����λ
//	Count++;
//}


/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint8_t k,uint16_t j)
* Description    : GPIO���
* EntryParameter :
* ReturnValue    : 
**************************************************************************************/
void EXTI0_IRQHandler(void)
{ 
		Count++;
	  EXTI_ClearITPendingBit(EXTI0_IRQn); //���LINE15��·����λ
}





/**************************************************************************************************
Function:   void TIM2_Configuration(void)
Description:��ʱ��4��ʼ��
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
		/* ��������*/
		TIM_TimeBaseStructure.TIM_Period = 5000; //����ֵ
		TIM_TimeBaseStructure.TIM_Prescaler = 72-1; //Ԥ��Ƶ,��ֵ+1 Ϊ��Ƶ�ĳ���
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		/*ʹ��Ԥװ��*/
		TIM_ARRPreloadConfig(TIM2, ENABLE);
		/*Ԥ����������ж�λ*/
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		/* ���� TIM2 ��ʼ���� */
		
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //TIM4�ж�
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�0��
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //�����ȼ�3��
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQͨ����ʹ��
	 NVIC_Init(&NVIC_InitStructure);                             //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���					
	
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
        
				Timer_Count.MSec++;	         //��ʱ			
				if(Timer_Count.MSec>20)
				{
					 Timer_Count.MSec=0; 	
					 Buff_1=Count;
					 Count=0;
				}
		}
		//���ٲ���
}
