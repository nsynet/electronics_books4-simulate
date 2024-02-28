/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Professional
Automatic Program Generator
� Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : p
Version : 1.00
Date    : 2007-7-11
Author  : hgs(qrs)
Company : jlddx
Comments: 
3·/8λ/��λ����ģʽPWM������Գ���,����PB1��2��3��PIN15��16��17��
���Ž���3ֻLED��������ܣ��������۲����ȱ仯��

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
//����Ϊ���
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
//����Ϊ����,��ʹ�ڲ�������Ч
PORTC=0xff;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
//����Ϊ����,����̬
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 62.500 kHz (����Լ122.5Hz��PWM�ź�)
// Mode: Ph. correct PWM top=00FFh
// OC1A output: Inverted
// OC1B output: Inverted
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off

//TCCR1A=0xF1; //�������������λ�����ࣩ
TCCR1A=0xA1;   //�������������λ�����ࣩ
TCCR1B=0x03; // (����Լ122.5Hz��PWM�ź�)
//TCCR1B=0x02;   // (����Լ980.4Hz��PWM�ź�)
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00; //�ı��ֵ���ı�PWM1��ռ�ձ�
OCR1BH=0x00; 
OCR1BL=0x00; //�ı��ֵ���ı�PWM2ռ�ձ�

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 62.500 kHz  (����Լ122.5Hz��PWM�ź�)
// Mode: Phase correct PWM top=FFh
// OC2 output: Inverted PWM
ASSR=0x00;
TCCR2=0x64;   //�������������λ�����ࣩ (����Լ122.5Hz��PWM�ź�)
//TCCR2=0x62;  //�������������λ�����ࣩ (����Լ980.4Hz��PWM�ź�)
//TCCR2=0x74; //�������������λ�����ࣩ
TCNT2=0x00;
OCR2=0x00;  //�ı��ֵ���ı�PWM3��ռ�ձ�

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
       if (key1==0) //�ж�PWM1+�Ƿ���
         { 
          delay_ms(20); //ȥ����
          if (key1==0) //�ٴ��ж�
            {  
             if (a!=255) //����ռ�ձ�
               ++a;
             else   //ʹռ�ձȱȽ������ֵ����Ϊ255
               a=255;
             OCR1AL=a; 
            }; 
         };
       if (key2==0) //�ж�PWM1-�Ƿ���
         { 
          delay_ms(20); //ȥ����
          if (key2==0) //�ٴ��ж�
            {  
             if (a!=0) //����ռ�ձ�
               --a;
             else   //ʹռ�ձȱȽ�����Сֵ����Ϊ0
               a=0;
             OCR1AL=a;
            }; 
         };
//-------------------------------------------
       if (key3==0) //�ж�PWM1+�Ƿ���
         { 
          delay_ms(20); //ȥ����
          if (key3==0) //�ٴ��ж�
            {  
             if (b!=255) //����ռ�ձ�
               ++b;
             else   //ʹռ�ձȱȽ������ֵ����Ϊ255
               b=255;
             OCR1BL=b;
            }; 
         };
       if (key4==0) //�ж�PWM1-�Ƿ���
         { 
          delay_ms(20); //ȥ����
          if (key4==0) //�ٴ��ж�
            {  
             if (b!=0) //����ռ�ձ�
               --b;
             else   //ʹռ�ձȱȽ�����Сֵ����Ϊ0
               b=0;
             OCR1BL=b;  
            }; 
         };
//---------------------------------------------------------
       if (key5==0) //�ж�PWM1+�Ƿ���
         { 
          delay_ms(20); //ȥ����
          if (key5==0) //�ٴ��ж�
            {  
             if (c!=255) //����ռ�ձ�
               ++c;
             else   //ʹռ�ձȱȽ������ֵ����Ϊ255
               c=255;
             OCR2=c;  
            }; 
         };
       if (key6==0) //�ж�PWM1-�Ƿ���
         { 
          delay_ms(20); //ȥ����
          if (key6==0) //�ٴ��ж�
            {  
             if (c!=0) //����ռ�ձ�
               --c;
             else   //ʹռ�ձȱȽ�����Сֵ����Ϊ0
               c=0;
             OCR2=c;  
            }; 
         };
//------------------------------------------------------------
       delay_ms(40); //���ư���ɨ����,��ֹ��ס����ʱ�仯����
      };
}
