//*****************************************************************************
#include <reg51.h>


#define LCDP  P1 	//定义LCM数据线接至P1口

sbit RS	=	P2^4;	//暂存器选择位元(0:指令,1:资料)
sbit RW	=	P2^5;	//设定读写位元 (0:写入,1:读取)
sbit E	=	P2^6;	//致能位元 (0:禁能,1:致能)
sbit BF	=	P1^7;	//忙碌检查位元(0:不忙,1:忙碌)数据线的最高位
sbit hongwai=	P3^3;//接红外光电传感器
sbit yanwu	=	P3^4;//接烟雾传感器
sbit meiqi	=	P3^5;//接煤气传感器
sbit speaker=	P3^6;//接蜂鸣器
sbit reset	=	P3^7;//接解除警报按钮

char code line[][32]={					   //二维数组表格
                     {"  家居报警系统  "},
					 {"保护您的家庭安全"},
					 {"    现在状态    "},
					 {"      安全      "},
					 {"    红外报警    "},
					 {"    有人进入    "},
					 {"                "},
					 {"    请检查！    "},
					 {"    烟雾报警    "},
					 {"    有火或烟    "},
					 {"                "},
					 {"    请检查！    "},
					 {"    煤气报警    "},
					 {"    煤气泄露    "},
					 {"                "},
					 {"    请检查！    "},
			    	};


void init_LCM(void);	//声明初始化子程序 
void write_inst(char);	//声明写入指令子程序 
void write_char(char);	//声明写入字元资料子程序 
void check_BF(void);	//声明检查忙碌子程序 
void xianshi(void);		//声明液晶显示子程序

int j=0;				//变量用来存放显示的屏数

 	
// ============ 主程序 ===========================
main()
{	 
	init_LCM();						//调用初始化子程序
	speaker=1;						//蜂鸣器关闭
	
	 
	while(1)						//无尽循环 
	
	{if(reset==0){j=0;speaker=1;}	//如果解除警报按钮有输入，由j＝0，蜂鸣器打开关闭
	 if(hongwai==0){j=1;speaker=0;}	//如果红外有输入，由j＝1，蜂鸣器打开 
	 if(yanwu==0){j=2;speaker=0;}	//如果烟雾有输入，由j＝2，蜂鸣器打开
	 if(meiqi==0){j=3;speaker=0;}	//如果煤气有输入，由j＝3，蜂鸣器打开
	 

	 xianshi();						//调用液晶显示子程序
		 
	}								// while结束 
}									// 主程序main()结束

//====液晶显示子程序===================
void xianshi(void)
{
int i;
            write_inst(0x80);			// 指定第一行位置 
			for (i=0;i<16;i++)			// 循环 
			write_char(line[4*j][i]);	// 显示16个字 
	
			write_inst(0x90);			// 指定第二行位置 
			for (i=0;i<16;i++)			// 循环 
			write_char(line[4*j+1][i]);	// 显示16个字 
	
	
			write_inst(0x88);			// 指定第三行位置 
			for (i=0;i<16;i++)			// 循环 
			write_char(line[4*j+2][i]);	// 显示16个字 
	
			write_inst(0x98);			// 指定第四行位置 
			for (i=0;i<16;i++)			// 循环 
			write_char(line[4*j+3][i]);	// 显示16个字

}


 
//====初始设定函数(8位元传输模式)===================
void init_LCM(void)
{	write_inst(0x30);	// 设定功能-8位元-基本指令 
	write_inst(0x08);	// 显示功能-关显示幕-无游标-游标不闪 
	write_inst(0x01);	// 清除显示幕(填0x20,I/D=1)
	write_inst(0x06);	// 输入模式-位址递增-关显示幕（只要给出首地址即可） 
	write_inst(0x0c);	// 显示功能-开显示幕-无游标-游标不闪  
}						// init_LCM()函数结束 
//==== 写入指令函数 ================================
void write_inst(char inst)
{	check_BF();				// 检查是否忙碌 
	LCDP = inst;			// LCM读入MPU指令 
	RS = 0; RW = 0; E = 1;	// 写入指令至LCM
	check_BF();				// 检查是否忙碌 
}							// write_inst()函数结束 
//==== 写入字元资料函数 ============================
void write_char(char chardata)
{	check_BF();				// 检查是否忙碌 
	LCDP = chardata;		// LCM读入字元 
	RS = 1; RW = 0 ;E = 1;	// 写入资料至LCM
	check_BF();				// 检查是否忙碌 
}							// write_char()函数结束	
//====检查忙碌函数================================
void check_BF(void)
{	E=0;					// 禁止读写动作 
	do						// do-while循环开始 
	{ 	BF=1;				// 设定BF为输入 
  	RS = 0; RW = 1;E = 1;	// 读取BF及AC
	}while(BF == 1);		// 忙碌继续等 
}							//	check_BF()函数结束 
 

//****************************************************************
