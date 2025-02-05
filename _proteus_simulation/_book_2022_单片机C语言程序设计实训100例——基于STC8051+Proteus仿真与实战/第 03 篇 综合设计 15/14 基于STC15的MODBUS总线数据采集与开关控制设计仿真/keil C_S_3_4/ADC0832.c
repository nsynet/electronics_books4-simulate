//-----------------------------------------------------------------
// 名称: ADC0832模数转换程序
//-----------------------------------------------------------------
#include <intrins.h>
#include <reg51.h>
#define INT8U unsigned char
#define INT16U unsigned int
//ADC0832引脚定义
sbit  CS   =  P3^4;					//片选线(电路中固定连接低电平)
sbit  CLK  =  P3^5;					//时钟钟线
sbit  DIO  =  P3^7;					//数据线
//-----------------------------------------------------------------
// 获取指定通道的A/D转换结果
//-----------------------------------------------------------------
INT8U ADx_Value(INT8U ch)
{
	INT8U i,dat1 = 0, dat2 = 0;
	//使能ADC0832，时钟线初始置为低电平
	CS  = 0; CLK = 0;
	//第1个时钟脉冲上升沿之前置DIO为1,表示Start Bit
	DIO = 1;			_nop_(); _nop_();
	CLK = 1;			_nop_(); _nop_();
	//第2个时钟脉冲上升沿之前,通过DIO选择模式
	//设DI = 1 选择单端(SGL) 设DI = 0 选择差分(DIF)
	CLK = 0;  DIO = 1;	_nop_(); _nop_();
	CLK = 1;			_nop_(); _nop_();
	//第3个时钟脉冲上升沿之前,设DI = 0/1,分别对应于选择CH0/CH1 
	CLK = 0;  DIO = ch;	_nop_(); _nop_();
	CLK = 1;			_nop_(); _nop_();
	//第3个时钟脉冲下降沿之后置DI = 1,释放数据线,准备接收
	//P1端口读取数据时先写1,否则总线将出现逻辑冲突(黄色方块闪烁)
	CLK = 0;  DIO = 1;	_nop_(); _nop_();
	//第4 ~11,共8个下降沿读数据(MSB->LSB)
	for(i = 0; i < 8; i++)
	{ 	CLK = 1;		_nop_(); _nop_();
		CLK = 0;		_nop_(); _nop_(); 
		dat1 = (dat1 << 1) | DIO;
	}	
	//第11~18,共8个下降沿读数据(LSB->MSB)
	for(i = 0; i < 8; i++)
	{ 	dat2 = dat2 | ((INT8U)DIO << i);
		CLK = 1;		_nop_(); _nop_();
		CLK = 0;		_nop_(); _nop_();
	}
	CS  = 1;	//禁止ADC0832
	//如果MSB->LSB和LSB->MSB读取的结果相同则返回读取的结果,否则返回0
	return (dat1 == dat2) ? dat1 : 0x00;
}