#ifndef display_c
  #define display_c

  #include "main.h"

  uchar dzl( void ) //��ָ�� ����LCDæµ״̬
  {
    uchar value; //
    data_direc = in;
    PORTB &= ~( 1 << rs ); //0
    PORTB |= ( 1 << rw ); //1
    PORTB |= ( 1 << e ); //1
    _delay_us( 2 );
    value = data_in;
    PORTB &= ~( 1 << e ); //0
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
    PORTB &= ~( 1 << rs ); //0
    PORTB &= ~( 1 << rw ); //0
    PORTB &= ~( 1 << e ); //0
    data_out = zhilin; //����
    PORTB |= ( 1 << e ); //1
    _delay_us( 2 );
    PORTB &= ~( 1 << e ); //0
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
    PORTB |= ( 1 << rs );
    PORTB &= ~( 1 << rw );
    PORTB |= ( 1 << e );
    data_out = shujv; //����
    _delay_us( 2 );
    PORTB &= ~( 1 << e ); //0
  }


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

    xzl( xsh );

    xzl( gb );

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
