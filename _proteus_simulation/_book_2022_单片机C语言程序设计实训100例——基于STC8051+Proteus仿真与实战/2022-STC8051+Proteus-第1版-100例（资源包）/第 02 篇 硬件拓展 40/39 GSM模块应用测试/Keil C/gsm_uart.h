#ifndef __UART_H__
#define __UART_H__

#include	"config.h"

void Uart1Init();
void Uart2Init();
void Uart1_PutChar(u8 c);
void Uart2_PutChar(u8 c);
void Uart1_Putstr(char *s);
void Uart2_Putstr(char *s);
void Set_PDUMode();
void Send_PDUSms(char *str);

#endif