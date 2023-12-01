	.module M16_AN_Compare.c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_AN_Compare\M16_AN_Compare.c
	.dbfunc e main _main fV
;              i -> <dead>
	.even
_main::
	.dbline -1
	.dbline 6
; #include <iom16v.h>
; #define uchar unsigned char
; #define uint unsigned int
; 
; void main(void)
; {
	.dbline 8
;  uchar i;
;  DDRB=0xf0;
	ldi R24,240
	out 0x17,R24
	.dbline 9
;  PORTB=0x00;
	clr R2
	out 0x18,R2
	.dbline 10
;  ACSR=0x00;
	out 0x8,R2
	xjmp L3
L2:
	.dbline 12
;  while(1)
;  {
	.dbline 13
;   if((ACSR&0x20)==0x20)
	in R24,0x8
	andi R24,32
	cpi R24,32
	brne L5
	.dbline 14
;   PORTB=PORTB|0xf0;
	in R24,0x18
	ori R24,240
	out 0x18,R24
	xjmp L6
L5:
	.dbline 16
;   else
;   PORTB=PORTB&0x0f;
	in R24,0x18
	andi R24,15
	out 0x18,R24
L6:
	.dbline 17
L3:
	.dbline 11
	xjmp L2
X0:
	.dbline -2
	.dbline 18
;  }
; }
L1:
	.dbline 0 ; func end
	ret
	.dbsym l i 1 c
	.dbend
