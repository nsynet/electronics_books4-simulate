/*             AVR-ARM��������̳                    */
/*           http://www.avrarm.com                  */
/*              MCU���ڲ��Գ���                     */
/*--------------------------------------------------*/
/*     ������AVR���ڿ�������V2.0.0�Զ�����          */
/*     MCUϵͳ�Ĵ�����Ϊ��   ATMega16               */
/*     MCUϵͳ�ľ���Ƶ�ʣ�   8.0000 Mhz             */
/*--------------------------------------------------*/

#include <iom16v.h>
#include <macros.h>
#include "uart.h"


//-----------------------------------------------------------
//������
//-----------------------------------------------------------
void main(void)
{
   unsigned char i=0;

   Uart_Init();

   Puts("AVR-ARM RS232 TEST CODE");
   Puts("Http://www.avrarm.com");
   Puts("ATMega16 UART TEST");
   Putchar(0x0a);
   Putchar(0x0d);

   while(1)
   {
      i=Getchar();
      if (i!=0)    //����0x0F��ʼ����
      {
         i=0;
         Puts("AVR-ARM RS232 TEST CODE");
         Puts("Http://www.avrarm.com");
         Puts("ATMega16 UART TEST");
         Putchar(0x0a);
         Putchar(0x0d);
      }
   }
}
