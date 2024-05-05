//-----------------------------------------------------------------
// 名称: SD驱动程序头文件
//-----------------------------------------------------------------
#ifndef __SDX_H__
#define __SDX_H__

#include "STC15xxx.h"
#include "FAT/mytype.h"
#include <intrins.h>

sbit SPI_CS			= P0^4;									//SD卡片选
sbit SPI_MOSI		= P0^5;									//SPI主机输出从机（SD）输入线
sbit SPI_MISO		= P0^7;									//SPI主机输入从机（SD）输出线
sbit SPI_CLK		= P0^6;									//SD卡时钟线
//-----------------------------------------------------------------
//相关宏定义
//-----------------------------------------------------------------
#define SD_VER_ERR								0x00	//无法识别的版本
#define SD_VER_MMC								0x01	//版本号：MMC
#define SD_VER_V1									0x02	//版本号：SD1.0
#define SD_VER_V2									0x03	//版本号：SD2.0(普通SD)
#define SD_VER_V2HC								0x04	//版本号：SD2.0(高容量SDHC)

#define INIT_ERROR								0x01	//初始化错误
#define INIT_CMD0_ERROR						0x02	//CMD0错误
#define INIT_CMD1_ERROR						0x03	//CMD1错误
#define INIT_SDV2_ACMD41_ERROR		0x04	//ACMD41错误
#define INIT_SDV1_ACMD41_ERROR		0x05	//ACMD41错误
#define WRITE_CMD24_ERROR					0x06	//写块时产生CMD24错误
#define WRITE_BLOCK_ERROR					0x07	//写块错误
#define READ_BLOCK_ERROR					0x08	//读块错误
#define WRITE_CMD25_ERROR					0x09	//在连续多块写时产生CMD25错误
#define WRITE_NBLOCK_ERROR				0x0A	//连续多块写失败
#define READ_CMD18_ERROR					0x0B	//在连续多块读时产生CMD18错误
#define GET_CSD_ERROR							0x0C	//读CSD失败 

#define TRY_TIME									100			//写SD卡命令重试次数
//-----------------------------------------------------------------
u8 SD_Init();															//SD卡初始化
u8 SD_Write_Sector(u32 addr, u8* buffer);	//将buffer数据缓冲区中的数据写入地址为addr的扇区中
u8 SD_Read_Sector(u32 addr, u8* buffer);	//从地址为addr的扇区中读取数据到buffer数据缓冲区中
u8 SD_Write_nSector(u32 nsec, u32 addr, u8* buffer); //将buffer数据缓冲区中的数据写入起始地址为addr的nsec个连续扇区中
u8 SD_Read_nSector(u32 nsec, u32 addr, u8* buffer); //将buffer数据缓冲区中的数据写入起始地址为addr的nsec个连续扇区中
u8 SD_Erase_nSector(u32 addr_sta, u32 addr_end);
u32 SD_GetTotalSec(void);													//获取SD卡的总扇区数

#endif