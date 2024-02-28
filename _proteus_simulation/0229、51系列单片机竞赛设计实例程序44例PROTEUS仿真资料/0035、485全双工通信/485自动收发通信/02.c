#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10];                      //�����վ�
uchar idata buf1[3]={0x06,0x09,0x05};     //�ӻ����͵�����
uchar data1,data2,data3;
uchar pf,i;
uchar flag,flag2;

sbit key1=P2^0;

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
    TH1=0xfd;
    TL1=0xfd;
    PCON=0x00;
    TR1=1;
    SCON=0Xd0;
} 

void receive(void)
{  
     SM2=1;                         //SM2=1���ӻ�ֻ���ڽ��ܵ�ַ״̬
     key1=0;
     while(RI==0)
          {
            ;
          }
        data1=SBUF;               //���ܵ�ַ�뱾���ĵ�ַ�Ƚ�
        RI=0;                
       if(data1!=0x04)
         {  
         flag2=3;                  //���Ǳ����ĵ�ַ
         }
    else {                         //��ַ��ȷ
              key1=1;
              flag2=2;
              TB8=1;                //TB8=1�Ǵӻ����͵�ַ��־
              SM2=0;                //SM2=2�������κη��ͺͽ�������
              SBUF=0x04;             //�ӻ����ͱ�־
              while(TI==0)
                   {
                     ;
                   }
              TI=0;
              pf=0;
              TB8=0;                 //TB8=0�Ǵӻ�����ͨ�ŵ�ȫ������
              key1=0;
              while(RI==0)
                    {
                      ;
                    }
              data3=SBUF;             //�ӻ���������״̬
              RI=0;
              key1=1;
             if(data3==0x02)           //11111�����ǽ���״̬
                   { TB8=0;
                    
                     SBUF=0x02;        //�ӻ����ͱ�����״̬
                     while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     for(i=0;i<=2;i++)            //�ӻ���������
                          {  SBUF=buf1[i];
                             pf+=buf1[i];
                             while(TI==0)
                                  {
                                    ;
                                  }
                             TI=0;
                           }
                      SBUF=pf;                 //�ӻ�����Ч���
                      while(TI==0)
                            {
                              ;
                            }
                      TI=0;
                  }
             
               if(data3==0x01)                  //22222�����Ƿ���״̬
                   {  TB8=0;
                      key1=1;
                      SBUF=0x01;                //�ӻ����ͱ�����״̬
                      while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     key1=0;
                     for(i=0;i<=9;i++)
                        {                           //�ӻ���������������
                         while(RI==0)
                              {
                               ;
                              }
                         buf[i]=SBUF;
                         pf+=buf[i];
                         RI=0;
                        }
                     while(RI==0)
                            {
                               ;                   //�ӻ�����Ч���
                            }
                     data2=SBUF;                  
                     RI=0;
                     key1=1;
                     if(data2==pf)                //�ӻ����ܵ�Ч����뱾����Ч��ͱȽ�
                         {                //Ч����ȷ
                            TB8=0;
                            SBUF=0xcc;            //������ȷ�ı�־
                            while(TI==0)  
                                 {
                                   ;
                                 } 
                            TI=0;
                         }
                  else{  
                         TB8=0;                    //Ч�����
                         SBUF=0xdd;         //���ʹ����־�������������·�������
                         while(TI==0)
                               {
                                  ;
                                }
                          TI=0;
                       }
                }
             else                           //����״̬����
                   {  key1=1;
                      flag2=3;
                      SBUF=0xac;             //���ʹ����־
                      while(TI==0)
                        {
                         ;
                        }
                       TI=0;
                    }
       }
}

void display(void)
{ if(flag2==2)                   //�ӻ���ʾ��־
    {
         for(i=0;i<=9;i++)
            {
              P1=buf[i];
              delay(50);
             }
     }
}


void main(void)
{
    delay(500);
    init();
    while(1)
    {  
      receive();                //�ӻ�ͨ���ӳ���
      display();                //�ӻ���ʾ�ӳ���
    }
}