#ifndef SPI_H
#define SPI_H

#include "STC15xxx.h"
#include "My_Macro.h"
#include <intrins.h>
#include "uipopt.h"

//ENC28J60 -- pin connect
sbit CS 		= P1^0;	//28J60-- CS
sbit SCK		= P1^1;	//SCK
sbit SI 		= P1^2;	//MOSI
sbit SO 		= P1^3;	//MISO
sbit RST		= P1^4;	//RST

void WriteByte(u8 temp);
u8 ReadByte(void);

#endif