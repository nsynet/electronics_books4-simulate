//-----------------------------------------------------------------
//  名称: 1-Wire总线器件搜索及DS18B20操作命令头文件
//-----------------------------------------------------------------
#define INT8	signed char
#define u8  	unsigned char
#define u16 	unsigned int
sbit DQ = P1^7;										//DS18B20数据线 
//DS18B20 ROM命令集
#define SERACH_ROM				0xF0		//ROMCODE搜索命令
//#define READ_ROM				0x33		//读单ROMCODE命令
#define MATCH_ROM					0x55		//ROM匹配命令
//#define SKIP_ROM				0xCC		//跳过ROM命令
//#define ALARM_SERACH		0xEC		//查找报警ROM命令
//DS18B20功能命令集
#define CONVERT						0x44		//温度转换
#define WRITE_SCRATCHPAD	0x4E		//写DS18B20RAM
#define READ_SCRATCHPAD		0xBE		//读DS18B20RAM
#define COPY_SCRATCHPAD		0x48		//复制RAM数据到EEPROM
#define RECALL_EE					0xB8		//从EEPROM恢复数据到RAM
#define READ_POWER_SUPPLY	0xB4		//读器件供电方式
//-----------------------------------------------------------------
// 函数声明
//-----------------------------------------------------------------
u8 RESET();
u8 READ_ID_BIT();
u8 Read_Byte();
u8 Search_ROM1();
u8 Read_ROMCODE_Bit_i(u8 [],u8);
void Search_ALL_ROM();
void Save_ROMCODE_Bit_i(u8 [],u8 ,u8);
void Show_Romcode(u8, u8);
void Read_Slot();
void Write_DQ_bit(u8);
void CRC_8(u8 d);
void ROMCODE_Match(u8 *);
void Write_Byte(u8);
float Get_Temperature(u8 *);
