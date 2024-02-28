
#include "PMPDataR.h"

unsigned char zu[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8d};
/* ��ʱt���� */
void delay(uint t)
{
	uint i;
	while(t--)
	{
		/* ����11.0592Mʱ�ӣ�Լ��ʱ1ms */
		for (i=0;i<125;i++)
		{}
	}
} 

/* �������ݺ��� */
uchar recvdata()
{

	/* �������� */
		while(!RI);
		if (RB8==1)
			return 0xee;		// �����յ�Ϊ��ַ֡���򷵻�0xee
		buf = SBUF;	
		RI = 0;	
	return 0;					// ����0
}

/* ���ڳ�ʼ������ */
void init_serial()
{
	TMOD = 0x20;				// ��ʱ��T1ʹ�ù�����ʽ2
	TH1 = 250;
	TL1 = 250;
	TR1 = 1;					// ��ʼ��ʱ
	PCON = 0x80;				// SMOD = 1
	SCON = 0xd0;				// ������ʽ��9λ����λ��������9600kbit/s��������� 
}

/* ������ */
void main()
{ 
	uchar i = 0;
	uchar tmp = 0xff;
	P1= 0xff;
	addr = P1&0x0f;				// ��ȡ������ַ
	P23 = 1;					// ����ܲ���
	
	init_serial();				// ���ڳ�ʼ�� 

	EA = 1;						// �ر������ж�
	
	/* �����豸Ӧ�� */
	while(1)
	{
		SM2 = 1;				// ֻ���յ�ַ֡
		
		/* ������յ��ĵ�ַ֡���Ǳ�����ַ��������ȴ� */
		while (tmp!=addr)
		{
			RI = 0;
			while(!RI)
			tmp = SBUF;
			RI = 0;
		}	
		SM2 = 0;				// �����������

		/* ���ݽ��� */
       tmp = recvdata();
	   //if(buf!=0x00)
	    
		if (tmp==0x00)	
		{		 
	   	     P0=buf;
			/* �̵���������500ms����ʾ�������ݳɹ� */
			P23 = 0;			
			delay(30);
			P23 = 1;
			
		}	    
		// �����������ʱ���ֵ�ַ֡�������¿�ʼ�������չ���
	}
}