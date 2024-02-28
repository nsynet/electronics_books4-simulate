#include <iom16v.h>
#define uchar unsigned char
#define uint unsigned int

void main(void)
{
 uchar i;
 DDRB=0xf0;
 PORTB=0x00;
 ACSR=0x00;
 while(1)
 {
  if((ACSR&0x20)==0x20)
  PORTB=PORTB|0xf0;
  else
  PORTB=PORTB&0x0f;
 }
}