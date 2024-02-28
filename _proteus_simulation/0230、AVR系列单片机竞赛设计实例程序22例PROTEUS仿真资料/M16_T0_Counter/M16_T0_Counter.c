#include <iom16v.h>
#define uchar unsigned char
#define uint unsigned int

//segment code 0123456789
uchar Table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uint Data[4]={0,0,0,0};
uint CNT=0;

void DelayMs(uchar i)
{
 uchar j;
 for(;i>0;i--)
 {
  for(j=0;j<250;j++);
 }
}

void Display(uint *p)
{
 uchar i,sel=0x01;
 for(i=0;i<4;i++)
 {
  PORTC=sel;
  PORTA=Table[p[i]];
  DelayMs(2);
  sel=sel<<1;
 }
}

void Process(uint i,uint *p)//����T0��8λ��ʱ/��������������ֵΪ255
{                           // ���������p[0]�ò���
 p[0]=i/1000;
 i=i%1000;
 p[1]=i/100;
 i=i%100;
 p[2]=i/10;
 i=i%10;
 p[3]=i;
}

void Init_IO(void)
{
 DDRA=0xff;
 PORTA=0xff;
 DDRC=0xff;
 PORTC=0xff;
 DDRB=0x00;
 PORTB=0x00;
}

void main(void)
{
 uint load;
 Init_IO();
 TCCR0=0x06;//T0�����ڼ�����ʽ��T0��8λ������������ֵΪ255��
 //TCCR1B=0x07;//T1�����ڼ�����ʽ��T1��16λ������������ֵΪ65535��
 //TCNT1H=CNT;
 //TCNT1L=CNT;
 while(1)
 {
  load=TCNT0;//T0������8λ������ʽ
  //load=(TCNT1H<<8)+TCNT1L;//T1������16λ������ʽ
  Process(load,Data);
  Display(Data);
 }
}