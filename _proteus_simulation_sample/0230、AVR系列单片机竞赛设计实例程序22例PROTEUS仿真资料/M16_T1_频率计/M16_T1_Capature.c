//***************FileName:Capature.C***************//
//***************ICCAVR V6.30编译*****************//

#include <iom16v.h>       
#include <macros.h>          
#define uchar unsigned char
#define uint  unsigned int

#define CON 1000      //频率常数定义
uchar Flag=0;         //捕获次数定义

//数码管字型表，对应0，1，2，3，4，5，6，7，8，9,A,b,C,d,E,F//
uchar Table[20]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                 0x7f,0x6f,0x77,0x7c,0x39,0x5E,0x79,0x71};
uchar Data[4]={0,0,0,0};       //显示初始值：0 0 0 0
uint  CNT1;                    //第一次捕获值
uint  CNT2;                    //第二此捕获值
uint  CNT=100;                 //捕获差值 
      
void DelayMs(uint i)           //Ms级延时，参数i为延时时间
{uint j;
 for(;i!=0;i--)
  {for(j=250;j!=0;j--) {;}}
}

void Pre_Display(void)         //预显示函数，数码管显示检测
{uchar i;
 for(i=0;i<16;i++)
  {PORTC=0x00;
   PORTA=Table[i];
  DelayMs(100);
  }
}

void Display(uchar *p)         //动态显示函数，参数p为待显示的数组名
{uchar i,sel=0x08;           
 for(i=0;i<4;i++)
  {PORTC=~sel;                  //选通最右边的数码管
   PORTA=Table[p[i]];          //送字型码
   DelayMs(2);                 //显示延时    
   sel=sel>>1;                 //移位以显示前一位
  }
}

void HZ(uint i,uchar *p)
{uint TEM;
 p[0]=CON/i;
 TEM=CON%i;
 TEM=TEM*10;
 p[1]=TEM/i;
 TEM=TEM%i;
 TEM=TEM*10;
 p[2]=TEM/i;
 TEM=TEM%i;
 TEM=TEM*10;
 p[3]=TEM/i;
}

void Init_IO(void)             //初始化I/O口
{DDRA=0xff;                    //设置A口为推挽1输出
 PORTA=0xff;
 DDRC=0xff;                    //设置C口为推挽1输出             
 PORTC=0xff;
 DDRD=0x00;                    //设置D口为带上拉电阻输入
 PORTD=0x00;    
}

void Init_Timer1(void)         //初始化T/C1的输入捕获中断
{TIMSK=TIMSK|0x20;             //输入捕获使能
 TCCR1B=0xC2;                  //输入捕获噪音使能，下降沿捕获，时钟8分频1uS计数一次。
 TIFR=0x20;                    //清中断标志
 SREG=SREG&0x7f;               //全局中断关
} 

void main(void)
{uchar i;
 Init_IO();                    //初始化I/O口
 PORTA=0xff;                   //点亮以测试所有的数码管
 PORTC=0xf0;   
 DelayMs(300);
 PORTC=0xff;                   //熄灭所有的数码管
 Pre_Display();                //预显示，数码管显示测试
 PORTC=0xff;
 Init_Timer1();                //T/C1初试化 
 while(1)
  {
  while(TIFR&0x20)             //捕获检测
      {TIFR|=0x20;             //清除捕获标志
	   CNT=ICR1L;              //CNT暂存
       CNT2=(ICR1H<<8)+ICR1L;  //CNT2存放当前捕获值
       CNT=CNT2-CNT1;          //CNT存放两次时间差
       CNT1=CNT2;              //CNT1存放上次捕获值
       Flag++;}                //检测到第一次捕获
   if(Flag==2)                 //检测到第二此捕获
      {Flag=0;                 //清除捕获检测标志
	   HZ(CNT,Data);           //数据处理
	   for(i=0;i<100;i++)      //频率显示
	       Display(Data);
	   CNT=0;CNT1=0;CNT2=0;}}  //清除捕获值及捕获差值
}

