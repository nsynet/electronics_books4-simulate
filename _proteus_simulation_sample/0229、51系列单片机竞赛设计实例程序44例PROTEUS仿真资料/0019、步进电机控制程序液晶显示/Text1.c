#include <reg51.h>
#define uchar unsigned char 
sbit P1_0=P1^0;sbit P1_1=P1^1;sbit P1_2=P1^2;sbit P1_3=P1^3;
sbit P1_4=P1^4;sbit P1_5=P1^5;sbit P1_6=P1^6;sbit P1_7=P1^7;
uchar RRR,flg,KKK; //RRR���ڵ��ٿ��ƣ�flg=0��ת��flg=1��ת; flg=2��ת��KKKΪP1��״̬�Ĵ�
uchar loop[2][4]={{0x0c,0x06,0x03,0x09},{0x09,0x03,0x06,0x0c}};
void loop1(void);
void loop2(void);
void step(void);

main()
{
uchar i,j;
TMOD=0x10;
TL1=0xe0;
TH1=0xb1;
IE=0;
while(1)
{
  if(KKK!=P1)           //��P1��ֵ�����仯�������ɼ��ź�
    loop1();
  if(flg!=2)            
  {
   for(i=0;i<=3;i++)
    {
     P0=loop[flg][i];
     for(j=0;j<=RRR;j++)
	 {step();}
	}
  }
}
}

void step(void)        //����20MS�ĵ�λ��ʱ��
{
TF1=0;
TR1=1;
while(TF1==0);
TR1=0;
TL1=0xe0;
TH1=0xb1;
}

void loop1(void)                 //�ɼ�˳ʱ�����ʱ���źţ�P1.6=1��˳ʱ�룬P1.7=1����ʱ��
{
KKK=P1;                          //�ݴ�P1��״̬       
if(P1_6==1)
 {flg=0;loop2();}
else if(P1_7==1)
 {flg=1;loop2();}
else
 flg=2;
}
void loop2(void)
{
  if(P1_0==1)
  RRR=5;

 else if(P1_1==1)
  RRR=8;

 else if(P1_2==1)
  RRR=11;

 else if(P1_3==1)
  RRR=14;

 else if(P1_4==1)
  RRR=17;

 else if(P1_5==1)
  RRR=20;
}










