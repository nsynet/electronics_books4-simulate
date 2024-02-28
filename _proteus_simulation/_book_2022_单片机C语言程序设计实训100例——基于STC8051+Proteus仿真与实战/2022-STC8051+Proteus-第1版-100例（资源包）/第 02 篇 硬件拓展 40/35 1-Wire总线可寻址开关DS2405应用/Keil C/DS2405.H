//-------------------------- ds2405.h -----------------------------
//  名称: DS2405头文件
//-----------------------------------------------------------------
#define u8	unsigned char
#define u16	unsigned int
sbit DQ = P0^0;						//DS2405引脚定义
//DS2405 ROM命令集
#define SERACH_ROM	0xF0			//搜索ROMCODE
#define READ_ROM	0x33			//读单个ROMCODE
#define MATCH_ROM	0x55			//ROMCODE匹配
#define SKIP_ROM	0xCC			//跳过ROM匹配
//DS2405函数声明
u8 DS_Read_Byte();					//读一字节
void DS_Write_Byte(u8 dat);			//写一字节
void DS_Match_ROM(u8 sROMID[]);		//匹配ROM函数
void DS_Read_ROM(u8 sSerialNumber[]);//读ROM函数