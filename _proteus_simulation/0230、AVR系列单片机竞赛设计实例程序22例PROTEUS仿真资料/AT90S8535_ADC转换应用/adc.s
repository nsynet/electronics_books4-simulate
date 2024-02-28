	.module adc.c
	.area text(rom, con, rel)
	.dbfile E:\学习\AVR\adc\adc.c
	.dbfunc e adc_init _adc_init fV
	.even
_adc_init::
	.dbline -1
	.dbline 9
; #define _adc_c
; #include <io8535v.h>
; #include <macros.h>
; #include <adc.h>
; //#define debug_p (*(volatile uint *)0xa0)
; //ADC initialisation
; // Conversion time: 416uS
; void adc_init(void)
; {
	.dbline 10
;  ADCSR = 0x00; //disable adc
	clr R2
	out 0x6,R2
	.dbline 11
;  ADMUX = 0x00; //select adc input 0
	out 0x7,R2
	.dbline 12
;  ADCSR = 0xcF;
	ldi R24,207
	out 0x6,R24
	.dbline -2
	.dbline 13
; }
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 28
	rjmp _adc_isr
	.area text(rom, con, rel)
	.dbfile E:\学习\AVR\adc\adc.c
	.dbfunc e adc_isr _adc_isr fV
;      temp_val2 -> y+0
;       temp_val -> R20,R21
	.even
_adc_isr::
	st -y,R0
	st -y,R1
	st -y,R2
	st -y,R3
	st -y,R4
	st -y,R5
	st -y,R16
	st -y,R17
	st -y,R18
	st -y,R19
	st -y,R30
	st -y,R31
	in R0,0x3f
	st -y,R0
	rcall push_gset1
	sbiw R28,4
	.dbline -1
	.dbline 17
; 
; #pragma interrupt_handler adc_isr:15
; void adc_isr(void)
; {
	.dbline 21
;  uint temp_val;
;  float temp_val2;
;  //conversion complete, read value (int) using...
;  temp_val=ADCL;   //Read 8 low bits first (important)
	in R20,0x4
	clr R21
	.dbline 22
;  temp_val|=(int)ADCH << 8; //read 2 high bits and shift into top byte
	in R2,0x5
	clr R3
	mov R3,R2
	clr R2
	or R20,R2
	or R21,R3
	.dbline 23
;  temp_val2 =temp_val*PER_VOL_DATA;//两位整数两位小数，全当整数处理
	ldi R16,<L3
	ldi R17,>L3
	rcall lpm32
	st -y,R19
	st -y,R18
	st -y,R17
	st -y,R16
	ldi R16,<L4
	ldi R17,>L4
	rcall lpm32
	st -y,R19
	st -y,R18
	st -y,R17
	st -y,R16
	movw R16,R20
	lsr R17
	ror R16
	rcall int2fp
	st -y,R19
	st -y,R18
	st -y,R17
	st -y,R16
	rcall empy32fs
	movw R16,R20
	andi R16,1
	andi R17,0
	rcall int2fp
	st -y,R19
	st -y,R18
	st -y,R17
	st -y,R16
	rcall add32fs
	rcall empy32f
	movw R30,R28
	std z+0,R16
	std z+1,R17
	std z+2,R18
	std z+3,R19
	.dbline 24
;  adc_val = (uint)temp_val2;
	movw R30,R28
	ldd R2,z+0
	ldd R3,z+1
	ldd R4,z+2
	ldd R5,z+3
	st -y,R5
	st -y,R4
	st -y,R3
	st -y,R2
	ldi R16,<L7
	ldi R17,>L7
	rcall lpm32
	st -y,R19
	st -y,R18
	st -y,R17
	st -y,R16
	rcall cmp32f
	brlt L5
	movw R30,R28
	ldd R2,z+0
	ldd R3,z+1
	ldd R4,z+2
	ldd R5,z+3
	st -y,R5
	st -y,R4
	st -y,R3
	st -y,R2
	ldi R16,<L7
	ldi R17,>L7
	rcall lpm32
	st -y,R19
	st -y,R18
	st -y,R17
	st -y,R16
	rcall sub32f
	rcall fp2int
	movw R20,R16
	subi R20,0  ; offset = 32768
	sbci R21,128
	rjmp L6
L5:
	movw R30,R28
	ldd R16,z+0
	ldd R17,z+1
	ldd R18,z+2
	ldd R19,z+3
	rcall fp2int
	movw R20,R16
L6:
	sts _adc_val+1,R21
	sts _adc_val,R20
	.dbline 26
;  //debug_p = adc_val;
;  ADCSR|=0X40;
	sbi 0x6,6
	.dbline -2
	.dbline 27
; }
L2:
	adiw R28,4
	rcall pop_gset1
	ld R0,y+
	out 0x3f,R0
	ld R31,y+
	ld R30,y+
	ld R19,y+
	ld R18,y+
	ld R17,y+
	ld R16,y+
	ld R5,y+
	ld R4,y+
	ld R3,y+
	ld R2,y+
	ld R1,y+
	ld R0,y+
	.dbline 0 ; func end
	reti
	.dbsym l temp_val2 0 D
	.dbsym r temp_val 20 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile E:\学习\AVR\adc\adc.c
_adc_val::
	.blkb 2
	.dbfile E:/学习/AVR/adc/adc.h
	.dbsym e adc_val _adc_val i
	.area lit(rom, con, rel)
L7:
	.word 0x0,0x4700
L4:
	.word 0x0,0x4000
L3:
	.word 0x8000,0x3fbb
