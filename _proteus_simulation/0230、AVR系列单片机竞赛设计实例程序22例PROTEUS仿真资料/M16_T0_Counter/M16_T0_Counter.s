	.module M16_T0_Counter.c
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
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
	.dbsym e Table _Table A[10:10]c
_Data::
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
	.dbsym e Data _Data A[8:4]i
_CNT::
	.blkb 2
	.area idata
	.word 0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
	.dbsym e CNT _CNT i
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_T0_Counter\M16_T0_Counter.c
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
; //segment code 0123456789
; uchar Table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
; uint Data[4]={0,0,0,0};
; uint CNT=0;
; 
; void DelayMs(uchar i)
; {
	.dbline 13
;  uchar j;
;  for(;i>0;i--)
	xjmp L5
L2:
	.dbline 14
;  {
	.dbline 15
	clr R20
	xjmp L9
L6:
	.dbline 15
L7:
	.dbline 15
	inc R20
L9:
	.dbline 15
	cpi R20,250
	brlo L6
	.dbline 16
L3:
	.dbline 13
	dec R16
L5:
	.dbline 13
	clr R2
	cp R2,R16
	brlo L2
	.dbline -2
	.dbline 17
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
	.dbline 20
; 
; void Display(uint *p)
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
	ldi R24,2
	mul R24,R22
	movw R30,R0
	add R30,R10
	adc R31,R11
	ldd R2,z+0
	ldd R3,z+1
	ldi R24,<_Table
	ldi R25,>_Table
	movw R30,R2
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x1b,R2
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
	.dbsym r p 10 pi
	.dbend
	.dbfunc e Process _Process fV
;              p -> R22,R23
;              i -> R20,R21
	.even
_Process::
	xcall push_gset2
	movw R22,R18
	movw R20,R16
	.dbline -1
	.dbline 32
; 
; void Process(uint i,uint *p)//由于T0是8位定时/计数器，最大计数值为255
; {                           // 所以下面的p[0]用不着
	.dbline 33
;  p[0]=i/1000;
	ldi R18,1000
	ldi R19,3
	movw R16,R20
	xcall div16u
	movw R30,R22
	std z+1,R17
	std z+0,R16
	.dbline 34
;  i=i%1000;
	.dbline 35
;  p[1]=i/100;
	ldi R18,1000
	ldi R19,3
	movw R16,R20
	xcall mod16u
	movw R20,R16
	ldi R18,100
	ldi R19,0
	xcall div16u
	movw R30,R22
	std z+3,R17
	std z+2,R16
	.dbline 36
;  i=i%100;
	.dbline 37
;  p[2]=i/10;
	ldi R18,100
	ldi R19,0
	movw R16,R20
	xcall mod16u
	movw R20,R16
	ldi R18,10
	ldi R19,0
	xcall div16u
	movw R30,R22
	std z+5,R17
	std z+4,R16
	.dbline 38
;  i=i%10;
	.dbline 39
;  p[3]=i;
	ldi R18,10
	ldi R19,0
	movw R16,R20
	xcall mod16u
	movw R20,R16
	movw R30,R22
	std z+7,R21
	std z+6,R20
	.dbline -2
	.dbline 40
; }
L15:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r p 22 pi
	.dbsym r i 20 i
	.dbend
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 43
; 
; void Init_IO(void)
; {
	.dbline 44
;  DDRA=0xff;
	ldi R24,255
	out 0x1a,R24
	.dbline 45
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 46
;  DDRC=0xff;
	out 0x14,R24
	.dbline 47
;  PORTC=0xff;
	out 0x15,R24
	.dbline 48
;  DDRB=0x00;
	clr R2
	out 0x17,R2
	.dbline 49
;  PORTB=0x00;
	out 0x18,R2
	.dbline -2
	.dbline 50
; }
L16:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;           load -> R20,R21
	.even
_main::
	.dbline -1
	.dbline 53
; 
; void main(void)
; {
	.dbline 55
;  uint load;
;  Init_IO();
	xcall _Init_IO
	.dbline 56
;  TCCR0=0x06;//T0工作在计数方式，T0是8位，所以最大计数值为255；
	ldi R24,6
	out 0x33,R24
	xjmp L19
L18:
	.dbline 61
	.dbline 62
	.dbline 64
	in R20,0x32
	clr R21
	ldi R18,<_Data
	ldi R19,>_Data
	movw R16,R20
	xcall _Process
	.dbline 65
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 66
L19:
	.dbline 60
	xjmp L18
X0:
	.dbline -2
	.dbline 67
;  //TCCR1B=0x07;//T1工作在计数方式，T1是16位，所以最大计数值为65535；
;  //TCNT1H=CNT;
;  //TCNT1L=CNT;
;  while(1)
;  {
;   load=TCNT0;//T0工作在8位计数方式
;   //load=(TCNT1H<<8)+TCNT1L;//T1工作在16位计数方式
;   Process(load,Data);
;   Display(Data);
;  }
; }
L17:
	.dbline 0 ; func end
	ret
	.dbsym r load 20 i
	.dbend
