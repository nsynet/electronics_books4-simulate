/**************************************************************************************************
Title: 				main source program based on STM32F10 c
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
/***************************************************************************************************/
/*
@file	��Ƕ��ʽ΢������ԭ����ơ��鼮������:��ʢ�� Email:picy@scut.edu.cn  ���ӹ�ҵ�����磩����ʵ��13 STM32��׼��汾
*/

/*========================================Include Head===============================================
***************************************************************************************************/
#include "main.h"
#include "sys.h"
#include "delay.h" 
#include "ds18b20.h"
#include "adc.h"
#include "string.h"
#include "ultrasonic.h"
#include "pwm.h"
#include "velocity.h"
#include "OLED.h"
#include "time.h"

#include "OneWire.h"
#include "18B20.h"
#define     LED_PORT            GPIOC
extern uint8_t     temp_flag;  //�¶���������,0Ϊ����,1=����
extern uint16_t    temp_aa;       //�¶�ֵ��16λ�����е�4λΪС��,�����ȫ�ֱ���
uint8_t     ram[8];            //��ʾ������
u8 *p,id[8];
u16 ADC_val,DIS_val;//
u8  tem[12]={0};
extern uint32_t Buff_1;

uint8_t NixieTubeBit[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0xbf};
uint8_t     DisplayByte[10]={0};



/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC ,ENABLE); 						 
 				 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);

}


void chappross(u8 k,u8* tem1)//�ַ�����
{
	switch (k)							    
	{
		case 0:	 *tem1  = 7;  break;
	  case 1:	 *tem1 =  8;  break;
		case 2:	 *tem1 =  9;  break;
	  case 3:	 *tem1  = 10; break;
		case 4:	 *tem1  = 11; break;
		case 5:	 *tem1  = 12; break;
		case 6:	 *tem1  = 13; break;
		case 7:	 *tem1  = 14; break;
		case 8:	 *tem1  = 15; break;
		case 9:	 *tem1  = 16; break;		
		default: *tem1  = 7;  break;
	}
}



void  coposs_DS18B20(void)//�¶���ֵת��
{
	uint8_t i,k1,k2,k3,k4;
	
	if(temp_aa>99)
    ram[5]=temp_aa/100;
	else 
		ram[5]=0x10; //��ʮλ0
	ram[6]=temp_aa/10%10;
	ram[7]=temp_aa%10;
	if(temp_flag)
	{
		if(temp_aa>99)
		{
			ram[4]=0x11;
		}
		else ram[5]=0x11;
	}
	k1=ram[4];
	k2=ram[5];
	k3=ram[6];
	k4=ram[7];
	DisplayByte[0]=k1;
	DisplayByte[1]=k2;
	DisplayByte[2]=k3;
	DisplayByte[3]=k4;
	
	chappross(k1,&tem[0]);
	chappross(k2,&tem[1]);
	chappross(k3,&tem[2]);
	chappross(k4,&tem[3]);
}  


void  coposs_distance(u16 k)//
{
	u8 k1,k2,k3,k4;
	k=k*100;
	k4=(u8)(k%10);
	k3=(u8)(k/10%10);
	k2=(u8)(k/100%10);
	k1=(u8)(k/1000%10);
	chappross(k1,&tem[4]);
	chappross(k2,&tem[5]);
	chappross(k3,&tem[6]);
	chappross(k4,&tem[7]);
}


void  coposs_speed(u32 k )//������ֵת��
{
	u8 k1,k2,k3,k4;
	k4=k%10;
	k3=k/10%10;
	k2=k/100%10;
	k1=(u8)(k/1000%10);
	chappross(k1,&tem[8]);
	chappross(k2,&tem[9]);
	chappross(k3,&tem[10]);
	chappross(k4,&tem[11]);
}

/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t j)
* Description    : ������λ��GPIO_Pin_PositionΪҪ�����λ��PortVal��Ҫ����Ķ˿�ֵ
* EntryParameter :(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
* ReturnValue    : NO
**************************************************************************************/
void GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
{
	GPIO_SetBits(GPIOx, GPIO_Pin_Position & PortVal);
	GPIO_ResetBits(GPIOx, GPIO_Pin_Position &(~PortVal));	 
}

/**************************************************************************************
* FunctionName   : OSDelay()
* Description    : ��ʱ
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void OSDelay(uint32_t t)
{
  u8 i;
  while (t--)
	{
	    for (i=0; i<200; i++) ;
	}

}
/**************************************************************************************************
========================================Program Start===============================================
***************************************************************************************************/

/**************************************************************************************************
Function:   main
Description:������
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
int main(void)
{  
	  u8 i,k;
	  
    u8 str[]={0};
    delay_init(72);//��ʼ����ʱ  	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ����
	  LCD_Init();
    ADC_Configuration();
	  EXTIX_Init();//�ⲿ�жϳ�ʼ��
	  COMTIM_Configuration();////��ʱ����ʼ��1����ΪpWM���
	  TIM2_Configuration();//��ʱ����ʼ��2,�ٶȼ���
	  TIM3_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��������������
	   beep_Init();	
		
		Ultrasonic_Init();//��������ʼ��
		clrscr(0,8,0,128);
		COMTIM_SetPwm(10);
		Onewire_Enable_GPIO_Port();
	  p=readID();
	  while(1)
		{	
	    readTemp();		
			Draw_word(2,4,2,0,16);
			Draw_word(3,4,2,16,16);//
			coposs_DS18B20();	
			Draw_word(tem[0],4,2,32,16);//
			Draw_word(tem[1],4,2,40,16);//
			Draw_word(tem[2],4,2,48,16);//
			Draw_word(tem[3],4,2,56,16);//	
			
	    DIS_val = distance();
			
			Draw_word(5,7,2,0,16);//��ʾ����������
			Draw_word(6,7,2,16,16);//	
      coposs_distance(DIS_val);			
			Draw_word(tem[4],7,2,32,16);//
			Draw_word(tem[5],7,2,40,16);//
			Draw_word(tem[6],7,2,48,16);//	
      Draw_word(tem[7],7,2,56,16);//	
			
			ADC_val = ADC_GetVoltageVal();
			coposs_speed( Buff_1);
			Draw_word(4,10,2,0,16);//��ʾ��ǰ�ĳ���
			Draw_word(3,10,2,16,16);//	
			Draw_word(tem[8],10,2,32,16);//
			Draw_word(tem[9],10,2,40,16);//			
      Draw_word(tem[10],10,2,48,16);//	
			Draw_word(tem[11],10,2,56,16);//	
			
			COMTIM_SetPwm(ADC_val*255/4096);///���ڳ���
		}
}


/**************************************************************************************************
Function:   SysTick_Handler
Description:ϵͳʱ��:1ms�δ�1�� 
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void SysTick_Handler(void)  
{  

} 







/******************* (C)***Program End************�ļ�����*****************************************/
