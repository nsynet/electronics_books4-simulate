/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Professional
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : p
Version : 1.00
Date    : 2007-7-11
Author  : hgs(qrs)
Company : jlddx
Comments: 
3Â·/8Î»/ÏàÎ»ĞŞÕıÄ£Ê½PWMÊä³ö²âÊÔ³ÌĞò,¿ÉÔÚPB1¡¢2¡¢3£¨PIN15¡¢16¡¢17£©
Òı½Å½ÓÈë3Ö»LED·¢¹â¶ş¼«¹Ü£¨¹²Òõ£©¹Û²âÁÁ¶È±ä»¯¡£

Chip type           : ATmega8
Program type        : Application
Clock frequency     : 4.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega8.h>
#include <delay.h>

#define key1 PINC.0
#define key2 PINC.1
#define key3 PINC.2
#define key4 PINC.3
#define key5 PINC.4
#define key6 PINC.5

// Declare your global variables here

void main(void)
{
unsigned char a=0; 
unsigned char b=0;
unsigned char c=0;
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
//ÅäÖÃÎªÊä³ö
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
//ÅäÖÃÎªÊäÈë,²¢Ê¹ÄÚ²¿ÉÏÀ­ÓĞĞ§
PORTC=0xff;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
//ÅäÖÃÎªÊäÈë,¸ß×èÌ¬
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 62.500 kHz (²úÉúÔ¼122.5HzµÄPWMĞÅºÅ)
// Mode: Ph. correct PWM top=00FFh
// OC1A output: Inverted
// OC1B output: Inverted
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off

//TCCR1A=0xF1; //µ÷ÕûÊä³ö²¨ĞÎÏàÎ»£¨·´Ïà£©
TCCR1A=0xA1;   //µ÷ÕûÊä³ö²¨ĞÎÏàÎ»£¨ÕıÏà£©
TCCR1B=0x03; // (²úÉúÔ¼122.5HzµÄPWMĞÅºÅ)
//TCCR1B=0x02;   // (²úÉúÔ¼980.4HzµÄPWMĞÅºÅ)
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00; //¸Ä±ä´ËÖµ½«¸Ä±äPWM1µÄÕ¼¿Õ±È
OCR1BH=0x00; 
OCR1BL=0x00; //¸Ä±ä´ËÖµ½«¸Ä±äPWM2Õ¼¿Õ±È

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 62.500 kHz  (²úÉúÔ¼122.5HzµÄPWMĞÅºÅ)
// Mode: Phase correct PWM top=FFh
// OC2 output: Inverted PWM
ASSR=0x00;
TCCR2=0x64;   //µ÷ÕûÊä³ö²¨ĞÎÏàÎ»£¨ÕıÏà£© (²úÉúÔ¼122.5HzµÄPWMĞÅºÅ)
//TCCR2=0x62;  //µ÷ÕûÊä³ö²¨ĞÎÏàÎ»£¨ÕıÏà£© (²úÉúÔ¼980.4HzµÄPWMĞÅºÅ)
//TCCR2=0x74; //µ÷ÕûÊä³ö²¨ĞÎÏàÎ»£¨·´Ïà£©
TCNT2=0x00;
OCR2=0x00;  //¸Ä±ä´ËÖµ½«¸Ä±äPWM3µÄÕ¼¿Õ±È

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

while (1)
      {
       if (key1==0) //ÅĞ¶ÏPWM1+ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (key1==0) //ÔÙ´ÎÅĞ¶Ï
            {  
             if (a!=255) //Ôö¼ÓÕ¼¿Õ±È
               ++a;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×î´óÖµ±£³ÖÎª255
               a=255;
             OCR1AL=a; 
            }; 
         };
       if (key2==0) //ÅĞ¶ÏPWM1-ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (key2==0) //ÔÙ´ÎÅĞ¶Ï
            {  
             if (a!=0) //¼õÉÙÕ¼¿Õ±È
               --a;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×îĞ¡Öµ±£³ÖÎª0
               a=0;
             OCR1AL=a;
            }; 
         };
//-------------------------------------------
       if (key3==0) //ÅĞ¶ÏPWM1+ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (key3==0) //ÔÙ´ÎÅĞ¶Ï
            {  
             if (b!=255) //Ôö¼ÓÕ¼¿Õ±È
               ++b;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×î´óÖµ±£³ÖÎª255
               b=255;
             OCR1BL=b;
            }; 
         };
       if (key4==0) //ÅĞ¶ÏPWM1-ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (key4==0) //ÔÙ´ÎÅĞ¶Ï
            {  
             if (b!=0) //¼õÉÙÕ¼¿Õ±È
               --b;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×îĞ¡Öµ±£³ÖÎª0
               b=0;
             OCR1BL=b;  
            }; 
         };
//---------------------------------------------------------
       if (key5==0) //ÅĞ¶ÏPWM1+ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (key5==0) //ÔÙ´ÎÅĞ¶Ï
            {  
             if (c!=255) //Ôö¼ÓÕ¼¿Õ±È
               ++c;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×î´óÖµ±£³ÖÎª255
               c=255;
             OCR2=c;  
            }; 
         };
       if (key6==0) //ÅĞ¶ÏPWM1-ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (key6==0) //ÔÙ´ÎÅĞ¶Ï
            {  
             if (c!=0) //¼õÉÙÕ¼¿Õ±È
               --c;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×îĞ¡Öµ±£³ÖÎª0
               c=0;
             OCR2=c;  
            }; 
         };
//------------------------------------------------------------
       delay_ms(40); //¿ØÖÆ°´¼üÉ¨Ãè¼ä¸ô,·ÀÖ¹°´×¡²»·ÅÊ±±ä»¯¹ı¿ì
      };
}
