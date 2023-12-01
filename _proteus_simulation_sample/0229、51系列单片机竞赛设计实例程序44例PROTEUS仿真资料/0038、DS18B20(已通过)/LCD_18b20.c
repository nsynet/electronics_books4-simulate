#include <at89x51.h>//��AT89C51ʱ�������ͷ�ļ�
//#include <reg52.h>//�û���W78E58Bʱ���������ͷ�ļ�
#include <absacc.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <DS18B20.h>
#include "LCD1602.h"			////Һ����ʾͷ�ļ�
//sbit DQ = P3^4;					//����DQ����ΪP3.4
unsigned char t[2],*pt;				//��������¶�ֵ,���³������ͨ�����������������ͨ�ŵ�
unsigned char  TempBuffer1[9]={0x2b,0x31,0x32,0x32,0x2e,0x30,0x30,0x43,'\0'};
								//��ʾʵʱ�¶�,�ϵ�ʱ��ʾ+125.00C
unsigned char  TempBuffer0[17]={0x54,0x48,0x3a,0x2b,0x31,0x32,0x35,0x20,
								0x54,0x4c,0x3a,0x2b,0x31,0x32,0x34,0x43,'\0'};
								//��ʾ�¶�������,�ϵ�ʱ��ʾTH:+125 TL:+124C							
unsigned char code dotcode[4]={0,25,50,75};
/***����ʾ�ֱ���Ϊ0.25,��С������Ƚ��鷳,�ʲ��ò��ķ���*******
�ٽ���ֵ�����ʮλ�͸�λ���͵�ʮ��λ�Ͱٷ�λ********************/


void covert0( unsigned char TH, unsigned char TL)	//���¶�������ת��ΪLCD��ʾ������
{ 
   if(TH>0x7F)                    //�ж�����,���Ϊ����,����ת��Ϊ�����ֵ
   {
    TempBuffer0[3]=0x2d;	     //0x2dΪ"-"��ASCII��
	TH=~TH;
	TH++;
   }
   else TempBuffer0[3]=0x2b;	//0x2BΪ"+"��ASCII��

   if(TL>0x7f)
   {
   TempBuffer0[11]=0x2d;	     //0x2dΪ"-"��ASCII��
   TL=~TL+1;
   }
   else TempBuffer0[11]=0x2b;	//0x2BΪ"+"��ASCII��

  TempBuffer0[4]=TH/100+0x30;		             //�����TH�İ�ʮ��λ
  if( TempBuffer0[4]==0x30) TempBuffer0[4]=0xfe; //��λ������
  TempBuffer0[5]=(TH%100)/10+0x30;				//�����ʮλ
  TempBuffer0[6]=(TH%100)%10+0x30;	 			//�������λ
  TempBuffer0[12]=TL/100+0x30;		             //�����TL�İ�ʮ��λ
  if( TempBuffer0[12]==0x30) TempBuffer0[12]=0xfe; //��λ������
  TempBuffer0[13]=(TL%100)/10+0x30;				//�����ʮλ
  TempBuffer0[14]=(TL%100)%10+0x30;	 			//�������λ
}


void covert1(void)	//���¶�ת��ΪLCD��ʾ������
{
   unsigned char x=0x00,y=0x00;
   t[0]=*pt;
   pt++;
   t[1]=*pt;
   if(t[1]>0x07)                    //�ж������¶�
   {
    TempBuffer1[0]=0x2d;	     //0x2dΪ"-"��ASCII��
	t[1]=~t[1];			 /*���漸��Ѹ����Ĳ���*/
	t[0]=~t[0]; 		 /* ����ɾ���ֵ*********/
	x=t[0]+1;				 /***********************/
	t[0]=x;					 /***********************/
	if(x>255)                /**********************/
	t[1]++;				 /*********************/
   }
   else TempBuffer1[0]=0x2b;	//0xfeΪ��"+"��ASCII��
  t[1]<<=4;		//�����ֽ�����4λ
  t[1]=t[1]&0x70;		//ȡ�����ֽڵ�3����Ч����λ
  x=t[0];					//��t[0]�ݴ浽X,��ΪȡС�����ֻ�Ҫ�õ���
  x>>=4;					//����4λ
  x=x&0x0f;					//��ǰ���������ȡ��t[0]�ĸ���λ	
  t[1]=t[1]|x;			//���ߵ��ֽڵ���Чֵ����������ƴ��һ���ֽ�
  TempBuffer1[1]=t[1]/100+0x30;		             //+0x30 Ϊ�� 0~9 ASCII��
   if( TempBuffer1[1]==0x30) TempBuffer1[1]=0xfe; //��λ������
  TempBuffer1[2]=(t[1]%100)/10+0x30;				//�����ʮλ
  TempBuffer1[3]=(t[1]%100)%10+0x30;	 			//�������λ
  t[0]=t[0]&0x0c;							//ȡ��Ч����λС��
  t[0]>>=2;									//������λ,�Ա���
  x=t[0];										
  y=dotcode[x];									//������ʵ�ʵ�С��
  TempBuffer1[5]=y/10+0x30;							//�����ʮ��λ
  TempBuffer1[6]=y%10+0x30;							//������ٷ�λ
}			

void delay(unsigned char i)
{
	while(i--);
}

main()
{
 unsigned char TH=110,TL=-20;    					//��һ����չʱ����ͨ������������,����������
       									 //���º���������������ͷ��ַ
 while(1)
 {	
    pt=ReadTemperature(TH,TL,0x3f);		 //�����¶�-22,����-24,�ֱ���10λ,Ҳ����0.25C
										 //��ȡ�¶�,�¶�ֵ�����һ�������ֽڵ�������,
	delay(100); 
	covert1();
	covert0(TH,TL);
	LCD_Initial();							//��һ�������к�,�ڶ���Ϊ�к�,Ϊ0��ʾ��һ��
											//Ϊ1��ʾ�ڶ���,����������Ϊ��ʾ���ݵ��׵�ַ
	LCD_Print(0,0,TempBuffer0);	
	LCD_Print(0,1,TempBuffer1); 				
 }
}
  



