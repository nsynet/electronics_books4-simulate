#include <reg51.h>
#include <absacc.h>
#define TR 1
#define uchar unsigned char
#define uint  unsigned int

//uchar idata buf[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
uchar data1,data2;
uchar pf;
uchar flag,flag1;

sbit key1=P1^0;
sbit key2=P2^0;
/************��ʱ����************/
void delay(uchar k)
    {
        uchar j;
        while((k--)!=0)           
        	{
                for(j=0;j<125;j++)
                	{;}
        	}
    }


void init(void)
{
    TMOD=0x20;                 
    TH1=0xe8;
    TL1=0xe8;
    PCON=0x00;               //���ε��ڷ���485ͨ�Ŷ��ԣ������ʶԴ�����Ϣ�к�
    TR1=1;                   //��Ҫ�����ã���Ϊ�����ʵ͵Ļ������Ǵ����ٶ�����
    SCON=0x90;               //�����޷��������ݣ����ǵ���ʱ���ֵ���������
}                            //������485ͨ���������ǵ���ͨ�ţ����Ƕ��ͨ�ţ�
 //����ͨ�ŵķ�ʽ������-----��ʽ2�����Ƿ�ʽ3�������Ƿ�ʽ0���߷�ʽ1����һ���ر����Ҫ��
                              
void send(void)
{     
        key2=1;
       SBUF=0x01;
       while(TI==0)
         {
           ;
         }
       TI=0;
       key2=0;
       while(RI==0)
       {
        ;
       }
        data1=SBUF;
        RI=0;
        key2=1;
       if(data1!=0x01)
         {
           SBUF=0x0f;
            while(TI==0)
            {
                ;
            }
            TI=0;
         }
       else{
            SBUF=0x09;
            while(TI==0)
            {
                ;
            }
            TI=0;
            
           }
}


void main(void)
{
    //delay(500);
    init();
 
    while(1)
    {
        //keyscan();
        send();
        delay(100);
    }
}

     
