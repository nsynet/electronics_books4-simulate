	.module M16_EEPROM.C
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
	.blkb 2
	.area idata
	.byte 'w,124
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 57,94
	.area data(ram, con, rel)
	.blkb 2
	.area idata
	.byte 'y,'q
	.area data(ram, con, rel)
	.dbfile F:\myavr\temp\M16_EEPROM\M16_EEPROM.C
	.dbsym e Table _Table A[16:16]c
	.area text(rom, con, rel)
	.dbfile F:\myavr\temp\M16_EEPROM\M16_EEPROM.C
	.dbfunc e DelayMs _DelayMs fV
;              j -> R20,R21
;              i -> R16,R17
	.even
_DelayMs::
	xcall push_gset1
	.dbline -1
	.dbline 15
; //***************FileName:Capature.C***************//
; //***************ICCAVR V6.30编译*****************//
; 
; #include <iom16v.h>                 
; #define uchar unsigned char
; #define uint  unsigned int
; 
; //数码管字型表，对应0，1，2，3，4，5，6，7，8，9，A,B,C,D,E,F//
; uchar Table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
;                  0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
; uchar Read_Data[4];            //定义读出数据
; uchar *p1;
; 
; void DelayMs(uint i)           //Ms级延时，参数i为延时时间
; {uint j;
	.dbline 16
;  for(;i!=0;i--)
	xjmp L5
L2:
	.dbline 17
	.dbline 17
	ldi R20,250
	ldi R21,0
	xjmp L9
L6:
	.dbline 17
	.dbline 17
	.dbline 17
L7:
	.dbline 17
	subi R20,1
	sbci R21,0
L9:
	.dbline 17
	cpi R20,0
	cpc R20,R21
	brne L6
X0:
	.dbline 17
L3:
	.dbline 16
	subi R16,1
	sbci R17,0
L5:
	.dbline 16
	cpi R16,0
	cpc R16,R17
	brne L2
X1:
	.dbline -2
	.dbline 18
;   {for(j=250;j!=0;j--) {;}}
; }
L1:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r j 20 i
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
	.dbline 21
; 
; void Display(uchar *p)         //动态显示函数，参数p为待显示的数组名
; {uchar i,sel=0x01;           
	.dbline 21
	ldi R20,1
	.dbline 22
;  for(i=0;i<4;i++)
	clr R22
	xjmp L14
L11:
	.dbline 23
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
	ldi R17,0
	xcall _DelayMs
	.dbline 26
	lsl R20
	.dbline 27
L12:
	.dbline 22
	inc R22
L14:
	.dbline 22
	cpi R22,4
	brlo L11
	.dbline -2
	.dbline 28
;   {PORTC=sel;                  //选通最右边的数码管
;    PORTA=0xff-Table[p[i]];     //送字型码
;    DelayMs(2);                 //显示延时    
;    sel=sel<<1;                 //移位以显示前一位
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
	.dbfunc e Init_IO _Init_IO fV
	.even
_Init_IO::
	.dbline -1
	.dbline 31
; 
; void Init_IO(void)             //初始化I/O口
; {DDRA=0xff;                    //设置A口为推挽1输出
	.dbline 31
	ldi R24,255
	out 0x1a,R24
	.dbline 32
;  PORTA=0xff;
	out 0x1b,R24
	.dbline 33
;  DDRC=0xff;                    //设置C口为推挽1输出             
	out 0x14,R24
	.dbline 34
;  PORTC=0xff;
	out 0x15,R24
	.dbline -2
	.dbline 35
; }
L15:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Write_EEPROM _Write_EEPROM fV
;        Address -> R22,R23
;           Data -> R20
	.even
_Write_EEPROM::
	xcall push_gset2
	movw R22,R18
	mov R20,R16
	.dbline -1
	.dbline 38
; 
; void Write_EEPROM(uchar Data,uint Address)
; {if(EECR&0x20) DelayMs(4);
	.dbline 38
	sbis 0x1c,5
	rjmp L17
	.dbline 38
	ldi R16,4
	ldi R17,0
	xcall _DelayMs
L17:
	.dbline 39
;  EEARH=Address>>8;
	movw R2,R22
	mov R2,R3
	clr R3
	out 0x1f,R2
	.dbline 40
;  EEARL=Address&0x00ff;
	movw R24,R22
	andi R25,0
	out 0x1e,R24
	.dbline 41
;  EEDR=Data;
	out 0x1d,R20
	.dbline 42
;  EECR=EECR|0x04;
	sbi 0x1c,2
	.dbline 43
;  EECR=EECR|0x02;
	sbi 0x1c,1
	.dbline 44
;  DelayMs(4);
	ldi R16,4
	ldi R17,0
	xcall _DelayMs
	.dbline -2
	.dbline 45
; }
L16:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r Address 22 i
	.dbsym r Data 20 c
	.dbend
	.dbfunc e Read_EEPROM _Read_EEPROM fc
;              i -> R20
;        Address -> R20,R21
	.even
_Read_EEPROM::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 48
; 
; uchar Read_EEPROM(uint Address)
; {uchar i;
	.dbline 49
;  if(EECR&0x01) DelayMs(4);
	sbis 0x1c,0
	rjmp L20
	.dbline 49
	ldi R16,4
	ldi R17,0
	xcall _DelayMs
L20:
	.dbline 50
;  EEARH=Address>>8;
	movw R2,R20
	mov R2,R3
	clr R3
	out 0x1f,R2
	.dbline 51
;  EEARL=Address&0x00ff;
	movw R24,R20
	andi R25,0
	out 0x1e,R24
	.dbline 52
;  EECR=EECR|0x01;
	sbi 0x1c,0
	.dbline 53
;  DelayMs(5);
	ldi R16,5
	ldi R17,0
	xcall _DelayMs
	.dbline 54
;  i=EEDR;
	.dbline 55
;  return(i);
	in R20,0x1d
	mov R16,R20
	.dbline -2
L19:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r Address 20 i
	.dbend
	.dbfunc e main _main fV
;              i -> R20
	.even
_main::
	.dbline -1
	.dbline 59
; }
; 
; void main(void)
; {uchar i;
	.dbline 60
;  Init_IO();                    //初始化I/O口
	xcall _Init_IO
	.dbline 61
;  PORTA=0xff;                   //点亮以测试所有的数码管
	ldi R24,255
	out 0x1b,R24
	.dbline 62
;  PORTC=0x00;   
	clr R2
	out 0x15,R2
	.dbline 63
;  DelayMs(30);                 //延时
	ldi R16,30
	ldi R17,0
	xcall _DelayMs
	.dbline 64
;  PORTC=0xff;                   //熄灭所有的数码管
	ldi R24,255
	out 0x15,R24
	.dbline 65
;  for(i=0;i<4;i++)
	clr R20
	xjmp L26
L23:
	.dbline 66
	.dbline 66
	mov R18,R20
	clr R19
	ldi R24,5
	mul R24,R20
	mov R16,R0
	xcall _Write_EEPROM
	.dbline 66
L24:
	.dbline 65
	inc R20
L26:
	.dbline 65
	cpi R20,4
	brlo L23
	.dbline 67
;     {Write_EEPROM(5*i,i);}
;  for(i=0;i<4;i++)
	clr R20
	xjmp L30
L27:
	.dbline 68
	.dbline 68
	mov R16,R20
	clr R17
	xcall _Read_EEPROM
	ldi R24,<_Read_Data
	ldi R25,>_Read_Data
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	std z+0,R16
	.dbline 69
L28:
	.dbline 67
	inc R20
L30:
	.dbline 67
	cpi R20,4
	brlo L27
	xjmp L32
L31:
	.dbline 71
	.dbline 72
	lds R2,_Read_Data
	lds R30,_p1
	lds R31,_p1+1
	std z+0,R2
	.dbline 73
	movw R16,R30
	xcall _Display
	.dbline 74
	ldi R16,2
	ldi R17,0
	xcall _DelayMs
	.dbline 75
L32:
	.dbline 70
	xjmp L31
X2:
	.dbline -2
	.dbline 76
;     {Read_Data[i]=Read_EEPROM(i);
; 	}
;  while(1)
;  {
;   p1[0]=Read_Data[0];
;   Display(p1);
;   DelayMs(2);
;  }
; }
L22:
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\myavr\temp\M16_EEPROM\M16_EEPROM.C
_p1::
	.blkb 2
	.dbsym e p1 _p1 pc
_Read_Data::
	.blkb 4
	.dbsym e Read_Data _Read_Data A[4:4]c
