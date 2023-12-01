#include <iom16v.h>
#define uchar unsigned char
#define uint unsigned int
//segment code//
uchar Table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar Data[4]={1,2,3,4};//定义初始时间00：00
uchar CNT;
void DelayMs(uchar i)
{
 uchar j;
 for(;i!=0;i--)
 {
  for(j=250;j!=0;j--);
 }
}

void Display(uchar *p)
{
 uchar i,sel=0x01;
 for(i=0;i<4;i++)
 {
  PORTB=sel;
  PORTA=0xff-Table[p[i]];
  DelayMs(1);
  sel=sel<<1;
 }
}

void Init_IO(void)
{
 DDRA=0xff;
 PORTA=0xff;
 DDRB=0xff;
 PORTB=0xff;
 DDRC=0xff;
 PORTC=0xff;
 }

void Add_Second(uchar *p)
{
 p[3]++;
 if(p[3]==10){p[3]=0;p[2]++;}
 if(p[2]==6){p[2]=0;p[1]++;}
 if(p[1]==10){p[1]=0;p[0]++;}
 if(p[0]==6){p[0]=0;}
}

void main(void)
{
 uchar i;
 Init_IO();
 PORTA=0xff;
 PORTB=0x00;
 DelayMs(10);
 PORTB=0xff;
 ASSR=0x08;//异步时钟使能
 TCCR2=0x07;//32.768KHZ的晶振1024分频作为T/C2的时钟源
 TIMSK=0x40;//T/C2中断溢出使能
 SREG=SREG|0x80;//全局中断使能
 while(1)
 {
  Display(Data);
  if(CNT==32)
  {
   CNT=0;
   Add_Second(Data);
  }
 }
}

#pragma interrupt_handler Timer2:5
void Timer2(void)
{CNT=CNT+1;}










