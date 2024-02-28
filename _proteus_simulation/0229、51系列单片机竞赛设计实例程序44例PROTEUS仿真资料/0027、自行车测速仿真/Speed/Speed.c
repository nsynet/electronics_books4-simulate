#include "d:\c51\reg51.h"
#include "d:\c51\intrins.h"


sbit LCM_RS=P3^0;
sbit LCM_RW=P3^1;
sbit LCM_EN=P3^7;

#define BUSY  		0x80              //��������
#define DATAPORT 	P1
#define uchar 		unsigned char
#define uint   		unsigned int
#define L			50

uchar str0[16],str1[16],count;
uint speed;
unsigned long time;

void ddelay(uint);
void lcd_wait(void);
void display();
void initLCM();
void WriteCommandLCM(uchar WCLCM,uchar BusyC);
void STR();
void account();


/*********��ʱK*1ms,12.000mhz**********/

void int0_isr(void) interrupt 0         /*ң��ʹ���ⲿ�ж�0,��P3.2��*/
{
    unsigned int temp;
	time=count;
    TR0=0;
	temp=TH0;
	temp=((temp << 8) | TL0);
    TH0=0x3c;
    TL0=0xaf;
	count=0;
    TR0=1;
	time=time*50000+temp;
}

void time0_isr(void) interrupt 1        /*ң��ʹ�ö�ʱ������1 */
{
   TH0 =0x3c;
   TL0 =0xaf;
   count++;
}

void main(void)
{
   	TMOD=0x01;                       /*TMOD T0ѡ�÷�ʽ1(16λ��ʱ) */
    IP|=0x01;                           /*INT0 �ж�����*/
    TCON|=0x11;                         /*TCON  EX0�½��ش���,����T0*/
    IE|=0x83;  
    TH0=0x3c;
    TL0=0xaf;
  
	initLCM();
   	WriteCommandLCM(0x01,1);		    //����ʾ��
	for(;;)
	{
		account();
		display();
	}
}

void account()
{
	unsigned long a; 
	if (time!=0)
	{
		a=L*360000000/time;
	}
	speed=a;
}



void STR()
{
	str0[0]='S';
	str0[1]='p';
	str0[2]='e';
    str0[3]='e';
	str0[4]='d';
	str0[5]=' ';	
	str0[6]=(speed%100000)/10000+0x30;
	str0[7]=(speed%10000)/1000+0x30;
	str0[8]=(speed%1000)/100+0x30;
	str0[9]='.';
	str0[10]=(speed%100)/10+0x30;
	str0[11]=speed%10+0x30;
	str0[12]='k';
	str0[13]='m';
	str0[14]='/';
	str0[15]='h';
}

void ddelay(uint k)
{
    uint i,j;
    for(i=0;i<k;i++)
    {
        for(j=0;j<60;j++)
        	{;}
    }
}
/**********дָ�LCD�Ӻ���************/

void WriteCommandLCM(uchar WCLCM,uchar BusyC)
{
    if(BusyC)lcd_wait();
	DATAPORT=WCLCM;
    LCM_RS=0;                   /* ѡ��ָ��Ĵ���*/
    LCM_RW=0;               	// дģʽ
    LCM_EN=1;
	_nop_();
	_nop_();
	_nop_();
    LCM_EN=0;

}

/**********д���ݵ�LCD�Ӻ���************/

void WriteDataLCM(uchar WDLCM)
{
    lcd_wait( );            //���æ�ź�
	DATAPORT=WDLCM;
    LCM_RS=1;               /* ѡ�����ݼĴ���  */
    LCM_RW=0;           	// дģʽ
    LCM_EN=1;
    _nop_();
	_nop_();
	_nop_();
    LCM_EN=0;
}

/***********lcd�ڲ��ȴ�����*************/

void lcd_wait(void)
{
    DATAPORT=0xff;	     //��LCDǰ����Ƭ������͵�ƽ,������LCDΪ�ߵ�ƽ,���ͻ,Proteus���������ʾ�߼���ɫ
	LCM_EN=1;
    LCM_RS=0;
    LCM_RW=1;
    _nop_();
    _nop_();
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

/**********LCD��ʼ���Ӻ���***********/
void initLCM( )
{
	DATAPORT=0;
	ddelay(15);
	WriteCommandLCM(0x38,0);    //������ʾģʽ���ã������æ�ź�
    ddelay(5);
    WriteCommandLCM(0x38,0);
    ddelay(5);
    WriteCommandLCM(0x38,0);
    ddelay(5);

    WriteCommandLCM(0x38,1);    //8bit���ݴ��ͣ�2����ʾ��5*7���ͣ����æ�ź�
    WriteCommandLCM(0x08,1);    //�ر���ʾ�����æ�ź�
    WriteCommandLCM(0x01,1);    //���������æ�ź�
    WriteCommandLCM(0x06,1);    //��ʾ����������ã����æ�ź�
    WriteCommandLCM(0x0c,1);    //��ʾ���򿪣���겻��ʾ������˸�����æ�ź�
}

/****��ʾָ�������һ���ַ��Ӻ���****/

void DisplayOneChar(uchar X,uchar Y,uchar DData)
{
    Y&=1;
    X&=15;
    if(Y)X|=0x40;               //��yΪ1����ʾ�ڶ��У�����ַ��+0X40
    X|=0x80;                    //ָ����Ϊ��ַ��+0X80
    WriteCommandLCM(X,0);
    WriteDataLCM(DData);
}

/*******��ʾָ�������һ���ַ��Ӻ���*****/

void DisplayListChar(uchar X,uchar Y,uchar *DData)
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


void display()
{

	STR(); 
	DisplayListChar(0,0,str0);
   	DisplayListChar(0,1,str1);
}
