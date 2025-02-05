//----------------------------- I2C.h -----------------------------
// 名称: IIC总线通用宏及函数
//-----------------------------------------------------------------
#ifndef ___I2C___
#define ___I2C___
//-----------------------------------------------------------------
void Delay() { //@11.0592MHz //约5us
	u8 i;
	_nop_();
	i = 11;
	while (--i);
}
//总线启动	-------------------------------------------------------
#define IIC_Start()		\
{ SDA = 1; Delay(); SCL = 1; Delay(); SDA = 0; Delay(); /*SCL=0;*/}
//总线停止	-------------------------------------------------------
#define IIC_Stop()		\
{ SDA = 0; Delay(); SCL = 1; Delay(); SDA = 1; Delay(); /*SCL=0;*/}
//-----------------------------------------------------------------
//以下3个有关应答的宏定义均生成第9个时钟脉冲,读取应答或发送应答/非应答
//1.主机读从机应答	-----------------------------------------------
//注：SDA=1设为输入,准备读取应答位,要根据应答位作出响应时可引用F0)
#define IIC_Rd_Ack()	\
{ SDA=1;Delay();SCL=1;Delay();/*F0=!SDA;*/Delay();SCL=0; }	//OK版
//{ SDA=1;Delay();SCL=1;Delay();SCL=0;Delay();F0=!SDA; }	//OK版
//以下2个宏执行的前一时刻SCL均已为0，此时SDA处于允许变化的时钟窗口
//2.主机发送应答位	-----------------------------------------------
//时序：SCL此前为低,SDA先高,后拉低>4us,SCL维持高>4us,最后SCL置低,SDA还原为高
#define IIC_Ack()		\
{ SDA = 1; Delay(); SDA = 0; Delay(); SCL = 1; Delay(); SCL = 0; SDA = 1; }
//3.主机发送非应答位	-------------------------------------------
//时序：SCL此前为低,SDA先低,后拉高>4us,SCL维持高>4us,最后SCL置低,SDA还原为低
#define IIC_NAck()		\
{ SDA = 0; Delay(); SDA = 1; Delay(); SCL = 1; Delay(); SCL = 0; SDA = 0;}
//-----------------------------------------------------------------
// 主机向IIC总线写一字节
//-----------------------------------------------------------------
bit IIC_WriteByte(u8 dat) {
	u8 i; SCL = 0;
	for(i = 0; i < 8; i++) {			//8个时钟脉冲
		Delay(); dat <<= 1; SDA = CY;	//高位优先输出
		Delay(); SCL = 1; Delay(); SCL = 0;
	}//时钟序列：SCL = 0 1 0 1 0 1 0 1  0 1 0 1 0 1 0 1 -- 0
	Delay(); 
	IIC_Rd_Ack();						//读取从机应答
	return F0;							//返回应答状态
}
//-----------------------------------------------------------------
// 主机从IIC总线读一字节
//-----------------------------------------------------------------
u8 IIC_ReadByte() {
	u8 i,dat = 0x00; //SDA = 1;			//置数据线为输入
	for(i = 0; i < 8; i++) {			//8时钟周期循环读取1字节
		Delay(); SDA = 1;
		Delay(); SCL = 1; 				//时钟线置高电平
		Delay(); dat = (dat<<1) | SDA;	//主机读取1位
		Delay(); SCL = 0; 				//时钟线置低电平
	}//时钟序列：SCL = 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 
	Delay();
	return dat;							//返回读取的字节
}
//-----------------------------------------------------------------
#endif