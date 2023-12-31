//EDM12864B DRIVE//
/**************************************
   PAGEADD为页地址起使
   TIERADD为行地址起使
   DIS_STARTADD为开始命令
   CTABLE为汉字字库数组
   ETABLE为英文字库数组
***************************************/
#include <reg51.h>
#define	uchar unsigned char
#define uint unsigned int
#define High 1
#define Low	0
#define _nop {}
#define PAGEADD 0xb8
#define TIERADD 0x40
#define DIS_STARADD 0xc0
uint key_value;
sbit DI=P1^4;
sbit E=P1^2;
sbit CS1=P1^1;
sbit CS2=P1^0;
sbit RW=P1^3;
sbit cs=P1^7;
sbit sclk=P1^6;
sbit dout=P1^5;
sbit I2C_SCL = P3^7;
sbit I2C_SDA = P3^6;
//uchar ntable[]={61,49,57,60,19,49,62,49,60,63,55,2,0,0,6,22,56,
//63,68,61,49,57,60,17,51,63,61};//email:analog2006@hotmail.com
uchar data voltage_display[8];

/*****************************
          字符表 
	 显示"Welcome Use"
******************************/
uchar code table1[]={
0x00,0x3e,0x51,0x49,0x45,0x3e,0x00,0x00,//0(0)
0x00,0x00,0x42,0x7f,0x40,0x00,0x00,0x00,//1
0x00,0x42,0x61,0x51,0x49,0x46,0x00,0x00,//2
0x00,0x21,0x41,0x45,0x4b,0x31,0x00,0x00,//3
0x00,0x18,0x14,0x12,0x7f,0x10,0x00,0x00,//4
0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00,//5
0x00,0x3c,0x4a,0x49,0x49,0x30,0x00,0x00,//6
0x00,0x01,0x01,0x79,0x05,0x03,0x00,0x00,//7
0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00,//8
0x00,0x06,0x49,0x49,0x29,0x1e,0x00,0x00,//9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// (10)
0x00,0x00,0x00,0x47,0x00,0x00,0x00,0x00,//!
0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00,//%
0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00,//&
0x00,0x14,0x08,0x3e,0x08,0x14,0x00,0x00,//*
0x00,0x08,0x08,0x3e,0x08,0x08,0x00,0x00,//+
0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00,//-
0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00,//.
0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00,///
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,//:(19)
0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00,//=
0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00,//?
0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00,//@(22)
0x00,0x7e,0x11,0x11,0x11,0x7f,0x00,0x00,//A
0x00,0x41,0x7f,0x49,0x49,0x36,0x00,0x00,//B
0x00,0x3e,0x41,0x41,0x41,0x22,0x00,0x00,//C
0x00,0x41,0x7f,0x41,0x41,0x3e,0x00,0x00,//D
0x00,0x7f,0x49,0x49,0x49,0x49,0x00,0x00,//E
0x00,0x7f,0x09,0x09,0x09,0x01,0x00,0x00,//F
0x00,0x3e,0x41,0x41,0x49,0x7a,0x00,0x00,//G(29)
0x00,0x7f,0x08,0x08,0x08,0x7f,0x00,0x00,//H
0x00,0x00,0x41,0x7f,0x41,0x00,0x00,0x00,//I
0x20,0x40,0x41,0x3f,0x01,0x01,0x00,0x00,//J
0x00,0x7f,0x08,0x14,0x22,0x41,0x00,0x00,//K
0x00,0x7f,0x40,0x40,0x40,0x40,0x00,0x00,//L
0x00,0x7f,0x02,0x0c,0x02,0x7f,0x00,0x00,//M
0x00,0x7f,0x06,0x08,0x30,0x7f,0x00,0x00,//N
0x00,0x3e,0x41,0x41,0x41,0x3e,0x00,0x00,//O
0x00,0x7f,0x09,0x09,0x09,0x06,0x00,0x00,//P
0x00,0x3e,0x41,0x51,0x21,0x5e,0x00,0x00,//Q(39)
0x00,0x7f,0x09,0x19,0x29,0x46,0x00,0x00,//R
0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00,//S
0x00,0x01,0x01,0x7f,0x01,0x01,0x00,0x00,//T
0x00,0x3f,0x40,0x40,0x40,0x3f,0x00,0x00,//U
0x00,0x1f,0x20,0x41,0x20,0x1f,0x00,0x00,//V
0x00,0x7f,0x20,0x80,0x20,0x7f,0x00,0x00,//W
0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00,//X
0x00,0x07,0x08,0x70,0x08,0x07,0x00,0x00,//Y
0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00,//Z
0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00,//a(49)
0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00,//b
0x00,0x38,0x44,0x44,0x44,0x28,0x00,0x00,//c
0x00,0x38,0x44,0x44,0x48,0x7f,0x00,0x00,//d	
0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00,//e
0x00,0x00,0x08,0x7e,0x09,0x02,0x00,0x00,//f
0x00,0x0c,0x52,0x52,0x4c,0x3e,0x00,0x00,//g
0x00,0x7f,0x08,0x04,0x04,0x78,0x00,0x00,//h
0x00,0x00,0x44,0x7d,0x40,0x00,0x00,0x00,//i
0x00,0x20,0x40,0x44,0x3d,0x00,0x00,0x00,//j
0x00,0x00,0x7f,0x10,0x28,0x44,0x00,0x00,//k(59)
0x00,0x00,0x41,0x7f,0x40,0x00,0x00,0x00,//l
0x00,0x7c,0x04,0x78,0x04,0x78,0x00,0x00,//m
0x00,0x7c,0x08,0x04,0x04,0x78,0x00,0x00,//n
0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x00,//o
0x00,0x7e,0x0c,0x12,0x12,0x0c,0x00,0x00,//p
0x00,0x0c,0x12,0x12,0x0c,0x7e,0x00,0x00,//q
0x00,0x7C,0x08,0x04,0x04,0x08,0x00,0x00,//r
0x00,0x58,0x54,0x54,0x54,0x64,0x00,0x00,//s
0x00,0x04,0x3f,0x44,0x40,0x20,0x00,0x00,//t
0x00,0x3c,0x40,0x40,0x3c,0x40,0x00,0x00,//u(69)
0x00,0x1c,0x20,0x40,0x20,0x1c,0x00,0x00,//v
0x00,0x3c,0x40,0x30,0x40,0x3c,0x00,0x00,//w
0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00,//x
0x00,0x1c,0xa0,0xa0,0x90,0x7c,0x00,0x00,//y
0x00,0x44,0x64,0x54,0x4c,0x44,0x00,0x00,//z(74)
};

/****************************
        中文字符表 
	显示"欢迎使用液晶模块"
*****************************/
uchar code table2[]={
0x14,0x24,0x44,0x84,0x64,0x1c,0x20,0x18,
0x0f,0xe8,0x08,0x08,0x28,0x18,0x08,0x00,
0x20,0x10,0x4c,0x43,0x43,0x2c,0x20,0x10,
0x0c,0x03,0x06,0x18,0x30,0x60,0x20,0x00,//欢(0)
0x40,0x41,0xce,0x04,0x00,0xfc,0x04,0x02,
0x02,0xfc,0x04,0x04,0x04,0xfc,0x00,0x00,
0x40,0x20,0x1f,0x20,0x40,0x47,0x42,0x41,
0x40,0x5f,0x40,0x42,0x44,0x43,0x40,0x00,//迎(1)
0x40,0x20,0xf0,0x1c,0x07,0xf2,0x94,0x94,
0x94,0xff,0x94,0x94,0x94,0xf4,0x04,0x00,
0x00,0x00,0x7f,0x00,0x40,0x41,0x22,0x14,
0x0c,0x13,0x10,0x30,0x20,0x61,0x20,0x00,//使(2)
0x00,0x00,0x00,0xfe,0x22,0x22,0x22,0x22,
0xfe,0x22,0x22,0x22,0x22,0xfe,0x00,0x00,
0x80,0x40,0x30,0x0f,0x02,0x02,0x02,0x02,
0xff,0x02,0x02,0x42,0x82,0x7f,0x00,0x00,//用(3)
0x10,0x61,0x06,0xe0,0x18,0x84,0xe4,0x1c,
0x84,0x65,0xbe,0x24,0xa4,0x64,0x04,0x00,
0x04,0x04,0xff,0x00,0x01,0x00,0xff,0x41,
0x21,0x12,0x0c,0x1b,0x61,0xc0,0x40,0x00,//液(4)
0x00,0x00,0x00,0x00,0x7e,0x2a,0x2a,0x2a,
0x2a,0x2a,0x2a,0x7e,0x00,0x00,0x00,0x00,
0x00,0x7f,0x25,0x25,0x25,0x25,0x7f,0x00,
0x00,0x7f,0x25,0x25,0x25,0x25,0x7f,0x00,//晶(5)
0x10,0xd0,0xff,0x50,0x90,0x04,0xf4,0x54,
0x5f,0x54,0x54,0x5f,0xf4,0x04,0x00,0x00,
0x03,0x00,0xff,0x00,0x00,0x84,0x85,0x45,
0x35,0x0f,0x15,0x25,0x65,0xc4,0x44,0x00,//模(6)
0x10,0x10,0xff,0x10,0x10,0x00,0x08,0x08,
0xff,0x08,0x08,0x08,0xf8,0x00,0x00,0x00,
0x08,0x18,0x0f,0x04,0x85,0x41,0x31,0x0d,
0x03,0x05,0x09,0x11,0x31,0x61,0x21,0x00,//块(7)
0x00,0x00,0xF8,0x48,0x48,0x48,0x48,0xFF, 
0x48,0x48,0x48,0x48,0xF8,0x00,0x00,0x00,
0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0x3F, 
0x44,0x44,0x44,0x44,0x4F,0x40,0x70,0x00,//电(8)
0x00,0x00,0xFE,0x02,0x42,0x42,0x42,0x42,
0xFA,0x42,0x42,0x42,0x62,0x42,0x02,0x00,
0x20,0x18,0x27,0x20,0x20,0x20,0x20,0x20, 
0x3F,0x20,0x21,0x2E,0x24,0x20,0x20,0x00,//压(9)
0x10,0x21,0x86,0x70,0x00,0x7E,0x4A,0x4A, 
0x4A,0x4A,0x4A,0x7E,0x00,0x00,0x00,0x00, 
0x02,0xFE,0x01,0x40,0x7F,0x41,0x41,0x7F,
0x41,0x41,0x7F,0x41,0x41,0x7F,0x40,0x00,//温(10)
0x00,0x00,0xFC,0x04,0x24,0x24,0xFC,0xA5,
0xA6,0xA4,0xFC,0x24,0x24,0x24,0x04,0x00,
0x80,0x60,0x1F,0x80,0x80,0x42,0x46,0x2A, 
0x12,0x12,0x2A,0x26,0x42,0xC0,0x40,0x00,//度(11)
0x08,0x31,0x86,0x60,0x00,0xFE,0x02,0xF2, 
0x02,0xFE,0x00,0xF8,0x00,0x00,0xFF,0x00, 
0x04,0xFC,0x03,0x00,0x80,0x47,0x30,0x0F, 
0x10,0x67,0x00,0x07,0x40,0x80,0x7F,0x00,//测(12)
0x40,0x40,0x40,0xDF,0x55,0x55,0x55,0xD5,
0x55,0x55,0x55,0xDF,0x40,0x40,0x40,0x00, 
0x40,0x40,0x40,0x57,0x55,0x55,0x55,0x7F, 
0x55,0x55,0x55,0x57,0x50,0x40,0x40,0x00,//量(13)
};

/********************************
       显示用的延时函数
	 延时长度有参数 n 决定
*********************************/


Delay_nms(uchar n)
 { uchar a;
   for(;n>0;n--)
      {
	   for(a=0;a<100;a++)
	      {
		   _nop;
		   _nop;
		   _nop;
		   _nop;
		   };
	   };
  }


/*****************************************
    DEM12864B状态检测,从EDM12864B读出数
    据检测标志位BF
******************************************/


void LCD_Busy()
 {
  uchar busy;
  E=Low;
  DI=Low;
  RW=High;
  while(1)
  {
    E=High;
    _nop;
	_nop;
    busy=P2;//读状态标志寄存器
	_nop;
    E=Low;
    if((busy&0x90)==0)//检测BF和RES位,两者都为零时表示可进行写入
    break;
  };
 }

/*********************************
 　　      写指令
**********************************/
void WRCommand_L(uchar command)
 {
  CS1=High;
  CS2=Low;
  LCD_Busy();
  DI=Low;
  _nop;
  RW=Low;
  _nop;
  E=High;
  _nop;
  P2=command;
  _nop;
  E=Low;
  _nop;
 }


void WRCommand_R(uchar command)
 {
  CS1=Low;
  CS2=High;
  LCD_Busy();
  DI=Low;
  _nop;
  RW=Low;
  _nop;
  E=High;
  _nop;
  P2=command;
  _nop;
  E=Low;
  _nop;
 }


/***********************************
       写一个字节的显示数据
************************************/
void WRdata_L(uchar ucdata)
  {
   CS1=High;
   CS2=Low;
   LCD_Busy();
   DI=High;
   _nop;
   RW=Low;
   _nop;
   E=High;
   _nop;
   P2=ucdata;
   _nop;
   E=Low;
   _nop;
  }


void WRdata_R(uchar ucdata)
  {
   CS1=Low;
   CS2=High;
   LCD_Busy();  
   DI=High;
   _nop;
   RW=Low;
   _nop;
   E=High;
   _nop;
   P2=ucdata;
   _nop;
   E=Low;
   _nop;
  }


/************************************
    读显示数据
*************************************/

/********************************************
RDdata_L()
  {
   uchar receiver;
   CS1=High;
   CS2=Low;
   LCD_Busy();
   DI=High;
   _nop;
   WR=High;
   _nop;
   E=High;
   _nop;
   receiver=P0;
   E=Low;
   return(receiver);
  }


RDdata_R()
  {
   uchar receiver;
   CS1=Low;
   CS2=High;
   LCD_Busy();
   DI=High;
   _nop;
   WR=High;
   _nop;
   E=High;
   _nop;
   receiver=P0;
   E=Low;
   return(receiver);
  }

/*****************************************

/**************************************
   I2C时钟时序要求的数据建立时间,
   nop_可以用其它短延时替代,比如喂狗
***************************************/

I2C_delay()
   {
    uchar n=5;
    while(n--)
      {
	   _nop;
	   _nop;
	   }
    }

/*********************************************
     I2C的时钟信号可发送和接收.
     接收时通过判断sample对寄存器的值加.
     发送的时候只调用程序产生时序.
**********************************************/

bit I2C_clock(void)
    {
     bit sample;
     I2C_delay();
     I2C_SCL=High;
     I2C_delay();
     sample=I2C_SDA;
     I2C_SCL=Low;
     I2C_delay();
     return(sample);
    }

/********************************************
   I2C确定接收有效的应答信号Acknowledge
*********************************************/

I2C_ACK()
   {
    I2C_SDA=Low;
    I2C_clock();
    I2C_SDA=High;
   }

/*****************************************
I2C的非应答信号
******************************************/

I2C_NACK()
   {
    I2C_SDA=High;
    I2C_clock();
    I2C_SDA=High;
   }

/*************************************************
     I2C的开始信号.发送和接受数据时,必须先调用.
 *************************************************/

I2C_start()
   { 
    I2C_SDA=High;
    I2C_delay();
    I2C_SCL=High;
    I2C_delay();
    I2C_SDA=Low;
    I2C_delay();
    I2C_SCL=Low;
    I2C_delay();
  }

/***************************************************
    I2C停止信号.发送和接受数据时结束时,需要调用.
****************************************************/

I2C_stop()
   {
    I2C_SDA=Low;
    I2C_delay();
    I2C_SCL=High;
    I2C_delay();
    I2C_SDA=High;//产生停止控制信号,并且释放数据线
    I2C_delay();
   }

/*****************************************
    I2C初始化.在main函数中必须先调用它.
     进行初始化后才能调用其他函数.
******************************************/

void I2C_init(void)
   {
    I2C_SDA=High;
    I2C_SCL=High;
    I2C_delay();
    I2C_stop();
   }

/*****************************************
    I2C总线写一个字节,即发送一个字节
   发送结束后,需要返回一个检测应答位
******************************************/

bit I2C_send(uchar I2C_data)
   {
    uchar a;
    for(a=0;a<8;a++)
      {
       I2C_SDA=(bit)(I2C_data&0x80);
       I2C_data=I2C_data<<1;
       I2C_clock();
      };
    I2C_SDA=High;
    I2C_delay();
    return(I2C_clock()); //返回应答信号
   }

/***********************************************
   I2C总线读一个字节,即接收一个字节数据
   接收结束后需要发送一个应答位acknowledge
***********************************************/

uchar I2C_receive()
     {
      uchar a,receive_data;
      for(a=0;a<8;a++)
         {
          receive_data=receive_data<<1;
          if(I2C_clock())
           {
            receive_data++;
           }; 
         };
 //I2C_ACK();
      return(receive_data);
      }


 DS1621_start()
   {
	do
	{
     I2C_start();
	 }
    while(I2C_send(0x90));//发送数据完地址字节的数据时,检测从机的应答位        
	if(I2C_send(0xee)==0)
	  {
	   I2C_stop();
	   return 1;
	   }
    else
	  return 0;			        
	  }

 DS1621_stop()
   {
    do
	{
	 I2C_start();
	 //I2C_send(0x90);
	 }
	while(I2C_send(0x90));
	if(I2C_send(0x22)==0)
     {
	  I2C_stop();
	  return 1;
	  }
	else
	  return 0;	    
	}

char read_count_remain()
      {
	   char temp_remain=0;
	   do
	   	{
	     I2C_start();
	     }
	   while(I2C_send(0x90));//是否应答
	   if(I2C_send(0xa8)==0)
	     {
		  I2C_start();
	      if(I2C_send(0x91)==0)
	        {
			temp_remain=I2C_receive();
			I2C_NACK();
		    I2C_stop();
			return temp_remain;
			}
		  else
		    return 0;
	      }
		else
		  return 0;
	   }
char read_count_c()
      {
	   char temp_c=0;
	   do
	   	{
	     I2C_start();
	     }
	   while(I2C_send(0x90));//是否应答
	   if(I2C_send(0xa9)==0)
	     {
		  I2C_start();
	      if(I2C_send(0x91)==0)
	        {
			temp_c=I2C_receive();
			I2C_NACK();
		    I2C_stop();
			return temp_c;
			}
		  else
		    return 0;
	      }
		else
		  return 0;
	   }
bit read_temperature(char *point1)
   {
	do
	{
	I2C_start();
	}
	while(I2C_send(0x90));
    if(I2C_send(0xaa)==0)
	  {
	   do{
	     I2C_start();
	     }
	     while(I2C_send(0x91));
	   (*point1)=I2C_receive();
	   I2C_ACK();
	   (*(point1+1))=I2C_receive();
	   I2C_NACK();
	   I2C_stop();
	   return 1;
	   }
	else
	return 0;
	}

 DS1621_state()
   {
	do
	{
	 I2C_start();
	 }
	while(I2C_send(0x90));
	if(I2C_send(0xac)==0)
      {
	   do
		{
	     I2C_start();
		}
	   while(I2C_send(0x90));
	   if(I2C_send(0x00)==0)
	   //if(I2C_send(0x01)==0)
		 {
		 I2C_stop();
		 return 1;
		  }
	   else
	   return 0;
		}
	else
	  return 0;	    
	}

 DS1621_th()
   {
	 
    }
 DS1621_tl()
   {
	 
    }
 DS1621_init()
   {
	while(DS1621_stop()==0)
	{};
	while(DS1621_state()==0)
	{};
	DS1621_th();
	DS1621_tl();
	}

/****************************************************
       字符为16*16显示,分为两个部分写入32个字节
       前16个字节写入第一页(16*8),后16个字节写入
	   第二页(16*8)
	   左侧写入"欢迎",右侧写入"使用"
*****************************************************/
C_display_L(uchar C_Pagenum,uchar C_Tiernum,uchar C_Temp)
  {
   uchar k;
   C_Pagenum=PAGEADD|C_Pagenum;
   C_Tiernum=TIERADD|C_Tiernum;
   WRCommand_L(C_Pagenum);
   WRCommand_L(C_Tiernum);
   for(k=0;k<16;k++)
      {
       WRdata_L(table2[C_Temp*32+k]);
	     };
   C_Pagenum=C_Pagenum+1;
   WRCommand_L(C_Pagenum);
   WRCommand_L(C_Tiernum);
   for(k=0;k<16;k++)
      {
       WRdata_L(table2[C_Temp*32+k+16]);
	   };
   }

C_display_R(uchar C_Pagenum,uchar C_Tiernum,uchar C_Temp)
  {
   uchar k;
   C_Pagenum=PAGEADD|C_Pagenum;
   C_Tiernum=TIERADD|C_Tiernum;
   WRCommand_R(C_Pagenum);
   WRCommand_R(C_Tiernum);
   for(k=0;k<16;k++)
      {
       WRdata_R(table2[C_Temp*32+k]);
	     };
   C_Pagenum=C_Pagenum+1;
   WRCommand_R(C_Pagenum);
   WRCommand_R(C_Tiernum);
   for(k=0;k<16;k++)
      {
       WRdata_R(table2[C_Temp*32+k+16]);
	     };
  }

/****************************************
   写入西文字符,共11个字符,左侧写入6个
   右侧写入5个,左侧起始从16开始,右侧从
   0开始
*****************************************/

E_Display_L(uchar E_Pagenum,uchar E_Tiernum,uchar E_Temp)
  {
   uchar k;
   WRCommand_L(PAGEADD|E_Pagenum);
   WRCommand_L(TIERADD|E_Tiernum);
   for(k=0;k<8;k++)
	  {
	   WRdata_L(table1[E_Temp*8+k]);
	   };
   }   
E_Display_R(uchar E_Pagenum,uchar E_Tiernum,uchar E_Temp)
   {
   uchar k;
   WRCommand_R(PAGEADD|E_Pagenum);
   WRCommand_R(TIERADD|E_Tiernum);
   for(k=0;k<8;k++)
	  {
	   WRdata_R(table1[E_Temp*8+k]);
	   };
   	}

/*********************************
	   清除所有显示RAM内容
**********************************/

CLR_DisplayRAM()
   {
    uchar C_page,i,k;
    for(i=0;i<8;i++)
	   {
	    C_page=PAGEADD|i;//清除起始页为0
	    WRCommand_L(C_page);//清除起始页写入
		WRCommand_L(TIERADD);//清除起始行地址写入
		WRCommand_R(C_page);
		WRCommand_R(TIERADD);
		for(k=0;k<64;k++)
		   {		   	
			WRdata_L(0x00);
			WRdata_R(0x00);//lcm的ram自动加一,只许循环64次即可    
		 	};
		 };
    }

/*********************************
       初始化 设置启使行
**********************************/
void Init_LCD(void)
   {
	CLR_DisplayRAM();//清除所有显示寄存器
	WRCommand_L(DIS_STARADD);
	WRCommand_R(DIS_STARADD);//设置显示起始行地址
	WRCommand_L(0x3f);
	WRCommand_R(0x3f);//开显示
    }
/***************************************
    max1241读转换结果
****************************************/
uint read_max1241()
	 {
	  uint voltage_temp=0;
	  uchar ucloop=12;
	  cs=High;
	  //dout=low;
	  sclk=Low;
	  cs=Low;
      while(dout==0);//EOC信号为高表示转换结束
	  sclk=High;
	  sclk=Low;
      while(ucloop--)
	   {
		sclk=High;//上升沿数据稳定并读出
		voltage_temp<<=1;
	    if(dout==1)
	    voltage_temp+=1;
	    sclk=Low;
		};	 
	  //sclk=low;
	  cs=High;
	  return voltage_temp;
	  }

main()
  {
   uchar a=0,temp=0,b=0,number=0,pagenum=0;
   uchar etable[]={0,0,0,0,0,45,53,60,51,63,61,53,10,69,67,53};//Welcome use
   uchar ttable[]={42,57,61,53,19,10,2,0,0,6,18,1,1,18,0,7};//Time:2006/11/07
   char count_remain=0,count_c=0;
   bit flag=1;
   char temperature_buf[2]={0};
   uchar temperature_display[8]={0};
   //uchar voltage=0; //测试0831时使用
   double voltage=0;
   double temp_buffer=0;
   cs=High;
   sclk=High;
   Init_LCD();
   I2C_init();
   DS1621_init();//初始化
   DS1621_start();//开始温度采集

   /***************************************
   利用开机显示时间(大概三秒)空读一次DS1621
   ***************************************/
   for(b=0;b<2;b++)
      {
      for(number=0;number<20;number++)
	     {
	      //中文显示:欢迎使用液晶模块
     	  pagenum=1;//在第二行开始显示
	      for(a=0;a<4;a++)
	        {
	         C_display_L(pagenum,a*16,a);
	         C_display_R(pagenum,a*16,a+4);
	         }; 
        
		  //英文显示:Welcome use	            
          pagenum=5;//在第六行显示
          for(a=0;a<3;a++)
             {
              E_Display_L(pagenum,(a+5)*8,etable[a+5]);
              };
          for(a=0;a<8;a++)
             { 
              E_Display_R(pagenum,a*8,etable[a+8]);
              };
        
		  //显示制作时间:Time:2006/11/07				
          pagenum=7;//在第八行显示
          for(a=0;a<8;a++)
             {
              E_Display_L(pagenum,a*8,ttable[a]);
              E_Display_R(pagenum,a*8,ttable[a+8]);
              }          
	      Delay_nms(100);
		  };
		  if(flag)
		 	 {
              read_temperature(temperature_buf);//在转到下一个显示界面之前空读一次
			  read_count_remain();
			  read_count_c();
			  DS1621_start();
              flag=0;
   	          };
   	  };  

	WRCommand_L(0x3e);
	WRCommand_R(0x3e);
	CLR_DisplayRAM();  //清除显示ram
	WRCommand_L(0x3f);
	WRCommand_R(0x3f);   
			
    while(1)
	   {
	    while(read_temperature(temperature_buf)==0);//读温度值(两字节有符数),并检测应答位,只使用第一字节
	    count_remain=read_count_remain();//读斜率
		count_c=read_count_c();//读计数器
		temp_buffer = temperature_buf[0] -0.75 + (count_c-count_remain) / (double)count_c;
		DS1621_start();//读完数据后,重新开始一次温度转化

		   	temperature_display[0]=19;
			if(temp_buffer<0)
			  {
			   temperature_display[1]=16;//显示负号
		       temperature_display[2]=(-temp_buffer)/10;//十位
			   temperature_display[3]=((uchar)(-temp_buffer))%10;
			   temperature_display[4]=17;//小数点
			   temperature_display[5]=(int)((-temp_buffer)*10)%10;
			   temperature_display[6]=(int)((-temp_buffer)*100)%10;//小数点后两位
			   }
			else
			  {
			   temperature_display[1]=temp_buffer/100;//百位
		       temperature_display[2]=((uchar)temp_buffer)/10%10;
			   temperature_display[3]=((uchar)temp_buffer)%10;
			   temperature_display[4]=17;
			   temperature_display[5]=((int)(temp_buffer*10))%10;
			   temperature_display[6]=((int)(temp_buffer*100))%10;//小数点后两位
			   }

			// 测试从max1241读出的原始数据
		    /***************************
			//pagenum=3;
	 	    voltage=read_max1241();
		    voltage_display[0]=19;
		    voltage_display[1]= voltage/1000;   
		    voltage_display[2]=(voltage/100)%10;
		    voltage_display[3]=(voltage/10)%10;
                                voltage_display[4]= voltage%10;		  
		    //*******************************/

		//LCD显示第二部分
		for(b=0;b<40;b++)
	       {
		    //*************************
			//更新max1241显示值		    
			voltage=(double)read_max1241();
		    voltage=5000*voltage/4095;
		    voltage_display[0]=19;
		    voltage_display[5]=(uint)voltage %10;//个位
		    voltage_display[2]=17;
		    voltage_display[4]=(uint)(voltage/10)%10;//小数点后1位
		    voltage_display[3]=(uchar)(voltage/100)%10;//小数点后2位
			voltage_display[1]=(uchar)(voltage/1000)%10;//小数点后3位
			//***********************************/
			//显示文字:电压测量		
		    pagenum=2;
		    for(a=0;a<2;a++)
		       C_display_L(pagenum,a*16,a+8);
		    for(a=0;a<2;a++)
		       C_display_L(pagenum,(a+2)*16,a+12);	
		   
		   	//显示文字:温度测量
		    pagenum=5;
		    for(a=0;a<2;a++)
		       C_display_L(pagenum,a*16,a+10);
		    for(a=0;a<2;a++)
		       C_display_L(pagenum,(a+2)*16,a+12);
		    
			//显示1241采样值
			pagenum=3;
		    for(a=0;a<6;a++)
              {
		   	   E_Display_R(pagenum,a*8,voltage_display[a]); 
		       }

			//显示ds1621采样值
			pagenum=6;
		    for(a=0;a<7;a++)
              {
		   	   E_Display_R(pagenum,a*8,temperature_display[a]); 
		       }
          };
	  };	
   }