//------------------------- BMP180.c ------------------------------
// 名称：BMP180驱动程序
//-----------------------------------------------------------------
#include "BMP180.h"
//BMP180的11个校准系数（根据技术手册定义）
short ac1, ac2, ac3;
unsigned short ac4, ac5, ac6;
short b1, b2, mb, mc, md;
sbit SCL = P3^0;					//时钟线
sbit SDA = P3^1;					//数据线
int	dis_data;						//变量
u8 x[6];							//数据临时分解缓冲
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void Delay5us() {					//@12MHz
	u8 i = 12; _nop_(); nop_(); while (--i);
}
void Delay5ms() {					//@12MHz
	u8 i = 59, j = 90;
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
// 起始信号
//-----------------------------------------------------------------
void BMP180_Start() {

}
//-----------------------------------------------------------------
// 停止信号
//-----------------------------------------------------------------
void BMP180_Stop() {

}
//-----------------------------------------------------------------
// 发送应答信号:入口参数:ack (0:ACK 1:NAK)
//-----------------------------------------------------------------
void BMP180_SendACK(bit ack) {

}
//-----------------------------------------------------------------
// 接收应答信号
//-----------------------------------------------------------------
bit BMP180_RecvACK() {

} 
//-----------------------------------------------------------------
// 向IIC总线发送一字节数据
//-----------------------------------------------------------------
void BMP180_SendByte(u8 dat) {

}
//-----------------------------------------------------------------
// 从IIC总线接收一字节数据
//-----------------------------------------------------------------
u8 BMP180_RecvByte() {

}
//-----------------------------------------------------------------
// 单字节写入BMP180内部数据
//-----------------------------------------------------------------
void Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data) {
	BMP180_Start();					//起始信号
	BMP180_SendByte(SlaveAddress);	//写设备地址+写信号
	BMP180_SendByte(REG_Address);	//写内部寄存器地址
	BMP180_SendByte(REG_data);		//写内部寄存器数据
	BMP180_Stop();					//发送停止信号
}
//-----------------------------------------------------------------
// 单字节读取BMP180内部数据
//-----------------------------------------------------------------
u8 Single_Read(u8 REG_Address) {
	u8 REG_data;
	BMP180_Start();					//起始信号
	BMP180_SendByte(BMP180_SlaveAddress);	//发送设备地址+写信号
	BMP180_SendByte(REG_Address);	//写内部寄存器地址
	BMP180_Start();					//起始信号
	BMP180_SendByte(BMP180_SlaveAddress+1); //发送设备地址+读信号
	REG_data=BMP180_RecvByte();		//读出内部寄存器数据
	BMP180_SendACK(1);				//发送非应答NACK
	BMP180_Stop();					//停止信号
	return REG_data; 
}
//-----------------------------------------------------------------
// 读BMP180内部数据(两字节)
//-----------------------------------------------------------------
short Multiple_read(u8 ST_Address) {
	u8 msb, lsb;
	short _data;
	BMP180_Start();					//起始信号
	BMP180_SendByte(BMP180_SlaveAddress);	//发送设备地址+写信号
	BMP180_SendByte(ST_Address);	//写内部寄存器地址
	BMP180_Start();					//起始信号
	BMP180_SendByte(BMP180_SlaveAddress+1);//发送设备地址+读信号
	msb = BMP180_RecvByte();		//读取数据高字节
	BMP180_SendACK(0);				//发送答应ACK
	lsb = BMP180_RecvByte();		//读取数据低字节
	BMP180_SendACK(1);				//发送非应答NACK
	BMP180_Stop();					//停止信号
	Delay5ms();
	_data = (msb << 8) | lsb;
	return _data;
}
//-----------------------------------------------------------------
// 读温度
//-----------------------------------------------------------------
long BMP180ReadTemp() {
	BMP180_Start();					//起始信号
	BMP180_SendByte(BMP180_SlaveAddress);//发送设备地址+写信号
	BMP180_SendByte(0xF4);			//写内部寄存器地址（ctrl_meas）
	BMP180_SendByte(0x2E);			//写内部寄存器数据（温度）
	BMP180_Stop();        			//发送停止信号
	Delay5ms();						//最大为4.5ms
	return (long)Multiple_read(0xF6);//从F6地址(out_msb)开始读取两字节
}
//-----------------------------------------------------------------
// 读气压
//-----------------------------------------------------------------
long BMP180ReadPressure() {
	long pressure = 0;				//气压变量
	BMP180_Start();					//起始信号
	BMP180_SendByte(BMP180_SlaveAddress);//发送设备地址+写信号
	BMP180_SendByte(0xF4);			//写内部寄存器地址（ctrl_meas）
	BMP180_SendByte(0x34);			//写内部寄存器数据(气压 OSS=0，4.5ms)
	BMP180_Stop();					//发送停止信号
	Delay5ms();						//最大转换时间4.5ms
	pressure = Multiple_read(0xF6);//从F6地址(out_msb)开始读取两字节
	pressure &= 0x0000FFFF;
	return pressure;
}
//-----------------------------------------------------------------
// 初始化BMP180(从0xAA~0xBE分别一次读取2字节系数,共11个校准系统)
//-----------------------------------------------------------------
void Init_BMP180() {
	ac1 = Multiple_read(0xAA);
	ac2 = Multiple_read(0xAC);
	ac3 = Multiple_read(0xAE);
	ac4 = Multiple_read(0xB0);
	ac5 = Multiple_read(0xB2);
	ac6 = Multiple_read(0xB4);
	b1 =  Multiple_read(0xB6);
	b2 =  Multiple_read(0xB8);
	mb =  Multiple_read(0xBA);
	mc =  Multiple_read(0xBC);
	md =  Multiple_read(0xBE);
}
//-----------------------------------------------------------------
// 转换（读取温度、气压，执行换算，并在LCD显示）
//-----------------------------------------------------------------
void BMP180Convert() {
	long ut, up;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;
	long temperature,pressure;
	ut = BMP180ReadTemp();			//连续两次读取温度
	ut = BMP180ReadTemp();
	up = BMP180ReadPressure();		//连续两次读取气压
	up = BMP180ReadPressure();
	x1 = ((long)ut - ac6) * ac5 >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;
	temperature = (b5 + 8) >> 4;
	conversion(temperature);		//温度分解转换到数组x
	DisplayOneChar(0, 1,'T');
	DisplayOneChar(0, 2,'E');
	DisplayOneChar(0, 3,'M');
	DisplayOneChar(0, 4,'P');		//温度显示
	DisplayOneChar(0, 5,':'); 
	DisplayOneChar(0, 8,x[2]+'0'); 
	DisplayOneChar(0, 9,x[1]+'0'); 
	DisplayOneChar(0,10,'.'); 
	DisplayOneChar(0,11,x[0]+'0'); 
	DisplayOneChar(0,12,0xDF);		//温度单位
	DisplayOneChar(0,13,'C'); 
	b6 = b5 - 4000;
	x1 = (b2 * (b6 * b6 >> 12)) >> 11;
	x2 = ac2 * b6 >> 11;
	x3 = x1 + x2;
	b3 = (((long)ac1 * 4 + x3) + 2)/4;
	x1 = ac3 * b6 >> 13;
	x2 = (b1 * (b6 * b6 >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (unsigned long) (x3 + 32768)) >> 15;
	b7 = ((unsigned long) up - b3) * (50000 >> OSS);
	if( b7 < 0x80000000)	p = (b7 * 2) / b4 ;
	else  					p = (b7 / b4) * 2;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	pressure = p + ((x1 + x2 + 3791) >> 4);
	conversion(pressure);			//气压分解转换到数组x
	DisplayOneChar(1, 1,'P');
	DisplayOneChar(1, 2,'R');
	DisplayOneChar(1, 3,'E');
	DisplayOneChar(1, 4,'S'); 		//显示气压
	DisplayOneChar(1, 5,':'); 
	DisplayOneChar(1, 6,x[5]+'0');
	DisplayOneChar(1, 7,x[4]+'0');
	DisplayOneChar(1, 8,x[3]+'0');
	DisplayOneChar(1, 9,x[2]+'0');
	DisplayOneChar(1,10,'.'); 
	DisplayOneChar(1,11,x[1]+'0');
	DisplayOneChar(1,12,'h');		//气压单位
	DisplayOneChar(1,13,'P');
	DisplayOneChar(1,14,'a');
}
//-----------------------------------------------------------------
// 数据分解转换函数
//-----------------------------------------------------------------
void conversion(long d) {
	long k = 100000; 	u8 i;
	for (i = 5; i >=1; i--) {
		x[i] = d / k; d -= x[i]*k; k /= 10;
	}
}