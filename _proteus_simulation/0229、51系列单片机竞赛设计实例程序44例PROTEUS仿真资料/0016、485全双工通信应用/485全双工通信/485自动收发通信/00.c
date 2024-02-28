#include <reg51.h>
#include <absacc.h>
#define TR 1
#define uchar unsigned char
#define uint  unsigned int

uchar idata buf[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};  //�ӻ�1���͵�����
uchar idata buf1[10]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x09}; //�ӻ�2���͵�����
uchar idata buf2[3];                                                      //���ܴӻ�������
uchar data1,data2,data3;
uchar pf,addr,TRR,count,count1;
uchar flag,flag1,flag2=3;
uchar i; 

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
    SCON=0xd0;
} 



void send(uchar addr,uchar TRR)
{ 
                       
        
      TB8=1;  
      key1=1;                     //TB8��1
      SBUF=addr;                   //���ʹӻ��ĵ�ַ 
       while(TI==0) 
         {
           ;
         }
       TI=0;
       key1=0;
      while(RI==0)
       {
        ;
       }
        data1=SBUF;                //���ܴӻ���ַ������
        RI=0; 
       if(data1!=addr)             //�ӻ���ַ�д���
         {
          flag2=0;
           
         }      
     else{                        //�ӻ���ַ��ȷ--------�Ƿ������ݱ�־0X01 
           if(TRR==0x01)          
               { 
                 TB8=0;            //TB8��0
                 key1=1;
                 SBUF=TRR;
                 while(TI==0)
                  {
                    ;
                  }
                  TI=0;
                  key1=0;
                 while(RI==0)       //���ܴӻ�״̬
                      {
                        ;
                      }
                 data3=SBUF;
                 RI=0;
                 if(data3!=TRR)     //�ӻ�û�о���
                     {
                      flag2=0;
                     }
                 
                 else{              //�ӻ�����
                       pf=0;        //��Ч��λ
                       key1=1;  
                       for(i=0;i<=9;i++)         //��������   
                         {
                           TB8=0;
                            SBUF=buf[i];
                            pf+=buf[i];
                            while(TI==0)
                                {
                                  ;
                                }
                             TI=0;
                           } 
                         TB8=0;
                         SBUF=pf;                //����Ч���
                         while(TI==0)
                              {
                                ;
                              }
                         TI=0;
                         key1=0;
                         while(RI==0)            //�������ܴӻ��Ƿ���ȷ��������
                               {
                                ;
                               }
                         data2=SBUF;
                         RI=0;
                         if(data2==0xcc)         //�����ȷ��������ͨ��
                            {
                             flag2=3;            //ͨ�Ž�����־
                            }
                         else{
                             flag2=0;            //�������ȷ����ͨ��------������ͨ�ű�־
                             }
                       }
                   }
             if(TRR==0x02)
                 {               //�ǽ��ܴӻ����ݱ�־------��TRR=0X0
                    TB8=0;
                    key1=1; 
                    SBUF=TRR;                    //���ͽ��ܱ�־0X02
                    while(TI==0)
                        {
                          ;
                        }
                    TI=0;
                    key1=0;
                    while(RI==0)                 //���ܴӻ���״̬
                       {
                           ;
                        }
                     data3=SBUF;
                     RI=0;
                     if(data3!=TRR)              //�ӻ�û�о���
                          {
                             flag2=0;
                          }
                   
                     else{ key1=0;                     //�ӻ�����---������������
                           pf=0;
                           for(i=0;i<=2;i++)
                            { 
                              while(RI==0)
                                 {
                                   ;
                                  }
                              buf2[i]=SBUF;        //���ܴӻ����͵�����
                              pf+=buf2[i];
                              RI=0;
                            }
                           key1=0;
                           while(RI==0)            //���ܴӻ���Ч���
                                {
                                  ;
                                }
                            data2=SBUF;            
                            RI=0;
                            if(pf==data2)         //�Ƚ�Ч���
                              {
                                flag2=3;          //Ч�����ȷ��־
                              }
                            else{
                                  flag2=0;        //Ч��ʹ����־
                                 
                                }
                         }
                  }  
             
         }
    
 }

void  display(void)
{
     if(flag2==3)                  //���������ȷ��ʼ��ʾ
       {
        for(i=0;i<=2;i++)
          {
            P0=buf2[i];
            delay(50);
          }
       }
}

void main(void)
{
    delay(500);
    init();
    count=2;
    count1=2;
    while(1)
    {  
      while(count!=0) 
      { 
        count--;
        send(0x03,0x01);               //����---�ӻ�1���������Ӻ���
        send(0x03,0x02); 
         display(); 
      } 
      
      while(count1!=0)
        { count1--;
          send(0x04,0x01);               //����---�ӻ�1���������Ӻ���
          send(0x04,0x02); 
          display(); 
          
        }
       if(count1==0)
       {
        count1=2;
        count=2;
       }
     
      
    }
}