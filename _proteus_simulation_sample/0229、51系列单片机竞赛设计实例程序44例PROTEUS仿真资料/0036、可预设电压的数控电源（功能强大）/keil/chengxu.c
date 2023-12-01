#ifndef	_PWLOCK_H 		// ��ֹPWLock.h���ظ�����

#define	_PWLOCK_H

#include <reg52.h>
#include <absacc.h>
#include <stdio.h>	
#include <math.h>

#define uchar unsigned char
#define uint unsigned int

uchar px;
uint a;
uint b;
uint c;                          //Ϊ0XFF
uint i;
uchar digbit;                    // ��λ
uchar dy;				
uchar wordbuf[2];				// �����뻺����
uchar count;					// λ����
uchar pwbuf[2];					// �������ִ洢��
bit enterflag;					// ȷ�ϼ���������־
bit lh;
bit pwflag;						// ������ȷ����־
bit showflag;					// �������ʾ����־

sbit P20=P2^0;
sbit P21=P2^1;

void display(void);				// ��ʾ����

#endif

//#include "PWLock.h"

/* ��������ʱ���� */
void delay(void)
{
	uint i;
	for (i=4000;i>0;i--);
}


/* ��ɨ�躯�� */
uchar keyscan(void)
{
	uchar scancode,tmpcode;
	P1 = 0xf0;			 					// ��ȫ0��ɨ����
	if ((P1&0xf0)!=0xf0)					// ���м�����
	{
		delay();							// ��ʱȥ����
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

/* ��ʱ��0�жϷ����ӳ���2ms��ʱ��̬ɨ����ʾ */
void time0_int(void) interrupt 1 
{
	/* ����2ms��ʱ */
	TH0 = -2000/256;
	TL0 = -2000%256;

         px++;                  //Ƭѡ
	if (showflag==1)
		display();				// ������ʾ����
}


/* ���ݹ��������ͱ�����ȡ0~9��A~B���ʹ��� */
uchar getcode(uchar i)
{
	uchar p;
	switch (i)
	{
		case 0:	 p=0x3f;	break;			/* 0 */
		case 1:	 p=0x06;	break;			/* 1 */
		case 2:	 p=0x5B;	break;			/* 2 */
		case 3:	 p=0x4F;	break;			/* 3 */
		case 4:	 p=0x66;	break;			/* 4 */
		case 5:	 p=0x6D;	break;			/* 5 */
		case 6:	 p=0x7D;	break;			/* 6 */
		case 7:	 p=0x07;	break;			/* 7 */
		case 8:	 p=0x7F;	break;			/* 8 */
		case 9:	 p=0x67;	break;			/* 9 */
		default: 			break;
	}
	return(p);
}

void Display(void)   //LED��ֵ��ʾ
{ 
 switch (px%2)
  {
case 0:
        P20 = 1;P21 = 0; P0 = getcode(wordbuf[0]);break;
case 1:
        P21 = 1;P20 = 0; P0 = getcode(wordbuf[1]);break;
default:  return;
 }
}

/* ��ʾ���� */
/*void display(void)
{
	uchar i;
	switch (digbit)
	{
		case 1:		i=0;	break;
		case 2:		i=1;	break;
		default: 	break;
	}

	P2 = 0x0;						// �ر���ʾ
//	P20=0;
//	P21=0;
	P0 = getcode(wordbuf[i]);		// ��������
	P2=digbit;                    	// ����λ��
	digbit=1;
	if(digbit==1)
    {	
    digbit=2;
	P20 = 1;				
	P21 = 0;
    }
	digbit=2;
	P21 = 1;
	P20 = 0;
	if (digbit<0x02)				// ��2λ
		digbit = digbit*2;			// ����һλ
	else
	    digbit = 0x01;
}
*/
/* ������ */
void main()
{
	uchar j,key;
    uint temp;

	P20 = 1;
	P21 = 1;							// �ر��������ʾ
	
	TMOD = 0x11;						// T0��T1������ʽ1

	/* 2ms ��ʱ���� */
	TH0 = -2000/256;
	TL0 = 2000%256;
	
	/* ����������0���رռ�����1 */
	TR0 = 1;
	ET0 = 1;
	TR1 = 0;
	ET1 = 1;
	EA = 1;

	count = 0;						// ��ʼ��������Ϊ0
	enterflag = 0;					// û�а���ȷ�ϼ�
	lh = 0;
	pwflag = 0;						// ��־����Ϊ0
	
	digbit = 0x01;					// �ӵ�һλ����ܿ�ʼ��̬ɨ��

	/* �ռӵ�ʱ��bu��ʾ*/
	for (j=0;j<2;j++)
		wordbuf[j] = 17;

	showflag = 1;					// ���������	

  	while(1)

    {
		key = keyscan();					// ���ü���ɨ�躯��
        switch(key)
   		{
      		case 0x11:						// 1��1�У�����1
				if (count<2)
				{
					wordbuf[count] = 1;	// ��Ӧλ����ʾ��1��
					pwbuf[count] = 1;
					if(count==0)
                    {a=1;
                    }
					if(count==1)
                    {b=1;
                    }
					count++;
					
				}
				break;
			case 0x21:						// 1��2�У�����3
				if (count<2)
				{
					wordbuf[count] = 2;	// ��Ӧλ����ʾ��2"
					pwbuf[count] = 2;
					if(count==0)
                    {a=2;
                    }	
					if(count==1)
                    {b=2;
                    }
					count++;
				}
				break;			
			case 0x41:						// 1��3�У�����3
				if (count<2)
				{
					wordbuf[count] = 3;	// ��Ӧλ����ʾ��3"
					pwbuf[count] = 3;
					if(count==0)
                    {a=3;
                    }
					if(count==1)
                    {b=3;
                    }
					count++;
				}
				break;
    
			case 0x12:						// 2��1�У�����4
				if (count<2)
				{
					wordbuf[count] = 4;	// ��Ӧλ����ʾ��4"
					pwbuf[count] = 4;
					if(count==0)
                    {a=4;
                    }	
					if(count==1)
                    {b=4;
                    }
					count++;
				}
				break;
			case 0x22:						// 2��2�У�����5
				if (count<2)
				{
					wordbuf[count] = 5;	// ��Ӧλ����ʾ��5"
					pwbuf[count] = 5;
					if(count==0)
                    {a=5;
                    }
					if(count==1)
                    {b=5;
                    }
					count++;
				}
				break;
			case 0x42:						// 2��3�У�����6
				if (count<2)
				{
					wordbuf[count] = 6;	// ��Ӧλ����ʾ��6"
					pwbuf[count] = 6;
			    	if(count==0)
                    {a=6;
                    }	
					if(count==1)
                    {b=6;
                    }
					count++;
				}
				break;
	
			case 0x14:						// 3��1�У�����7
				if (count<2)
				{
					wordbuf[count] = 7;	// ��Ӧλ����ʾ��7"
					pwbuf[count] = 7;
					if(count==0)
                    {a=7;
                    }
					if(count==1)
                    {b=7;
                    }
					count++;
				}
				break;
			case 0x24:						// 3��2�У�����8
				if (count<2)
				{
					wordbuf[count] = 8;	// ��Ӧλ����ʾ��8"
					pwbuf[count] = 8;
					if(count==0)
                    {a=8;
                    }
					if(count==1)
                    {b=8;
                    }
					count++;
				}
				break;
			case 0x44:						// 3��3�У�����9
				if (count<2)
				{
					wordbuf[count] = 9;	// ��Ӧλ����ʾ��9"
					pwbuf[count] = 9;
					if(count==0)
                    {a=9;
                    }	
					if(count==1)
                    {b=9;
                    }
					count++;
				}
				break;	
		
			 case 0x18:						// 4��1�У�����*
				count = 0;
				P3=0;
				px=0;					// ��ʾ����
				for (j=0;j<2;j++)
				{
					wordbuf[j] = 17;			// ����ܲ���ʾ
					pwbuf[j] = 0;		// ��FFFFFF����Ѿ����������
				}
				break;	
			case 0x28:              	// 4��2�У�����0
				if (count<2)
				{
					wordbuf[count] = 0;	// ��Ӧλ����ʾ��0"
					pwbuf[count] = 0;
					if(count==0)
                    {a=0;
                    
                    }	
					if(count==1)
                    {b=0;
                    }
					count++;
				}
				break;
			case 0x48:						// 4��3�У�����#
				 enterflag = 1;				// ȷ�ϼ�����	
				 if (count==2) 				// ֻ������2������ȷ�ϼ�����Ч���
			    	pwflag = 1;      
				break;
		
			default:break;
		}

		if (enterflag==1)					// �������ȷ�ϼ�
		{
			enterflag = 0; 					// ��־λ�û�0
			count = 0;                      // ����������
			c=0xff/6;						
			if (pwflag==1)			
            {
             P3=a*c+b*c/10+12*c/100;
             temp=a*c+b*c/10+12*c/100;
               if(temp>=0xff)
               {
                  P3=0xff;
               }
            }
            				
		}
	}    
}
