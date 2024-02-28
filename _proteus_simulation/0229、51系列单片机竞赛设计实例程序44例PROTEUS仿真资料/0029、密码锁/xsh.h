#ifndef _xsh_h
#define _xsh_h
#include<AT89x51.h> 
#define uchar unsigned char 
#define uint unsigned int
sbit shj=P1^0;//�������ݿ�
sbit sck=P1^1;//����ʱ��
uchar code tab[20]={   0x88,/*0*/
        0xBE,/*1*/
        0xC4,/*2*/
        0x94,/*3*/
        0xB2,/*4*/
        0x91,/*5*/
        0x81,/*6*/
        0xBC,/*7*/
        0x80,/*8*/
        0x90,/*9*/
        0xA0,/*A*/
        0x83,/*b*/
        0xC9,/*C*/
        0x86,/*d*/
        0xC1,/*E*/
        0xE1,/*F*/
        0xA8,/*N*/
        0xF7,/*-*/
		0x94,/*��E*/
		0xE0/*P*/  };	//���������
uchar code sb0[3]={8,8,8},/*��������ʾ*/
       code sb1[3]={0,15,15},/*����ǰ��ʾ*/
       code sb2[6]={17,17,17,17,17,17},/*�޸���ʾ*/ 
       code sb3[6]={16,0,16,0,16,0},/*��һ���α�����ʾ*/
	   code sb4[6]={8,8,8,8,8,8},/*����Ա������ʾ*/
	   code sb5[6]={18,18,18,18,18,18};/*�����α�����ʾ*/ 

//////////////////////////*��ʾ��·*/////////////////////////
void writedata(uchar num)//����һ���ֽ�
{
 uchar temp;
 int i;
 temp=tab[num];
 for(i=0;i<8;i++)
 { temp=temp<<1;
   shj=CY;
   sck=0;
   sck=1; 
 }
 }
 void display_0(uchar temp)//����ǰ״̬	
 { int i,g,s,q;
   uchar m;
  q=temp/100;
  s=temp%100/10;
  g=temp%10;
  for(i=0;i<3;i++)
  {	
     m=sb1[i];
     writedata(m);
  }
  writedata(q);	
  writedata(s);
  writedata(g);
}
 void display_1(uchar temp)//������״̬	
 {
  int i,g,s,q;
  uchar m;
  q=temp/100;
  s=temp%100/10;
  g=temp%10;
  for(i=0;i<3;i++)
  {	
     m=sb0[i];
     writedata(m);
  }	
  writedata(q);
  writedata(s);
  writedata(g);
}
void display_2()//�޸�������ʾ	
{
  int i;
  uchar m;
  for(i=0;i<6;i++)
  {	
     m=sb2[i];
     writedata(m);
  }	
}
void display_3()//������ʾ	
{
  int i;
  uchar m;
  for(i=0;i<6;i++)
  {	
     m=sb3[i];
     writedata(m);
  }	
}

void display_4()//����Աģʽ��ʾ	
{ 
  int i;
  uchar m;
  for(i=0;i<6;i++)
  {	
     m=sb4[i];
     writedata(m);
  }	
}
void display_5()//����Աģʽ��ʾ	
{ 
  int i;
  uchar m;
  for(i=0;i<6;i++)
  {	
     m=sb5[i];
     writedata(m);
  }	
}
#endif