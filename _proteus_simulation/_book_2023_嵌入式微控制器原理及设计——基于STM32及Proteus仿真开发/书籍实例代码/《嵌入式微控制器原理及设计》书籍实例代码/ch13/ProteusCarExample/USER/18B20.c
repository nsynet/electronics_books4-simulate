/********************************************************************************************************
*
* File                : 18B20.h
* Hardware Environment: Open103V
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : WaveShare
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include "18B20.h"
uint16_t    temp_aa;                 //温度值，16位，其中低4位为小数,定义成全局变量
uint8_t     temp_flag=0;          //温度正负符号,0为正数,1=负数
void convertDs18b20(void) 
{ 
    resetOnewire(); 
    wOnewire(0xcc); 
    wOnewire(0x44); 
}


u8* readID(void) 
{ 
	u8 ID[8],i,*p;
	resetOnewire(); 
	wOnewire(0x33);
	for(i=0;i<8;i++)
	{ID[i]=rOnewire();}
	p=ID;
	return p;
}


void readTemp(void) 
{ 
	u8 temp1,temp2;
	convertDs18b20();
	resetOnewire(); 
	wOnewire(0xcc); 
	wOnewire(0xbe); 	
	temp1=rOnewire(); 
	temp2=rOnewire(); 
	temp_aa = temp2<<8;
  temp_aa|= temp1;
  if (temp2>0x0f)
  { 
	  temp_flag=1;            //负温度符号
    temp_aa=-temp_aa;
  }
  else temp_flag=0;         //正温度
  temp_aa=temp_aa*0.625;          //温度值扩大10倍，精确到十进制数的 1位小数
	
}

