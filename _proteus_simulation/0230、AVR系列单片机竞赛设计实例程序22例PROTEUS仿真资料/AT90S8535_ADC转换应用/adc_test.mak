CC = iccavr
CFLAGS =  -ID:\ICC\include\ -IE:\ѧϰ\AVR\adc -e  -l -g -Mavr_enhanced_small -Wa-W 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LD:\ICC\lib\ -g -Wl-W -bfunc_lit:0x22.0x2000 -dram_end:0x25f -bdata:0x60.0x25f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = adc.o led_dsp.o main.o dac.o 

adc_test:	$(FILES)
	$(CC) -o adc_test $(LFLAGS) @adc_test.lk  
adc.o: D:/ICC/include/io8535v.h D:/ICC/include/macros.h E:/ѧϰ/AVR/adc/adc.h
adc.o:	E:\ѧϰ\AVR\adc\adc.c
	$(CC) -c $(CFLAGS) E:\ѧϰ\AVR\adc\adc.c
led_dsp.o: D:/ICC/include/io8535v.h D:/ICC/include/macros.h E:/ѧϰ/AVR/adc/led_dsp.h E:/ѧϰ/AVR/adc/adc.h
led_dsp.o:	E:\ѧϰ\AVR\adc\led_dsp.c
	$(CC) -c $(CFLAGS) E:\ѧϰ\AVR\adc\led_dsp.c
main.o: D:/ICC/include/io8535v.h D:/ICC/include/macros.h E:/ѧϰ/AVR/adc/adc.h E:/ѧϰ/AVR/adc/led_dsp.h E:/ѧϰ/AVR/adc/dac.h
main.o:	E:\ѧϰ\AVR\adc\main.c
	$(CC) -c $(CFLAGS) E:\ѧϰ\AVR\adc\main.c
dac.o: D:/ICC/include/io8535v.h D:/ICC/include/macros.h E:/ѧϰ/AVR/adc/dac.h
dac.o:	E:\ѧϰ\AVR\adc\dac.c
	$(CC) -c $(CFLAGS) E:\ѧϰ\AVR\adc\dac.c
