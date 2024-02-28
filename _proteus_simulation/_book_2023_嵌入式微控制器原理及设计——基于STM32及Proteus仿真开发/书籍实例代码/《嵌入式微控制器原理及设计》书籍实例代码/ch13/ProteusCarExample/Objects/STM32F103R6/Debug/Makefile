###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103R6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -IC:/Keil_v5/ARM/CMSIS/Include -g -DSTM32F10X_LD -DUSE_STDPERIPH_DRIVER
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/Debug.elf: TOOL=LD
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/startup_stm32f10x_md.o: TOOL=ASM
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/startup_stm32f10x_md.s
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_gpio.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_gpio.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_rcc.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_rcc.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/system_stm32f10x.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/system_stm32f10x.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_usart.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_usart.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/core_cm3.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/core_cm3.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/main.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/main.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/misc.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/misc.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_adc.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_adc.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_it.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_it.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/usart.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/usart.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_dma.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_dma.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_tim.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_tim.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/stm32f10x_exti.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/stm32f10x_exti.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/DHT11.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/DHT11.c
#     D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/Debug/sys.o: TOOL=CC
#        D:/2020年上半年授课/研究生嵌入式技术/嵌入式技术20200324/综合项目_SUF/Proteus/Car/Objects/STM32F103R6/sys.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	startup_stm32f10x_md.o stm32f10x_gpio.o stm32f10x_rcc.o system_stm32f10x.o stm32f10x_usart.o core_cm3.o main.o misc.o stm32f10x_adc.o stm32f10x_it.o usart.o stm32f10x_dma.o stm32f10x_tim.o stm32f10x_exti.o DHT11.o sys.o 
	$(LD)  $(LDFLAGS)  "startup_stm32f10x_md.o" "stm32f10x_gpio.o" "stm32f10x_rcc.o" "system_stm32f10x.o" "stm32f10x_usart.o" "core_cm3.o" "main.o" "misc.o" "stm32f10x_adc.o" "stm32f10x_it.o" "usart.o" "stm32f10x_dma.o" "stm32f10x_tim.o" "stm32f10x_exti.o" "DHT11.o" "sys.o" --output "Debug.elf"

startup_stm32f10x_md.o:	../startup_stm32f10x_md.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f10x_md.s" -o "startup_stm32f10x_md.o"

stm32f10x_gpio.o:	../stm32f10x_gpio.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_gpio.c" -c -o "stm32f10x_gpio.o"

stm32f10x_rcc.o:	../stm32f10x_rcc.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_rcc.c" -c -o "stm32f10x_rcc.o"

system_stm32f10x.o:	../system_stm32f10x.c 
	$(CC) $(CCFLAGS)  "../system_stm32f10x.c" -c -o "system_stm32f10x.o"

stm32f10x_usart.o:	../stm32f10x_usart.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_usart.c" -c -o "stm32f10x_usart.o"

core_cm3.o:	../core_cm3.c 
	$(CC) $(CCFLAGS)  "../core_cm3.c" -c -o "core_cm3.o"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

misc.o:	../misc.c 
	$(CC) $(CCFLAGS)  "../misc.c" -c -o "misc.o"

stm32f10x_adc.o:	../stm32f10x_adc.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_adc.c" -c -o "stm32f10x_adc.o"

stm32f10x_it.o:	../stm32f10x_it.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_it.c" -c -o "stm32f10x_it.o"

usart.o:	../usart.c 
	$(CC) $(CCFLAGS)  "../usart.c" -c -o "usart.o"

stm32f10x_dma.o:	../stm32f10x_dma.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_dma.c" -c -o "stm32f10x_dma.o"

stm32f10x_tim.o:	../stm32f10x_tim.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_tim.c" -c -o "stm32f10x_tim.o"

stm32f10x_exti.o:	../stm32f10x_exti.c 
	$(CC) $(CCFLAGS)  "../stm32f10x_exti.c" -c -o "stm32f10x_exti.o"

DHT11.o:	../DHT11.c 
	$(CC) $(CCFLAGS)  "../DHT11.c" -c -o "DHT11.o"

sys.o:	../sys.c 
	$(CC) $(CCFLAGS)  "../sys.c" -c -o "sys.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf startup_stm32f10x_md.o
	rm -rf stm32f10x_gpio.o
	rm -rf stm32f10x_rcc.o
	rm -rf system_stm32f10x.o
	rm -rf stm32f10x_usart.o
	rm -rf core_cm3.o
	rm -rf main.o
	rm -rf misc.o
	rm -rf stm32f10x_adc.o
	rm -rf stm32f10x_it.o
	rm -rf usart.o
	rm -rf stm32f10x_dma.o
	rm -rf stm32f10x_tim.o
	rm -rf stm32f10x_exti.o
	rm -rf DHT11.o
	rm -rf sys.o
