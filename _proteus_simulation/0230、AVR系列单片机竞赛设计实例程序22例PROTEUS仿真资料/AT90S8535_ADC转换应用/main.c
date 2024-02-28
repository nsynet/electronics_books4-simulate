//ICC-AVR application builder : 00-1-16 4:13:00
// Target : 8535
// Crystal: 4.0000Mhz

#include <io8535v.h>
#include <macros.h>
#define uchar unsigned char
#define uint unsigned int
#include <adc.h>
#include <led_dsp.h>
#include <dac.h>



void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0x00;
 PORTB = 0xFF;
 DDRB  = 0xFF;
 PORTC = 0x00;
 DDRC  = 0xff;
 PORTD = 0xF0;
 DDRD  = 0x0F;
}


void main (void)
{
 uchar i;
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
port_init();
adc_init();
dac_init ();
 MCUCR = 0x00; 
 GIMSK = 0x00;
 SEI(); //re-enable interrupts
 //all peripherals are now initialised
 while (1)
 {
	change_data(adc_val);
 	scan_led(disp_buffer);
// 	put_to_dac();
	}
}

