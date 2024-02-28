#ifndef display_c
  #define display_c

#include"test.h"

//-----------------------------�ڲ�����
  uchar dzl( void ) //��ָ�� ����LCDæµ״̬
  {
    uchar value; //
    data_direc = in;       //����Ϊ��
    PORTC &= ~( 1 << rs ); //0
    PORTC |= ( 1 << rw );  //1
    PORTC |= ( 1 << e );   //1
    _delay_us( 4 );
    value = data_in;
    PORTC &= ~( 1 << e );  //0
    _delay_us( 1 );
    return value;
  }

//-------------------------------
  void xzl( uchar zhilin ) //дָ��
  {
    uchar busy;
    busy = dzl(); //��æ
//���Ϊ1�ȴ�
    while ( busy >= 80 )
    {
      busy = dzl();
    }
    data_direc = out;
    PORTC &= ~( 1 << rs ); //0
    PORTC &= ~( 1 << rw ); //0
    PORTC &= ~( 1 << e );  //0
    data_out = zhilin; //����
    PORTC |= ( 1 << e ); //1
    _delay_us( 4 );
    PORTC &= ~( 1 << e ); //0
  }

//------------------------
  void xsj( uchar shujv ) //д����
  {
    uchar busy;
    busy = dzl(); //��æ
//���λ���Ϊ1
    while ( busy >= 80 )
    {
      busy = dzl();
    }
    data_direc = out;
    PORTC |= ( 1 << rs );
    PORTC &= ~( 1 << rw );
    PORTC |= ( 1 << e );
    data_out = shujv; //����
    _delay_us( 4 );
    PORTC &= ~( 1 << e ); //0
  }

//******************���⺯��
//----------------------
  void clearall() //����ָ��
  {
    xzl( 0x01 );
  }

//------------------------------
  void yj_set( uchar xsh, uchar gb, uchar dt ) //��ʾ����
  {
//���ã���������ʾģʽ�����ģʽ����̬ģʽ
    xzl( 0x01 );
  _delay_ms( 1 ); //��avr���Ȼ�ֲ�Ҫ��ʱ��,����ļ�
    xzl( xsh );
  _delay_ms( 1 );
    xzl( gb );
  _delay_ms( 1 );
    xzl( dt );
  }

//----------------------------------------
  void makecg( uchar address, uchar* cg ) //�����ֿ�
  {
//�׵�ַ���ֿ�ָ��
    uchar num;
//8�ֽ�Ϊһ��ͼ�� 
    for ( num = 0; num < 8; num++ )
    {
      xzl( address++ ); //һ����ַһ������
      xsj( *cg++ );
    }
  }

//------------------------------
  void showstr( uchar* str, uchar xpot, uchar ypot, uchar num ) //Һ����ʾ
  {
//�ַ�ָ�룬���꣬���� ����1--16��1--2
//��һ��
    if ( ypot == 1 )
    {
      xzl( 0x80 + xpot - 1 );
    }
//�ڶ��� 
    else
    {
      xzl( 0xc0 + xpot - 1 );
    }
//д���� ��Ҫ����16-xpot��
    if ( num > 16-xpot )
    {
      num = 16-xpot;
    }
    for ( ; num > 0; num-- )
    {
      xsj( *str++ );
    }
  }

#endif
