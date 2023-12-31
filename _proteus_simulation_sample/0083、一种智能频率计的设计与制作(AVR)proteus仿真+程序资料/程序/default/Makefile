###############################################################################
# Makefile for the project biyesheji
###############################################################################

## General Flags
PROJECT = biyesheji
MCU = atmega16
TARGET = biyesheji.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2        -DF_CPU=16000000UL -Os -fsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += 


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0


## Objects that must be built in order to link
OBJECTS = cale.o display.o intree.o mian.o chk.o celiang.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) biyesheji.hex biyesheji.eep size

## Compile
cale.o: ../cale.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

display.o: ../display.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

intree.o: ../intree.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mian.o: ../mian.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

chk.o: ../chk.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

celiang.o: ../celiang.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) biyesheji.elf dep/* biyesheji.hex biyesheji.eep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

