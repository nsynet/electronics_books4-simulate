#ifndef	__DS18B20__H
#define	__DS18B20__H

//DS18B20端口定义 
#define DS18B20_O PORTA
#define DS18B20_I PINA
#define DS18B20_C DDRA
#define DS18B20_L PA0

//DS18B20操作定义 
#define	BIT_SET(a,b)    a|=BIT(b) 
#define	BIT_CLR(a,b)    a&=~BIT(b)
#define	BIT_INV(a,b)    a^=BIT(b) 
#define	BIT_STATUS(a,b) a&BIT(b)
#define	CLR_DS18B20	BIT_CLR(DS18B20_O,DS18B20_L)     //数据线强制拉低
#define	SET_DS18B20	BIT_SET(DS18B20_O,DS18B20_L)     //数据线强制拉高，上拉
#define	HLD_DS18B20	BIT_SET(DS18B20_C,DS18B20_L)     //Mega16控制总线
#define	RLS_DS18B20	BIT_CLR(DS18B20_C,DS18B20_L)     //释放总线
#define	STU_DS18B20	BIT_STATUS(DS18B20_I,DS18B20_L)  //数据线的状态

extern unsigned char temp_buf[4];

//DS18B20初始化
unsigned char resetDS18B20(void);

//读取DS18B20的温度值
unsigned int readTempDS18B20(void);

//读取当前温度并解释
void Read_Temp(void);

#endif
