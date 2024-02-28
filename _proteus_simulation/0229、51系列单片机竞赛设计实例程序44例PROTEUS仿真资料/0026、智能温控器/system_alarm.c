/*******************************************************************
                          �����¿���

�������������¿ؿ��ش�ʱ������û����¶ȴ����趨�¶ȣ���̵�������
		  ������ѹ��������������û����¶�С���趨�¶ȣ���̵����ͷţ�
		  ѹ����ֹͣ������
          ��ʵ�����Ӧ���ڶ��¶ȿ��ƾ���Ҫ���Ǻܸߵĳ��ϣ����磬���֣�
		  ����䣬�յ����緹���ȡ��������ͨѶ�ӿڣ��������ɶ���¶ȼ�
          ����ϵͳ�����м�ǿ����չ�ԡ�

���ߣ�    yiwei  "shannxi university of technolog " 
���ڣ�    2007.4.1��proteus�Ϸ���ɹ���
          2007.4.3��·�庸�ӵ��Գɹ�

�ο����ϣ�[1] ���˻� ���� ����Ƭ�����ܲ�Ʒc�������ʵ����⡷
          [2]������������ 2006.11
          [3] www.proteus.com

ע�⣺ ���ĵ�Ϊ���������Ҫ�����������֤����Ҫ���һ�º���
        

void lcd_wait(void)
{
    DATAPORT=0xff;	     
	LCM_EN=1;
    LCM_RS=0;   			
    LCM_RW=1;   			
    _nop_();
    while(DATAPORT&BUSY)��
   	LCM_EN=0;
	
}

*******************************************************************/

#include<reg51.h>
#include<intrins.h>
#include <absacc.h>
#define uchar unsigned char
#define uint   unsigned int

#define BUSY  0x80                               //lcdæ����־
#define DATAPORT P0                              //����P0��ΪLCDͨѶ�˿�
#define PLAYE_ADDR XBYTE[0XBFFF]                 //����������ַ

sbit RED_ALARM=P1^0;           					 //��ɫָʾ��
sbit WRITE_ALARM=P1^1;          				//��ɫָʾ��
sbit GREEN_ALARM=P1^2;          				//��ɫָʾ��
sbit P1_4=P1^4;                				    //ʱ�ӵ���
sbit P1_5=P1^5;                 				//ʱ�Ӽ�
sbit P1_6=P1^6;                 				//ʱ�Ӽ�

sbit DQ = P1^7;                 				//����ds18b20ͨ�Ŷ˿� 
sbit LCM_RS=P2^0;								//����/�����
sbit LCM_RW=P2^1;								//��/дѡ���
sbit LCM_EN=P2^2;               				//LCDʹ���ź�
sbit ad_busy=P3^2;              				//adc�жϷ�ʽ�ӿ�
sbit RECLED_EOC=P3^5;           				//ISD1420����������ѯ��־
sbit OUT=P3^7;

uchar ad_data;                  				//ad����ֵ�洢						
uchar seconde=0;                				//���岢��ʼ��ʱ�ӱ���
uchar minite=0;
uchar hour=12;
uchar mstcnt=0;
uchar temp1,temp2,temp;         			    //�¶���ʾ����
uchar t,set;
uchar K;
bit ON_OFF=0;
bit outflag;

uchar code str0[]={"---  :  :  ---  "};
uchar code str1[]={"SET:  C SA:  . C"};

void delay_LCM(uint);             											//LCD��ʱ�ӳ���
void initLCM( void);               											//LCD��ʼ���ӳ���
void lcd_wait(void);              											//LCD���æ�ӳ���
void WriteCommandLCM(uchar WCLCM,uchar BusyC);                              //дָ�ICM�Ӻ���
void WriteDataLCM(uchar WDLCM);                                             //д���ݵ�LCM�Ӻ���
void DisplayOneChar(uchar X,uchar Y,uchar DData);                           //��ʾָ�������һ���ַ��Ӻ���
void DisplayListChar(uchar X,uchar Y,uchar code *DData);                    //��ʾָ�������һ���ַ��Ӻ���
void init_timer0(void);               										//��ʱ����ʼ��
void displayfun1(void);
void displayfun2(void);
void displayfun3(void);
void displayfun4(void);
void keyscan(void );                									    //����ɨ���ӳ���
void set_adj(void);
void inc_key(void);
void dec_key(void);
void delay_18B20(unsigned int i);
void Init_DS18B20(void) ;
uchar ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void ReadTemperature(void);
void ad0809(void);
void playalarm(void); 


/*********��ʱK*1ms,12.000mhz**********/

void delay_LCM(uint k)
{
    uint i,j;
    for(i=0;i<k;i++)
    {
        for(j=0;j<60;j++)
        	{;}
    }
}   
/**********дָ�ICM�Ӻ���************/

void WriteCommandLCM(uchar WCLCM,uchar BusyC)
{
    if(BusyC)lcd_wait();
	DATAPORT=WCLCM;
    LCM_RS=0;                   // ѡ��ָ��Ĵ���
    LCM_RW=0;               	// дģʽ	
    LCM_EN=1;    
	_nop_();   
	_nop_();
	_nop_(); 
    LCM_EN=0;  
}

/**********д���ݵ�LCM�Ӻ���************/

void WriteDataLCM(uchar WDLCM)
{ 
    lcd_wait( );            //���æ�ź�    
	DATAPORT=WDLCM;
    LCM_RS=1;               // ѡ�����ݼĴ���
    LCM_RW=0;           	// дģʽ
    LCM_EN=1;
    _nop_();
	_nop_();
	_nop_();
    LCM_EN=0;
}

/***********lcm�ڲ��ȴ�����*************/

void lcd_wait(void)
{
    DATAPORT=0xff;	     
	LCM_EN=1;
    LCM_RS=0;   			
    LCM_RW=1;   			
    _nop_();
    while(DATAPORT&BUSY)
	{  LCM_EN=0;
	   _nop_();
	   _nop_();
	   LCM_EN=1;
	   _nop_();
	   _nop_();
	   }
   	LCM_EN=0;
	
}

/**********LCM��ʼ���Ӻ���***********/

void initLCM( )
{   
	DATAPORT=0;	
	delay_LCM(15);
	WriteCommandLCM(0x38,0);    //������ʾģʽ���ã������æ�ź�
    delay_LCM(5); 
    WriteCommandLCM(0x38,0);
    delay_LCM(5); 
    WriteCommandLCM(0x38,0);
    delay_LCM(5); 

    WriteCommandLCM(0x38,1);    //8bit���ݴ��ͣ�2����ʾ��5*7���ͣ����æ�ź�
    WriteCommandLCM(0x08,1);    //�ر���ʾ�����æ�ź�
    WriteCommandLCM(0x01,1);    //���������æ�ź�
    WriteCommandLCM(0x06,1);    //��ʾ����������ã����æ�ź�
    WriteCommandLCM(0x0c,1);    //��ʾ���򿪣���겻��ʾ������˸�����æ�ź�
}

/****************��ʾָ�������һ���ַ��Ӻ���*************/

void DisplayOneChar(uchar X,uchar Y,uchar DData)
{
    Y&=1;
    X&=15;
    if(Y)X|=0x40;               //��yΪ1����ʾ�ڶ��У�����ַ��+0X40
    X|=0x80;                    //ָ����Ϊ��ַ��+0X80
    WriteCommandLCM(X,0);
    WriteDataLCM(DData);
}

/***********��ʾָ�������һ���ַ��Ӻ���***********/

void DisplayListChar(uchar X,uchar Y,uchar code *DData)
{
    uchar ListLength=0;
    Y&=0x01;
    X&=0x0f;
    while(X<16)
    {
        DisplayOneChar(X,Y,DData[ListLength]);
        ListLength++;
        X++;
    }
}

/***********ds18b20�ӳ��Ӻ���������12MHz ��*******/ 

void delay_18B20(unsigned int i)
{
	while(i--);
}

/**********ds18b20��ʼ������**********************/

void Init_DS18B20(void) 
{
	 unsigned char x=0;
	 DQ = 1;          //DQ��λ
	 delay_18B20(8);  //������ʱ
	 DQ = 0;          //��Ƭ����DQ����
	 delay_18B20(80); //��ȷ��ʱ ���� 480us
	 DQ = 1;          //��������
	 delay_18B20(14);
	 x=DQ;            //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	 delay_18B20(20);
}

/***********ds18b20��һ���ֽ�**************/  

unsigned char ReadOneChar(void)
{
	uchar i=0;
	uchar dat = 0;
	for (i=8;i>0;i--)
	 {
		  DQ = 0; // �������ź�
		  dat>>=1;
		  DQ = 1; // �������ź�
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(4);
	 }
 	return(dat);
}

/*************ds18b20дһ���ֽ�****************/  

void WriteOneChar(uchar dat)
{
 	unsigned char i=0;
 	for (i=8; i>0; i--)
 	{
  		DQ = 0;
 		DQ = dat&0x01;
    	delay_18B20(5);
 		DQ = 1;
    	dat>>=1;
 }
}

/**************��ȡds18b20��ǰ�¶�************/

void ReadTemperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned char t=0;

	Init_DS18B20();
	WriteOneChar(0xCC);    	// ����������кŵĲ���
	WriteOneChar(0x44); 	// �����¶�ת��

	delay_18B20(100);       // this message is wery important

	Init_DS18B20();
	WriteOneChar(0xCC); 	//����������кŵĲ���
	WriteOneChar(0xBE); 	//��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�

	delay_18B20(100);

	a=ReadOneChar();    	//��ȡ�¶�ֵ��λ
	b=ReadOneChar();   		//��ȡ�¶�ֵ��λ
	temp1=b<<4;
	temp1+=(a&0xf0)>>4;
	temp2=a&0x0f;

   temp=((b*256+a)>>4);    //��ǰ�ɼ��¶�ֵ��16��ʵ���¶�ֵ


}

/***************Һ����ʾ�Ӻ���1������ʾ*****************/

void displayfun1(void)
{	
	WriteCommandLCM(0x0c,1);   					 //��ʾ���򿪣���겻��ʾ������˸�����æ�ź�	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
											    	  
	DisplayOneChar(3,0,hour/10+0x30);		    //Һ������ʾСʱ
	DisplayOneChar(4,0,hour%10+0x30);

	DisplayOneChar(6,0,minite/10+0x30);			//Һ������ʾ��
	DisplayOneChar(7,0,minite%10+0x30);
	
	DisplayOneChar(9,0,seconde/10+0x30);	    //Һ������ʾ��
	DisplayOneChar(10,0,seconde%10+0x30);

	DisplayOneChar(4,1,K/10+0x30);			    //Һ������ʾ�趨���¶�
	DisplayOneChar(5,1,K%10+0x30);
 
   	DisplayOneChar(11,1,temp1/10+0x30);         //Һ������ʾ��õ��¶�  
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

	if(ON_OFF==0)						      //���¿ر�־Ϊ0
	{
		DisplayOneChar(14,0,0x4f);			   // Һ������ʾ�����µı�־
		DisplayOneChar(15,0,0x46);
	}
	else
	{
		DisplayOneChar(14,0,0x4f);			   // Һ������ʾ���µı�־
		DisplayOneChar(15,0,0x4e);
		if(outflag==1)
		    DisplayOneChar(0,0,0x7c);			   
	    else
			DisplayOneChar(0,0,0xef);
	}

	
}
/************Һ����ʾ�Ӻ���2***************/

void displayfun2(void)
{
	WriteCommandLCM(0x0c,1);                     //��ʾ���򿪣���겻��ʾ������˸�����æ�ź�	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
		
	DisplayOneChar(6,0,minite/10+0x30);
	DisplayOneChar(7,0,minite%10+0x30);
	
	DisplayOneChar(9,0,seconde/10+0x30);
	DisplayOneChar(10,0,seconde%10+0x30);

	DisplayOneChar(4,1,K/10+0x30);			   
	DisplayOneChar(5,1,K%10+0x30);
 
   	DisplayOneChar(11,1,temp1/10+0x30);         
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

   	WriteCommandLCM(0x0f,1);   					 //��ʾ���򿪣������ʾ����˸�����æ�ź�	
    DisplayOneChar(3,0,hour/10+0x30);
	DisplayOneChar(4,0,hour%10+0x30);
}

/**************Һ����ʾ�Ӻ���3*****************/

void displayfun3(void)
{
	WriteCommandLCM(0x0c,1);    				//��ʾ���򿪣���겻��ʾ������˸�����æ�ź�	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
	
	DisplayOneChar(3,0,hour/10+0x30);
	DisplayOneChar(4,0,hour%10+0x30); 

	DisplayOneChar(9,0,seconde/10+0x30);
	DisplayOneChar(10,0,seconde%10+0x30);

	DisplayOneChar(4,1,K/10+0x30);			   
	DisplayOneChar(5,1,K%10+0x30);

   	DisplayOneChar(11,1,temp1/10+0x30);         
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

   
	WriteCommandLCM(0x0f,1);   					 //��ʾ���򿪣������ʾ����˸�����æ�ź�
	DisplayOneChar(6,0,minite/10+0x30);
	DisplayOneChar(7,0,minite%10+0x30);

}

/**************Һ����ʾ�Ӻ���4 *****************/

void displayfun4(void)
{
	WriteCommandLCM(0x0c,1);    				//��ʾ���򿪣���겻��ʾ������˸�����æ�ź�	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);	
	
	DisplayOneChar(3,0,hour/10+0x30);
	DisplayOneChar(4,0,hour%10+0x30); 

	DisplayOneChar(6,0,minite/10+0x30);
	DisplayOneChar(7,0,minite%10+0x30);

	DisplayOneChar(9,0,seconde/10+0x30);
	DisplayOneChar(10,0,seconde%10+0x30);

	
   	DisplayOneChar(11,1,temp1/10+0x30);         
	DisplayOneChar(12,1,temp1%10+0x30);
	DisplayOneChar(14,1,temp2/10+0x30);

   
	WriteCommandLCM(0x0f,1);   					 //��ʾ���򿪣������ʾ����˸�����æ�ź�
	DisplayOneChar(4,1,K/10+0x30);			   
	DisplayOneChar(5,1,K%10+0x30);

}

/**************����ɨ���Ӻ���******************/

void keyscan(void)
{
	uchar xx;                                           //�ֲ�����
	P1=0xff;
	if(P1!=0xff)
	  {
	    delay_LCM(50);

		if(P1!=0xff)
		  {	
			xx=P1;
			switch(xx)					               // ���ݰ���״̬�����ò�ͬ���Ӻ���
			{
				case 0xfe:set_adj();       break;               
				case 0xfd:inc_key();       break;               
				case 0xfb:dec_key();       break;               
				case 0xf7:ON_OFF=!ON_OFF;  break;
				default:break;
			}
		  }
		
	  }
  
}

/**************�趨����ģʽ�Ӻ���****************/

void set_adj(void)
{
	delay_LCM(100);
	set++;
    if(set>=4)set=0;
		
}

/****************�����ӷ��Ӻ���******************/

void inc_key(void)
{
	delay_LCM(100);
		
	switch(set)
	{
		case 0:if(P1==0xf7)ON_OFF=!ON_OFF;       break;
		case 1:hour++;   if(hour>=23)hour=23;    break;
		case 2:minite++; if(minite>=59)minite=59;break;
		case 3:K++;if(K>=99)K=99;				 break; 
		default:break;
	}
		
}

/****************���������Ӻ���*****************/

void dec_key(void)
{
	delay_LCM(100);
	
	switch(set)
	{
	   	case 0:if(P1==0xf7)ON_OFF=!ON_OFF;    break;
		case 1:hour--;  if(hour<=0)hour=0;    break;
		case 2:minite--;if(minite<=0)minite=0;break;
		case 3:K--;if(K<=1)K=1;				  break; 
		default:break;
	}
		
}

/***************��ʱ��t0��ʼ��*******************/

void init_timer0(void)
{
	 TMOD=0x01;                                  //time0Ϊ��ʱ������ʽ1
     TH0=0x3c;                                   //Ԥ�ü�����ֵ
     TL0=0xb0;
     EA=1;   								
     ET0=1;          											
     TR0=1;          		
}

/***********��ʱ��t0�ж��Ӻ���**************/

void timer0(void) interrupt 1 using 0          //��ʱ��0��ʽ1��50ms�ж�һ��
{
     TH0=0x3c;
     TL0=0xb0;
     mstcnt++;
     if(mstcnt>=20 )  {seconde++; mstcnt=0; }
	 if(seconde>=60)  {minite++;  seconde=0;}
	 if(minite>=60 )  {hour++;    minite=0; }
	 if(hour>=24   )  {hour=0;}
	 keyscan( );                               //����ɨ��
}

/***********the main funtion*************/
    
void main(void)
{ 

    P1=0xff;                                   				//��ʼ��p1�ڣ�ȫ��Ϊ1       
	delay_LCM(500);	                                        //��ʱ500ms����
	initLCM( );                               				//LCD��ʼ��
	init_timer0( );	                           				//ʱ�Ӷ�ʱ��0��ʼ��	
    Init_DS18B20( ) ;                          				//DS18B20��ʼ��
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str1);  
                     	
    while (1)
    {   
       	keyscan();                                            //����ɨ��		
	    ReadTemperature();                                    //�¶Ȳɼ�
	    switch(set)                                           //LCD���ݹ���ģʽ��ʾ
		{
			case 0:displayfun1();delay_LCM(1000);break;       //����������ʾ
			case 1:displayfun2();delay_LCM(1000);break;       //����ʱ��ʾ
			case 2:displayfun3();delay_LCM(1000);break;       //��������ʾ
			case 3:displayfun4();delay_LCM(1000);break; 	  //�¶��趨
			default:break;
		} 	
		keyscan( );  	                                     //�൱����ʱ
		if(ON_OFF==1)      								     //���¿ر�־λ1�� ����LAMP����
		{
			if(temp1>=K+1){outflag=1;OUT=0;}
			if(temp1<K)
			{ 
				delay_LCM(1000);
				if(temp1<K){outflag=0;OUT=1;}		        //
			}
		}
		else{outflag=0;OUT=1;}
    }
	
}


