	.module dac.c
	.area vector(rom, abs)
	.org 16
	rjmp _put_to_dac
	.area data(ram, con, rel)
_sin_tabel::
	.blkb 2
	.area idata
	.byte 128,168
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 204,231
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 249,255
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 249,231
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 203,167
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 128,'Y
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 53,25
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 7,0
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 7,25
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 53,'Y
	.area data(ram, con, rel)
	.blkb 1
	.area idata
	.byte 128
	.area data(ram, con, rel)
	.dbfile E:/学习/AVR/adc/dac.h
	.dbsym e sin_tabel _sin_tabel A[21:21]c
	.area text(rom, con, rel)
	.dbfile E:/学习/AVR/adc/dac.h
	.dbfile E:\学习\AVR\adc\dac.c
	.dbfunc e dac_init _dac_init fV
	.even
_dac_init::
	.dbline -1
	.dbline 8
; #define _dac_c
; 
; #include <io8535v.h>
; #include <macros.h>
; #include <dac.h>
; #define debug_p (*(volatile uint *)0xa0)
; void dac_init (void)
; {
	.dbline 9
; 	 vol_data = 0;
	clr R2
	sts _vol_data,R2
	.dbline 10
;  TIMSK = 0x04;//为什么是04啊？？？？？？？？？
	ldi R24,4
	out 0x39,R24
	.dbline 11
;  TCCR1B = 0x00; //stop
	out 0x2e,R2
	.dbline 12
;  TCNT1H = 0xf5; //setup
	ldi R24,245
	out 0x2d,R24
	.dbline 13
;  TCNT1L = 0xEE;
	ldi R24,238
	out 0x2c,R24
	.dbline 14
;  OCR1AH = 0x7A;
	ldi R24,122
	out 0x2b,R24
	.dbline 15
;  OCR1AL = 0x12;
	ldi R24,18
	out 0x2a,R24
	.dbline 16
;  OCR1BH = 0x7A;
	ldi R24,122
	out 0x29,R24
	.dbline 17
;  OCR1BL = 0x12;
	ldi R24,18
	out 0x28,R24
	.dbline 18
;  TCCR1A = 0x00;
	out 0x2f,R2
	.dbline 19
;  TCCR1B = 0x02; //start Timer
	ldi R24,2
	out 0x2e,R24
	.dbline -2
	.dbline 21
; 	 
; }
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e put_to_dac _put_to_dac fV
	.even
_put_to_dac::
	st -y,R2
	st -y,R3
	st -y,R24
	st -y,R25
	st -y,R30
	st -y,R31
	in R2,0x3f
	st -y,R2
	.dbline -1
	.dbline 25
	.dbline 26
	ldi R24,245
	out 0x2d,R24
	.dbline 27
	ldi R24,238
	out 0x2c,R24
	.dbline 28
	ldi R24,<_sin_tabel
	ldi R25,>_sin_tabel
	lds R30,_vol_data
	clr R31
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x15,R2
	.dbline 29
	lds R24,_vol_data
	subi R24,255    ; addi 1
	sts _vol_data,R24
	.dbline 30
	mov R2,R24
	clr R3
	sts 160+1,R3
	sts 160,R2
	.dbline 31
	ldi R24,20
	cp R24,R2
	brsh L3
	.dbline 31
	clr R2
	sts _vol_data,R2
L3:
	.dbline -2
	.dbline 32
; 
; 
; void put_to_dac (void)
; {
;  TCNT1H = 0xf5; //setup
;  TCNT1L = 0xEE;
; 	data_port = sin_tabel[vol_data];
; 	vol_data++;
; 	debug_p= vol_data;
; 	if (vol_data>20) vol_data =0;
; }
L2:
	ld R2,y+
	out 0x3f,R2
	ld R31,y+
	ld R30,y+
	ld R25,y+
	ld R24,y+
	ld R3,y+
	ld R2,y+
	.dbline 0 ; func end
	reti
	.dbend
	.area bss(ram, con, rel)
	.dbfile E:\学习\AVR\adc\dac.c
_vol_data::
	.blkb 1
	.dbfile E:/学习/AVR/adc/dac.h
	.dbsym e vol_data _vol_data c
