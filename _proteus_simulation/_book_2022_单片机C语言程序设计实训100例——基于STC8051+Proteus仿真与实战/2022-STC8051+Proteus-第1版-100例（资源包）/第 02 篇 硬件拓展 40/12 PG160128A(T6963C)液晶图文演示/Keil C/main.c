//---------------------------- main.c -----------------------------
//  名称: PG160128A(T6963C)液晶图文演示
//  说明: 本例可显示一幅图像,可控制图像滚动,反白,合上"图文"开关时,
//        还可以显示一幅条形统计图.
//
//-----------------------------------------------------------------
#define	u8 	unsigned char
#define	u16	unsigned int
#define	MAIN_Fosc  12000000L		//定义主时钟
#include "STC15xxx.h"
#include "T6963C.h"
#include "PictureDots.h"
#include <intrins.h>
//开关定义
#define S1_ON() ((P0 & (1<<0)) == 0)	//正常显示
#define S2_ON() ((P0 & (1<<1)) == 0)	//反白
#define S3_ON() ((P0 & (1<<2)) == 0)	//滚动
#define S4_ON() ((P0 & (1<<3)) == 0)	//图文
//当前操作序号
u8 Current_Operation = 0;
//待显示的统计数据
u8 Statistics_Data[] = {20,70,80,40,90,65,30};
extern const u8 LCD_WIDTH;
extern const u8 LCD_HEIGHT;
//-----------------------------------------------------------------
// 绘制条形图
//-----------------------------------------------------------------
void Draw_Bar_Graph(u8 d[]) {


}
extern u8 Read_LCD_Status();
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u8 i,j,m,c = 0;  u16 k;
	P0M1 = 0xFF; P0M0 = 0x00;		//P0配置为高阻输入
	P2M1 = 0x00; P2M0 = 0x00;		//P2、P3配置为准双向口
	P3M1 = 0x00; P3M0 = 0x00;
	P2 = 0xFF; P3 = 0xFF;			//P2、P3初始输出高电平
	LCD_Initialise();				//初始化LCD
	while(1) {
		if		(S1_ON()) Current_Operation = 1;	//正常
		else if	(S2_ON()) Current_Operation = 2;	//反白
		else if	(S3_ON()) Current_Operation = 3;	//滚动
		else if	(S4_ON()) Current_Operation = 4;	//图文
		//如果操作类型未改变则仅执行延时.
		if ( c == Current_Operation) { delay_ms(200); continue; }
		c = Current_Operation; 
		switch (Current_Operation) {
			case 1://正常或反白显示(在160x128液晶上显示160x80BMP图像,
			case 2://余下面部分用间隔线条填充. 

			
			case 3://滚动显示

			
			case 4://图文显示
					Clear_Screen();
					LCD_Write_Command_P2(LCD_GRH_STP,0x00,0x00);
					Set_LCD_POS(0,0); 
					//根据统计数据数组显示条形图
					Draw_Bar_Graph(Statistics_Data); 
					//显示统计图Label(2011 B2B统计图显示)
					Display_Str_at_xy(3,110, 
					(u8*)" 2021 B2B .\xCD\xB3\xBC\xC6\xCD\xBC\xCF\xD4\xCA\xBE.",0);
					//语句中:\xCD\xB3\xBC\xC6\xCD\xBC\xCF\xD4\xCA\xBE分别是:
					//"统计图显示"五个汉字的内码,内码获取方法可参考本书说明.
					break;
		}
	}
}
