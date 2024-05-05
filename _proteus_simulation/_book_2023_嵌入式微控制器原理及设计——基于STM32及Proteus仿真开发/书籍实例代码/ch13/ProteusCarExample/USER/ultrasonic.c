#include "ultrasonic.h"
#include "delay.h"
#include "time.h"
#include "stm32f10x.h"
u32 temp5=0; 
float UltrasonicWave_Distance=0;//������ľ���
extern u8  TIM3CH1_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM3CH1_CAPTURE_VAL;//���벶��ֵ


void beep_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //PB2 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB2
	 GPIO_ResetBits(GPIOB,GPIO_Pin_2);						 
		
}

void Ultrasonic_Init(void)
{
   
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PA.5 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.5
	 GPIO_ResetBits(GPIOA,GPIO_Pin_5);						 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //PA.6�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.6	
	 beep_Init();
}

u16 distance(void)
{	
		u16 i=0;
		u16 Buff; 		
/*---------------���ģ��-------------------*/	
		GPIO_SetBits(GPIOA,GPIO_Pin_5); //��1
		delay_us(20);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5); //��0
 		if(TIM3CH1_CAPTURE_STA&0X80)//�ɹ�������һ������
		{
			temp5=TIM3CH1_CAPTURE_STA&0X3F;
			temp5*=65536;//���ʱ���ܺ�
			temp5+=TIM3CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			
			UltrasonicWave_Distance=(float)temp5*170/10000;//������㹫ʽ������=�ߵ�ƽ����ʱ��*����/2   
														  //�� ����= �ߵ�ƽ����ʱ��*340*100/��2*1000 000�� = �ߵ�ƽ����ʱ��*170/10000			
			//printf("Distance:%f cm\r\n",UltrasonicWave_Distance);//��ӡ�ܵĸߵ�ƽʱ��
			TIM3CH1_CAPTURE_STA=0;//������һ�β���
		  Buff=(u16)UltrasonicWave_Distance;
		}	
		if(Buff<=10)
		{
				GPIO_SetBits(GPIOB,GPIO_Pin_2);
			  delay_us(20);
				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		    delay_us(20);
				GPIO_SetBits(GPIOB,GPIO_Pin_2);
			  delay_us(20);
				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		    delay_us(20);
				GPIO_SetBits(GPIOB,GPIO_Pin_2);
			  delay_us(20);
				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		    delay_us(20);
				GPIO_SetBits(GPIOB,GPIO_Pin_2);
			  delay_us(20);
				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		    delay_us(20);
		}
		delay_ms(10);
		return Buff;
}
