//---------------------------- main.c -----------------------------
//  ����: SD��FAT32�ļ�ϵͳ��д���� (����znFAT)
//-----------------------------------------------------------------
//  ˵��: ��������ʱ����ȡ1·��������״̬��1·AD�������ֵ��Ȼ��ֱ�
//        д��2����ͬ�ļ������а����������������/mycount.txt��ADת��
//        ֵ������/data/myadc.txt������K1��K2ʱ���ֱ���ʾ����
//        �ļ�����������ݡ�
// ����˵����Memory Model��Large 64K Model
//-----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "fat/FAT.h"
#include "sd.h"
#include "uart.h"
#include "ds1302.h"
//-----------------------------------------------------------------
#define ADC_POWER 		0x80			//ADC��Դ����λ
#define ADC_FLAG 			0x10			//ADC��ɱ�־
#define ADC_START 		0x08			//ADC��ʼ����λ
#define ADC_SPEEDLL		0x00			//540��ʱ��
#define ADC_SPEEDL 		0x20			//360��ʱ��
#define ADC_SPEEDH 		0x40			//180��ʱ��
#define ADC_SPEEDHH		0x60			//90��ʱ��
//-----------------------------------------------------------------
struct FATInfo	idata SDInfo;			//��ʼ����������
struct DateTime	idata dt;				//������ʱ��
struct FileInfo	idata file1;			//�ļ���Ϣ
struct FileInfo	idata file2;			//�ļ���Ϣ
//-----------------------------------------------------------------
sbit S1 = P3^4;							//����ʱɾ��ԭʼ�ļ��п��ƿ���
sbit K1 = P3^6;							//��ȡSD��ADC���ݲ���ʾ
sbit K2 = P3^7;							//��ȡSD�������������ݲ���ʾ
sbit LED0 = P2^0;						//AD����ת��ָʾ��
sbit LED1 = P2^3;						//������������ָʾ��
sbit LED2 = P2^6;						//SD����д����ָʾ��
volatile bit sLED0 = 0,sLED1 = 0,sLED2 = 0;//����ָʾ����ʾ���Ʊ�ʶ
u16 res,res1,res2;						//SD�����ļ�����������
//-----------------------------------------------------------------
void InitADC();
u16 GetADCResult(u8 ch);
void Timer0Init();
u32 WriteTextString(struct FileInfo *pf,char *s);
extern void delay_ms(u8);
extern void GetDateTime() ;
extern u8 DateTime[7];
//-----------------------------------------------------------------
int	preKeyCount = 0,KeyCount = 0;		//����������ʼֵ
char	KeyStrBuff[10];					//���������ַ���ת������
u16		ADC_Value = 0x0000;
u8		ADCStrBuff[20];					//ADֵ�ַ���ת������
int		ADC_Voltage;					//�Ŵ�100���ĵ�ѹֵ���Ա�ֽ⣩
u8		ReadBuff[513];
//-----------------------------------------------------------------
// STC�˿ڡ���ʱ�������ڡ�ADC�ȳ�ʼ��
//-----------------------------------------------------------------
void InitSTC() {
	
	
	
	
}
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	u32 i = 0, j = 0, k = 0, len = 0;
	InitSTC();
	UART_Send_Str("���ڳ�ʼ�����.\r\a");
	sLED2 = 1;
	FAT_Device_Init();					//�洢�豸��ʼ��
	UART_Send_Str("SD����ʼ�����.\r\a");
	FAT_Select_Device(0, &SDInfo);		//ѡ���豸
	UART_Send_Str("��ʼ��ʼ���ļ�ϵͳ...\r\a");
	res = FAT_Init();					//�ļ�ϵͳ��ʼ��
	if (!res){							//�ļ�ϵͳ��ʼ���ɹ�
		UART_Send_Str("�ļ�ϵͳ��ʼ���ɹ�.\r\n");
		UART_Send_StrNum("BPB������:\t",	SDInfo.BPB_Sector_No);
		UART_Send_StrNum("SD��������:\t",	SDInfo.Total_SizeKB);
		UART_Send_StrNum("ÿ�����ֽ�:\t",	SDInfo.BytesPerSector);
		UART_Send_StrNum("FATռ������:\t",	SDInfo.FATsectors);
		UART_Send_StrNum("ÿ��������:\t",	SDInfo.SectorsPerClust);
		UART_Send_StrNum("FAT��������:\t",	SDInfo.FirstFATSector);
		UART_Send_StrNum("��һ��Ŀ¼��������:\t",SDInfo.FirstDirSector);
		UART_Send_StrNum("�ļ�ϵͳ������:\t",SDInfo.FSINFO_Sec);
		UART_Send_StrNum("��һ�ɴغ�:\t",	SDInfo.Next_Free_Cluster);
		UART_Send_StrNum("���ôظ���:\t",	SDInfo.Free_nCluster);
	}
	else {	//�ļ�ϵͳ��ʼ��ʧ��
		UART_Send_StrNum("�ļ�ϵͳ��ʼ��ʧ�ܣ�������:\t", res);
	}
	//-------------------------------------------------------------
	//���S1������ɾ��������ʼ�ļ����ؽ��ļ�
	if (S1 == 0) {
		FAT_Delete_File("/mycount.txt");	//ɾ�����������ļ�
		FAT_Delete_File("/data/myadc.txt");//ɾ��ADת�������ļ�
		GetDateTime();						//��ȡDS1302����ʱ��
		//�����ļ�����ʱ������
		dt.date.year	= 2000+DateTime[6];
		dt.date.month	= DateTime[4];
		dt.date.day 	= DateTime[3];
		dt.time.hour	= DateTime[2];
		dt.time.min		= DateTime[1];
		dt.time.sec		= DateTime[0];
		//����Ŀ¼������ȷ��/data����,data�����б�ܲ���ʡ�ԣ�
		res = FAT_Create_Dir("/data/", &dt);
		//�����ļ��м�����ļ�
		res1 = FAT_Create_File(&file1, "/mycount.txt",		&dt);
		P6 = res1;
		res2 = FAT_Create_File(&file2, "/data/myadc.txt",	&dt);
		if (res1 || res2) goto Err;		//���������ֱ���˳�
		KeyCount = 0;					//��������������ֵ��Ϊ0
		//������ֵд���ı��ļ�
		if (!WriteTextString(&file1,"0000")) goto Err;
	}
	//-------------------------------------------------------------
	//���S1δ������������ļ������ȴӰ����ļ��ж�ȡ������ֵ
	else {
		res1 = FAT_Open_File(&file1, "/mycount.txt",	0, 1);
		res2 = FAT_Open_File(&file2, "/data/myadc.txt",0, 1);
		//�Ӱ��������ļ��ж�ȡ����������ֵ
		len = FAT_ReadData(&file1,0,4,KeyStrBuff);
		//����ļ����Ȳ���4�ֽڣ����ʾ�ļ����쳣�޸Ļ�����
		//Ϊ�淶�����ļ�������Ĵ�����ɾ�����ļ���Ȼ���ؽ���д��"0000"
		if (len != 4) {
			FAT_Delete_File("/mycount.txt");
			res1 = FAT_Create_File(&file1, "/mycount.txt", &dt);
			if (res1 || !WriteTextString(&file1,"0000")) goto Err;
		} else {
			for (i = 0; i < 4 && i < len; i++) {
				if (KeyStrBuff[i] >= '0' && KeyStrBuff[i] <= '9') 
					KeyCount = KeyCount * 10 + KeyStrBuff[i] - '0';
				else break;
			}
		}
		FAT_Close_File(&file1);	//�ر��ļ�
	}
	if (!res1) EX0 = 1;		//����INT0�жϣ�ʹ�ܰ���������дSD���ļ�
	//-------------------------------------------------------
	if (res2) goto Err;		//file2�쳣���˳�������ʼADת���뱣��
	else {
		len = file2.File_Size;
		if (len >= 2) {
			//ȡ�ļ���ĩβ���ֽڽ����ж�
			len = FAT_ReadData(&file2,len-2,2,ADCStrBuff);
			if (len == 2	&& ADCStrBuff[0] != 0x0D 
							&& ADCStrBuff[1] != 0x0A) {
				//�ڳ�ʼ�ļ����ϴ��ļ�ĩβ��ӻ��з���ָ���
				if (!WriteTextString(&file2,
					"\x0D\x0A-------------\x0D\x0A")) goto Err;
			}
		}
	}
	while (1) {
		//-------------------------------------------------------
		// 1.��ȡADֵ��10λ���ȣ���дSD���ļ�
		//-------------------------------------------------------

		
		
		
		//-------------------------------------------------------
		// 2.д�밴���������ֵ�������������INT0�ж�����ɣ�
		//-------------------------------------------------------

		
		
		
		//-------------------------------------------------------
		// 3.��ȡ��ʷ���ݼ�¼
		//-------------------------------------------------------

		
		
		
		
		//-------------------------------------------------------
		delay_ms(10);			//�ӿ�ɼ��ɵ�С��ʱ�������ɼ��ɼ�����ʱ
		//-------------------------------------------------------
	}
	Err:
	sLED0 = 0; sLED1 = 0; sLED2 = 0; UART_Send_Str("�ļ�����ʧ��!��");
	FAT_Flush_FS();				//ˢ���ļ�ϵͳ
	while (1) ;
}
//-----------------------------------------------------------------
// д�ַ������ı��ļ�
//-----------------------------------------------------------------
u32 WriteTextString(struct FileInfo *pf,char *s) {
	u32 len = FAT_WriteData(pf, strlen(s), s); 
	if (len == ERR_OVER_FILE_MAX_SIZE || len == ERR_OVER_DISK_SPACE) {
		UART_Send_Str("ADת��ֵдSD���ļ�����!");
		return 0;
	} else return len;
}
//-----------------------------------------------------------------
// ��ʼ��ADC
//-----------------------------------------------------------------
void InitADC() {
	P1ASF = 1<<1; 				//P1.1��ΪAD��
	ADC_RES = 0; 				//�������Ĵ���
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
	delay_ms(2); 				//ADC�ϵ粢��ʱ
}
//-----------------------------------------------------------------
// ��ȡָ��ͨ��ADC���
//-----------------------------------------------------------------
u16 GetADCResult(u8 ch) {
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
	delay_ms(1);
	while (!(ADC_CONTR & ADC_FLAG));	//�ȴ�ADCת�����
	ADC_CONTR &= ~ADC_FLAG; 			//�ر�ADC
	return (ADC_RES<<2) | ADC_RESL;		//���ؽ��
}
//-----------------------------------------------------------------
// T0��ʼ��(16λ12Tģʽ,20����@22.1184MHz)
//-----------------------------------------------------------------
void Timer0Init() {
	AUXR &= 0x7F;				//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;				//���ö�ʱ��ģʽ
	TL0 = 0x00;					//���ö�ʱ��ֵ
	TH0 = 0x70;					//���ö�ʱ��ֵ
	TF0 = 0;					//���TF0��־
	TR0 = 1;					//��ʱ��0��ʼ��ʱ
}
//-----------------------------------------------------------------
// T0�жϺ���(����LED��˸)
//-----------------------------------------------------------------
void LED_Flash() interrupt 1 {
	static u8 T0_Count = 0,T1_Count = 0,T2_Count = 0, Tx = 0;
	//2*20=40ms����ADת��ָʾ����˸
	if (sLED0 && ++T0_Count == 2) {	
		LED0 ^= 1; 
		T0_Count = 0;
	} else LED0 = 1;
	//2*20=40ms���ư���ָʾ����˸
	if (sLED1 && ++T1_Count == 2) {
			LED1 ^= 1; 
			if (++Tx == 6) { sLED1 = 0; LED1 = 1; Tx = 0; }
			T1_Count = 0;
	} else LED1 = 1;
	//4*20=80ms����SD��д����ָʾ����˸
	if (sLED2 && ++T2_Count == 4) {	
		LED2 ^= 1; ;
		T2_Count = 0;
	} else LED2 = 1;
}
//-----------------------------------------------------------------
// INT0�жϺ���
//-----------------------------------------------------------------
void EX_INT0() interrupt 0 {
	if ((P3 & (1<<2)) == 0x00) {
		sLED1 = 1;				//��������ָʾ������˸
		//����ֵ����(����Ϊ0000~9999)
		if (++KeyCount > 9999) KeyCount = 0;
	}
}