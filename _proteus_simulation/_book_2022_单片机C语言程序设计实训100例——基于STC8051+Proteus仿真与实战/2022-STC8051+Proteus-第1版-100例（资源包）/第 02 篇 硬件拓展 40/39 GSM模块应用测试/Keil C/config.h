
#ifndef		__CONFIG_H
#define		__CONFIG_H
//-----------------------------------------------------------------
#include	"STC15xxx.h" 
//-----------------------------------------------------------------
#define MAIN_Fosc		11059200L
#define Main_Fosc_KHZ	(MAIN_Fosc / 1000) 
//-----------------------------------------------------------------
#define u8	unsigned char
#define u16	unsigned int
#define u32	unsigned long
#define S2RI		0x01		//S2CON.0
#define S2TI		0x02		//S2CON.1
//-----------------------------------------------------------------
#endif