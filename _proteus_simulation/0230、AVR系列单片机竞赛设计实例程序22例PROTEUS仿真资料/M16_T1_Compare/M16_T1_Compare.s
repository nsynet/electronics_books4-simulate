	.module M16_T1_Compare.c
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
	.dbfile F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
	.dbsym e Table _Table A[10:10]c
_Data::
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
	.blkb 2
	.area idata
	.byte 0,1
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
	.dbsym e Data _Data A[4:4]c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
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
; #define uint unsigned int
; 
; uchar Table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
; uchar Data[4]={0,0,0,1};
; uchar Key1,Key2,Key3;
; 
; void DelayMs(uchar i)
; {
	.dbline 12
;  uchar j;
;  for(;i!=0;i++)
	xjmp L5
L2:
	.dbline 13
;  {
	.dbline 14
	ldi R20,10
	xjmp L9
L6:
	.dbline 14
L7:
	.dbline 14
	dec R20
L9:
	.dbline 14
	tst R20
	brne L6
	.dbline 15
L3:
	.dbline 12
	inc R16
L5:
	.dbline 12
	tst R16
	brne L2
	.dbline -2
	.dbline 16
;   for(j=10;j!=0;j--);
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
	clr R3
	ldi R24,255
	ldi R25,0
	sub R24,R2
	sbc R25,R3
	out 0x1b,R24
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
;   PORTA=0xff-Table[p[i]];
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
	.dbfunc e Key_Process _Key_Process fV
;              p -> R20,R21
	.even
_Key_Process::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 31
; 
; void Key_Process(uchar *p)
; {
	xjmp L17
L16:
	.dbline 32
	.dbline 32
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 32
	ldi R24,1
	sts _Key1,R24
	.dbline 32
L17:
	.dbline 32
;  while((PINB&0x01)==0){Display(Data);Key1=1;}
	sbis 0x16,0
	rjmp L16
	xjmp L20
L19:
	.dbline 33
	.dbline 33
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 33
	ldi R24,1
	sts _Key2,R24
	.dbline 33
L20:
	.dbline 33
;  while((PINB&0x02)==0){Display(Data);Key2=1;}
	sbis 0x16,1
	rjmp L19
	xjmp L23
L22:
	.dbline 34
	.dbline 34
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 34
	ldi R24,1
	sts _Key3,R24
	.dbline 34
L23:
	.dbline 34
;  while((PINB&0x04)==0){Display(Data);Key3=1;}
	sbis 0x16,2
	rjmp L22
	.dbline 35
;  if(Key1==1)
	lds R24,_Key1
	cpi R24,1
	brne L25
	.dbline 36
;  {
	.dbline 37
;   p[3]++;
	movw R24,R20
	adiw R24,3
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 38
;   if(p[3]==10) p[3]=0;
	movw R30,R20
	ldd R24,z+3
	cpi R24,10
	brne L27
	.dbline 38
	clr R2
	movw R30,R20
	std z+3,R2
L27:
	.dbline 39
;   Key1=0;
	clr R2
	sts _Key1,R2
	.dbline 40
;  }
L25:
	.dbline 41
;  if(Key2==1)
	lds R24,_Key2
	cpi R24,1
	brne L29
	.dbline 42
;  {
	.dbline 43
;   p[2]++;
	movw R24,R20
	adiw R24,2
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 44
;   if(p[2]==10) p[2]=0;
	movw R30,R20
	ldd R24,z+2
	cpi R24,10
	brne L31
	.dbline 44
	clr R2
	movw R30,R20
	std z+2,R2
L31:
	.dbline 45
;   Key2=0;
	clr R2
	sts _Key2,R2
	.dbline 46
;  }
L29:
	.dbline 47
;  if(Key3==1)
	lds R24,_Key3
	cpi R24,1
	brne L33
	.dbline 48
;  {
	.dbline 49
;   p[1]++;
	movw R24,R20
	adiw R24,1
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 50
;   if(p[1]==10) p[1]=0;
	movw R30,R20
	ldd R24,z+1
	cpi R24,10
	brne L35
	.dbline 50
	clr R2
	movw R30,R20
	std z+1,R2
L35:
	.dbline 51
	clr R2
	sts _Key3,R2
	.dbline 52
L33:
	.dbline -2
	.dbline 53
;   Key3=0;
;  }
; }
L15:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r p 20 pc
	.dbend
	.dbfunc e Set_Process _Set_Process fV
;              i -> R20,R21
;              j -> R20,R21
	.even
_Set_Process::
	xcall push_gset1
	.dbline -1
	.dbline 56
; 
; void Set_Process(void)
; {
	.dbline 58
;  uint i,j;
;  i=Data[0]*1000+Data[1]*100+Data[2]*10+Data[3];
	.dbline 59
;  j=500/i;
	.dbline 60
;  OCR1AH=j>>8;
	lds R2,_Data+1
	ldi R24,100
	mul R24,R2
	movw R2,R0
	lds R18,_Data
	clr R19
	ldi R16,1000
	ldi R17,3
	xcall empy16s
	movw R20,R16
	add R20,R2
	adc R21,R3
	lds R2,_Data+2
	ldi R24,10
	mul R24,R2
	add R20,R0
	adc R21,R1
	lds R2,_Data+3
	clr R3
	add R20,R2
	adc R21,R3
	ldi R16,500
	ldi R17,1
	movw R18,R20
	xcall div16u
	movw R20,R16
	movw R2,R20
	mov R2,R3
	clr R3
	out 0x2b,R2
	.dbline 61
;  OCR1AL=j&0x00ff;
	movw R24,R20
	andi R25,0
	out 0x2a,R24
	.dbline -2
	.dbline 62
; }
L37:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r j 20 i
	.dbend
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 65
; 
; void Init_IO(void)
; {
	.dbline 66
;  DDRA=0xff;
	ldi R24,255
	out 0x1a,R24
	.dbline 67
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 68
;  DDRC=0xff;
	out 0x14,R24
	.dbline 69
;  PORTC=0xff;
	out 0x15,R24
	.dbline 70
;  DDRB=0x00;
	clr R2
	out 0x17,R2
	.dbline 71
;  PORTB=0x00;
	out 0x18,R2
	.dbline 72
;  DDRD=0xff;
	out 0x11,R24
	.dbline 73
;  PORTD=0xff;
	out 0x12,R24
	.dbline -2
	.dbline 74
; }
L41:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Init_Timer1 _Init_Timer1 fV
	.even
_Init_Timer1::
	.dbline -1
	.dbline 77
; 
; void Init_Timer1(void)
; {
	.dbline 78
;  TIMSK=TIMSK|0x10;
	in R24,0x39
	ori R24,16
	out 0x39,R24
	.dbline 79
;  TCCR1B=0x0a;
	ldi R24,10
	out 0x2e,R24
	.dbline 80
;  TCNT1H=0x00;
	clr R2
	out 0x2d,R2
	.dbline 81
;  TCNT1L=0x00;
	out 0x2c,R2
	.dbline 82
;  Set_Process();
	xcall _Set_Process
	.dbline 83
;  SREG=SREG|0x80;
	bset 7
	.dbline -2
	.dbline 84
; }
L42:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 87
; 
; void main(void)
; {
	.dbline 88
;  Init_IO();
	xcall _Init_IO
	.dbline 89
;  Init_Timer1();
	xcall _Init_Timer1
	.dbline 90
;  DelayMs(50);
	ldi R16,50
	xcall _DelayMs
	xjmp L45
L44:
	.dbline 92
	.dbline 93
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Key_Process
	.dbline 94
	xcall _Set_Process
	.dbline 95
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 96
L45:
	.dbline 91
	xjmp L44
X0:
	.dbline -2
	.dbline 97
;  while(1)
;  {
;   Key_Process(Data);
;   Set_Process();
;   Display(Data);
;  }
; }
L43:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 24
	jmp _Compare
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
	.dbfunc e Compare _Compare fV
	.even
_Compare::
	st -y,R2
	in R2,0x3f
	st -y,R2
	.dbline -1
	.dbline 101
; 
; #pragma interrupt_handler Compare:7
; void Compare(void)
; {PORTD=~PORTD;}
	.dbline 101
	in R2,0x12
	com R2
	out 0x12,R2
	.dbline -2
	.dbline 101
L47:
	ld R2,y+
	out 0x3f,R2
	ld R2,y+
	.dbline 0 ; func end
	reti
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_Compare\M16_T1_Compare.c
_Key3::
	.blkb 1
	.dbsym e Key3 _Key3 c
_Key2::
	.blkb 1
	.dbsym e Key2 _Key2 c
_Key1::
	.blkb 1
	.dbsym e Key1 _Key1 c
