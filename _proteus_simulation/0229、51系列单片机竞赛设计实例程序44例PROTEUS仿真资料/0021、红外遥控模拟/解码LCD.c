/*******************************************************************/
//Name of this design:     LCD show Electric Clock
//Author:                  Huangxiang
//Date:                    2007-10-02
/*******************************************************************/

#include <reg51.h>
#include <intrins.h>
#include <string.h>
#include <absacc.h>
#define uchar  unsigned char
#define uint   unsigned int

#define BUSY  0x80                               //lcdæ����־
#define DATAPORT P0                             //����P0��ΪLCDͨѶ�˿�

sbit light=P1^3;
sbit LCM_RS=P2^0;								 //����/�����
sbit LCM_RW=P2^1;								 //��/дѡ���
sbit LCM_EN=P2^2;
						

void delay_LCM(uint);             											//LCD��ʱ�ӳ���
void lcd_wait(void);              											//LCD���æ�ӳ���
void WriteCommandLCM(uchar WCLCM,uchar BusyC);                              //дָ�ICM�Ӻ���
void WriteDataLCM(uchar WDLCM);                                             //д���ݵ�LCM�Ӻ���
void DisplayOneChar(uchar X,uchar Y,uchar DData);                           //��ʾָ�������һ���ַ��Ӻ���
void initLCM( void);               											//LCD��ʼ���ӳ���
void DisplayListChar(uchar X,uchar Y, unsigned char *DData);                    //��ʾָ�������һ���ַ��Ӻ���


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
/**********дָ�LCM�Ӻ���************/

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
    lcd_wait( );                //���æ�ź�
	DATAPORT=WDLCM;
    LCM_RS=1;                   // ѡ�����ݼĴ���
    LCM_RW=0;           	    // дģʽ
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
uchar mx,my;
	my=Y&1;
	mx=X&0xf;
    if(my>0)mx+=0x40;               //��yΪ1����ʾ�ڶ��У�����ַ��+0X40
    mx+=0x80;                    //ָ����Ϊ��ַ��+0X80
    WriteCommandLCM(mx,0);
    WriteDataLCM(DData);
}

/***********��ʾָ�������һ���ַ��Ӻ���***********/

void DisplayListChar(uchar X,uchar Y, unsigned char *DData)
{
    uchar i=0,n;
    Y&=0x01;
    X&=0x0f;
	n=strlen(DData);
    while(i<n)
    {
        DisplayOneChar(X,Y,DData[i]);
        i++;
        X++;
    }
}

