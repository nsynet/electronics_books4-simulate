	.module M16_T1_PWM.c
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
	.blkb 1
	.area idata
	.byte 'y
	.area data(ram, con, rel)
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
	.dbsym e Table _Table A[12:12]c
_Data1::
	.blkb 2
	.area idata
	.byte 10,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
	.blkb 2
	.area idata
	.byte 5,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
	.dbsym e Data1 _Data1 A[4:4]c
_Data2::
	.blkb 2
	.area idata
	.byte 3,9
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
	.blkb 2
	.area idata
	.byte 1,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
	.dbsym e Data2 _Data2 A[4:4]c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
	.dbfunc e DelayMs _DelayMs fV
;              j -> R20
;              i -> R16
	.even
_DelayMs::
	xcall push_gset1
	.dbline -1
	.dbline 11
; #include <iom16v.h>
; #define uchar unsigned char
; #define uint unsigned int
; 
; uchar Table[12]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x79};
; uchar Data1[4]={10,0,5,0};
; uchar Data2[4]={3,9,1,0};
; uchar Key1,Key2;
; 
; void DelayMs(uchar i)
; {
	.dbline 13
;  uchar j;
;  for(;i!=0;i--)
	xjmp L5
L2:
	.dbline 14
;  {
	.dbline 15
	ldi R20,25
	xjmp L9
L6:
	.dbline 15
L7:
	.dbline 15
	dec R20
L9:
	.dbline 15
	tst R20
	brne L6
	.dbline 16
L3:
	.dbline 13
	dec R16
L5:
	.dbline 13
	tst R16
	brne L2
	.dbline -2
	.dbline 17
;   for(j=25;j!=0;j--);
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
	.dbline 20
; 
; void Display(uchar *p)
; {
	.dbline 21
;  uchar i,sel=0x01;
	ldi R20,1
	.dbline 22
;  for(i=0;i<4;i++)
	clr R22
	xjmp L14
L11:
	.dbline 23
	.dbline 24
	out 0x15,R20
	.dbline 25
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
	.dbline 26
	ldi R16,2
	xcall _DelayMs
	.dbline 27
	lsl R20
	.dbline 28
L12:
	.dbline 22
	inc R22
L14:
	.dbline 22
	cpi R22,4
	brlo L11
	.dbline -2
	.dbline 29
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
	.dbfunc e Add_Process _Add_Process fV
;              p -> R16,R17
	.even
_Add_Process::
	.dbline -1
	.dbline 32
; 
; void Add_Process(uchar *p)
; {
	.dbline 33
;  if(p[1]!=1)
	movw R30,R16
	ldd R24,z+1
	cpi R24,1
	breq L16
	.dbline 34
;  {
	.dbline 35
;   p[2]++;
	movw R24,R16
	adiw R24,2
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 36
;   if(p[2]==10) {p[2]=0;p[1]++;}
	movw R30,R16
	ldd R24,z+2
	cpi R24,10
	brne L18
	.dbline 36
	.dbline 36
	clr R2
	movw R30,R16
	std z+2,R2
	.dbline 36
	movw R24,R16
	adiw R24,1
	movw R30,R24
	ldd R24,z+0
	subi R24,255    ; addi 1
	std z+0,R24
	.dbline 36
L18:
	.dbline 37
L16:
	.dbline -2
	.dbline 38
;  }
; }
L15:
	.dbline 0 ; func end
	ret
	.dbsym r p 16 pc
	.dbend
	.dbfunc e Sub_Process _Sub_Process fV
;           temp -> R22
;              p -> R20,R21
	.even
_Sub_Process::
	xcall push_gset2
	movw R20,R16
	.dbline -1
	.dbline 40
	.dbline 42
	.dbline 43
	movw R30,R20
	ldd R2,z+1
	ldi R24,10
	mul R24,R2
	mov R22,R0
	movw R30,R20
	ldd R2,z+2
	add R22,R2
	breq L21
	.dbline 44
	.dbline 45
	.dbline 46
	dec R22
	ldi R17,10
	mov R16,R22
	xcall div8u
	movw R30,R20
	std z+1,R16
	.dbline 47
	ldi R17,10
	mov R16,R22
	xcall mod8u
	movw R30,R20
	std z+2,R16
	.dbline 48
L21:
	.dbline -2
	.dbline 49
; void Sub_Process(uchar *p)
; {
;  uchar temp;
;  temp=p[1]*10+p[2];
;  if(temp!=0)
;  {
;   temp=temp-1;
;   p[1]=temp/10;
;   p[2]=temp%10;
;  }
; }
L20:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r temp 22 c
	.dbsym r p 20 pc
	.dbend
	.dbfunc e Key_Process _Key_Process fV
	.even
_Key_Process::
	.dbline -1
	.dbline 51
; void Key_Process()
; {
	xjmp L25
L24:
	.dbline 52
	.dbline 52
	ldi R16,<_Data1
	ldi R17,>_Data1
	xcall _Display
	.dbline 52
	ldi R24,1
	sts _Key1,R24
	.dbline 52
L25:
	.dbline 52
;  while((PINB&0x01)==0){Display(Data1);Key1=1;}
	sbis 0x16,0
	rjmp L24
	xjmp L28
L27:
	.dbline 53
	.dbline 53
	ldi R16,<_Data1
	ldi R17,>_Data1
	xcall _Display
	.dbline 53
	ldi R24,1
	sts _Key2,R24
	.dbline 53
L28:
	.dbline 53
;  while((PINB&0x02)==0){Display(Data1);Key2=1;}
	sbis 0x16,1
	rjmp L27
	.dbline 54
;  if(Key1==1)
	lds R24,_Key1
	cpi R24,1
	brne L30
	.dbline 55
;  {
	.dbline 56
;   Add_Process(Data1);
	ldi R16,<_Data1
	ldi R17,>_Data1
	xcall _Add_Process
	.dbline 57
;   Key1=0;
	clr R2
	sts _Key1,R2
	.dbline 58
;  }
L30:
	.dbline 59
	lds R24,_Key2
	cpi R24,1
	brne L32
	.dbline 60
	.dbline 61
	ldi R16,<_Data1
	ldi R17,>_Data1
	xcall _Sub_Process
	.dbline 62
	clr R2
	sts _Key2,R2
	.dbline 63
L32:
	.dbline -2
	.dbline 64
;  if(Key2==1)
;  {
;   Sub_Process(Data1);
;   Key2=0;
;  }
; }
L23:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Set_Process _Set_Process fV
;              i -> R20,R21
;              p -> R20,R21
	.even
_Set_Process::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 66
; void Set_Process(uchar *p)
; {
	.dbline 68
;  uint i;
;  i=p[1]*10+p[2];
	.dbline 69
;  i=1023*i/10;
	.dbline 70
;  OCR1AH=i>>8;
	movw R30,R20
	ldd R2,z+1
	ldi R24,10
	mul R24,R2
	movw R2,R0
	movw R30,R20
	ldd R4,z+2
	clr R5
	add R2,R4
	adc R3,R5
	ldi R16,1023
	ldi R17,3
	movw R18,R2
	xcall empy16s
	ldi R18,10
	ldi R19,0
	xcall div16u
	movw R20,R16
	movw R2,R20
	mov R2,R3
	clr R3
	out 0x2b,R2
	.dbline 71
;  OCR1AL=i&0x00ff;
	movw R24,R20
	andi R25,0
	out 0x2a,R24
	.dbline -2
	.dbline 72
; }
L34:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r p 20 pc
	.dbend
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 74
; void Init_IO(void)
; {
	.dbline 75
;  DDRA=0xff;
	ldi R24,255
	out 0x1a,R24
	.dbline 76
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 77
;  DDRC=0xff;
	out 0x14,R24
	.dbline 78
;  PORTC=0xff;
	out 0x15,R24
	.dbline 79
;  DDRB=0x00;
	clr R2
	out 0x17,R2
	.dbline 80
;  PORTB=0x00;
	out 0x18,R2
	.dbline 81
;  DDRD=0xff;
	out 0x11,R24
	.dbline 82
;  PORTD=0xff;
	out 0x12,R24
	.dbline -2
	.dbline 83
; }
L35:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 85
; void main(void)
; {
	.dbline 86
;  Init_IO();
	xcall _Init_IO
	.dbline 87
;  TCCR1A=0xc3;
	ldi R24,195
	out 0x2f,R24
	.dbline 88
;  TCCR1B=0x02;
	ldi R24,2
	out 0x2e,R24
	.dbline 89
;  DelayMs(50);
	ldi R16,50
	xcall _DelayMs
	xjmp L38
L37:
	.dbline 91
	.dbline 92
	xcall _Key_Process
	.dbline 93
	ldi R16,<_Data1
	ldi R17,>_Data1
	xcall _Set_Process
	.dbline 94
	ldi R16,<_Data1
	ldi R17,>_Data1
	xcall _Display
	.dbline 95
L38:
	.dbline 90
	xjmp L37
X0:
	.dbline -2
	.dbline 96
;  while(1)
;  {
;   Key_Process();
;   Set_Process(Data1);
;   Display(Data1);
;  }
; }
L36:
	.dbline 0 ; func end
	ret
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T1_PWM\M16_T1_PWM.c
_Key2::
	.blkb 1
	.dbsym e Key2 _Key2 c
_Key1::
	.blkb 1
	.dbsym e Key1 _Key1 c
