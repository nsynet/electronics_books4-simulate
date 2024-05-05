//------------------------- BMP180.c ------------------------------
// ���ƣ�BMP180��������
//-----------------------------------------------------------------
#include "BMP180.h"
//BMP180��11��У׼ϵ�������ݼ����ֲᶨ�壩
short ac1, ac2, ac3;
unsigned short ac4, ac5, ac6;
short b1, b2, mb, mc, md;
sbit SCL = P3^0;					//ʱ����
sbit SDA = P3^1;					//������
int	dis_data;						//����
u8 x[6];							//������ʱ�ֽ⻺��
//-----------------------------------------------------------------
// ��ʱ����
//-----------------------------------------------------------------
void Delay5us() {					//@12MHz
	u8 i = 12; _nop_(); nop_(); while (--i);
}
void Delay5ms() {					//@12MHz
	u8 i = 59, j = 90;
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
// ��ʼ�ź�
//-----------------------------------------------------------------
void BMP180_Start() {

}
//-----------------------------------------------------------------
// ֹͣ�ź�
//-----------------------------------------------------------------
void BMP180_Stop() {

}
//-----------------------------------------------------------------
// ����Ӧ���ź�:��ڲ���:ack (0:ACK 1:NAK)
//-----------------------------------------------------------------
void BMP180_SendACK(bit ack) {

}
//-----------------------------------------------------------------
// ����Ӧ���ź�
//-----------------------------------------------------------------
bit BMP180_RecvACK() {

} 
//-----------------------------------------------------------------
// ��IIC���߷���һ�ֽ�����
//-----------------------------------------------------------------
void BMP180_SendByte(u8 dat) {

}
//-----------------------------------------------------------------
// ��IIC���߽���һ�ֽ�����
//-----------------------------------------------------------------
u8 BMP180_RecvByte() {

}
//-----------------------------------------------------------------
// ���ֽ�д��BMP180�ڲ�����
//-----------------------------------------------------------------
void Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data) {
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(SlaveAddress);	//д�豸��ַ+д�ź�
	BMP180_SendByte(REG_Address);	//д�ڲ��Ĵ�����ַ
	BMP180_SendByte(REG_data);		//д�ڲ��Ĵ�������
	BMP180_Stop();					//����ֹͣ�ź�
}
//-----------------------------------------------------------------
// ���ֽڶ�ȡBMP180�ڲ�����
//-----------------------------------------------------------------
u8 Single_Read(u8 REG_Address) {
	u8 REG_data;
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(BMP180_SlaveAddress);	//�����豸��ַ+д�ź�
	BMP180_SendByte(REG_Address);	//д�ڲ��Ĵ�����ַ
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(BMP180_SlaveAddress+1); //�����豸��ַ+���ź�
	REG_data=BMP180_RecvByte();		//�����ڲ��Ĵ�������
	BMP180_SendACK(1);				//���ͷ�Ӧ��NACK
	BMP180_Stop();					//ֹͣ�ź�
	return REG_data; 
}
//-----------------------------------------------------------------
// ��BMP180�ڲ�����(���ֽ�)
//-----------------------------------------------------------------
short Multiple_read(u8 ST_Address) {
	u8 msb, lsb;
	short _data;
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(BMP180_SlaveAddress);	//�����豸��ַ+д�ź�
	BMP180_SendByte(ST_Address);	//д�ڲ��Ĵ�����ַ
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(BMP180_SlaveAddress+1);//�����豸��ַ+���ź�
	msb = BMP180_RecvByte();		//��ȡ���ݸ��ֽ�
	BMP180_SendACK(0);				//���ʹ�ӦACK
	lsb = BMP180_RecvByte();		//��ȡ���ݵ��ֽ�
	BMP180_SendACK(1);				//���ͷ�Ӧ��NACK
	BMP180_Stop();					//ֹͣ�ź�
	Delay5ms();
	_data = (msb << 8) | lsb;
	return _data;
}
//-----------------------------------------------------------------
// ���¶�
//-----------------------------------------------------------------
long BMP180ReadTemp() {
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(BMP180_SlaveAddress);//�����豸��ַ+д�ź�
	BMP180_SendByte(0xF4);			//д�ڲ��Ĵ�����ַ��ctrl_meas��
	BMP180_SendByte(0x2E);			//д�ڲ��Ĵ������ݣ��¶ȣ�
	BMP180_Stop();        			//����ֹͣ�ź�
	Delay5ms();						//���Ϊ4.5ms
	return (long)Multiple_read(0xF6);//��F6��ַ(out_msb)��ʼ��ȡ���ֽ�
}
//-----------------------------------------------------------------
// ����ѹ
//-----------------------------------------------------------------
long BMP180ReadPressure() {
	long pressure = 0;				//��ѹ����
	BMP180_Start();					//��ʼ�ź�
	BMP180_SendByte(BMP180_SlaveAddress);//�����豸��ַ+д�ź�
	BMP180_SendByte(0xF4);			//д�ڲ��Ĵ�����ַ��ctrl_meas��
	BMP180_SendByte(0x34);			//д�ڲ��Ĵ�������(��ѹ OSS=0��4.5ms)
	BMP180_Stop();					//����ֹͣ�ź�
	Delay5ms();						//���ת��ʱ��4.5ms
	pressure = Multiple_read(0xF6);//��F6��ַ(out_msb)��ʼ��ȡ���ֽ�
	pressure &= 0x0000FFFF;
	return pressure;
}
//-----------------------------------------------------------------
// ��ʼ��BMP180(��0xAA~0xBE�ֱ�һ�ζ�ȡ2�ֽ�ϵ��,��11��У׼ϵͳ)
//-----------------------------------------------------------------
void Init_BMP180() {
	ac1 = Multiple_read(0xAA);
	ac2 = Multiple_read(0xAC);
	ac3 = Multiple_read(0xAE);
	ac4 = Multiple_read(0xB0);
	ac5 = Multiple_read(0xB2);
	ac6 = Multiple_read(0xB4);
	b1 =  Multiple_read(0xB6);
	b2 =  Multiple_read(0xB8);
	mb =  Multiple_read(0xBA);
	mc =  Multiple_read(0xBC);
	md =  Multiple_read(0xBE);
}
//-----------------------------------------------------------------
// ת������ȡ�¶ȡ���ѹ��ִ�л��㣬����LCD��ʾ��
//-----------------------------------------------------------------
void BMP180Convert() {
	long ut, up;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;
	long temperature,pressure;
	ut = BMP180ReadTemp();			//�������ζ�ȡ�¶�
	ut = BMP180ReadTemp();
	up = BMP180ReadPressure();		//�������ζ�ȡ��ѹ
	up = BMP180ReadPressure();
	x1 = ((long)ut - ac6) * ac5 >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;
	temperature = (b5 + 8) >> 4;
	conversion(temperature);		//�¶ȷֽ�ת��������x
	DisplayOneChar(0, 1,'T');
	DisplayOneChar(0, 2,'E');
	DisplayOneChar(0, 3,'M');
	DisplayOneChar(0, 4,'P');		//�¶���ʾ
	DisplayOneChar(0, 5,':'); 
	DisplayOneChar(0, 8,x[2]+'0'); 
	DisplayOneChar(0, 9,x[1]+'0'); 
	DisplayOneChar(0,10,'.'); 
	DisplayOneChar(0,11,x[0]+'0'); 
	DisplayOneChar(0,12,0xDF);		//�¶ȵ�λ
	DisplayOneChar(0,13,'C'); 
	b6 = b5 - 4000;
	x1 = (b2 * (b6 * b6 >> 12)) >> 11;
	x2 = ac2 * b6 >> 11;
	x3 = x1 + x2;
	b3 = (((long)ac1 * 4 + x3) + 2)/4;
	x1 = ac3 * b6 >> 13;
	x2 = (b1 * (b6 * b6 >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (unsigned long) (x3 + 32768)) >> 15;
	b7 = ((unsigned long) up - b3) * (50000 >> OSS);
	if( b7 < 0x80000000)	p = (b7 * 2) / b4 ;
	else  					p = (b7 / b4) * 2;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	pressure = p + ((x1 + x2 + 3791) >> 4);
	conversion(pressure);			//��ѹ�ֽ�ת��������x
	DisplayOneChar(1, 1,'P');
	DisplayOneChar(1, 2,'R');
	DisplayOneChar(1, 3,'E');
	DisplayOneChar(1, 4,'S'); 		//��ʾ��ѹ
	DisplayOneChar(1, 5,':'); 
	DisplayOneChar(1, 6,x[5]+'0');
	DisplayOneChar(1, 7,x[4]+'0');
	DisplayOneChar(1, 8,x[3]+'0');
	DisplayOneChar(1, 9,x[2]+'0');
	DisplayOneChar(1,10,'.'); 
	DisplayOneChar(1,11,x[1]+'0');
	DisplayOneChar(1,12,'h');		//��ѹ��λ
	DisplayOneChar(1,13,'P');
	DisplayOneChar(1,14,'a');
}
//-----------------------------------------------------------------
// ���ݷֽ�ת������
//-----------------------------------------------------------------
void conversion(long d) {
	long k = 100000; 	u8 i;
	for (i = 5; i >=1; i--) {
		x[i] = d / k; d -= x[i]*k; k /= 10;
	}
}