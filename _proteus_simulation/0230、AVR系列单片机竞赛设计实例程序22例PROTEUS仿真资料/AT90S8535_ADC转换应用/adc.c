#define _adc_c
#include <io8535v.h>
#include <macros.h>
#include <adc.h>
//#define debug_p (*(volatile uint *)0xa0)
//ADC initialisation
// Conversion time: 416uS
void adc_init(void)
{
 ADCSR = 0x00; //disable adc
 ADMUX = 0x00; //select adc input 0
 ADCSR = 0xcF;
}

#pragma interrupt_handler adc_isr:15
void adc_isr(void)
{
 uint temp_val;
 float temp_val2;
 //conversion complete, read value (int) using...
 temp_val=ADCL;   //Read 8 low bits first (important)
 temp_val|=(int)ADCH << 8; //read 2 high bits and shift into top byte
 temp_val2 =temp_val*PER_VOL_DATA;//两位整数两位小数，全当整数处理
 adc_val = (uint)temp_val2;
 //debug_p = adc_val;
 ADCSR|=0X40;
}
