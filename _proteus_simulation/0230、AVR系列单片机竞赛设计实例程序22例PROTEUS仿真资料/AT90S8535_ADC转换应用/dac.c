#define _dac_c

#include <io8535v.h>
#include <macros.h>
#include <dac.h>
#define debug_p (*(volatile uint *)0xa0)
void dac_init (void)
{
	 vol_data = 0;
 TIMSK = 0x04;//ÎªÊ²Ã´ÊÇ04°¡£¿£¿£¿£¿£¿£¿£¿£¿£¿
 TCCR1B = 0x00; //stop
 TCNT1H = 0xf5; //setup
 TCNT1L = 0xEE;
 OCR1AH = 0x7A;
 OCR1AL = 0x12;
 OCR1BH = 0x7A;
 OCR1BL = 0x12;
 TCCR1A = 0x00;
 TCCR1B = 0x02; //start Timer
	 
}


void put_to_dac (void)
{
 TCNT1H = 0xf5; //setup
 TCNT1L = 0xEE;
	data_port = sin_tabel[vol_data];
	vol_data++;
	debug_p= vol_data;
	if (vol_data>20) vol_data =0;
}