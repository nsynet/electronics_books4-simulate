#ifndef celiang_c
  #define celiang_c

  #include "main.h"
//***************************************��ʱ������
//t0ֻ������ʱ,�̶���1s t1������try��f��,��ʱ��t��
  void timer0_init() //CTCģʽ ��ʱ1s
  {
    TCNT0 = bch; //����  ��5mhz�µó��Ĳ���ϵ��
    OCR0 = 249;   //�趨TOPֵ  ÿ��250��
    TCCR0 = ( 1 << WGM01 ) | ( 0 << WGM00 ) | ( 0 << COM01 ) | ( 0 << COM00 ) |
      ( 0 << CS02 ) | ( 0 << CS01 ) | ( 0 << CS00 );
  }
//*************��ʱ��1 16λ
  void timer1_init( uchar moshi ) //����������ֻ��������ĳЩ
  {
    TCNT1 = 0X00; //���
//���� ����
    if ( moshi == try )
    {
      OCR1A = 0XFFFE; //������
      TCCR1A = ( 0 << COM1A1 ) | ( 0 << COM1A0 ) | ( 0 << COM1B1 ) | ( 0 <<
        COM1B0 ) | ( 0 << WGM11 ) | ( 0 << WGM10 ); //��ƥ��  ctcģʽ
      TCCR1B = ( 0 << ICNC1 ) | ( 0 << ICES1 ) | ( 0 << WGM13 ) | ( 1 << WGM12 )
        | ( 0 << CS12 ) | ( 0 << CS11 ) | ( 0 << CS10 ); //�ر�
    }
//��Ƶ�� ����
    else if ( moshi == cef )
    {
      OCR1A = 49999; //50k������ //��Ƶ<50k��Ҫ����һ������ ����Ҫ
      TCCR1A = ( 0 << COM1A1 ) | ( 0 << COM1A0 ) | ( 0 << COM1B1 ) | ( 0 <<
        COM1B0 ) | ( 0 << WGM11 ) | ( 0 << WGM10 ); //��ƥ��  ctcģʽ
      TCCR1B = ( 0 << ICNC1 ) | ( 0 << ICES1 ) | ( 0 << WGM13 ) | ( 1 << WGM12 )
        | ( 0 << CS12 ) | ( 0 << CS11 ) | ( 0 << CS10 ); //�ر�
    }
//������ ��ʱ
    else
    {
      OCR1A = 49999; //50ms
      TCCR1A = ( 0 << COM1A1 ) | ( 0 << COM1A0 ) | ( 0 << COM1B1 ) | ( 0 <<
        COM1B0 ) | ( 0 << WGM11 ) | ( 0 << WGM10 ); //��ƥ��  ctcģʽ
      TCCR1B = ( 0 << ICNC1 ) | ( 0 << ICES1 ) | ( 0 << WGM13 ) | ( 1 << WGM12 )
        | ( 0 << CS12 ) | ( 0 << CS11 ) | ( 0 << CS10 ); //�ر�
    }
  }

//-------------------------------------------------------------------------
//   //ˢ�����еĶ��� Ϊ���²�����׼��    
//-------------------------------------------------------------------------
  void refish()
  {
    TIFR = 0Xff;     //���ж�
    _delay_ms( 40 ); //��ʱ
    _delay_ms( 40 );
    t0_cont = 0;     //��ֵ
    t1_cont = 0;
    flg1 = 0;        //flag
	#if pc
send_char('F');
send_char('F');
    #endif
  }
//-------------------------------------------------------------------------
//   //���Ʒ�Χ   997Ϊ��
//-------------------------------------------------------------------------
  uchar hz_try() //���Ʒ�Χ 1k
  {
    timer1_init( try ); //����ģʽ
    TCCR1B |= 7;        
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    _delay_ms( 10 );
    TCCR1B &= ~7; 
    if ( t1_cont == 0 )
    {
      if ( TCNT1 > 99 )
      {
        return 1;
      }
//�������100
      else
      {
        return 0;
      }
//���С��100
    }
    else
    {
      t1_cont = 0; 
      return 1;    
    }
  }
//-------------------------------------------------------------------------
//       //Ƶ�ʷ�
//-------------------------------------------------------------------------
  void cl_f()
  {
    uchar back[7]; //7λ����
    uchar time;

    showstr( "c_f", 1, 2, 3 ); //Ƶ�ʷ�

    timer1_init( cef );        //
    timer0_init();             //  

while( !( PINB& ( 1 << 4 )));//�ȴ���1
while (( PINB& ( 1 << 4 )));//�ȴ���0
    TCCR1B = 0X0e; //���������� �ȿ�Ƶ��
    TCCR0 = 0X09;  //ʱ����
    for ( time = 9; time > 0; time-- )
    {
      _delay_ms( 10 );
    }
    _delay_ms( 9 );
    _delay_us( 800 );//����Ҫʵ�ʵ���
#if pc
	send_char('A');
#endif
    while ( !flg1 )

    {
	#if pc
     send_char( 0x64 );
	#else
     send_char( 'w' );
	#endif
    }
//*************************�鿴����
    #if pc
    send_char( t1_cont / 0x100 ); //�鿴����
    send_char( t1_cont % 0X100 );
    send_char( TCNT1 / 0X100 ); //�鿴����
    send_char( TCNT1 % 0X100 );
	send_char('F');
    #endif
 cale_f(back);//����
 showstr( ">1KHz", 11, 1, 5 ); //����1k
 showstr( "             ", 4, 2, 10 );//����
 showstr(back,7,2,7);//��ʾ
  }
//-------------------------------------------------------------------------
//       //���ڷ�
//-------------------------------------------------------------------------
  void cl_t()
  {
    uchar xsh[6]; //��λС�� xxx.xxhz 

    showstr( "c_t", 1, 2, 3 );    

    timer1_init( cet ); //����ģʽ
//�ȴ����1
    while ( !( PINB& ( 1 << 4 )))
      ;
//�ȴ����0 ��ʼ��ʱ
    while (( PINB& ( 1 << 4 )))
      ;
    TCCR1B = 0x09; //������ʱ����ʱ
//�ȴ����1
    while ( !( PINB& ( 1 << 4 )))
      ;
//�ȴ����0 ֹͣ����
    while (( PINB& ( 1 << 4 )))
      ;
    TCCR1B = 0X80; //�رն�ʱ��
#if pc
send_char('B');
send_char(t1_cont/0x100);
send_char(t1_cont%0x100);
send_char(TCNT1/0X100); //
send_char(TCNT1%0x100); //
send_char('F');
#endif

cale_t(xsh);//����
showstr( "<1KHz", 11, 1, 5 ); //С��1k
showstr( "             ", 4, 2, 10 );//����
showstr( xsh,8,2,6 ); //��ʾ
  }

#endif 

