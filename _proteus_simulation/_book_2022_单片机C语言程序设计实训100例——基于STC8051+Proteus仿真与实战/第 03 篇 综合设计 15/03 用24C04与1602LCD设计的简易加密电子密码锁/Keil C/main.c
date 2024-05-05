//--------------------------- main.c ------------------------------
//  名称: 用1602LCD与24C04设计的电子密码锁
//-----------------------------------------------------------------
//  说明: 初始密码由24C04.BIN设定为"111111".
//	     按下数字键0-9可输入密码,不超过6位,输入完成后按下A
//	     键开锁,密码正确时锁开,液晶屏显示开锁成功.
//	     其他键功能是:B-上锁 C-重新输入密码 D-保存新密码 E-清除
//	     重设密码时要求先输入正确的密码成功开锁.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <string.h>
#define u8  unsigned char
#define u16 unsigned int
//矩阵键盘中按键序号范围为0～15,0xFF表示无按键被按下
u8 keyNum = 0xFF ;
u8 DSY_BUFFER[10] = "";					//显示缓冲
u8 UserPassword[7] = "";				//用户输入的密码
u8 IIC_Password[7];						//从IIC存储器读取的密码
extern void delay_ms(u8 x);				//延时函数
extern void Initialize_LCD();			//液晶初始化
extern void LCD_ShowString(u8, u8 ,u8*);//显示字符串
extern void IIC_Init();					//IIC初始化
extern void Write_IIC(u8,INT16U,u8);	//向指定地址写入1字节
extern u8 Random_Read(u8,INT16U);		//从指定地址读取1字节
extern u8 Keys_Scan();					//扫描键盘返回键值
sbit LOCK = P1^0;						//继电器锁控引脚
sbit BEEP = P3^3;						//蜂鸣器引脚
void Beep();							//蜂鸣器输出函数
//-----------------------------------------------------------------
// 蜂鸣器输出
//-----------------------------------------------------------------
void Beep() {

}
//-----------------------------------------------------------------
// 清除密码
//-----------------------------------------------------------------
void Clear_Pwd() {	 }
//-----------------------------------------------------------------
// 读取密码字符串(以'\0'为结束标志)
//-----------------------------------------------------------------
void Read_IIC_Pwd() {


}
//-----------------------------------------------------------------
// 写密码字符串(结束标志'\0'注意一并写入)
//-----------------------------------------------------------------
void Write_IIC_Pwd() {


}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u8 i = 0;
	u8 IS_Valid_User = 0;
	P0M1 = 0x00; P0M0 = 0x00;	//配置为准双向口
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	P4M1 = 0x00; P4M0 = 0x00;
	Initialize_LCD();		//初始化LCD
	LCD_ShowString(0,0,"Your Password...");
	Read_IIC_Pwd();	//将密码读入IIC_Password
	while(1) {
		keyNum = Keys_Scan();//扫描键盘获取键序号
		if (keyNum == 0xFF) { delay_ms(10); continue; }
		Beep();
		switch ( keyNum ) {
			case 0:  case 1: case 2: case 3: case 4:
			case 5:  case 6: case 7: case 8: case 9:
					if ( i<= 5 ) {		//密码不超过6位
						//如果i为0则执行一次清屏
						if (i ==0) LCD_ShowString(1,0,"                ");
						UserPassword[i] = keyNum + '0';
						UserPassword[i+1] = '\0';
						DSY_BUFFER[i] = '*';
						DSY_BUFFER[i+1] = '\0';i++;
						LCD_ShowString(1,0,DSY_BUFFER); 
					}
					 break;
			case 10: //按A键开锁
					Read_IIC_Pwd();	//从IIC存储器读回密码
					if (strcmp(UserPassword,IIC_Password) == 0)  {
						LOCK = 0;			//开锁
						Clear_Pwd();
						LCD_ShowString(1,0,"Unlock OK!      ");
						IS_Valid_User = 1;
					}
					else {
						LOCK = 1;			//闭锁
						Clear_Pwd();
						LCD_ShowString(1,0,"ERROR !         ");
						IS_Valid_User = 0;
					}
					i = 0; break;
			case 11: //按B键上锁
					LOCK = 1;				//闭锁
					Clear_Pwd();
					LCD_ShowString(0,0,"Your Password...");
					LCD_ShowString(1,0,"                ");
					i = 0;	IS_Valid_User = 0; break;
			case 12: //按C键设置新密码
					//如果是合法用户则提示输入新密码
					if ( !IS_Valid_User ) 
						LCD_ShowString(1,0,"No rights !");
					else {
						i = 0; //密码输入缓冲索引归0
						LCD_ShowString(0,0,"New Password:...");
						LCD_ShowString(1,0,"                ");
					}
					break;
			case 13: //按D键保存新密码
					if ( !IS_Valid_User )
						LCD_ShowString(1,0,"No rights !");
					else {
						//写入新设置的密码,并重新读回
						Write_IIC_Pwd();delay_ms(5);Read_IIC_Pwd();
						i = 0; //密码输入缓冲索引归0
						LCD_ShowString(0,0,"Your Password...");
						LCD_ShowString(1,0,"Password Saved! ");
					}
					break;
			case 14: //按E键消除所有输入
					i = 0; 	Clear_Pwd();
					LCD_ShowString(1,0,"                ");
		}
		//未释放时等待
		while (Keys_Scan() != 0xFF) delay_ms(5);
	}
}
