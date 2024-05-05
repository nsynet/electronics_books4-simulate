#include "ultrasonic.h"
#include "delay.h"
#include "time.h"
#include "stm32f10x.h"
u32 temp5=0; 
float UltrasonicWave_Distance=0;//计算出的距离
extern u8  TIM3CH1_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM3CH1_CAPTURE_VAL;//输入捕获值


void beep_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //PB2 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB2
	 GPIO_ResetBits(GPIOB,GPIO_Pin_2);						 
		
}

void Ultrasonic_Init(void)
{
   
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PA.5 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.5
	 GPIO_ResetBits(GPIOA,GPIO_Pin_5);						 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //PA.6端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.6	
	 beep_Init();
}

u16 distance(void)
{	
		u16 i=0;
		u16 Buff; 		
/*---------------测距模块-------------------*/	
		GPIO_SetBits(GPIOA,GPIO_Pin_5); //置1
		delay_us(20);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5); //清0
 		if(TIM3CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升
		{
			temp5=TIM3CH1_CAPTURE_STA&0X3F;
			temp5*=65536;//溢出时间总和
			temp5+=TIM3CH1_CAPTURE_VAL;//得到总的高电平时间
			
			UltrasonicWave_Distance=(float)temp5*170/10000;//距离计算公式：距离=高电平持续时间*声速/2   
														  //即 距离= 高电平持续时间*340*100/（2*1000 000） = 高电平持续时间*170/10000			
			//printf("Distance:%f cm\r\n",UltrasonicWave_Distance);//打印总的高点平时间
			TIM3CH1_CAPTURE_STA=0;//开启下一次捕获
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
