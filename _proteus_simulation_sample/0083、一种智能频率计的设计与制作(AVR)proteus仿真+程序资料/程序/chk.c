//SIGNAL ִ��ʱȫ���жϴ���λ������������жϱ���ֹ
//INTERRUPT ִ��ʱȫ���жϴ���λ����λ�������жϿ�Ƕ��ִ
#ifndef chk_c
  #define chk_c

  #include "main.h"

//*******���ڳ�ʼ�� �����ʣ����٣�λ����У�飬�жϣ������ͬ�첽ֹͣλ��ʱ�Ӽ���
  void usart_init( uint botelv )
  {
    UBRRH = ( f_cpu / botelv / 16-1 ) / 256;
    UBRRL = ( f_cpu / botelv / 16-1 ) % 256; //���㲨��
    UCSRA = 0X00; //
    UCSRB = ( 1 << RXCIE ) | ( 0 << RXEN ) | ( 1 << TXEN );
//ʹ�ܽ����жϣ�ʹ�ܽ��գ�ʹ�ܷ���  
    UCSRC = ( 1 << URSEL ) | 0x06;
//�첽��8λ���ݣ�����żУ�飬һ��ֹͣλ���ޱ���
  } //����ucsrcʱ��λҪΪ1����ubrrh����ַ

//***************����һ���ַ�
  void send_char( uchar zifu )
  {
    while ( !( UCSRA& ( 1 << UDRE )))
      ;
//���� ��ѯ����  
    UDR = zifu;
  }

//***************����һ���ַ���
  void send_str( uchar* str )
  {
    while ( *str )
//һֱ�������꼴0Ϊֹ  
    {
      send_char( *str++ );
    }
    send_char( 0x0D );
    send_char( 0x0A ); //��β���ͻس�����
  }

//****************�жϽ���  ɾ��
/* SIGNAL( SIG_USART_RECV ) //���ڽ����жϷ������
{

}*/

#endif
