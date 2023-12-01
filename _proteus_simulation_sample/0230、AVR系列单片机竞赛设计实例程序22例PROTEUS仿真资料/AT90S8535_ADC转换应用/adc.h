#ifndef _adc_h
#define _adc_h



#ifdef _adc_c
#define uchar unsigned char
#define uint unsigned int
#define AREF_VOL 15
#define PER_VOL_DATA 1.46484375//参考电压15V，十位ADC最大表示1024
void adc_init(void);
void adc_isr(void);
uint adc_val;

#else
#define AREF_VOL 15
extern void adc_init(void);
extern void adc_isr(void);
extern uint adc_val;

#endif
#endif