	.module main.c
	.area text(rom, con, rel)
	.dbfile E:\ѧϰ\AVR\adc\main.c
	.dbfunc e port_init _port_init fV
	.even
_port_init::
	.dbline -1
	.dbline 16
; //ICC-AVR application builder : 00-1-16 4:13:00
; // Target : 8535
; // Crystal: 4.0000Mhz
; 
; #include <io8535v.h>
; #include <macros.h>
; #define uchar unsigned char
; #define uint unsigned int
; #include <adc.h>
; #include <led_dsp.h>
; #include <dac.h>
; 
; 
; 
; void port_init(void)
; {
	.dbline 17
;  PORTA = 0x00;
	clr R2
	out 0x1b,R2
	.dbline 18
;  DDRA  = 0x00;
	out 0x1a,R2
	.dbline 19
;  PORTB = 0xFF;
	ldi R24,255
	out 0x18,R24
	.dbline 20
;  DDRB  = 0xFF;
	out 0x17,R24
	.dbline 21
;  PORTC = 0x00;
	out 0x15,R2
	.dbline 22
;  DDRC  = 0xff;
	out 0x14,R24
	.dbline 23
;  PORTD = 0xF0;
	ldi R24,240
	out 0x12,R24
	.dbline 24
;  DDRD  = 0x0F;
	ldi R24,15
	out 0x11,R24
	.dbline -2
	.dbline 25
; }
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;              i -> <dead>
	.even
_main::
	.dbline -1
	.dbline 29
; 
; 
; void main (void)
; {
	.dbline 32
;  uchar i;
;  //stop errant interrupts until set up
;  CLI(); //disable all interrupts
	cli
	.dbline 33
; port_init();
	rcall _port_init
	.dbline 34
; adc_init();
	rcall _adc_init
	.dbline 35
; dac_init ();
	rcall _dac_init
	.dbline 36
;  MCUCR = 0x00; 
	clr R2
	out 0x35,R2
	.dbline 37
;  GIMSK = 0x00;
	out 0x3b,R2
	.dbline 38
;  SEI(); //re-enable interrupts
	sei
	rjmp L4
L3:
	.dbline 41
	.dbline 42
	lds R16,_adc_val
	lds R17,_adc_val+1
	rcall _change_data
	.dbline 43
	ldi R16,<_disp_buffer
	ldi R17,>_disp_buffer
	rcall _scan_led
	.dbline 45
L4:
	.dbline 40
	rjmp L3
X0:
	.dbline -2
	.dbline 46
;  //all peripherals are now initialised
;  while (1)
;  {
; 	change_data(adc_val);
;  	scan_led(disp_buffer);
; // 	put_to_dac();
; 	}
; }
L2:
	.dbline 0 ; func end
	ret
	.dbsym l i 1 c
	.dbend
