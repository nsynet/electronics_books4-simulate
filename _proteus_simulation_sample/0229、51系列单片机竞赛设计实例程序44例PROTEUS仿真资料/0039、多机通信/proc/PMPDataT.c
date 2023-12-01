/*****************************************/
/* Copyright (c) 2005, ͨ�Ź���ѧԺ      */
/* All rights reserved.                  */
/* ��    �ߣ��� ��						 */
/*****************************************/

#include "PMPDataT.h"

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
uchar keyscan(void)
{
	uchar scancode,tmpcode;
	P1 = 0xf0;			 					// ��ȫ0��ɨ����
	if ((P1&0xf0)!=0xf0)					// ���м�����
	{
		delay(10);							// ��ʱȥ����
		if ((P1&0xf0)!=0xf0)				// ��ʱ�����ж�һ�Σ�ȥ������Ӱ��
		{
			scancode = 0xfe;
			while((scancode&0x10)!=0)		// ����ɨ��
			{
				P1 = scancode;				// �����ɨ����
				if ((P1&0xf0)!=0xf0)		// �����м�����
				{
					tmpcode = (P1&0xf0)|0x0f;

					/* ���������ֽ��룬Ϊ1��λ����Ӧ���к��� */
					return((~scancode)+(~tmpcode));
				}
				else scancode = (scancode<<1)|0x01;		// ��ɨ��������һλ
			}
		}
	}
	return(0);								// �޼����£�����ֵΪ0 	
}

/* �������ݺ��� */
void senddata(uchar buf)
{

	/* �������� */
		TI = 0;
		TB8 = 0;				// ��������֡
		SBUF =buf;	
		while(!TI);
		TI = 0;
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
void Getkey()
{
    switch(get_key)
   		{
      		case 0x11:						// 1��1�У�����0
			      key=0xc0;
				  break;
			case 0x21:						// 1��2�У�����1
                 key=0xf9;
				break;			
			case 0x41:						// 1��3�У�����2
				key=0xa4;
				break;
     		case 0x81:						// 1��4�У�����3
				key=0xb0;
				break;
			case 0x12:						// 2��1�У�����4
                key=0x99;
				break;
			case 0x22:						// 2��2�У�����5
				  key=0x92;
				break;
			case 0x42:						// 2��3�У�����6
				   key=0x82;
				break;
			case 0x82:						// 2��4�У�����7
				   key=0xf8;
				break;
			case 0x14:						// 3��1�У�����8
				   key=0x80;
				   break;
			case 0x24:						// 3��2�У�����9
				 key=0x90;
				break;
			case 0x44:						// 3��3�У�10
				  key=0x88;
				break;
			case 0x84:						// 3��4�У�11
				 key=0x83;
				break;
			case 0x18:						// 4��1�У�12
				 key=0xc6;
				break;
			case 0x28:						// 4��2�У�13
				 key=0xa1;
				break;
			case 0x48:						// 4��3�У�14
				 key=0x86;
				break;
			case 0x88:						// 3��4�У�15
				 key=0x8e;
				break;
			default:break;
		}


}
/* ������ */
void main()
{ 
	uchar i = 0;
	key=0xc0; 
	while(1)
    {
	 	 get_key = keyscan();				// ���ü���ɨ�躯�� 
	     Getkey();
		 buf=key;

    	/* ͨ��P0�ڶ�Ҫ���ʵĴӻ���ַ */
	  P0 = 0xff;
	  addr = P0&0x0f;
	  init_serial();				// ���ڳ�ʼ�� 

	  EA = 1;						// �ر������ж�
	
	     	TI = 0;
		    TB8 = 1;				// ���͵�ַ֡	
		    SBUF = addr;
		    while(!TI);
		    TI = 0;
		 senddata(buf);			// ��������
	 
	} 
	
}