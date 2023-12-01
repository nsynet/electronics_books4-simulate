
#ifndef main_h
  #define main_h
//���������ض���
  #define uchar unsigned char
  #define uint  unsigned int
  #define ulint unsigned long int
//ϵͳͷ�ļ�
  #include <avr/io.h>
  #include "util/delay.h"
  #include <avr/interrupt.h>//�ж�
//��Ŀͷ�ļ�
  #include "cale.h"     //����
  #include "display.h"  //��ʾ
  #include "intree.h"   //�ж�
  #include "chk.h"      //����
  #include "celiang.h"  //����
//********
  #define f_cpu 16000000//����
  #define m_cpu m16     //cpu����
  #define debug 1       //�������ģʽ
  #define pc    1       //����pc���д�������
  #define led_d 0       //ָʾ�Ƶ���
//**********
//*****************�жϳ�ʼ��
  #define mzd_on()  SREG=SREG|0X80  //�����ж�
  #define mzd_off() SREG=SREG&0X7F  //�ر����ж�
  #define stop()    while(1)        //ֹͣ
//****************�����õ�ledָʾ��,��Ŀ��û�õ�,ȫ�����ô��ڵ���
  #define led1 1   //���ӵ�pc��
  #define led2 2
  #define led3 3
  #define led1_on() PORTC|=(1<<led1)
  #define led2_on() PORTC|=(1<<led2)
  #define led3_on() PORTC|=(1<<led3)
  #define led1_off() PORTC&=~(1<<led1)
  #define led2_off() PORTC&=~(1<<led2)
  #define led3_off() PORTC&=~(1<<led3)
//������ϵƵĺ���,2^3-1=7
//~~~~~~~~~~~~~~
#endif 
//******************ȫ�ֱ������� ����main�ļ�,������ȫ������һ��
#ifndef main_c
  #define main_c

  extern uint t0_cont;
  extern uint t1_cont;

  extern uchar flg1;

#endif
