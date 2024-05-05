//-----------------------------------------------------------------
//  ����: 1-Wire��������������DS18B20��������ͷ�ļ�
//-----------------------------------------------------------------
#define INT8	signed char
#define u8  	unsigned char
#define u16 	unsigned int
sbit DQ = P1^7;										//DS18B20������ 
//DS18B20 ROM���
#define SERACH_ROM				0xF0		//ROMCODE��������
//#define READ_ROM				0x33		//����ROMCODE����
#define MATCH_ROM					0x55		//ROMƥ������
//#define SKIP_ROM				0xCC		//����ROM����
//#define ALARM_SERACH		0xEC		//���ұ���ROM����
//DS18B20�������
#define CONVERT						0x44		//�¶�ת��
#define WRITE_SCRATCHPAD	0x4E		//дDS18B20RAM
#define READ_SCRATCHPAD		0xBE		//��DS18B20RAM
#define COPY_SCRATCHPAD		0x48		//����RAM���ݵ�EEPROM
#define RECALL_EE					0xB8		//��EEPROM�ָ����ݵ�RAM
#define READ_POWER_SUPPLY	0xB4		//���������緽ʽ
//-----------------------------------------------------------------
// ��������
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
