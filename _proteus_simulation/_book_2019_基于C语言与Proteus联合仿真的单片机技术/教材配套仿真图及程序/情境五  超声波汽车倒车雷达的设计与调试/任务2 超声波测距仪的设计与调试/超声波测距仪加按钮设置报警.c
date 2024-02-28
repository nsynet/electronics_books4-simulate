//***********************************************************************************************************
//超声波倒车，数码管显示，可以按钮设置距离报警
//
//***********************************************************************************************************	    
#include<reg51.h>
#include <intrins.h>

#define seg P0	   //接数码管
#define pianxuan P3//接片选

sbit set=P1^2;	   //设置按钮
sbit jia=P1^3;	   //加
sbit jian=P1^4;	   //减
sbit TX=P1^5;	   //接超声波模块，发信号给超声波
sbit RX=P1^6;	   //接超声波模块，接收超声波的高电平信号
sbit speaker=P1^7; //蜂鸣器

char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98,0xbf}; //数码
char code pianxuan_lab[]={0xfe,0xfd,0xfb,0xf7};		  //片选

int gewei;		   //存个位数信息
int shiwei;	       //存十位数信息
int shiwei_set=0;  //存十位数设置信息，初始设定值为1.0米
int baiwei;	       //存百位数信息
int baiwei_set=1;  //存百位数设置信息
int qianwei;	   //存千位数信息

bit set_biaozhi=0;	   //设置标志位
unsigned long juli;			   //实际超声波测量距离
unsigned int juli_set;		   //设置开始提示距离，再减去0.5米就是报警
int time2ms;		   //2ms寄存器
int time;			   //超声波时间
bit t0_flag;		   //T0溢出标志位
int weizhi;			   //数码管片选时的位置

saomiao();			   //扫描子程序
jisuan();			   //计算距离子程序

main()
{
    speaker=1;			   // 蜂鸣器器关
    RX=1;				   //作为输入端，先设为1

    TMOD=0x11;		   //设T0,T1为定时，方式1
	TH0=0;			   //T0初始值为0，到关闭时，TH0和TL0的数值则是从T0开到关的时间
	TL0=0;             //
	TH1=(65536-50000)/256;		   //50MS定时
	TL1=(65536-50000)%256;
	ET0=1;             //允许T0中断
	ET1=1;			   //允许T1中断
	TR1=1;			   //开启定时器1
	EA=1;			   //开启总中断

	while(1)		   //无限循环
	{	
	
    if(set==0)						  //设置按钮按一下则set_biaozhi取反
	    {while(set==0);	  //
		 set_biaozhi=~set_biaozhi;	  //
		 }
	if(set_biaozhi==1)				  //如果set_biaozhi为1，则是设置状态，可以加和减
	    {if(jia==0)					  //加
		     {while(jia==0); //
			  shiwei_set++;			  //最低位加
			  }						  
		 if(jian==0)				  //减
		     {while(jian==0);//
			  shiwei_set--;			  //最低位减
			  }
		}
	if(shiwei_set==10){shiwei_set=0;baiwei_set++;}	//以下四行做数据处理，范围是0－2.9米
	if(shiwei_set==-1){shiwei_set=9;baiwei_set--;}	//
	if(baiwei_set==3)baiwei_set=0;					//
	if(baiwei_set==-1)baiwei_set=2;					//
	

	juli_set=baiwei_set*100+shiwei_set*10;//合并设置数据

	if(juli<juli_set)                     //实际距离小于设定距离由报警
	    { 
		  speaker=0;
		   						 		   		  
		}

	if(juli>=juli_set)                     //实际距离大于设定距离不报警
	    { 
		  speaker=1;
		   						 		   		  
		}

	if(RX==1)
	     {
		 TR0=1;			    //开启计数
	     while(RX==1);	    //当RX为1计数并等待
	     TR0=0;				//关闭计数
         jisuan();			//计算
		 }
	
	}

}


saomiao()
{	seg=0xff;
	pianxuan=pianxuan_lab[weizhi];
	if(set_biaozhi==0)
	     {
		 if(weizhi==0)seg=tab[gewei];
		 if(weizhi==1)seg=tab[shiwei];
		 if(weizhi==2)seg=tab[baiwei]&0x7f;		//加小数点
		 if(weizhi==3)seg=0xff;	//不显示
		 }
	
	if(set_biaozhi==1)
		 {
		 if(weizhi==0)seg=tab[10];	//设置时显示符号“－”
		 if(weizhi==1)seg=tab[shiwei_set]; //设置时显示
		 if(weizhi==2)seg=tab[baiwei_set]&0x7f;	//加小数点//设置时显示
		 if(weizhi==3)seg=tab[10];	//设置时显示符号“－”
		 }
		 	
	weizhi++;
	if(weizhi==4)weizhi=0;

}	
	


jisuan()						//
{
	 time=TH0*256+TL0;			//算出时间
	 TH0=0;
	 TL0=0;
	
	 juli=(time*1.7)/100;     //算出距离
	 if((juli>=300)||t0_flag==1) //超出测量范围显示“-”
	 {	 
	  t0_flag=0;
	  gewei=10;	       //“-”
	  shiwei=10;	   //“-”
	  baiwei=10;	   //“-”
	 }
	 else							//按4位数来分离
	 {
	  baiwei=juli%1000/100;
	  shiwei=juli%1000%100/10;
	  gewei=juli%1000%100%10;
	 }
}

void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
{
    t0_flag=1;							 //中断溢出标志
}

void  zd3()  interrupt 3 		 //T1中断用来扫描数码管和计800MS启动模块
{
int c;	 
	 TH1=0xf8;
	 TL1=0x30;
	 saomiao();
	 time2ms++;					 //
	 if(time2ms>=400)			 //
	 {
	  time2ms=0;
	  TX=1;			                //800MS  启动一次模块//***********仿真时暂时不用	  
	  for(c=0;c<20;c++)			//
	  {_nop_();} 					//	  
	  TX=0;							//800MS  启动一次模块//***********仿真时暂时不用
	 }
	 
	
}

