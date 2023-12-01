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
3Â·/8Î»/ÏàÎ»ÐÞÕýÄ£Ê½PWMÊä³ö²âÊÔ³ÌÐò,¿ÉÔÚPB1¡¢2¡¢3£¨PIN15¡¢16¡¢17£©
Òý½Å½ÓÈë3Ö»LED·¢¹â¶þ¼«¹Ü£¨¹²Òõ£©¹Û²âÁÁ¶È±ä»¯¡£

Chip type           : ATmega8
Program type        : Application
Clock frequency     : 4.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/
// CodeVisionAVR C Compiler
// (C) 1998-2004 Pavel Haiduc, HP InfoTech S.R.L.
// I/O registers definitions for the ATmega8
#pragma used+
sfrb TWBR=0;
sfrb TWSR=1;
sfrb TWAR=2;
sfrb TWDR=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      // 16 bit access
sfrb ADCSRA=6;
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRRL=9;
sfrb UCSRB=0xa;
sfrb UCSRA=0xb;
sfrb UDR=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   // 16 bit access
sfrb UBRRH=0x20;
sfrb UCSRC=0X20;
sfrb WDTCR=0x21;
sfrb ASSR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrw ICR1=0x26;   // 16 bit access
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  // 16 bit access
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  // 16 bit access
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  // 16 bit access
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb SFIOR=0x30;
sfrb OSCCAL=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TWCR=0x36;
sfrb SPMCR=0x37;
sfrb TIFR=0x38;
sfrb TIMSK=0x39;
sfrb GIFR=0x3a;
sfrb GICR=0x3b;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-
// Interrupt vectors definitions
// CodeVisionAVR C Compiler
// (C) 1998-2000 Pavel Haiduc, HP InfoTech S.R.L.
#pragma used+
void delay_us(unsigned int n);
void delay_ms(unsigned int n);
#pragma used-
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
//ÅäÖÃÎªÊäÈë,²¢Ê¹ÄÚ²¿ÉÏÀ­ÓÐÐ§
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
// Clock value: 62.500 kHz (²úÉúÔ¼122.5HzµÄPWMÐÅºÅ)
// Mode: Ph. correct PWM top=00FFh
// OC1A output: Inverted
// OC1B output: Inverted
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
//TCCR1A=0xF1; //µ÷ÕûÊä³ö²¨ÐÎÏàÎ»£¨·´Ïà£©
TCCR1A=0xA1;   //µ÷ÕûÊä³ö²¨ÐÎÏàÎ»£¨ÕýÏà£©
TCCR1B=0x03; // (²úÉúÔ¼122.5HzµÄPWMÐÅºÅ)
//TCCR1B=0x02;   // (²úÉúÔ¼980.4HzµÄPWMÐÅºÅ)
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
// Clock value: 62.500 kHz  (²úÉúÔ¼122.5HzµÄPWMÐÅºÅ)
// Mode: Phase correct PWM top=FFh
// OC2 output: Inverted PWM
ASSR=0x00;
TCCR2=0x64;   //µ÷ÕûÊä³ö²¨ÐÎÏàÎ»£¨ÕýÏà£© (²úÉúÔ¼122.5HzµÄPWMÐÅºÅ)
//TCCR2=0x62;  //µ÷ÕûÊä³ö²¨ÐÎÏàÎ»£¨ÕýÏà£© (²úÉúÔ¼980.4HzµÄPWMÐÅºÅ)
//TCCR2=0x74; //µ÷ÕûÊä³ö²¨ÐÎÏàÎ»£¨·´Ïà£©
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
       if (PINC.0==0) //ÅÐ¶ÏPWM1+ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (PINC.0==0) //ÔÙ´ÎÅÐ¶Ï
            {  
             if (a!=255) //Ôö¼ÓÕ¼¿Õ±È
               ++a;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×î´óÖµ±£³ÖÎª255
               a=255;
             OCR1AL=a; 
            }; 
         };
       if (PINC.1==0) //ÅÐ¶ÏPWM1-ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (PINC.1==0) //ÔÙ´ÎÅÐ¶Ï
            {  
             if (a!=0) //¼õÉÙÕ¼¿Õ±È
               --a;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×îÐ¡Öµ±£³ÖÎª0
               a=0;
             OCR1AL=a;
            }; 
         };
//-------------------------------------------
       if (PINC.2==0) //ÅÐ¶ÏPWM1+ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (PINC.2==0) //ÔÙ´ÎÅÐ¶Ï
            {  
             if (b!=255) //Ôö¼ÓÕ¼¿Õ±È
               ++b;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×î´óÖµ±£³ÖÎª255
               b=255;
             OCR1BL=b;
            }; 
         };
       if (PINC.3==0) //ÅÐ¶ÏPWM1-ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (PINC.3==0) //ÔÙ´ÎÅÐ¶Ï
            {  
             if (b!=0) //¼õÉÙÕ¼¿Õ±È
               --b;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×îÐ¡Öµ±£³ÖÎª0
               b=0;
             OCR1BL=b;  
            }; 
         };
//---------------------------------------------------------
       if (PINC.4==0) //ÅÐ¶ÏPWM1+ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (PINC.4==0) //ÔÙ´ÎÅÐ¶Ï
            {  
             if (c!=255) //Ôö¼ÓÕ¼¿Õ±È
               ++c;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×î´óÖµ±£³ÖÎª255
               c=255;
             OCR2=c;  
            }; 
         };
       if (PINC.5==0) //ÅÐ¶ÏPWM1-ÊÇ·ñ°´ÏÂ
         { 
          delay_ms(20); //È¥¶¶¶¯
          if (PINC.5==0) //ÔÙ´ÎÅÐ¶Ï
            {  
             if (c!=0) //¼õÉÙÕ¼¿Õ±È
               --c;
             else   //Ê¹Õ¼¿Õ±È±È½ÏÆ÷×îÐ¡Öµ±£³ÖÎª0
               c=0;
             OCR2=c;  
            }; 
         };
//------------------------------------------------------------
       delay_ms(40); //¿ØÖÆ°´¼üÉ¨Ãè¼ä¸ô,·ÀÖ¹°´×¡²»·ÅÊ±±ä»¯¹ý¿ì
      };
}
