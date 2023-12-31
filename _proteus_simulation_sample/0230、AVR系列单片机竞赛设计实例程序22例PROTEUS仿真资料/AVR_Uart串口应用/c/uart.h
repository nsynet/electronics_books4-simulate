#ifndef	__UART__H
#define	__UART__H


//-----------------------------------------------------------
//串口初始化子程序
//-----------------------------------------------------------
void Uart_Init(void);

//-----------------------------------------------------------
//串口接收字节子程序
//-----------------------------------------------------------
unsigned char Getchar(void);

//-----------------------------------------------------------
//串口发送字节子程序
//-----------------------------------------------------------
void Putchar(unsigned char c);

//-----------------------------------------------------------
//串口发送字符串子程序
//-----------------------------------------------------------
void Putstr(char *s);

//-----------------------------------------------------------
//串口发送字符串子程序(带有换行符)
//-----------------------------------------------------------
void Puts(char *s);

//-----------------------------------------------------------

#endif
