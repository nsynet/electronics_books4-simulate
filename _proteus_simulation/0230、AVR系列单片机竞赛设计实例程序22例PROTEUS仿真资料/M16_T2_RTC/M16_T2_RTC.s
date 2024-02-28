	.module M16_T2_RTC.c
	.area data(ram, con, rel)
_Table::
	.blkb 2
	.area idata
	.byte 63,6
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 91,'O
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 'f,'m
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 125,7
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 127,'o
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T2_RTC\M16_T2_RTC.c
	.dbsym e Table _Table A[10:10]c
_Data::
	.blkb 2
	.area idata
	.byte 1,2
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T2_RTC\M16_T2_RTC.c
	.blkb 2
	.area idata
	.byte 3,4
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T2_RTC\M16_T2_RTC.c
	.dbsym e Data _Data A[4:4]c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T2_RTC\M16_T2_RTC.c
	.dbfunc e DelayMs _DelayMs fV
;              j -> R20
;              i -> R16
	.even
_DelayMs::
	xcall push_gset1
	.dbline -1
	.dbline 9
; #include <iom16v.h>
; #define uchar unsigned char
; #define uint unsigned int
; //segment code//
; uchar Table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
; uchar Data[4]={1,2,3,4};//定义初始时间00：00
; uchar CNT;
; void DelayMs(uchar i)
; {
	.dbline 11
;  uchar j;
;  for(;i!=0;i--)
	xjmp L5
L2:
	.dbline 12
;  {
	.dbline 13
	ldi R20,250
	xjmp L9
L6:
	.dbline 13
L7:
	.dbline 13
	dec R20
L9:
	.dbline 13
	tst R20
	brne L6
	.dbline 14
L3:
	.dbline 11
	dec R16
L5:
	.dbline 11
	tst R16
	brne L2
	.dbline -2
	.dbline 15
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
	.dbfunc e Display _Display fV
;            sel -> R20
;              i -> R22
;              p -> R10,R11
	.even
_Display::
	xcall push_gset3
	movw R10,R16
	.dbline -1
	.dbline 18
; 
; void Display(uchar *p)
; {
	.dbline 19
;  uchar i,sel=0x01;
	ldi R20,1
	.dbline 20
;  for(i=0;i<4;i++)
	clr R22
	xjmp L14
L11:
	.dbline 21
	.dbline 22
	out 0x18,R20
	.dbline 23
	mov R30,R22
	clr R31
	add R30,R10
	adc R31,R11
	ldd R30,z+0
	clr R31
	ldi R24,<_Table
	ldi R25,>_Table
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	clr R3
	ldi R24,255
	ldi R25,0
	sub R24,R2
	sbc R25,R3
	out 0x1b,R24
	.dbline 24
	ldi R16,1
	xcall _DelayMs
	.dbline 25
	lsl R20
	.dbline 26
L12:
	.dbline 20
	inc R22
L14:
	.dbline 20
	cpi R22,4
	brlo L11
	.dbline -2
	.dbline 27
;  {
;   PORTB=sel;
;   PORTA=0xff-Table[p[i]];
;   DelayMs(1);
;   sel=sel<<1;
;  }
; }
L10:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r sel 20 c
	.dbsym r i 22 c
	.dbsym r p 10 pc
	.dbend
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 30
; 
; void Init_IO(void)
; {
	.dbline 31
;  DDRA=0xff;
	ldi R24,255
	out 0x1a,R24
	.dbline 32
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 33
;  DDRB=0xff;
	out 0x17,R24
	.dbline 34
;  PORTB=0xff;
	out 0x18,R24
	.dbline 35
;  DDRC=0xff;
	out 0x14,R24
	.dbline 36
;  PORTC=0xff;
	out 0x15,R24
	.dbline -2
	.dbline 37
;  }
L15:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Add_Second _Add_Second fV
;              p -> R16,R17
	.even
_Add_Second::
	.dbline -1
	.dbline 40
; 
; void Add_Second(uchar *p)
; {
	.dbline 41
;  p[3]++;
	movw R24,R16
	adiw R24,3
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 42
;  if(p[3]==10){p[3]=0;p[2]++;}
	movw R30,R16
	ldd R24,z+3
	cpi R24,10
	brne L17
	.dbline 42
	.dbline 42
	clr R2
	movw R30,R16
	std z+3,R2
	.dbline 42
	movw R24,R16
	adiw R24,2
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 42
L17:
	.dbline 43
;  if(p[2]==6){p[2]=0;p[1]++;}
	movw R30,R16
	ldd R24,z+2
	cpi R24,6
	brne L19
	.dbline 43
	.dbline 43
	clr R2
	movw R30,R16
	std z+2,R2
	.dbline 43
	movw R24,R16
	adiw R24,1
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 43
L19:
	.dbline 44
;  if(p[1]==10){p[1]=0;p[0]++;}
	movw R30,R16
	ldd R24,z+1
	cpi R24,10
	brne L21
	.dbline 44
	.dbline 44
	clr R2
	movw R30,R16
	std z+1,R2
	.dbline 44
	movw R30,R16
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 44
L21:
	.dbline 45
	movw R30,R16
	ldd R24,z+0
	cpi R24,6
	brne L23
	.dbline 45
	.dbline 45
	clr R2
	std z+0,R2
	.dbline 45
L23:
	.dbline -2
	.dbline 46
;  if(p[0]==6){p[0]=0;}
; }
L16:
	.dbline 0 ; func end
	ret
	.dbsym r p 16 pc
	.dbend
	.dbfunc e main _main fV
;              i -> <dead>
	.even
_main::
	.dbline -1
	.dbline 49
; 
; void main(void)
; {
	.dbline 51
;  uchar i;
;  Init_IO();
	xcall _Init_IO
	.dbline 52
;  PORTA=0xff;
	ldi R24,255
	out 0x1b,R24
	.dbline 53
;  PORTB=0x00;
	clr R2
	out 0x18,R2
	.dbline 54
;  DelayMs(10);
	ldi R16,10
	xcall _DelayMs
	.dbline 55
;  PORTB=0xff;
	ldi R24,255
	out 0x18,R24
	.dbline 56
;  ASSR=0x08;//异步时钟使能
	ldi R24,8
	out 0x22,R24
	.dbline 57
;  TCCR2=0x07;//32.768KHZ的晶振1024分频作为T/C2的时钟源
	ldi R24,7
	out 0x25,R24
	.dbline 58
;  TIMSK=0x40;//T/C2中断溢出使能
	ldi R24,64
	out 0x39,R24
	.dbline 59
;  SREG=SREG|0x80;//全局中断使能
	bset 7
	xjmp L27
L26:
	.dbline 61
;  while(1)
;  {
	.dbline 62
;   Display(Data);
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 63
;   if(CNT==32)
	lds R24,_CNT
	cpi R24,32
	brne L29
	.dbline 64
;   {
	.dbline 65
;    CNT=0;
	.dbline 66
;    Add_Second(Data);
	clr R2
	sts _CNT,R2
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Add_Second
	.dbline 67
;   }
L29:
	.dbline 68
L27:
	.dbline 60
	xjmp L26
X0:
	.dbline -2
	.dbline 69
;  }
; }
L25:
	.dbline 0 ; func end
	ret
	.dbsym l i 1 c
	.dbend
	.area vector(rom, abs)
	.org 16
	jmp _Timer2
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T2_RTC\M16_T2_RTC.c
	.dbfunc e Timer2 _Timer2 fV
	.even
_Timer2::
	st -y,R24
	st -y,R25
	in R24,0x3f
	st -y,R24
	.dbline -1
	.dbline 73
; 
; #pragma interrupt_handler Timer2:5
; void Timer2(void)
; {CNT=CNT+1;}
	.dbline 73
	lds R24,_CNT
	subi R24,255    ; addi 1
	sts _CNT,R24
	.dbline -2
	.dbline 73
L31:
	ld R24,y+
	out 0x3f,R24
	ld R25,y+
	ld R24,y+
	.dbline 0 ; func end
	reti
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T2_RTC\M16_T2_RTC.c
_CNT::
	.blkb 1
	.dbsym e CNT _CNT c
