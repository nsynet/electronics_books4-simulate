#include"test.h"
#define out1 1 //��Ƶ
#define out2 2 //��Ƶ
//-------------------------------------------------------------------------
//mcu��ʼ�� �˿� ��ʱ�� �ж� ���ж� ����
//-------------------------------------------------------------------------
void mcu_init()
{
//******************�˿�
  data_direc = out; //���
  DDRB = out; //���
  DDRC = out; //���
  PORTC = 0X00; //���0
  DDRB &= ~( 0 << 4 ); //����
  PORTB &= ~( 0 << 4 );
  DDRB &= ~( 0 << 3 ); //����
  PORTB |= ( 1 << 3 );
//********************��ʱ��
  TIMSK |= 0x12; //��ʱ�ж�����λ ֻ��������ƥ��
}


int main()
{
uchar a;
  mcu_init();                 //��ʼ��
//  usart_init( 57600 );        //��ʼ��
//  yj_set( 0x38, 0x0f, 0x06 ); //��ʼ��
//  clearall(); //��ʼ��
//  showstr( "cymometer", 1, 1, 9 ); //Һ����ʾ

DDRA=0XFF;//OUT
PORTA=0XFF;
while(1)
{
for(a=0;a<200;a++)
{
_delay_us(10);
PORTA^=(1<<out1);
}
PORTA^=(1<<out2);

}

return 1;

}
