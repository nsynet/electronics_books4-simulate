#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10];                        //�Ĵ���������
uchar idata buf1[3]={0x0f,0x0f,0x09};       //�ӻ����͵�����   
uchar data1,data2,data3;
uchar pf,i;
uchar flag,flag1;

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
                          //�ӻ�����ͨ��
      key1=0; 
      SM2=1;              //SM2=1�ӻ����ܵ�ַ 
         
      while(RI==0)
          {
            ;
          }
      data1=SBUF;
      RI=0;
    
       if(data1==0x03) 
          {
            flag1=6;      //��ַ��ȷ��־
            TI=0;
            key1=1;
            TB8=1;        
            SM2=0;        //TB8=1��SM2=0----�����Ժ�ͨ�ŵĵĶ�������
            SBUF=0x03;    //���ͱ�����ַ
            while(TI==0)
               {
                ;
               }
             TI=0;
             pf=0;
             TB8=0;
             key1=0;
             while(RI==0)    //�ӻ����ܴӻ�״̬��־
                 {
                   ;
                 }
              data3=SBUF;
              RI=0;
               if(data3==0x02)       //�����������������״̬
                   { key1=1;
                     SBUF=0x02;      //�ط��ӻ�״̬
                     while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     for(i=0;i<=2;i++)       
                          {  
                             SBUF=buf1[i];      //�ӻ���������
                             pf+=buf1[i];
                             while(TI==0)
                                  {
                                    ;
                                  }
                             TI=0;
                           }
                      SBUF=pf;                //�ӻ�����Ч���
                      while(TI==0)
                            {
                              ;
                            }
                      TI=0;
                  }
             if(data3==0x01)                //����������������ݱ�־
                   { key1=1;
                     SBUF=0x01;             //�ط��ӻ�״̬
                     while(TI==0)
                       {
                         ;
                       }
                     TI=0;
                     key1=0;
                     for(i=0;i<=9;i++)        //�ӻ���������
                          { 
                             while(RI==0)
                                  {
                                    ;
                                  }
                              buf[i]=SBUF;
                              pf+=buf[i];
                              RI=0;
                           }
                      while(RI==0)           //�ӻ�����Ч���
                            {
                              ;
                            }
                     data2=SBUF;
                     RI=0;                   //�뱾����Ч��ͽ��бȽ�
                     key1=1;
                     if(data2==pf)           //Ч�����ȷ
                             {               
                                SBUF=0xcc;      //���ʹӻ���ȷ���ܱ�־
                                while(TI==0)  
                                    {
                                      ;
                                    }
                                TI=0;
                              }
                     else{                     //Ч��ʹ���
                              SBUF=0xdd;      //�ӻ����ʹ����־----�����������·�������
                              while(TI==0)
                                 {
                                   ;
                                 }
                               TI=0;
                          }
                     }
                  
                    
         
              else
                 {key1=1;                   //����ӻ����ܵļȲ����������ܱ�־Ҳ�����������ͱ�־���ӻ����ʹ������ݣ��ӻ������������·�������
                  flag1=1;
                  SBUF=0xad;
                  while(TI==0)
                  {
                    ;
                  }
                 TI=0;
                }
           }
          
          
      else
          { 
            flag1=5;       //��ַ����ȷ
                           //************ע�����ﲻ�ط��κ�����**************
          }
  }

void display(void)
{ if(flag1==6)                       //�ӻ���ʾ��־
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
      receive();                 //ͨ���ӳ���
      display();                 //��ʾ�ӳ���
    }     
}