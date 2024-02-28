//-------------------------- Nokia5110.h ----------------------------
//  名称: Nokia5110液晶头文件(PCD8544)
//-------------------------------------------------------------------
#define u8	unsigned char
#define u16	unsigned int
//-------------------------------------------------------------------
// 函数声明
//-------------------------------------------------------------------
void Nokia_Reset();
void Nokia_Init();
void Nokia_CLS();
void Write_Nokia_Comm(u8 cmd);
void Write_Nokia_Data(u8 cd);
void Write_Nokia_POS(u8 page, u8 col);
void Show_Char(char c, u8 reverse); 
void Show_String(char *str,u8 reverse);