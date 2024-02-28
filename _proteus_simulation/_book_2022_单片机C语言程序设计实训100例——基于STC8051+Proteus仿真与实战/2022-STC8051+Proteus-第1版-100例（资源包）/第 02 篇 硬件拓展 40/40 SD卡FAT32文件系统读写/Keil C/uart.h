//-----------------------------------------------------------------
// 名称: 串口驱动程序头文件
//-----------------------------------------------------------------
void UART_Init(void);											//串口1初始化
void UART_Send_Str(char *s);							//发送字符串
void UART_Send_Num(u32 dat);							//发送数值
void Hex2Str(u16 hex,char *str);					//十六进制转换为字符串
void UART_Send_StrNum(char *inf,u32 dat);	//发送字符串+数值
void UART_Send_Hex(u16 hex);							//发送16进制(整数范围)
void UART_Send_binary(u8 dat);						//发送2进制
void UART_Send_Enter();
void UART_Send_Byte(u8 dat);