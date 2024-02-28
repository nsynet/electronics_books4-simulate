	.module led_dsp.c
	.area lit(rom, con, rel)
_led_tabel::
	.byte 63,6
	.byte 91,'O
	.byte 'f,'m
	.byte 125,7
	.byte 127,'o
	.dbfile E:/学习/AVR/adc/led_dsp.h
	.dbsym e led_tabel _led_tabel A[10:10]kc
	.area data(ram, con, rel)
	.dbfile E:/学习/AVR/adc/led_dsp.h
_disp_buffer::
	.blkb 2
	.area idata
	.byte 63,63
	.area data(ram, con, rel)
	.dbfile E:/学习/AVR/adc/led_dsp.h
	.blkb 2
	.area idata
	.byte 63,63
	.area data(ram, con, rel)
	.dbfile E:/学习/AVR/adc/led_dsp.h
	.dbsym e disp_buffer _disp_buffer A[4:4]c
	.area text(rom, con, rel)
	.dbfile E:/学习/AVR/adc/led_dsp.h
	.dbfile E:\学习\AVR\adc\led_dsp.c
	.dbfunc e change_data _change_data fV
;         temp_n -> R22
;       dsp_data -> R20,R21
	.even
_change_data::
	rcall push_gset2
	movw R20,R16
	.dbline -1
	.dbline 7
; #define _led_dsp_c
; #include <io8535v.h>
; #include <macros.h>
; #include <led_dsp.h>
; #include <adc.h>
; void change_data (int dsp_data)
; {
	.dbline 9
; 	uchar temp_n;
; 	if(dsp_data<=(AREF_VOL*100))
	ldi R24,1500
	ldi R25,5
	cp R24,R20
	cpc R25,R21
	brge X0
	rjmp L1
X0:
	.dbline 10
; 		{
	.dbline 11
; 			temp_n = dsp_data/1000;
	ldi R18,1000
	ldi R19,3
	movw R16,R20
	rcall div16s
	mov R22,R16
	.dbline 12
; 			disp_buffer[0]=led_tabel[temp_n];
	ldi R24,<_led_tabel
	ldi R25,>_led_tabel
	mov R30,R22
	clr R31
	add R30,R24
	adc R31,R25
	lpm R30,Z
	sts _disp_buffer,R30
	.dbline 13
; 			dsp_data %=1000;
	ldi R18,1000
	ldi R19,3
	movw R16,R20
	rcall mod16s
	movw R20,R16
	.dbline 14
; 			temp_n = dsp_data/100;
	ldi R18,100
	ldi R19,0
	rcall div16s
	mov R22,R16
	.dbline 15
; 			disp_buffer[1]=(led_tabel[temp_n])|0x80;//加上小数点
	ldi R24,<_led_tabel
	ldi R25,>_led_tabel
	mov R30,R22
	clr R31
	add R30,R24
	adc R31,R25
	lpm R30,Z
	ori R30,128
	sts _disp_buffer+1,R30
	.dbline 16
; 			dsp_data %=100;
	ldi R18,100
	ldi R19,0
	movw R16,R20
	rcall mod16s
	movw R20,R16
	.dbline 17
; 			temp_n = dsp_data/10;
	ldi R18,10
	ldi R19,0
	rcall div16s
	mov R22,R16
	.dbline 18
; 			disp_buffer[2]=led_tabel[temp_n];
	ldi R24,<_led_tabel
	ldi R25,>_led_tabel
	mov R30,R22
	clr R31
	add R30,R24
	adc R31,R25
	lpm R30,Z
	sts _disp_buffer+2,R30
	.dbline 19
; 			dsp_data %=10;
	ldi R18,10
	ldi R19,0
	movw R16,R20
	rcall mod16s
	movw R20,R16
	.dbline 20
; 			disp_buffer[3]=led_tabel[dsp_data];
	ldi R24,<_led_tabel
	ldi R25,>_led_tabel
	movw R30,R20
	add R30,R24
	adc R31,R25
	lpm R30,Z
	sts _disp_buffer+3,R30
	.dbline 21
; 		}
	.dbline 23
; 	//scan_led(disp_buffer);
; 	return;
	.dbline -2
L1:
	rcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r temp_n 22 c
	.dbsym r dsp_data 20 I
	.dbend
	.dbfunc e scan_led _scan_led fV
;         scan_n -> R20
;              i -> R22
;         disp_p -> R10,R11
	.even
_scan_led::
	rcall push_gset3
	movw R10,R16
	.dbline -1
	.dbline 27
; }
; 
; void scan_led(uchar *disp_p)
; {
	.dbline 29
; 	uchar i,scan_n;
; 	scan_n=0xfe;
	ldi R20,254
	.dbline 30
; 	for (i=0; i<4; i++)
	clr R22
	rjmp L11
L8:
	.dbline 31
	.dbline 32
	mov R30,R22
	clr R31
	add R30,R10
	adc R31,R11
	ldd R2,z+0
	out 0x18,R2
	.dbline 33
	out 0x12,R20
	.dbline 34
	lsl R20
	subi R20,255    ; addi 1
	.dbline 35
	ldi R16,50
	rcall _delay
	.dbline 36
	ldi R24,255
	out 0x12,R24
	.dbline 37
L9:
	.dbline 30
	inc R22
L11:
	.dbline 30
	cpi R22,4
	brlo L8
	.dbline 38
; 	{
; 		data_port = *(disp_p+i);
; 		scan_port = scan_n;
; 		scan_n=(scan_n<<1)+1;
; 		delay(50);
; 		scan_port = 0xff;
; 	}
; 	return;
	.dbline -2
L7:
	rcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r scan_n 20 c
	.dbsym r i 22 c
	.dbsym r disp_p 10 pc
	.dbend
	.dbfunc e delay _delay fV
;              c -> R20
;        delay_t -> R16
	.even
_delay::
	rcall push_gset1
	.dbline -1
	.dbline 43
; 	
; }
; 
; void delay(uchar delay_t)
; {
	rjmp L14
L13:
	.dbline 46
; 	uchar c;
; 	while(delay_t--)
; 	{
	.dbline 47
; 		c=10;
	ldi R20,10
L16:
	.dbline 48
L17:
	.dbline 48
	mov R2,R20
	clr R3
	subi R20,1
	tst R2
	brne L16
	.dbline 49
L14:
	.dbline 45
	mov R2,R16
	clr R3
	subi R16,1
	tst R2
	brne L13
	.dbline -2
	.dbline 50
; 		while(c--);
; 	}
; }
L12:
	rcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r c 20 c
	.dbsym r delay_t 16 c
	.dbend
