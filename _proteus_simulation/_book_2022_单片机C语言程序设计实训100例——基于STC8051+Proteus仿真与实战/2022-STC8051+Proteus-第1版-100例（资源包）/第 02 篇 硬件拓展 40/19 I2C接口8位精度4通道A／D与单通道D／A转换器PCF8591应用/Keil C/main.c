//------------------------- main.c --------------------------------
//  名称: I2C接口8位精度多通道A／D与D／A转换器PCF8591件应用
//-----------------------------------------------------------------
//  说明: PCF8591是具有I2C总线接口的8位AD及DA转换器,有4路A/D转换输入
//	     和1路D/A转换模拟输出,本例中对4个通道进行递增A/D转换,转/换
//	     结果显示在LCD上,同时将转换后得到的值再逆向转换为模拟信号,
//	     经过Aout引脚输出到LED上,控制其亮度变化.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#define u8	unsigned char
#define u16	unsigned int
u8 LCD_Line_1[] = {"0-0.00V  2-0.00V"};
u8 LCD_Line_2[] = {"1-0.00V  3-0.00V"};
u8 Recv_Buffer[4];				//数据接收缓冲(每通道一字节)
u16 Voltage[]={'0','0','0'};	//数据分解为电压X.XX
extern void delay_ms(u8 x);
extern void Initialize_LCD();
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void ADC_PCF8591(u8 CtrlByte,u8 *R);
extern void DAC_PCF8591(u8 CtrlByte,u8 dat);
//-----------------------------------------------------------------
// 将模数转换后得到的值分解存入缓冲
//-----------------------------------------------------------------
void Convert_To_Voltage(u8 val) {	

}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	P1M1 = 0; P1M0 = 0;				//配置为准双向口
	P2M1 = 0; P2M0 = 0;
	Initialize_LCD();
	while(1) {
		//---------------------------------------------------------
		// PCF8591控制字节定义: 0***0*** ,第3,7位固定为0
		// 第6位取0为模拟输入,取1时为模拟输出
		// 第4,5位为00表示四路单端的模拟输入
		// 第2位为自动递增标志,取1时自动递增
		// 第0,1位取值为00,01,10,11分别表示通道0,1,2,3
		// 调用ADC_PCF8591时参数为00000100,即0x04
		// 调用DAC_PCF8591时参数为01000000,即0x40
		//---------------------------------------------------------
		//下面的A/D转换函数参数本来只需要设为0x04即可,但为了保持后面
		//的D/A转换能保持稳定输出为0通道的值,能够不仅在D/A转换后打开
		//模拟输出(AOUT),而且能够在A/D转换时也保持模拟输出,
		//故而在下面的A/D转换调用中同时打开了模拟输出,参数由0x04改为0x44.
		ADC_PCF8591(0x44,Recv_Buffer);
		//将AN0通道模数转换后的数值重新进行数模转换,模拟量从Aout输出,
		//结果通过LED的亮度表现出来.
		DAC_PCF8591(0x40,Recv_Buffer[0]);
		//将四个通道模数转换结果放入LCD显示缓冲LCD_Line_1,2
		Convert_To_Voltage(Recv_Buffer[0]);
		LCD_Line_1[2] = Voltage[2];
		LCD_Line_1[4] = Voltage[1];
		LCD_Line_1[5] = Voltage[0];
		Convert_To_Voltage(Recv_Buffer[2]);
		LCD_Line_1[11] = Voltage[2];
		LCD_Line_1[13] = Voltage[1];
		LCD_Line_1[14] = Voltage[0];
		Convert_To_Voltage(Recv_Buffer[1]);
		LCD_Line_2[2] = Voltage[2];
		LCD_Line_2[4] = Voltage[1];
		LCD_Line_2[5] = Voltage[0];
		Convert_To_Voltage(Recv_Buffer[3]);
		LCD_Line_2[11] = Voltage[2];
		LCD_Line_2[13] = Voltage[1];
		LCD_Line_2[14] = Voltage[0];
		//液晶两行显示四个通道的转换结果

		
		
		
		
	}
}