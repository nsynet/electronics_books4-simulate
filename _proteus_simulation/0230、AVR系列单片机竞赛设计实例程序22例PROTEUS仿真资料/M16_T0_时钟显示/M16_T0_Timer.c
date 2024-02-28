#include<iom16v.h>
#define uchar unsigned char

uchar Table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar Data[4]={0,0,0,0};
uchar Time[2]={0,0};
uchar CNT=0;

void DelayMs(uchar i)
{
 uchar j;
 for(;i>0;i--)
 {
  for(j=0;j<250;j++);
 }
}

void Display(uchar *p)
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

void Process(uchar *p1,uchar *p2)
{
 p2[0]=p1[0]/10;
 p2[1]=p1[0]%10;
 p2[2]=p1[1]/10;
 p2[3]=p1[1]%10;
}

void Init_IO(void)
{
 DDRA=0xff;
 PORTA=0xff;
 DDRC=0xff;
 PORTC=0xff;
}

void main(void)
{
 Init_IO();
 DelayMs(10);
 TCCR0=0x04;
 TCNT0=0x06;
 TIMSK=0x01;
 SREG=SREG|0x80;
 while(1)
 {
  Process(Time,Data);
  Display(Data);
 }
}

#pragma interrupt_handler Timer0:10
void Timer0(void)
{
 CNT++;
 if(CNT==125)
 {
  CNT=0;
  Time[1]++;
  if(Time[1]==60)
  {
   Time[1]=0;
   Time[0]++;
  }
  if(Time[0]==60)
  Time[0]=0;
 }
}