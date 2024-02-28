//******************************方法一 ****************************************
//*****************************************************************************


#include <reg51.h>


#define LCDP  P1 	//	定义LCM 资料汇流排接至P1

sbit RS	=	P2^4;	//	暂存器选择位元(0:指令,1:资料)
sbit RW	=	P2^5;	//	设定读写位元 (0:写入,1:读取)
sbit E	=	P2^6;	//	致能位元 (0:禁能,1:致能)
sbit BF	=	P1^7;	//	忙碌检查位元(0:不忙,1:忙碌)数据线的最高位//液晶实物中没有BF这个脚的，实物不用接线的


char code line1[]="    广州市      ";// 第1次显示字串(第1行)	 //字符串时，大括号可省略
char code line2[]="  轻工技师学院  ";// 第1次显示字串(第2行)
char code line3[]="    广州市      ";// 第1次显示字串(第3行)
char code line4[]="轻工高级技工学校";// 第1次显示字串(第4行)
char code line5[]="国家重点公办院校";// 第2次显示字串(第1行)
char code line6[]="                ";// 第2次显示字串(第2行)
char code line7[]="网址 http://www.";// 第2次显示字串(第3行)
char code line8[]=" gzslits.com.cn ";// 第2次显示字串(第4行)
char code line9[]="招生热线：      ";// 第3次显示字串(第1行)
char code line10[]=" 020－87481623  ";// 第3次显示字串(第2行)
char code line11[]="      84423747  ";// 第3次显示字串(第3行)
char code line12[]="      34466202  ";// 第3次显示字串(第4行)



void init_LCM(void);	//	初始设定函数 
void write_inst(char);	//	写入指令函数 
void write_char(char);	//	写入字元资料函数 
void check_BF(void);	//	检查忙碌函数 
void delay1ms(int);		//	延迟函数 	
// ============ 主程序 ===========================
main()
{	char i;							// 声明变量 
	init_LCM();						// 初始设定 
	while(1)						// 无尽循环 
	
	{	write_inst(0x80);			// 指定第一行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line1[i]);	// 显示16个字 
	
		write_inst(0x90);			// 指定第二行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line2[i]);	// 显示16个字 
		
		write_inst(0x88);			// 指定第三行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line3[i]);	// 显示16个字 
		
		write_inst(0x98);			// 指定第四行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line4[i]);	// 显示16个字 
		delay1ms(30000);				// 延迟10秒




		
		write_inst(0x80);			// 指定第一行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line5[i]);	// 显示16个字 
	
		write_inst(0x90);			// 指定第二行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line6[i]);	// 显示16个字 
		
		write_inst(0x88);			// 指定第三行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line7[i]);	// 显示16个字 
	
		write_inst(0x98);			// 指定第四行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line8[i]);	// 显示16个字 
		delay1ms(30000);				// 延迟10秒




		
		write_inst(0x80);			// 指定第一行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line9[i]);	// 显示16个字 

		write_inst(0x90);			// 指定第二行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line10[i]);	// 显示16个字 
	
		write_inst(0x88);			// 指定第三行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line11[i]);	// 显示16个字 
		
		write_inst(0x98);			// 指定第四行位置 
		for (i=0;i<16;i++)			// 循环 
			write_char(line12[i]);	// 显示16个字 
		delay1ms(30000);				// 延迟10秒 
		
		 
	}								// while结束 
}									// 主程序main()结束 
//====初始设定函数(8位元传输模式)===================
void init_LCM(void)
{	write_inst(0x30);	// 设定功能-8位元-基本指令 
	//write_inst(0x30);	// 设定功能-8位元-基本指令 
	//write_inst(0x30);	// 英文LCM相容设定，中交LCM可忽略 
	//write_inst(0x38);	// 英文LCM设定两列，中交LCM可忽略 
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
//==== 延迟函数 ================================
void delay1ms(int x)
{	int i,j;				// 声明变量 
	for (i=0;i<x;i++)		// 执行x次,延迟X*1ms
		for (j=0;j<120;j++);// 执行120次,延迟1ms
}							// delay1ms()函数结束 



//****************************************************************


//******************************方法二  用二维数组 ****************************
//*****************************************************************************
/*

#include <reg51.h>


#define LCDP  P1 	//	定义LCM 资料汇流排接至P1

sbit RS	=	P2^4;	//	暂存器选择位元(0:指令,1:资料)
sbit RW	=	P2^5;	//	设定读写位元 (0:写入,1:读取)
sbit E	=	P2^6;	//	致能位元 (0:禁能,1:致能)
sbit BF	=	P1^7;	//	忙碌检查位元(0:不忙,1:忙碌)数据线的最高位//液晶实物中没有BF这个脚的，实物不用接线的


char code line[][32]={
                     {"    广州市      "},
					 {"  轻工技师学院  "},
					 {"    广州市      "},
					 {"轻工高级技工学校"},
					 {"国家重点公办院校"},
					 {"                "},
					 {"网址 http://www."},
					 {" gzslits.com.cn "},
					 {"招生热线：      "},
					 {" 020－87481623  "},
					 {"      84423747  "},
					 {"      34466202  "},
			    	};




void init_LCM(void);	//	初始设定函数 
void write_inst(char);	//	写入指令函数 
void write_char(char);	//	写入字元资料函数 
void check_BF(void);	//	检查忙碌函数 
void delay1ms(int);		//	延迟函数 	
// ============ 主程序 ===========================
main()
{	char i,j;							// 声明变量 
	init_LCM();						// 初始设定
	
	 
	while(1)						// 无尽循环 
	
	{ for(j=0;j<3;j++)	
	   {	write_inst(0x80);			// 指定第一行位置 
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

			delay1ms(30000);				// 延迟10秒
	   }
		
		 
	}								// while结束 
}									// 主程序main()结束 
//====初始设定函数(8位元传输模式)===================
void init_LCM(void)
{	write_inst(0x30);	// 设定功能-8位元-基本指令 
	write_inst(0x30);	// 设定功能-8位元-基本指令 
	write_inst(0x30);	// 英文LCM相容设定，中交LCM可忽略 
	write_inst(0x38);	// 英文LCM设定两列，中交LCM可忽略 
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
//==== 延迟函数 ================================
void delay1ms(int x)
{	int i,j;				// 声明变量 
	for (i=0;i<x;i++)		// 执行x次,延迟X*1ms
		for (j=0;j<120;j++);// 执行120次,延迟1ms
}							// delay1ms()函数结束 


*/
//****************************************************************


