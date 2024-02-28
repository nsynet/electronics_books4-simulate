#ifndef _dac_h
#define _dac_h
#ifdef _dac_c

#define uchar unsigned char
#define uint unsigned int
#define data_port PORTC
void dac_init (void);
#pragma interrupt_handler put_to_dac:9
void put_to_dac (void);
uchar vol_data;
uchar sin_tabel[21] ={128,168,204,231,249,255,249,231,203,
											167,128,89,53,25,7,0,7,25,53,89,128
};

#else
extern uchar vol_data;
extern uchar sin_tabel[21];
extern void dac_init (void);
//extern void put_to_dac (void);
//#pragma interrupt_handler put_to_dac:9

#endif
#endif