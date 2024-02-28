//----------------------------- main.c --------------------------------
//  ����: ����STC15��С������վϵͳ
//---------------------------------------------------------------------
//  ˵��: ����������ʱ����ǰ��ʪ�ȡ���ѹ�����������١����򡢹���ǿ�ȵ���Ϣ��ˢ��
//        ��ʾ��20��4 LCD�ϣ���ش������Arduino��ıࣩ
//
//---------------------------------------------------------------------
#define u8	unsigned char
#define u16	unsigned int
#define u32	unsigned long
#define MAIN_Fosc		11059200L	//ϵͳʱ��Ƶ��11.0592MHz
//---------------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include "LM044L-4bit.h"
//---------------------------------------------------------------------
code char* Prompts[21] = {
	"  Weather  Station  ",
	"********************",
	"    TEST PROGRAM    ",
	"********************",
};
volatile u32 Millis = 0;
extern float getRH();
extern float getTemp();
extern float readAltitude();
extern float readPressure();
extern float readMPL3115A2_Temp();
extern void delay_ms(u8);
extern void setModeBarometer();
extern void setOversampleRate(u8);
extern void enableEventFlags();
extern void setModeAltimeter();
extern void setModeActive();
extern void InitADC();
float GetADCResult(u8 ch);

extern void poll();
extern float getRainHour();
extern float getRainDay();
extern float getWindSpeed();
extern float getWindDirection();
extern float rawWindDirection();
extern float rawWindSpeed();
extern float getGustSpeed();
extern float getGustDirection();
extern float getDaylight();
extern void reset_WSx();
//---------------------------------------------------------------------
// T0��ʼ��(��12Tģʽ������)
//---------------------------------------------------------------------
void Timer0Init() {		//1����@11.0592MHz


}
//---------------------------------------------------------------------
// T0�жϺ���(���ں��뼶��ʱ,��ȡNOW)
//---------------------------------------------------------------------
void Timer0_INT () interrupt 1 {                      }
//---------------------------------------------------------------------
// ������
//---------------------------------------------------------------------
void main() {
	u8 i; char s[30];
	float Rh,T1,Pr,T2,Ra,Ws,Wd,Ld;
	P0M1 = 0x00; P0M0 = 0x00;	//P0-P3����Ϊ׼˫���
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	reset_WSx();				//��λ��ز�����������
	setModeBarometer();			//������ѹ����20~110kPa��
	setOversampleRate(7);		//������������Ϊ128-----
	enableEventFlags();			//ʹ������������ѹ���¶��¼����-----
	Timer0Init();				//T0��ʼ��
	InitADC();					//ADCģ���ʼ�� 
	Initialize_LCD();			//LCD��ʼ��
	//���ϵͳ��������(4��)
	for (i = 0; i < 4; i++) {
		LCD_ShowString(i,0,(char*)Prompts[i]);
	}
	IT0 = 1;					//INT0�½��ش���
	IT1 = 1;					//INT1�½��ش���
	PX0 = 1;					//�������ȼ�
	IE |= 0x05;					//INT0,INT1���ж�
	EA = 1;
	while (1) {

	}
}