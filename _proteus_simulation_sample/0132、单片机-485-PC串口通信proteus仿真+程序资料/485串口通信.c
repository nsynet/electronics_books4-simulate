#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit P12=P1^2;
char code str[] = "you are the best! \n\r";

main()
{
uint j;
TMOD=0x20;
TL1=0xfd;TH1=0xfd;
SCON=0x50;
PCON &= 0xef;
TR1=1;
IE=0x00;
P12=1;
while(1)
{

uchar i=0;
while(str[i]!='\0')
{
SBUF=str[i];
while(!TI);
TI=0;
i++;
}

for(j=0;j<50000;j++);
}
}