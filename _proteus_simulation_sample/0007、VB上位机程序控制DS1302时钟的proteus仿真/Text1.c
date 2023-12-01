//http://proteus.5d6d.com
#include <reg52.h>

sbit T_CLK = P2^4; /*实时时钟时钟线引脚 */
sbit T_IO = P2^3; /*实时时钟数据线引脚 */
sbit T_RST = P2^2; /*实时时钟复位线引脚 */
sbit ACC0=ACC^0;
sbit ACC7=ACC^7;
sbit rs=P2^0;
sbit rw=P2^1;
sbit e=P2^7;
sbit setd=P3^2;
sbit sett=P3^3;
sbit add=P2^5;
sbit enter=P2^6;
sbit speaker=P3^7;
unsigned char code tab[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};


void v_RTInputByte(unsigned char ucDa) 
{ 
unsigned char i;
ACC = ucDa;
for(i=8; i>0; i--)
{
T_IO = ACC0; /*相当于汇编中的 RRC */
T_CLK = 1;
T_CLK = 0;
ACC = ACC >> 1; 
} 
}

unsigned char uc_RTOutputByte(void) 
{ 
unsigned char i;
for(i=8; i>0; i--)
{
ACC = ACC >>1; /*相当于汇编中的 RRC */
ACC7 = T_IO;
T_CLK = 1;
T_CLK = 0;
} 
return(ACC); 
}

void v_W1302(unsigned char ucAddr, unsigned char ucDa)
{
T_RST = 0;
T_CLK = 0;
T_RST = 1;
v_RTInputByte(ucAddr); /* 地址，命令 */
v_RTInputByte(ucDa); /* 写1Byte数据*/
T_CLK = 1;
T_RST =0;
} 

unsigned char uc_R1302(unsigned char ucAddr)
{
unsigned char ucDa;
T_RST = 0;
T_CLK = 0;
T_RST = 1;
v_RTInputByte(ucAddr); /* 地址，命令 */
ucDa = uc_RTOutputByte(); /* 读1Byte数据 */
T_CLK = 1;
T_RST =0;
return(ucDa);
}

void v_BurstW1302T(unsigned char *pSecDa)
{
unsigned char i;
v_W1302(0x8e,0x00); /* 控制命令,WP=0,写操作?*/
T_RST = 0;
T_CLK = 0;
T_RST = 1;
v_RTInputByte(0xbe); /* 0xbe:时钟多字节写命令 */
for (i=8;i>0;i--) /*8Byte = 7Byte 时钟数据 + 1Byte 控制*/
{
v_RTInputByte(*pSecDa);/* 写1Byte数据*/
pSecDa++;
}
T_CLK = 1;
T_RST =0;
} 

void v_BurstR1302T(unsigned char *pSecDa)
{
unsigned char i;
T_RST = 0;
T_CLK = 0;
T_RST = 1;
v_RTInputByte(0xbf); /* 0xbf:时钟多字节读命令 */
for (i=8; i>0; i--) 
{
*pSecDa = uc_RTOutputByte(); /* 读1Byte数据 */
pSecDa++;
}
T_CLK = 1;
T_RST =0;
}

void v_BurstW1302R(unsigned char *pReDa)
{
unsigned char i;
v_W1302(0x8e,0x00); /* 控制命令,WP=0,写操作?*/
T_RST = 0;
T_CLK = 0;
T_RST = 1;
v_RTInputByte(0xfe); /* 0xbe:时钟多字节写命令 */
for (i=31;i>0;i--) /*31Byte 寄存器数据 */
{
v_RTInputByte(*pReDa); /* 写1Byte数据*/
pReDa++;
}
T_CLK = 1;
T_RST =0;
} 

void v_BurstR1302R(unsigned char *pReDa)
{
unsigned char i;
T_RST = 0;
T_CLK = 0;
T_RST = 1;
v_RTInputByte(0xff); /* 0xbf:时钟多字节读命令 */
for (i=31; i>0; i--) /*31Byte 寄存器数据 */
{
*pReDa = uc_RTOutputByte(); /* 读1Byte数据 */
pReDa++;
}
T_CLK = 1;
T_RST =0;
}

void v_setd1302(unsigned char *pSecDa) 
{
unsigned char i;
unsigned char ucAddr = 0x80; 
v_W1302(0x8e,0x00); /* 控制命令,WP=0,写操作?*/
for(i =7;i>0;i--)
{ 
v_W1302(ucAddr,*pSecDa); /* 秒 分 时 日 月 星期 年 */

pSecDa++;
ucAddr +=2;
}
v_W1302(0x8e,0x80); /* 控制命令,WP=1,写保护?*/
}


void delay()
{ unsigned char y;
 for(y=0;y<0xff;y++)
 {;}
}


void wc51r(unsigned char j)//写命令
{
e=0;rs=0;rw=0;
e=1;
P1=j;
e=0;
delay();
}

void init()//初始化
{
wc51r(0x01);
wc51r(0x38);
wc51r(0x38);
wc51r(0x0e);
wc51r(0x06);
wc51r(0x0c);
}


void wc51ddr(unsigned char j)//写数据
{
e=0;rs=1;rw=0;
e=1;
P1=j;
e=0;
delay();
}

void write1602(unsigned char add,unsigned char da)//写入显示数据
{wc51r(add);wc51ddr(da);}
 


void main(void)
{
unsigned char ucCurtime[7];
unsigned char i,yearh,yearl,monh,monl,dah,dal,hoh,hol,mih,mil,seh,sel;
unsigned char ucAddr;
unsigned int c;

init();
write1602(0x85,0x35);
for(c=0;c<30000;c++);
write1602(0x86,0x32);
for(c=0;c<30000;c++);
write1602(0x87,0x4D);
for(c=0;c<30000;c++);
write1602(0x88,0x43);
for(c=0;c<30000;c++);
write1602(0x89,0x55);
for(c=0;c<30000;c++);
write1602(0xC2,0x51);
write1602(0xC3,0x51);
write1602(0xC4,0x3A);
write1602(0xC5,0x35);
write1602(0xC6,0x39);
write1602(0xC7,0x37);
write1602(0xC8,0x33);
write1602(0xC9,0x38);
write1602(0xCA,0x35);
write1602(0xCB,0x33);
write1602(0xCC,0x36);
write1602(0xCD,0x39);
for(c=0;c<50000;c++);
init();//LCD初始化





TMOD=0X20;
TH1=0XF3;
TL1=0XF3;
SCON=0X50;
PCON=0X00;
IT0=1;
EX0=1;
IT1=1;
EX1=1;
TR1=1;
EA=1;
ES=1;
while(1)
{ucAddr = 0x81;
for (i=0;i<7;i++)
{
ucCurtime[i] = uc_R1302(ucAddr);/*格式为: 秒 分 时 日 月 星期 年 */
ucAddr += 2;
}


yearh=ucCurtime[6]/16;
yearl=ucCurtime[6]%16;
monh=ucCurtime[4]/16;
monl=ucCurtime[4]%16;
dah=ucCurtime[3]/16;
dal=ucCurtime[3]%16;

hoh=ucCurtime[2]/16;
hol=ucCurtime[2]%16;
mih=ucCurtime[1]/16;
mil=ucCurtime[1]%16;
seh=ucCurtime[0]/16;
sel=ucCurtime[0]%16;



write1602(0x80,0x44);
write1602(0x81,0x61);
write1602(0x82,0x74);
write1602(0x83,0x65);
write1602(0x84,0x3a);//显示date:

write1602(0x85,tab[yearh]);
write1602(0x86,tab[yearl]);
write1602(0x87,0x2d);//显示年
write1602(0x88,tab[monh]);
write1602(0x89,tab[monl]);
write1602(0x8a,0x2d);//显示月
write1602(0x8b,tab[dah]);
write1602(0x8c,tab[dal]);

write1602(0xc0,0x54);
write1602(0xc1,0x69);
write1602(0xc2,0x6d);
write1602(0xc3,0x65);
write1602(0xc4,0x3a);//显示time:

write1602(0xc5,tab[hoh]);
write1602(0xc6,tab[hol]);
write1602(0xc7,0x3a);//显示小时
write1602(0xc8,tab[mih]);
write1602(0xc9,tab[mil]);
write1602(0xca,0x3a);//显示小时
write1602(0xcb,tab[seh]);
write1602(0xcc,tab[sel]);

if((ucCurtime[1]==0)&(ucCurtime[0]==0|ucCurtime[0]==1|ucCurtime[0]==2))//3秒整点报时
  speaker=0;
else speaker=1;

}
}




serint() interrupt 4
{ //EA=0;
  static unsigned char k;
  unsigned char temp,year,month,date,hour,min,sec,week;
  unsigned char stemp[7]={0};
  RI=1;
  temp=SBUF;
  RI=0;
  k++;
  switch (k)
  { case 1:sec=temp;
           break;
	case 2:min=temp;
	       break;
	case 3:hour=temp;
	       break;
	case 4:date=temp;
	       break;
	case 5:month=temp;
	       break;
	case 6:week=temp;
	       break;
	case 7:year=temp;
	       stemp[0]=(sec/10)*16+sec%10;
		   stemp[1]=(min/10)*16+min%10;
		   stemp[2]=(hour/10)*16+hour%10;
		   stemp[3]=(date/10)*16+date%10;
		   stemp[4]=(month/10)*16+month%10;
		   stemp[5]=(week/10)*16+week%10;
		   stemp[6]=(year/10)*16+year%10;
           v_setd1302(stemp);//设定值
		   k=0;
	       break;
  }
}
