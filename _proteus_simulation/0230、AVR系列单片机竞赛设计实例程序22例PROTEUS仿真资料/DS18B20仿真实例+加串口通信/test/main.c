/*--------------------------------------------------*/
/*             AVR-ARM开发网论坛                    */
/*           http://www.avrarm.com                  */
/*            AVR生成代码测试程序                   */
/*--------------------------------------------------*/
/*     程序由AVR辅助开发工具V2.1.0自动生成          */
/*     AVR系统的处理器为：   ATMega16               */
/*     AVR系统的晶振频率：   8.0000 Mhz             */
/*--------------------------------------------------*/

#include <iom16v.h>
#include <macros.h>
#include "uart.h"
#include "ds18b20.h"
#include "delay.h"

extern unsigned char rx_buff;       //串口接收中断缓冲区

//-----------------------------------------------------------
//主函数
//-----------------------------------------------------------
void main(void)
{
   unsigned char i=0;
   unsigned int  temp=0;

   CLI();
   Uart_Init();
   SEI();

  // Puts("AVR-ARM 开发网论坛RS232 通信测试程序");
  // Puts("Http://www.avrarm.com");
  // Puts("ATMega16 的串口测试");
  // Putchar(0x0d);
   //Putchar(0x0a);
   temp=resetDS18B20();             //检测DS1302的存在
   if(temp)
   { 
    // Puts("检测到DS18B20 的存在，可以测试！ ");
     //Puts("发送0x0C可以读取当前时间 ");
    // Puts("用户可以自行开发其他功能 ");
     Puts(" http://www.avrarm.com ");
   } 
   else
     Puts("NO!");

   while(1)
   {
      i = rx_buff;
      rx_buff = 0;
	  Putstr("Temp:   ");
         temp=readTempDS18B20();
        // Putchar(temp>>8);	          //发送到电脑
        // Putchar(temp);	            //发送到电脑
        // Putchar(0x0d);
        // Putchar(0x0a);
		 Puts(long2str(temp));
		 delay_nms(1000);
     /* if (i==0x0F)    //发送0x0F开始测试
      {
         i=0;
         CLI();
       //  Puts("AVR-ARM 开发网论坛RS232 通信测试程序");
         Puts("Http://www.avrarm.com");
        // Puts("ATMega16 的串口测试");
        // Putchar(0x0d);
        // Putchar(0x0a);
         SEI();
      }
      if (i==0x0C)             //发送0x0C读取温度
      {
         i=0;
         Puts("Temp：");
         temp=readTempDS18B20();
         Putchar(temp>>8);	          //发送到电脑
         Putchar(temp);	            //发送到电脑
         Putchar(0x0a);
         Putchar(0x0d);
      }*/
   }
}
