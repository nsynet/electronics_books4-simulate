#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit DQ=P3^7;//ds18b20�뵥Ƭ�����ӿ�
sbit RS=P3^0;
sbit RW=P3^1;
sbit EN=P3^2;

unsigned char code str1[]={"temperature:  "};
unsigned char code str2[]={"              "}; 

uchar data disdata[5];
uint tvalue;//�¶�ֵ
uchar tflag;//�¶�������־

/*************************lcd1602����**************************/
 void delay1ms(unsigned int ms)//��ʱ1���루������ȷ�ģ�
 {unsigned int i,j;
   for(i=0;i<ms;i++)
    for(j=0;j<100;j++);
 }

void wr_com(unsigned char com)//дָ��//
 {  delay1ms(1);
   RS=0;
   RW=0;
   EN=0;
   P2=com;
   delay1ms(1);
   EN=1;
   delay1ms(1);
   EN=0;
  }

void wr_dat(unsigned char dat)//д����//
{  delay1ms(1);;
   RS=1;
   RW=0;
   EN=0;
   P2=dat;
   delay1ms(1);
   EN=1;
   delay1ms(1);
   EN=0;
}

 void lcd_init()//��ʼ������//
{delay1ms(15);
  wr_com(0x38);delay1ms(5);
   wr_com(0x08);delay1ms(5);
    wr_com(0x01);delay1ms(5);
     wr_com(0x06);delay1ms(5);
      wr_com(0x0c);delay1ms(5);
}


 void display(unsigned char *p)//��ʾ//
{
while(*p!='\0')
{
wr_dat(*p);
p++;
delay1ms(1);
}
}

  init_play()//��ʼ����ʾ
  { lcd_init();
    wr_com(0x80);
	 display(str1);
	 wr_com(0xc0);
	 display(str2);
   }

/******************************ds1820����***************************************/
 void delay_18B20(unsigned int i)//��ʱ1΢��
{
 	while(i--);
}

void ds1820rst()/*ds1820��λ*/
 {  unsigned char x=0;
	 DQ = 1;          //DQ��λ
	 delay_18B20(4);  //��ʱ
	 DQ = 0;          //DQ����
	 delay_18B20(100); //��ȷ��ʱ����480us
	 DQ = 1;          //����
	 delay_18B20(40);	 
   }  
  
   uchar ds1820rd()/*������*/
  { unsigned char i=0;
	 unsigned char dat = 0;
	 for (i=8;i>0;i--)
	 {   DQ = 0; //�������ź�
		  dat>>=1;
		  DQ = 1; //�������ź�
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(10);
	 }
 	return(dat);
  }

  void ds1820wr(uchar wdata)/*д����*/
  {unsigned char i=0;
    for (i=8; i>0; i--)
   { DQ = 0;
     DQ = wdata&0x01;
     delay_18B20(10);
     DQ = 1;
     wdata>>=1;
   }
 }
  
 

  read_temp()/*��ȡ�¶�ֵ��ת��*/
 {uchar a,b;
  ds1820rst();    
  ds1820wr(0xcc);//*���������к�*/
  ds1820wr(0x44);//*�����¶�ת��*/
  ds1820rst();    
  ds1820wr(0xcc);//*���������к�*/ 
  ds1820wr(0xbe);//*��ȡ�¶�*/ 
  a=ds1820rd();
  b=ds1820rd();
  tvalue=b;
  tvalue<<=8;
  tvalue=tvalue|a;
    if(tvalue<0x0fff)
   tflag=0;
    else
   {tvalue=~tvalue+1;
	 tflag=1;
   }
  tvalue=tvalue*(0.625);//�¶�ֵ����10������ȷ��1λС��
	return(tvalue);
  }

/*******************************************************************/
   void ds1820disp()//�¶�ֵ��ʾ
	{ uchar flagdat;
	  disdata[0]=tvalue/1000+0x30;//��λ��
     disdata[1]=tvalue%1000/100+0x30;//ʮλ��
     disdata[2]=tvalue%100/10+0x30;//��λ��
     disdata[3]=tvalue%10+0x30;//С��λ
    
     if(tflag==0)
	    flagdat=0x20;//���¶Ȳ���ʾ����
     else
       flagdat=0x2d;//���¶���ʾ����:-

     if(disdata[0]==0x30)
	   {disdata[0]=0x20;//�����λΪ0������ʾ
		 if(disdata[1]==0x30)
		  {disdata[1]=0x20;//�����λΪ0��ʮλΪ0Ҳ����ʾ
		  }
		}

	   wr_com(0xc0);
		wr_dat(flagdat);//��ʾ����λ
	   wr_com(0xc1);
	   wr_dat(disdata[0]);//��ʾ��λ
	   wr_com(0xc2);
	   wr_dat(disdata[1]);//��ʾʮλ 	
	   wr_com(0xc3);
	   wr_dat(disdata[2]);//��ʾ��λ 	
	   wr_com(0xc4);
	   wr_dat(0x2e);//��ʾС���� 	
	   wr_com(0xc5);
	   wr_dat(disdata[3]);//��ʾС��λ
   }
/********************������***********************************/
 void main()
 { init_play();//��ʼ����ʾ
   while(1)
	{read_temp();//��ȡ�¶�
    ds1820disp();//��ʾ
	 }
  }




