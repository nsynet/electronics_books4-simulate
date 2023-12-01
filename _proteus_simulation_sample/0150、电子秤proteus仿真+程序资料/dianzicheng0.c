/********************************************************
                   ѹ��������
ϵͳ����;����  15--115kPAѹ���ź�
         ���  00h--ffh�����źţ�adc0832��
         ��LCD����ʾʵ�ʵ�ѹ��ֵ����������򱨾�

���������ȱ任��ʽ��    y=(115-15)/(243-13)*X+15kpa   

���ߣ�
��λ��
���ڣ�2008.3.7

********************************************************/

#include<reg51.h>
#include<intrins.h>
#include <absacc.h>
#include <math.h>

#define uchar unsigned char
#define uint   unsigned int
#define BUSY  0x80                               //��������
#define DATAPORT P0


//ADC0832������
sbit ADCS =P3^5;  //ADC0832 chip seclect
sbit ADDI =P3^7;  //ADC0832 k in
sbit ADDO =P3^7;  //ADC0832 k out
sbit ADCLK =P3^6;  //ADC0832 clock signal

sbit LCM_RS=P2^0;
sbit LCM_RW=P2^1;
sbit LCM_EN=P2^2;

uchar ad_data;                                    //����ֵ�洢
sbit Alarm_led_red =P3^1;                         //����ѹ�����������ֵ��ɫled��������
sbit Alarm_led_green=P3^2;                        //����ѹ����������Сֵ��ɫled��������
                          //adc����ֵ�洢��Ԫ
char press_data;                                  //��ȱ任�洢��Ԫ
unsigned char ad_alarm;                           //����ֵ�洢��Ԫ
unsigned char press_ge=0;                        //��ʾֵ��λ
unsigned char press_shifen=0;                        //��ʾֵʮλ
unsigned char press_baifen=0;                         //��ʾֵ��λ
unsigned char press_qianfen=0;                        //��ʾֵʮ��λ

uchar code str0[]={"Weight:  .   Kg "};
uchar code str1[]={"Make by GUO TAO "};
uchar code str2[]={"Price:          "};
uchar code str3[]={"Total:          "};
void delay(uint);
void lcd_wait(void);
void delay_LCM(uint);             											//LCD��ʱ�ӳ���
void initLCM( void);               											//LCD��ʼ���ӳ���
void lcd_wait(void);              											//LCD���æ�ӳ���
void WriteCommandLCM(uchar WCLCM,uchar BusyC);                              //дָ�ICM�Ӻ���
void WriteDataLCM(uchar WDLCM);                                             //д���ݵ�LCM�Ӻ���
void DisplayOneChar(uchar X,uchar Y,uchar DData);                           //��ʾָ�������һ���ַ��Ӻ���
void DisplayListChar(uchar X,uchar Y,uchar code *DData);					 //��ʾָ�������һ���ַ��Ӻ���
  void keyscan();                   
void display(void);                                                         //ϵͳ��ʾ�Ӻ���
uchar Adc0832(unsigned char channel);															
void alarm(void);
void data_pro(void);


/**********main funcation************/

void main(void)
{ 
    delay(500);                      //ϵͳ��ʱ500ms����
//	ad_data=0;                       //����ֵ�洢��Ԫ��ʼ��Ϊ0
   	initLCM( );
        
   	WriteCommandLCM(0x01,1);		    //����ʾ��
    DisplayListChar(0,0,str0);
   	DisplayListChar(0,1,str2);
 
	while(1)
    {
	   ad_data =Adc0832(0);	   //����ֵ�洢��Ԫ��ʼ��Ϊ0
	   
	    alarm();
	
		data_pro();
		
		display();
				 
	}
}


/*********��ʱK*1ms,12.000mhz**********/

void delay(uint k)
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
    lcd_wait( );             //���æ�ź�    
	DATAPORT=WDLCM;
    LCM_RS=1;                // ѡ�����ݼĴ���
    LCM_RW=0;           	 // дģʽ
    LCM_EN=1;
    _nop_();
	_nop_();
	_nop_();
    LCM_EN=0;
}

/***********lcm�ڲ��ȴ�����*************/

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

/**********LCM��ʼ���Ӻ���***********/

void initLCM( )
{   
	DATAPORT=0;	
	delay(15);
	WriteCommandLCM(0x38,0);    //������ʾģʽ���ã������æ�ź�
    delay(5); 
    WriteCommandLCM(0x38,0);
    delay(5); 
    WriteCommandLCM(0x38,0);
    delay(5); 

    WriteCommandLCM(0x38,1);    //8bit���ݴ��ͣ�2����ʾ��5*7���ͣ����æ�ź�
    WriteCommandLCM(0x08,1);    //�ر���ʾ�����æ�ź�
    WriteCommandLCM(0x01,1);    //���������æ�ź�
    WriteCommandLCM(0x06,1);    //��ʾ����������ã����æ�ź�
    WriteCommandLCM(0x0c,1);    //��ʾ���򿪣���겻��ʾ������˸�����æ�ź�
}

/****��ʾָ�������һ���ַ��Ӻ���****/

void DisplayOneChar(uchar X,uchar Y,uchar DData)

{
   Y&=0x01;
    X&=0x0f;
    if(Y)X|=0x40;               //��yΪ1����ʾ�ڶ��У�����ַ��+0X40
    X|=0x80;                    //ָ����Ϊ��ַ��+0X80
    WriteCommandLCM(X,1);
    WriteDataLCM(DData);
}

/*******��ʾָ�������һ���ַ��Ӻ���*****/
 
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

 /*****************ϵͳ��ʾ�Ӻ���*****************/

void display(void)
{
   	WriteCommandLCM(0x0c,1);    				//��ʾ���򿪣���겻��ʾ������˸�����æ�ź�	
	DisplayListChar(0,0,str0);	
	DisplayListChar(0,1,str2);	


	DisplayOneChar(8,0,press_ge+0x30);
	DisplayOneChar(10,0,press_shifen+0x30);
	DisplayOneChar(11,0,press_baifen+0x30);
    DisplayOneChar(12,0,press_qianfen+0x30);
	delay(1000);                               //�ȶ���ʾ
}
/************
��ADC0832����
************/

//�ɼ�������
uchar Adc0832(unsigned char channel)     //ADת�������ؽ��
{
    uchar i=0;
    uchar j;
    uint dat=0;
    uchar ndat=0;

    if(channel==0)channel=2;
    if(channel==1)channel=3;
    ADDI=1;
    _nop_();
    _nop_();
    ADCS=0;//����CS��
    _nop_();
    _nop_();
    ADCLK=1;//����CLK��
    _nop_();
    _nop_();
    ADCLK=0;//����CLK��,�γ��½���1
    _nop_();
    _nop_();
    ADCLK=1;//����CLK��
    ADDI=channel&0x1;
    _nop_();
    _nop_();
    ADCLK=0;//����CLK��,�γ��½���2
    _nop_();
    _nop_();
    ADCLK=1;//����CLK��
    ADDI=(channel>>1)&0x1;
    _nop_();
    _nop_();
    ADCLK=0;//����CLK��,�γ��½���3
    ADDI=1;//����������� 
    _nop_();
    _nop_();
    dat=0;
    for(i=0;i<8;i++)
    {
        dat|=ADDO;//������
        ADCLK=1;
        _nop_();
        _nop_();
        ADCLK=0;//�γ�һ��ʱ������
        _nop_();
        _nop_();
        dat<<=1;
        if(i==7)dat|=ADDO;
    }  
    for(i=0;i<8;i++)
    {
        j=0;
        j=j|ADDO;//������
        ADCLK=1;
        _nop_();
        _nop_();
        ADCLK=0;//�γ�һ��ʱ������
        _nop_();
        _nop_();
        j=j<<7;
        ndat=ndat|j;
        if(i<7)ndat>>=1;
    }
    ADCS=1;//����CS��
    ADCLK=0;//����CLK��
    ADDO=1;//�������ݶ�,�ص���ʼ״̬
    dat<<=8;
    dat|=ndat;
    return(dat);            //return ad k
}


void data_pro(void)
{
      unsigned int temp;
      float  press;	   		  

	  if(14<ad_data<243)			               //��ѹ��ֵ����15kpa��115kpa֮��ʱ����ѭ���Ա任
	 	{			    
		    int vary=ad_data;						//y=(115-15)/(243-13)*X+15kpa			
			press=((10.0/23.0)*vary)+9.3;			//����ʱ����ֵΪ9.3
														  
			temp=(int)(press*10);	                //�Ŵ�10�������ں���ļ���
	   									    	
		    											
			press_ge=temp/1000;			     	//ȡѹ��ֵ��λ
			press_shifen=(temp%1000)/100;		    	//ȡѹ��ֵʮλ
			press_baifen=((temp%1000)%100)/10;	    	//ȡѹ��ֵ��λ
			press_qianfen=((temp%1000)%100)%10;			//ȡѹ��ֵʮ��λ

	   	   }	    
			 
}
/*****************�����Ӻ���*******************/

void alarm(void)
{
	 if(ad_data>=243)                           //�����ǰѹ��ֵ����115kpa��

          {  Alarm_led_red=0; }                 //������red led����
        
	  else
	     {	  Alarm_led_red=1; }		        //�ر�red led ����
		   
	
	  if(ad_data<=14)							//�����ǰѹ��ֵС��16kpa

	     {  Alarm_led_green=0;  }               //������green led����

      else
	     {   Alarm_led_green=1; }      			//�ر�green  led ����
         
}



