CC = iccavr
CFLAGS =  -ID:\icc\include\ -e -DATMEGA  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LD:\icc\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:20 -beeprom:1.512 -fihx_coff -S2
FILES = M16_AD.o 

M16_AD:	$(FILES)
	$(CC) -o M16_AD $(LFLAGS) @M16_AD.lk   -lcatmega
M16_AD.o: D:/icc/include/iom16v.h
M16_AD.o:	F:\myavr\temp\M16_AD\M16_AD.c
	$(CC) -c $(CFLAGS) F:\myavr\temp\M16_AD\M16_AD.c
