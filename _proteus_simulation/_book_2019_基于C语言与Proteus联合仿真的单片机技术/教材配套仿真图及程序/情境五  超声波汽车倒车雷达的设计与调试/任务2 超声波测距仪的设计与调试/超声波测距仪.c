//***********************************************************************************************************
//����������ǣ��������ʾ
//***********************************************************************************************************	    
#include<reg51.h>
#include <intrins.h>

#define seg P0	   //�Ӷ����
#define pianxuan P3//��Ƭѡ

sbit TX=P1^5;	   //�ӳ�����ģ�飬���źŸ�������
sbit RX=P1^6;	   //�ӳ�����ģ�飬���ճ������ĸߵ�ƽ�ź�

char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98,0xbf}; //����
char code pianxuan_lab[]={0xfe,0xfd,0xfb,0xf7};		  //Ƭѡ�ź�

int gewei;		   //���λ����Ϣ
int shiwei;	   //��ʮλ����Ϣ
int baiwei;	   //���λ����Ϣ
int qianwei;	   //��ǧλ����Ϣ
unsigned long juli;	//ʵ�ʳ�������������
int time2ms;		   //2ms�Ĵ���
int time;			   //������ʱ��
bit t0_flag;		   //T0�����־λ
int weizhi;			   //�����Ƭѡʱ��λ��

saomiao();			   //ɨ���ӳ���
jisuan();			   //��������ӳ���

main()
{
    RX=1;			   //��Ϊ����ˣ�����Ϊ1

    TMOD=0x11;		   //��T0,T1Ϊ��ʱ����ʽ1
	TH0=0;			   //T0��ʼֵΪ0�����ر�ʱ��TH0��TL0����ֵ���Ǵ�T0�����ص�ʱ��
	TL0=0;             //
	TH1=(65536-50000)/256;//50MS��ʱ
	TL1=(65536-50000)%256;
	ET0=1;             //����T0�ж�
	ET1=1;			   //����T1�ж�
	TR1=1;			   //������ʱ��1
	EA=1;			   //�������ж�

	while(1)		   //����ѭ��
	{	

	if(RX==1)
	     {
		 TR0=1;			    //��������
	     while(RX==1);			//��RXΪ1�������ȴ�
	     TR0=0;				//�رռ���
         jisuan();			//����
		 }

	
	}

}


saomiao()
{	seg=0xff;
	pianxuan=pianxuan_lab[weizhi];
	
		 if(weizhi==0)seg=tab[gewei];
		 if(weizhi==1)seg=tab[shiwei];
		 if(weizhi==2)seg=tab[baiwei]&0x7f;		//��С����
		 if(weizhi==3)seg=0xff;	//����ʾ
				 	
	weizhi++;
	if(weizhi==4)weizhi=0;

}	
	

jisuan()						//
{
	 time=TH0*256+TL0;			//���ʱ��
	 TH0=0;
	 TL0=0;
	
	 juli=(time*1.7)/100;     //�������
	
	  baiwei=juli%1000/100;
	  shiwei=juli%1000%100/10;
	  gewei=juli%1000%100%10;
	
}

void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
{
    t0_flag=1;							 //�ж������־
}

void  zd3()  interrupt 3 		 //T1�ж�����ɨ������ܺͼ�800MS����ģ��
{
     int c;	 
	 TH1=0xf8;
	 TL1=0x30;
	 saomiao();
	 time2ms++;					 //
	 if(time2ms>=400)			 //
	 {
	  time2ms=0;
	  TX=1;			                //800MS  ����һ��ģ��//***********����ʱ��ʱ����	  
	  for(c=0;c<20;c++)			//
	  {_nop_();} 					//	  
	  TX=0;							//800MS  ����һ��ģ��//***********����ʱ��ʱ����
	 }
	
}

