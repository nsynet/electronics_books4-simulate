/*--------------------------------------------------*/
/*             AVR-ARM��������̳                    */
/*           http://www.avrarm.com                  */
/*            AVR���ɴ�����Գ���                   */
/*--------------------------------------------------*/
/*     ������AVR������������V2.1.0�Զ�����          */
/*     AVRϵͳ�Ĵ�����Ϊ��   ATMega16               */
/*     AVRϵͳ�ľ���Ƶ�ʣ�   8.0000 Mhz             */
/*--------------------------------------------------*/

#include <iom16v.h>
#include <macros.h>
#include "uart.h"
#include "ds18b20.h"
#include "delay.h"

extern unsigned char rx_buff;       //���ڽ����жϻ�����

//-----------------------------------------------------------
//������
//-----------------------------------------------------------
void main(void)
{
   unsigned char i=0;
   unsigned int  temp=0;

   CLI();
   Uart_Init();
   SEI();

  // Puts("AVR-ARM ��������̳RS232 ͨ�Ų��Գ���");
  // Puts("Http://www.avrarm.com");
  // Puts("ATMega16 �Ĵ��ڲ���");
  // Putchar(0x0d);
   //Putchar(0x0a);
   temp=resetDS18B20();             //���DS1302�Ĵ���
   if(temp)
   { 
    // Puts("��⵽DS18B20 �Ĵ��ڣ����Բ��ԣ� ");
     //Puts("����0x0C���Զ�ȡ��ǰʱ�� ");
    // Puts("�û��������п����������� ");
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
        // Putchar(temp>>8);	          //���͵�����
        // Putchar(temp);	            //���͵�����
        // Putchar(0x0d);
        // Putchar(0x0a);
		 Puts(long2str(temp));
		 delay_nms(1000);
     /* if (i==0x0F)    //����0x0F��ʼ����
      {
         i=0;
         CLI();
       //  Puts("AVR-ARM ��������̳RS232 ͨ�Ų��Գ���");
         Puts("Http://www.avrarm.com");
        // Puts("ATMega16 �Ĵ��ڲ���");
        // Putchar(0x0d);
        // Putchar(0x0a);
         SEI();
      }
      if (i==0x0C)             //����0x0C��ȡ�¶�
      {
         i=0;
         Puts("Temp��");
         temp=readTempDS18B20();
         Putchar(temp>>8);	          //���͵�����
         Putchar(temp);	            //���͵�����
         Putchar(0x0a);
         Putchar(0x0d);
      }*/
   }
}
