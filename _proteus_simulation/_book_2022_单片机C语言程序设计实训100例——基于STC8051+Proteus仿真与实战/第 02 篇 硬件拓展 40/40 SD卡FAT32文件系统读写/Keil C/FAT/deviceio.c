//-----------------------------------------------------------------
// ����: �ײ��豸��������
//-----------------------------------------------------------------
#include "mytype.h"
#include "config.h"
#include "deviceio.h" 
#include "SD.h"	

struct FAT_IO_Ctl ioctl;
extern u8 Dev_No;
extern u8 * FAT_Buffer;
//-----------------------------------------------------------------
// �洢�豸��ʼ��
//-----------------------------------------------------------------
u8 FAT_Device_Init() {
	u8 res = 0, err = 0;
	ioctl.just_dev = 0;
	ioctl.just_sec = 0; 
	res = SD_Init();
	if (res) err |= 0x01;
	return err; 
}
//-----------------------------------------------------------------
// FAT�Ĵ洢�豸����������ȡ�����ӿ�
//-----------------------------------------------------------------
u8 FAT_Device_Read_Sector(u32 addr, u8* buffer){
	if (buffer == FAT_Buffer) 
	{
		if (ioctl.just_dev == Dev_No 
		 && (ioctl.just_sec == addr && 0 != ioctl.just_sec))
		{
			return 0;
		}
		else 
		{
			ioctl.just_dev = Dev_No;
			ioctl.just_sec = addr;
		}
	}
	switch (Dev_No)	{
		case 0:
			while (SD_Read_Sector(addr, buffer)) ;
			break;
	}
	return 0;
}
//-----------------------------------------------------------------
// FAT�Ĵ洢�豸��������д�������ӿ�
//-----------------------------------------------------------------
u8 FAT_Device_Write_Sector(u32 addr, u8* buffer) {
	if (buffer == FAT_Buffer) {
		ioctl.just_dev = Dev_No;
		ioctl.just_sec = addr; 
	}
	switch (Dev_No)	{
		case 0:
			while (SD_Write_Sector(addr, buffer)) ;
			break;
	}
	return 0;
}
//-----------------------------------------------------------------
// FAT�洢�豸��������������ȡ�����ӿ�
//-----------------------------------------------------------------
u8 FAT_Device_Read_nSector(u32 nsec, u32 addr, u8* buffer) {
	u32 i = 0;
	if (0 == nsec) return 0;
#ifndef USE_MULTISEC_R
	switch (Dev_No) {
		case 0:
			for (i = 0; i < nsec; i++) 	{
				while (SD_Read_Sector(addr + i, buffer)) ;
				buffer += 512;
			}
			break;
	}

#else

	switch (Dev_No)	{
		case 0:
			while (SD_Read_nSector(nsec, addr, buffer)) ;
			//case 1:
			//while(Device1_Read_nSector(nsec,addr,buffer));
	}
#endif

	return 0;
}
//-----------------------------------------------------------------
// FAT�洢�豸������������д�������ӿ�
//-----------------------------------------------------------------
u8 FAT_Device_Write_nSector(u32 nsec, u32 addr, u8* buffer) {
	u32 i = 0;
	if (0 == nsec) return 0;

#ifndef USE_MULTISEC_W //�˺�����Ƿ�ʹ��Ӳ������������д�뺯��

	switch (Dev_No)	{
		case 0:
			for (i = 0; i < nsec; i++) 	{
				while (SD_Write_Sector(addr + i, buffer)) ;
				buffer += 512;
			}
			break;
	}
#else
	switch (Dev_No) {
		case 0:
			while (SD_Write_nSector(nsec, addr, buffer)) ;
			break;
			//case 1:
			//while(Device1_Write_nSector(nsec,addr,buffer));
	}
#endif
	return 0;
}
//-----------------------------------------------------------------
// FAT�洢�豸��������������0�����ӿ�
//-----------------------------------------------------------------
u8 FAT_Device_Clear_nSector(u32 nsec, u32 addr){
#ifndef USE_MULTISEC_CLEAR 
	u32 i = 0;
	for (i = 0; i < 512; i++)	{
		FAT_Buffer[i] = 0;
	}
	switch (Dev_No) {
		case 0:
			for (i = 0; i < nsec; i++) 	{
				while (SD_Write_Sector(addr + i, FAT_Buffer)) ;
			}
			break;
	}
#else
	switch (Dev_No) {
		case 0:
			return SD_Erase_nSector(nsec, addr); 
	}

#endif
	ioctl.just_dev = Dev_No;
	ioctl.just_sec = (addr + nsec - 1);
	return 0;
}