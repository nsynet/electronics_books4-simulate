//-----------------------------------------------------------------
// 设备驱动程序头文件
//-----------------------------------------------------------------
#ifndef _DEVICE_IO_H_
#define _DEVICE_IO_H_
struct FAT_IO_Ctl 
{
	u32 just_sec;
	u8 just_dev;
};

u8 FAT_Device_Init(void);
u8 FAT_Device_Read_Sector(u32 addr, u8* buffer);
u8 FAT_Device_Write_Sector(u32 addr, u8* buffer);
u8 FAT_Device_Read_nSector(u32 nsec, u32 addr, u8* buffer);
u8 FAT_Device_Write_nSector(u32 nsec, u32 addr, u8* buffer);
u8 FAT_Device_Clear_nSector(u32 nsec, u32 addr);

#endif