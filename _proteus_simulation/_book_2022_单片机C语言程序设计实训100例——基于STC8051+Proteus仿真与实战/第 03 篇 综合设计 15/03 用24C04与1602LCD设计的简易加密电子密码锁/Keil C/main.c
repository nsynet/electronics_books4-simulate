//--------------------------- main.c ------------------------------
//  ����: ��1602LCD��24C04��Ƶĵ���������
//-----------------------------------------------------------------
//  ˵��: ��ʼ������24C04.BIN�趨Ϊ"111111".
//	     �������ּ�0-9����������,������6λ,������ɺ���A
//	     ������,������ȷʱ����,Һ������ʾ�����ɹ�.
//	     ������������:B-���� C-������������ D-���������� E-���
//	     ��������ʱҪ����������ȷ������ɹ�����.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <string.h>
#define u8  unsigned char
#define u16 unsigned int
//��������а�����ŷ�ΧΪ0��15,0xFF��ʾ�ް���������
u8 keyNum = 0xFF ;
u8 DSY_BUFFER[10] = "";					//��ʾ����
u8 UserPassword[7] = "";				//�û����������
u8 IIC_Password[7];						//��IIC�洢����ȡ������
extern void delay_ms(u8 x);				//��ʱ����
extern void Initialize_LCD();			//Һ����ʼ��
extern void LCD_ShowString(u8, u8 ,u8*);//��ʾ�ַ���
extern void IIC_Init();					//IIC��ʼ��
extern void Write_IIC(u8,INT16U,u8);	//��ָ����ַд��1�ֽ�
extern u8 Random_Read(u8,INT16U);		//��ָ����ַ��ȡ1�ֽ�
extern u8 Keys_Scan();					//ɨ����̷��ؼ�ֵ
sbit LOCK = P1^0;						//�̵�����������
sbit BEEP = P3^3;						//����������
void Beep();							//�������������
//-----------------------------------------------------------------
// ���������
//-----------------------------------------------------------------
void Beep() {

}
//-----------------------------------------------------------------
// �������
//-----------------------------------------------------------------
void Clear_Pwd() {	 }
//-----------------------------------------------------------------
// ��ȡ�����ַ���(��'\0'Ϊ������־)
//-----------------------------------------------------------------
void Read_IIC_Pwd() {


}
//-----------------------------------------------------------------
// д�����ַ���(������־'\0'ע��һ��д��)
//-----------------------------------------------------------------
void Write_IIC_Pwd() {


}
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	u8 i = 0;
	u8 IS_Valid_User = 0;
	P0M1 = 0x00; P0M0 = 0x00;	//����Ϊ׼˫���
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	P4M1 = 0x00; P4M0 = 0x00;
	Initialize_LCD();		//��ʼ��LCD
	LCD_ShowString(0,0,"Your Password...");
	Read_IIC_Pwd();	//���������IIC_Password
	while(1) {
		keyNum = Keys_Scan();//ɨ����̻�ȡ�����
		if (keyNum == 0xFF) { delay_ms(10); continue; }
		Beep();
		switch ( keyNum ) {
			case 0:  case 1: case 2: case 3: case 4:
			case 5:  case 6: case 7: case 8: case 9:
					if ( i<= 5 ) {		//���벻����6λ
						//���iΪ0��ִ��һ������
						if (i ==0) LCD_ShowString(1,0,"                ");
						UserPassword[i] = keyNum + '0';
						UserPassword[i+1] = '\0';
						DSY_BUFFER[i] = '*';
						DSY_BUFFER[i+1] = '\0';i++;
						LCD_ShowString(1,0,DSY_BUFFER); 
					}
					 break;
			case 10: //��A������
					Read_IIC_Pwd();	//��IIC�洢����������
					if (strcmp(UserPassword,IIC_Password) == 0)  {
						LOCK = 0;			//����
						Clear_Pwd();
						LCD_ShowString(1,0,"Unlock OK!      ");
						IS_Valid_User = 1;
					}
					else {
						LOCK = 1;			//����
						Clear_Pwd();
						LCD_ShowString(1,0,"ERROR !         ");
						IS_Valid_User = 0;
					}
					i = 0; break;
			case 11: //��B������
					LOCK = 1;				//����
					Clear_Pwd();
					LCD_ShowString(0,0,"Your Password...");
					LCD_ShowString(1,0,"                ");
					i = 0;	IS_Valid_User = 0; break;
			case 12: //��C������������
					//����ǺϷ��û�����ʾ����������
					if ( !IS_Valid_User ) 
						LCD_ShowString(1,0,"No rights !");
					else {
						i = 0; //�������뻺��������0
						LCD_ShowString(0,0,"New Password:...");
						LCD_ShowString(1,0,"                ");
					}
					break;
			case 13: //��D������������
					if ( !IS_Valid_User )
						LCD_ShowString(1,0,"No rights !");
					else {
						//д�������õ�����,�����¶���
						Write_IIC_Pwd();delay_ms(5);Read_IIC_Pwd();
						i = 0; //�������뻺��������0
						LCD_ShowString(0,0,"Your Password...");
						LCD_ShowString(1,0,"Password Saved! ");
					}
					break;
			case 14: //��E��������������
					i = 0; 	Clear_Pwd();
					LCD_ShowString(1,0,"                ");
		}
		//δ�ͷ�ʱ�ȴ�
		while (Keys_Scan() != 0xFF) delay_ms(5);
	}
}
