//-----------------------------------------------------------------
// ����: SD��������ͷ�ļ�
//-----------------------------------------------------------------
#ifndef __SDX_H__
#define __SDX_H__

#include "STC15xxx.h"
#include "FAT/mytype.h"
#include <intrins.h>

sbit SPI_CS			= P0^4;									//SD��Ƭѡ
sbit SPI_MOSI		= P0^5;									//SPI��������ӻ���SD��������
sbit SPI_MISO		= P0^7;									//SPI��������ӻ���SD�������
sbit SPI_CLK		= P0^6;									//SD��ʱ����
//-----------------------------------------------------------------
//��غ궨��
//-----------------------------------------------------------------
#define SD_VER_ERR								0x00	//�޷�ʶ��İ汾
#define SD_VER_MMC								0x01	//�汾�ţ�MMC
#define SD_VER_V1									0x02	//�汾�ţ�SD1.0
#define SD_VER_V2									0x03	//�汾�ţ�SD2.0(��ͨSD)
#define SD_VER_V2HC								0x04	//�汾�ţ�SD2.0(������SDHC)

#define INIT_ERROR								0x01	//��ʼ������
#define INIT_CMD0_ERROR						0x02	//CMD0����
#define INIT_CMD1_ERROR						0x03	//CMD1����
#define INIT_SDV2_ACMD41_ERROR		0x04	//ACMD41����
#define INIT_SDV1_ACMD41_ERROR		0x05	//ACMD41����
#define WRITE_CMD24_ERROR					0x06	//д��ʱ����CMD24����
#define WRITE_BLOCK_ERROR					0x07	//д�����
#define READ_BLOCK_ERROR					0x08	//�������
#define WRITE_CMD25_ERROR					0x09	//���������дʱ����CMD25����
#define WRITE_NBLOCK_ERROR				0x0A	//�������дʧ��
#define READ_CMD18_ERROR					0x0B	//����������ʱ����CMD18����
#define GET_CSD_ERROR							0x0C	//��CSDʧ�� 

#define TRY_TIME									100			//дSD���������Դ���
//-----------------------------------------------------------------
u8 SD_Init();															//SD����ʼ��
u8 SD_Write_Sector(u32 addr, u8* buffer);	//��buffer���ݻ������е�����д���ַΪaddr��������
u8 SD_Read_Sector(u32 addr, u8* buffer);	//�ӵ�ַΪaddr�������ж�ȡ���ݵ�buffer���ݻ�������
u8 SD_Write_nSector(u32 nsec, u32 addr, u8* buffer); //��buffer���ݻ������е�����д����ʼ��ַΪaddr��nsec������������
u8 SD_Read_nSector(u32 nsec, u32 addr, u8* buffer); //��buffer���ݻ������е�����д����ʼ��ַΪaddr��nsec������������
u8 SD_Erase_nSector(u32 addr_sta, u32 addr_end);
u32 SD_GetTotalSec(void);													//��ȡSD������������

#endif