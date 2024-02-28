#include "reg52.h"
#define uchar unsigned char
#define uint  unsigned int

void delay(uint count)
{
	while(--count);
}

void main(void)
{
	P1=0XFE;
 	while(1)
	{
		delay(300);
		 P1<<=1;
		P1|=0X01;
		if(P1==0x7f)
 		{ delay(300);
			P1=0xfe;
			}			/* Insert your code here. */
	}
}
