	.module M16_AD.c
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
	.dbfile F:\myavr\temp\M16_AD\M16_AD.c
	.dbsym e Table _Table A[10:10]c
_Data::
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_AD\M16_AD.c
	.blkb 2
	.area idata
	.byte 0,0
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_AD\M16_AD.c
	.dbsym e Data _Data A[4:4]c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_AD\M16_AD.c
	.dbfunc e DelayMs _DelayMs fV
;              j -> R20
;              i -> R16,R17
	.even
_DelayMs::
	xcall push_gset1
	.dbline -1
	.dbline 10
; #include<iom16v.h>
; #define uchar unsigned char
; #define uint  unsigned int
; 
; 
; uchar Table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
; uchar Data[4]={0,0,0,0};
; 
; void DelayMs(uint i)  //0.25ms
; {uchar j;
	.dbline 11
;  for(;i!=0;i--)
	xjmp L5
L2:
	.dbline 12
	.dbline 12
	ldi R20,250
	xjmp L9
L6:
	.dbline 12
	.dbline 12
	.dbline 12
L7:
	.dbline 12
	dec R20
L9:
	.dbline 12
	tst R20
	brne L6
	.dbline 12
L3:
	.dbline 11
	subi R16,1
	sbci R17,0
L5:
	.dbline 11
	cpi R16,0
	cpc R16,R17
	brne L2
X0:
	.dbline -2
	.dbline 13
;   {for(j=250;j!=0;j--) {;}}
; }
L1:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r j 20 c
	.dbsym r i 16 i
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
	.dbline 16
; 
; void Display(uchar *p) //间隔5ms显示
; {uchar i,sel=0x01;
	.dbline 16
	ldi R20,1
	.dbline 17
;  for(i=0;i<4;i++)
	clr R22
	xjmp L14
L11:
	.dbline 18
	.dbline 18
	out 0x12,R20
	.dbline 19
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
	out 0x18,R24
	.dbline 20
	ldi R16,10
	ldi R17,0
	xcall _DelayMs
	.dbline 21
	lsl R20
	.dbline 22
L12:
	.dbline 17
	inc R22
L14:
	.dbline 17
	cpi R22,4
	brlo L11
	.dbline -2
	.dbline 23
;   {PORTD=sel;
;    PORTB=0xff-Table[p[i]];
;    DelayMs(10);
;    sel=sel<<1;
;   }
; }
L10:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r sel 20 c
	.dbsym r i 22 c
	.dbsym r p 10 pc
	.dbend
	.dbfunc e ADC_Convert _ADC_Convert fi
;          temp1 -> R18,R19
;          temp2 -> R16,R17
	.even
_ADC_Convert::
	.dbline -1
	.dbline 26
; 
; uint ADC_Convert(void)
; {uint temp1,temp2;
	.dbline 27
;  temp1=(uint)ADCL;
	.dbline 28
;  temp2=(uint)ADCH;
	.dbline 29
;  temp2=(temp2<<8)+temp1;
	.dbline 30
;  return(temp2);
	in R18,0x4
	clr R19
	in R16,0x5
	clr R17
	movw R2,R16
	mov R3,R2
	clr R2
	add R2,R18
	adc R3,R19
	movw R16,R2
	.dbline -2
L15:
	.dbline 0 ; func end
	ret
	.dbsym r temp1 18 i
	.dbsym r temp2 16 i
	.dbend
	.dbfunc e Process _Process fV
;              p -> R20,R21
;              i -> R22,R23
	.even
_Process::
	xcall push_gset2
	movw R20,R18
	movw R22,R16
	.dbline -1
	.dbline 34
; }
; 
; void Process(uint i,uchar *p)
; {p[0]=i/1000;
	.dbline 34
	ldi R18,1000
	ldi R19,3
	movw R16,R22
	xcall div16u
	movw R30,R20
	std z+0,R16
	.dbline 35
;  i=i%1000;
	.dbline 36
;  p[1]=i/100;
	ldi R18,1000
	ldi R19,3
	movw R16,R22
	xcall mod16u
	movw R22,R16
	ldi R18,100
	ldi R19,0
	xcall div16u
	movw R30,R20
	std z+1,R16
	.dbline 37
;  i=i%100;
	.dbline 38
;  p[2]=i/10;
	ldi R18,100
	ldi R19,0
	movw R16,R22
	xcall mod16u
	movw R22,R16
	ldi R18,10
	ldi R19,0
	xcall div16u
	movw R30,R20
	std z+2,R16
	.dbline 39
;  i=i%10;
	.dbline 40
;  p[3]=i;
	ldi R18,10
	ldi R19,0
	movw R16,R22
	xcall mod16u
	movw R22,R16
	movw R30,R20
	std z+3,R22
	.dbline -2
	.dbline 41
; }
L16:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r p 20 pc
	.dbsym r i 22 i
	.dbend
	.dbfunc e main _main fV
;              i -> R20,R21
	.even
_main::
	.dbline -1
	.dbline 44
; 
; void main(void)
; {uint i;
	.dbline 45
;  DDRA=0x00;                    //设置A口为不带上拉输入；
	clr R2
	out 0x1a,R2
	.dbline 46
;  PORTA=0x00;
	out 0x1b,R2
	.dbline 47
;  DDRB=0xff;                    //设置B口为推挽1输出；
	ldi R24,255
	out 0x17,R24
	.dbline 48
;  PORTB=0xff;
	out 0x18,R24
	.dbline 49
;  DDRD=0xff;                    //设置C口为推挽1输出；
	out 0x11,R24
	.dbline 50
;  PORTD=0xff;
	out 0x12,R24
	.dbline 51
;  PORTB=0x00;                   //B口初始化输出1；C口初始化输出0；点亮全部数码管；
	out 0x18,R2
	.dbline 52
;  PORTD=0xff;
	out 0x12,R24
	.dbline 53
;  ADMUX=0x01;                   //选择第二通道ADC1；
	ldi R24,1
	out 0x7,R24
	.dbline 54
;  ADCSR=0xe6;                   //125K转换速率，自由转换模式；启动AD转换器；
	ldi R24,230
	out 0x6,R24
	.dbline 55
;  DelayMs(3000);                //延时待系统稳定；
	ldi R16,3000
	ldi R17,11
	xcall _DelayMs
	xjmp L19
L18:
	.dbline 57
	.dbline 57
	xcall _ADC_Convert
	movw R20,R16
	.dbline 58
	ldi R18,<_Data
	ldi R19,>_Data
	xcall _Process
	.dbline 59
	ldi R16,<_Data
	ldi R17,>_Data
	xcall _Display
	.dbline 60
L19:
	.dbline 56
	xjmp L18
X1:
	.dbline -2
	.dbline 61
;  while(1)
;  {i=ADC_Convert();
;   Process(i,Data);
;   Display(Data);
;  }
; }
L17:
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbend
