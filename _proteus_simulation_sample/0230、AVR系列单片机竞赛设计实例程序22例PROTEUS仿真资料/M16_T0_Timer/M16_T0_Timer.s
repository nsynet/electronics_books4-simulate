	.module M16_T0_Timer.c
	.area data(ram, con, rel)
_Table::
	.blkb 2
	.area idata
	.byte 192,249
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 164,176
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 153,146
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 130,248
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 128,144
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.dbsym e Table _Table A[10:10]c
_Data::
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.dbsym e Data _Data A[4:4]c
_Time::
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.dbsym e Time _Time A[2:2]c
_CNT::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.dbsym e CNT _CNT c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.dbfunc e DelayMs _DelayMs fV
;              j -> R20
;              i -> R16
	.even
_DelayMs::
	xcall push_gset1
	.dbline -1
	.dbline 10
; #include<iom16v.h>
; #define uchar unsigned char
; 
; uchar Table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
; uchar Data[4]={0,0,0,0};
; uchar Time[2]={0,0};
; uchar CNT=0;
; 
; void DelayMs(uchar i)
; {
	.dbline 12
;  uchar j;
;  for(;i>0;i--)
	xjmp L5
L2:
	.dbline 13
;  {
	.dbline 14
	clr R20
	xjmp L9
L6:
	.dbline 14
L7:
	.dbline 14
	inc R20
L9:
	.dbline 14
	cpi R20,250
	brlo L6
	.dbline 15
L3:
	.dbline 12
	dec R16
L5:
	.dbline 12
	clr R2
	cp R2,R16
	brlo L2
	.dbline -2
	.dbline 16
;   for(j=0;j<250;j++);
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
	.dbline 19
; 
; void Display(uchar *p)
; {
	.dbline 20
;  uchar i,sel=0x01;
	ldi R20,1
	.dbline 21
;  for(i=0;i<4;i++)
	clr R22
	xjmp L14
L11:
	.dbline 22
	.dbline 23
	out 0x15,R20
	.dbline 24
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
	out 0x1b,R2
	.dbline 25
	ldi R16,2
	xcall _DelayMs
	.dbline 26
	lsl R20
	.dbline 27
L12:
	.dbline 21
	inc R22
L14:
	.dbline 21
	cpi R22,4
	brlo L11
	.dbline -2
	.dbline 28
;  {
;   PORTC=sel;
;   PORTA=Table[p[i]];
;   DelayMs(2);
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
	.dbfunc e Process _Process fV
;             p2 -> R20,R21
;             p1 -> R22,R23
	.even
_Process::
	xcall push_gset2
	movw R20,R18
	movw R22,R16
	.dbline -1
	.dbline 31
; 
; void Process(uchar *p1,uchar *p2)
; {
	.dbline 32
;  p2[0]=p1[0]/10;
	ldi R17,10
	movw R30,R22
	ldd R16,z+0
	xcall div8u
	movw R30,R20
	std z+0,R16
	.dbline 33
;  p2[1]=p1[0]%10;
	ldi R17,10
	movw R30,R22
	ldd R16,z+0
	xcall mod8u
	movw R30,R20
	std z+1,R16
	.dbline 34
;  p2[2]=p1[1]/10;
	ldi R17,10
	movw R30,R22
	ldd R16,z+1
	xcall div8u
	movw R30,R20
	std z+2,R16
	.dbline 35
;  p2[3]=p1[1]%10;
	ldi R17,10
	movw R30,R22
	ldd R16,z+1
	xcall mod8u
	movw R30,R20
	std z+3,R16
	.dbline -2
	.dbline 36
; }
L15:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r p2 20 pc
	.dbsym r p1 22 pc
	.dbend
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 39
; 
; void Init_IO(void)
; {
	.dbline 40
;  DDRA=0xff;
	ldi R24,255
	out 0x1a,R24
	.dbline 41
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 42
;  DDRC=0xff;
	out 0x14,R24
	.dbline 43
;  PORTC=0xff;
	out 0x15,R24
	.dbline -2
	.dbline 44
; }
L16:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 47
; 
; void main(void)
; {
	.dbline 48
;  Init_IO();
	xcall _Init_IO
	.dbline 49
;  DelayMs(10);
	ldi R16,10
	xcall _DelayMs
	.dbline 50
;  TCCR0=0x04;
	ldi R24,4
	out 0x33,R24
	.dbline 51
;  TCNT0=0x06;
	ldi R24,6
	out 0x32,R24
	.dbline 52
;  TIMSK=0x01;
	ldi R24,1
	out 0x39,R24
	.dbline 53
;  SREG=SREG|0x80;
	bset 7
	xjmp L19
L18:
	.dbline 55
	.dbline 56
	ldi R18,<_Data
	ldi R19,>_Data
	ldi R16,<_Time
	ldi R17,>_Time
	xcall _Process
	.dbline 57
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 58
L19:
	.dbline 54
	xjmp L18
X0:
	.dbline -2
	.dbline 59
;  while(1)
;  {
;   Process(Time,Data);
;   Display(Data);
;  }
; }
L17:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 36
	jmp _Timer0
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Timer\M16_T0_Timer.c
	.dbfunc e Timer0 _Timer0 fV
	.even
_Timer0::
	st -y,R2
	st -y,R24
	st -y,R25
	in R2,0x3f
	st -y,R2
	.dbline -1
	.dbline 63
; 
; #pragma interrupt_handler Timer0:10
; void Timer0(void)
; {
	.dbline 64
;  CNT++;
	.dbline 65
;  if(CNT==25)
	lds R24,_CNT
	subi R24,255    ; addi 1
	sts _CNT,R24
	cpi R24,25
	brne L22
	.dbline 66
;  {
	.dbline 67
;   CNT=0;
	.dbline 68
;   Time[1]++;
	clr R2
	sts _CNT,R2
	lds R24,_Time+1
	subi R24,255    ; addi 1
	sts _Time+1,R24
	.dbline 69
;   if(Time[1]==60)
	cpi R24,60
	brne L25
	.dbline 70
;   {
	.dbline 71
;    Time[1]=0;
	sts _Time+1,R2
	.dbline 72
;    Time[0]++;
	lds R24,_Time
	subi R24,255    ; addi 1
	sts _Time,R24
	.dbline 73
;   }
L25:
	.dbline 74
;   if(Time[0]==60)
	lds R24,_Time
	cpi R24,60
	brne L29
	.dbline 75
;   Time[0]=0;
	clr R2
	sts _Time,R2
L29:
	.dbline 76
L22:
	.dbline -2
	.dbline 77
;  }
; }
L21:
	ld R2,y+
	out 0x3f,R2
	ld R25,y+
	ld R24,y+
	ld R2,y+
	.dbline 0 ; func end
	reti
	.dbend
