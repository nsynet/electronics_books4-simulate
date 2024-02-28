/*             AVR-ARM开发网论坛                    */
/*           http://www.avrarm.com                  */
/*              MCU串口测试程序                     */
/*--------------------------------------------------*/
/*     程序由AVR串口开发工具V2.0.0自动生成          */
/*     MCU系统的处理器为：   ATMega16               */
/*     MCU系统的晶振频率：   8.0000 Mhz             */
/*--------------------------------------------------*/

#include <iom16v.h>
#include <macros.h>
#include "uart.h"


//-----------------------------------------------------------
//主函数
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
      if (i!=0)    //发送0x0F开始测试
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
