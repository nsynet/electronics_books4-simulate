#include<reg51.h>
#include<intrins.h>
#include <absacc.h>
#include <math.h>

#define uchar unsigned char
#define uint   unsigned int
#define BUSY  0x80          //��������
#define DATAPORT P0


//ADC0832������
sbit ADCS =P3^5;  //ADC0832 chip seclect
sbit ADDI =P3^7;  //ADC0832 k in
sbit ADDO =P3^7;  //ADC0832 k out
sbit ADCLK =P3^6;  //ADC0832 clock signal

sbit LCM_RS=P2^0;
sbit LCM_RW=P2^1;
sbit LCM_EN=P2^2;

uchar ad_data,key;
uchar rrr=0xff;
uchar alldata[12]={0};
uchar love[14];
uchar exit=0,yes=0,kind=0,fu=0,pfu=0,position1=0,position2=0;
unsigned long  data1=0,data2=0,data3=0,ddata=0;    //����ֵ�洢
sbit Alarm_led_red =P3^0;                         //�����������������ֵ��ɫled��������
sbit Alarm_led_green=P3^1;                        //�������������Сֵ��ɫled��������
//adc����ֵ�洢��Ԫ
char press_data;                                  //��ȱ任�洢��Ԫ
unsigned char ad_alarm;                           //����ֵ�洢��Ԫ
unsigned char press_ge=0;                        //��ʾֵ��λ
unsigned char press_shifen=0;                      //��ʾֵʮλ
unsigned char press_baifen=0;                       //��ʾֵ��λ
unsigned char press_qianfen=0;                      //��ʾֵʮ��λ

uchar code str0[]={"Weight:  .   Kg "};
uchar code str2[]={"Price: "};
uchar code str3[]={"Total:          "};
void delay(uint);
void lcd_wait(void);
void delay_LCM(uint);             				    //LCD��ʱ�ӳ���
void initLCM( void);               					//LCD��ʼ���ӳ���
void lcd_wait(void);              					//LCD���æ�ӳ���
void WriteCommandLCM(uchar WCLCM,uchar BusyC);      //дָ�ICM�Ӻ���
void WriteDataLCM(uchar WDLCM);                     //д���ݵ�LCM�Ӻ���
void DisplayOneChar(uchar X,uchar Y,uchar DData);        //��ʾָ�������һ���ַ��Ӻ���
void DisplayListChar(uchar X,uchar Y,uchar code *DData); //��ʾָ�������һ���ַ��Ӻ���
void error(void);
unsigned long shi(uchar k);
void out(void);                     
uchar keyscan(void);                   
void display(void); 
void  display(uchar); 
void  keydisplay(uchar);
void  prodis(void);	   
void  clear(void);
void  datapc(void);
void remove0(void);
void  data3dis(void);                                       //ϵͳ��ʾ�Ӻ���
uchar Adc0832(unsigned char channel);															
void alarm(void);
void data_pro(void);


/**********main funcation************/

void main(void)
{ 
    delay(500);                      //ϵͳ��ʱ500ms����
	ad_data=0;                       //����ֵ�洢��Ԫ��ʼ��Ϊ0
   	initLCM( );
        
   	WriteCommandLCM(0x01,1);		    //����ʾ��
    DisplayListChar(0,0,str0);
	 WriteCommandLCM(0x01,0); 
   	DisplayListChar(0,1,str2);
 
	while(1)
    {
	   ad_data =Adc0832(0);	   //����ֵ�洢��Ԫ��ʼ��Ϊ0
	   alarm();
       data_pro();
	   display();
	   key=keyscan();
	   delay(5);
	   if(exit==1)
		  keydisplay(key);	 
	 }

 }
/*********��ʱK*1ms,12.000Mhz**********/

void delay(uint k)
{
    uint i,j;
    for(i=0;i<k;i++)
     for(j=0;j<60;j++);
      
}   
/**********дָ�ICM�Ӻ���************/

void WriteCommandLCM(uchar WCLCM,uchar BusyC)
{
    if(BusyC)
	lcd_wait();
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
void error(void)
{
  uchar derror[8]={'E','R','R','O','R','!','!','!'};
  uchar k;
  for(k=0;k<=7;k++)
  {
   WriteCommandLCM(0xc8+k,0);
   WriteDataLCM(derror[k]);
   DisplayOneChar(7,1,derror[k]);
   delay(5);
  }
}

void out(void)
{
   uchar k;
   uchar dout[12]={'O','U','T',' ','O','F',' ','R','A','N','G','E'};
   for(k=0;k<=11;k++)
  {
   WriteCommandLCM(0xc4+k,0);
   WriteDataLCM(dout[k]);
   DisplayOneChar(7,1,dout[k]);
   delay(5);
  }
}

unsigned long shi(uchar n)
{
   int m=1;
   while(n!=0)
    {
     m=m*10;
     n--;
    }
 return(m);
}

     /*����ɨ���ӳ���*/
uchar keyscan()
{
  uchar i=0,j=0;
  P1=0xf0;
  if(((~P1) & 0xf0)!=0)
   {
     delay(10);
     if(((~P1) & 0xf0)!=0)
      {
        exit=1;
        P1=0xfe;
        while(((~P1) & 0x0f)!=0) 
        {
          if(((~P1) & 0xf0)!=0) 
          {
              switch((~P1) & 0xf0)
          {
          case 0x10:
          j=0;break;
          case 0x20:
          j=1;break;
          case 0x40:
          j=2;break;
          case 0x80:
          j=3;break;
          }
		
        return(4*i+j);
      }
      else
      {  
       P1=P1<<1;
       i++;
      }
   }
  }
}
exit=0;
return(key);
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
/**********************************������ʾ�Ӻ���**********************************/
void keydisplay(uchar C)
{
  WriteCommandLCM(0x0c,1); 
  DisplayListChar(0,1,str2);
 switch(C)
 {
	 case 0:clear();
	        break;
	 case 1:prodis();
	        alldata[rrr]=0;
	        WriteDataLCM('0');
	        break;
	 case 2:prodis();
	        WriteDataLCM('=');       
	        kind=kind+10;
	        position2=rrr;
	        datapc();
	        remove0();
	        data3dis();
	        break;
	 case 3:prodis();
	        kind=kind+1;             //�ӷ����㣬 kind=1
	        position1=rrr;
	        WriteDataLCM('+');
	        break;
	 case 4:prodis();
	        alldata[rrr]=1;
	        WriteDataLCM('1');
	        break;
	 case 5:prodis();
	        alldata[rrr]=2;
	        WriteDataLCM('2');
	        break;
	 case 6:prodis();
	        alldata[rrr]=3;
	        WriteDataLCM('3');
	        break;
	 case 7:prodis();
	        kind=kind+5;             //�������㣬 kind=5
	        position1=rrr;
	        WriteDataLCM('-');
	        break;
	 case 8:prodis();
	        alldata[rrr]=4;
	        WriteDataLCM('4');
	        break;
	 case 9:prodis();
	        alldata[rrr]=5;
	        WriteDataLCM('5');
	        break;
	 case 10:prodis();
	         alldata[rrr]=6;
	         WriteDataLCM('6');
	        break;
	 case 11:prodis();
	         kind=kind+25;             //�˷����㣬 kind=25
	         position1=rrr;
	         WriteDataLCM('*');
	         break;
	 case 12:prodis();
	         alldata[rrr]=7;
	         WriteDataLCM('7');
	         break;
	 case 13:prodis();
	         alldata[rrr]=8;
	         WriteDataLCM('8');
	         break;
	 case 14:prodis();
	         alldata[rrr]=9;
	         WriteDataLCM('9'); 
	         break;
	 case 15:prodis();
	         kind=kind+125;              //�������㣬 kind=125
	         position1=rrr;
	         WriteDataLCM('/');   
	         break;
	 default:
	 break;
	 }
    }

void datapc(void)
{
  uchar k;
  if((position1==0) || (position2==(position1+1)))
       yes=1;
  else
   {
    for(k=0;k<position1;k++)
    {
      ddata=shi(position1-1-k);
      data1=data1+(alldata[k])*ddata;  
    }
    for(k=position1+1;k<position2;k++)
    {
       ddata=shi(position2-1-k);
       data2=data2+(alldata[k])*ddata;  
    }
  if((data1 > 50000) || (data2 > 50000))
         {yes=2;}
  else
    {
      switch (kind)
        {
         case 11:data3=data1+data2;yes=0;
		         break;
         case 15: if(data1<data2)
                 {
				   ddata=data1;
				   data1=data2;
				   data2=ddata;
				   fu=1;
				  }
	             data3=data1-data2;yes=0;
				  break;
         case 35:data3=data1*data2;yes=0;
		          break;
         case 135:data3=data1/data2;yes=0;
		          break;
         default:yes=1;
        }
    }
}
if(yes==0)
 {
   love[0]=data3 / 1000000000;
   love[1]=data3 / 100000000-love[0]*10;
   love[2]=data3 / 10000000-love[0]*100-love[1]*10;
   love[3]=data3 / 1000000-love[0]*1000-love[1]*100-love[2]*10;
   love[4]=data3 / 100000-love[0]*10000-love[1]*1000-love[2]*100-love[3]*10;
   love[5]=data3 / 10000-love[0]*100000-love[1]*10000-love[2]*1000-love[3]*100-love[4]*10;
   love[6]=(data3 % 10000)/1000;
   love[7]=(data3 % 1000)/100;
   love[8]=(data3 % 100)/10;
   love[9]= data3 % 10;
 }
if(kind==135)
 {
   love[10]=0xfe;
   love[11]=((data1 % data2)*10)/data2;
   love[12]=((((data1 % data2)*10)%data2)*10)/data2;
   love[13]=((((((data1 % data2)*10)%data2)*10)%data2)*10)/data2;
  }
}

void remove0(void)
{
  uchar k=0;
  while((love[k]==0) && (k<=8))
   {
    love[k]=0xf0;
    k++;
    }
  pfu=k;
}

void data3dis(void)
{
  uchar k;
  if(yes==0)
   {
     if(kind==135)
      {
       for(k=0;k<=13;k++)
       {
        WriteCommandLCM(0xc2+k,1);
        WriteDataLCM(love[k]+0x30);
        }
       }
  else
   {
    for(k=0;k<=9;k++)
    {
      WriteCommandLCM(0xc6+k,1);
      WriteDataLCM(love[k]+0x30);
    }
  if(fu==1)
    {
    WriteCommandLCM(0xc5+pfu,1);
    WriteDataLCM('-');
    }
   }
}
  else  
  if(yes==1)
     error();
  else   
     if(yes==2)
      out();
} 

void clear(void)
{
   uchar k;
   while(((~P1) & 0xf0)!=0);
   for(k=7;k<=15;k++)
    {
     WriteCommandLCM(k+0x80+0x40,1);
     WriteDataLCM(' ');
    }
   for(k=7;k<=15;k++)
   {
   WriteCommandLCM(k+0xc0,1);
   WriteDataLCM(' ');
   }
   rrr=0xff;
   kind=yes=position1=position2=0;                  //���������ͱ�־
   fu=pfu=0;
   data1=data2=0;                                   //������
   data3=0;
}

void prodis(void)
{
  rrr=6;
  rrr++;
  if(rrr==15)
   {rrr=7;}
  WriteCommandLCM(rrr+0x80+0x40,1);
  while(((~P1) & 0xf0)!=0);
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
      if(0<ad_data<256)			               //��ѹ��ֵ����0��5֮��ʱ����ѭ���Ա任
	 	{			    
		    int vary=ad_data;								
			press=(0.0195312*vary);
			temp=(int)(press*1000);	                //�Ŵ�1000�������ں���ļ���
	   									    	
		    press_ge=temp/1000;			     	      //ȡѹ��ֵ��λ
			press_shifen=(temp%1000)/100;		    	//ȡѹ��ֵʮλ
			press_baifen=((temp%1000)%100)/10;	    	//ȡѹ��ֵ��λ
			press_qianfen=((temp%1000)%100)%10;			//ȡѹ��ֵʮ��λ

	   	   }	    
			 
}
/*****************�����Ӻ���*******************/

void alarm(void)
{
	 if(ad_data>=256)                           //�����ǰѹ��ֵ����115kpa��

          {  Alarm_led_red=0; }                 //������red led����
        
	  else
	     {	  Alarm_led_red=1; }		        //�ر�red led ����
		   
	
	  if(ad_data<=0)							//�����ǰѹ��ֵС��16kpa

	     {  Alarm_led_green=0;  }               //������green led����

      else
	     {   Alarm_led_green=1; }      			//�ر�green  led ����
         
}



