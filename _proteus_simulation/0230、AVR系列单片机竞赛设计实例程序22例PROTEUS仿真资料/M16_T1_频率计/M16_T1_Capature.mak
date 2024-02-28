CC = iccavr
CFLAGS =  -ID:\icc\include\ -e -DATMEGA  -l -g -Wf-intenum -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LD:\icc\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = M16_T1_Capature.o 

M16_T1_Capature:	$(FILES)
	$(CC) -o M16_T1_Capature $(LFLAGS) @M16_T1_Capature.lk   -lstudio -lcatmega
M16_T1_Capature.o: D:/icc/include/iom16v.h D:/icc/include/macros.h
M16_T1_Capature.o:	F:\myavr\temp\M16_T1_Capature\M16_T1_Capature.c
	$(CC) -c $(CFLAGS) F:\myavr\temp\M16_T1_Capature\M16_T1_Capature.c
