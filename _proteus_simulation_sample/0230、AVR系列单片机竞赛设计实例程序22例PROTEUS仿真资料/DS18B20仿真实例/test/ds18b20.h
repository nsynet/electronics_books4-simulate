#ifndef	__DS18B20__H
#define	__DS18B20__H

//DS18B20�˿ڶ��� 
#define DS18B20_O PORTA
#define DS18B20_I PINA
#define DS18B20_C DDRA
#define DS18B20_L PA0

//DS18B20�������� 
#define	BIT_SET(a,b)    a|=BIT(b) 
#define	BIT_CLR(a,b)    a&=~BIT(b)
#define	BIT_INV(a,b)    a^=BIT(b) 
#define	BIT_STATUS(a,b) a&BIT(b)
#define	CLR_DS18B20	BIT_CLR(DS18B20_O,DS18B20_L)     //������ǿ������
#define	SET_DS18B20	BIT_SET(DS18B20_O,DS18B20_L)     //������ǿ�����ߣ�����
#define	HLD_DS18B20	BIT_SET(DS18B20_C,DS18B20_L)     //Mega16��������
#define	RLS_DS18B20	BIT_CLR(DS18B20_C,DS18B20_L)     //�ͷ�����
#define	STU_DS18B20	BIT_STATUS(DS18B20_I,DS18B20_L)  //�����ߵ�״̬

extern unsigned char temp_buf[4];

//DS18B20��ʼ��
unsigned char resetDS18B20(void);

//��ȡDS18B20���¶�ֵ
unsigned int readTempDS18B20(void);

//��ȡ��ǰ�¶Ȳ�����
void Read_Temp(void);

#endif
