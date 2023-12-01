#include <AT89X51.H>
#define uchar unsigned char
#define RXD P1_0
#define TXD P1_1

//��������ʼ��
void S2INI(void)
{
    TMOD |=0x02;                //������0����ʽ2
    TH0=0xA0;                    //ԤֵΪ256-96=140��ʮ������A0
    TL0=TH0;        
    TR0=1;                        //��ʼ����
    TF0=0;
}

//��ѯ�����������־λ
void WaitTF0( void )
{
    while(!TF0);
    TF0=0;
}

void WByte(uchar input)
{
    //������ʼλ
    uchar i=8;
    TR0=1;
    TXD=(bit)0;
    WaitTF0();
    //����8λ����λ
    while(i--)
    {
        TXD=(bit)(input&0x01);     //�ȴ���λ
        WaitTF0();
        input=input>>1;
    }
    //����У��λ(��)
    //���ͽ���λ
    TXD=(bit)1;
    WaitTF0();
    TR0=0;
}    
void delay()
{
 uchar i,j,k;
 for(i=100;i>0;i--)
 for(j=20;j>0;j--)
 for(k=248;k>0;k--);
}
void main(void)
{
 S2INI();
 while(1)
 {
   WByte(0x7f);
   delay();
   WByte(0xff);
	delay();
 }
}