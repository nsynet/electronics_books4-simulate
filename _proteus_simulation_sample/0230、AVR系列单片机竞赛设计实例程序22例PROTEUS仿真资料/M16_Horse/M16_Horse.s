	.module M16_Horse.c
	.area text(rom, con, rel)
	.dbfile F:\myavr\mydesign\M16_Horse\M16_Horse.c
	.dbfunc e Delay _Delay fV
;              j -> R20
;              i -> R16
	.even
_Delay::
	xcall push_gset1
	.dbline -1
	.dbline 6
; #include<iom16v.h>
; #define uchar unsigned char
; #define uint unsigned int
; 
; void Delay(uchar i)
; {
	.dbline 8
;  uchar j;
;  for(;i!=0;i--)
	xjmp L5
L2:
	.dbline 9
;  {
	.dbline 10
	ldi R20,250
	xjmp L9
L6:
	.dbline 10
L7:
	.dbline 10
	dec R20
L9:
	.dbline 10
	tst R20
	brne L6
	.dbline 11
L3:
	.dbline 8
	dec R16
L5:
	.dbline 8
	tst R16
	brne L2
	.dbline -2
	.dbline 12
;   for(j=250;j!=0;j--);
;  }
; }
L1:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r j 20 c
	.dbsym r i 16 c
	.dbend
	.dbfunc e Horse _Horse fV
;              i -> R16
	.even
_Horse::
	xcall push_gset1
	.dbline -1
	.dbline 15
; 
; void Horse(uchar i)
; {
	.dbline 16
;  switch(i)
	mov R20,R16
	clr R21
	cpi R20,0
	cpc R20,R21
	breq L14
X0:
	cpi R20,1
	ldi R30,0
	cpc R21,R30
	breq L15
	cpi R20,2
	ldi R30,0
	cpc R21,R30
	breq L16
	cpi R20,3
	ldi R30,0
	cpc R21,R30
	breq L17
	cpi R20,4
	ldi R30,0
	cpc R21,R30
	breq L18
	cpi R20,5
	ldi R30,0
	cpc R21,R30
	breq L19
	cpi R20,6
	ldi R30,0
	cpc R21,R30
	breq L20
	cpi R20,7
	ldi R30,0
	cpc R21,R30
	breq L21
	cpi R20,8
	ldi R30,0
	cpc R21,R30
	breq L22
	xjmp L12
X1:
	.dbline 17
;  {
L14:
	.dbline 18
;   case 0:PORTA=0x00;break;
	clr R2
	out 0x1b,R2
	.dbline 18
	xjmp L12
L15:
	.dbline 19
;   case 1:PORTA=0x01;break;
	ldi R24,1
	out 0x1b,R24
	.dbline 19
	xjmp L12
L16:
	.dbline 20
;   case 2:PORTA=0x03;break;
	ldi R24,3
	out 0x1b,R24
	.dbline 20
	xjmp L12
L17:
	.dbline 21
;   case 3:PORTA=0x07;break;
	ldi R24,7
	out 0x1b,R24
	.dbline 21
	xjmp L12
L18:
	.dbline 22
;   case 4:PORTA=0x0f;break;
	ldi R24,15
	out 0x1b,R24
	.dbline 22
	xjmp L12
L19:
	.dbline 23
;   case 5:PORTA=0x1f;break;
	ldi R24,31
	out 0x1b,R24
	.dbline 23
	xjmp L12
L20:
	.dbline 24
;   case 6:PORTA=0x3f;break;
	ldi R24,63
	out 0x1b,R24
	.dbline 24
	xjmp L12
L21:
	.dbline 25
;   case 7:PORTA=0x7f;break;
	ldi R24,127
	out 0x1b,R24
	.dbline 25
	xjmp L12
L22:
	.dbline 26
	ldi R24,255
	out 0x1b,R24
	.dbline 26
	.dbline 27
L12:
	.dbline -2
	.dbline 29
;   case 8:PORTA=0xff;break;
;   default:break;
;  }
; }
L10:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 16 c
	.dbend
	.dbfunc e main _main fV
;              i -> R20
	.even
_main::
	.dbline -1
	.dbline 32
; 
; void main()
; {
	.dbline 34
;  uchar i;
;  DDRA=0xff;
	ldi R24,255
	out 0x1a,R24
	.dbline 35
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 36
;  Delay(10);
	ldi R16,10
	xcall _Delay
	.dbline 37
;  PORTA=0x00;
	clr R2
	out 0x1b,R2
	xjmp L25
L24:
	.dbline 39
;  while(1)
;  {
	.dbline 40
;   for(i=0;i<9;i++)
	clr R20
	xjmp L30
L27:
	.dbline 41
	.dbline 42
	mov R16,R20
	xcall _Horse
	.dbline 43
	ldi R16,100
	xcall _Delay
	.dbline 44
L28:
	.dbline 40
	inc R20
L30:
	.dbline 40
	cpi R20,9
	brlo L27
	.dbline 45
;   {
;    Horse(i);
;    Delay(100);
;   }
;   for(i=8;i!=0;i--)
	ldi R20,8
	xjmp L34
L31:
	.dbline 46
	.dbline 47
	mov R16,R20
	xcall _Horse
	.dbline 48
	ldi R16,100
	xcall _Delay
	.dbline 49
L32:
	.dbline 45
	dec R20
L34:
	.dbline 45
	tst R20
	brne L31
	.dbline 50
L25:
	.dbline 38
	xjmp L24
X2:
	.dbline -2
	.dbline 51
;   {
;    Horse(i);
;    Delay(100);
;   }
;  }
; }
L23:
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
