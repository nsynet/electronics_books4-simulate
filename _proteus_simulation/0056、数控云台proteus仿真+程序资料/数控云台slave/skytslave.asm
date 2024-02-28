;CodeVisionAVR C Compiler V1.23.8c Standard
;(C) Copyright 1998-2003 HP InfoTech s.r.l.
;http://www.hpinfotech.ro
;e-mail:office@hpinfotech.ro

;Chip type           : ATmega8
;Program type        : Application
;Clock frequency     : 5.000000 MHz
;Memory model        : Small
;Optimize for        : Size
;(s)printf features  : int, width
;External SRAM size  : 0
;Data Stack size     : 256
;Promote char to int : No
;char is unsigned    : Yes
;8 bit enums         : Yes
;Enhanced core instructions    : On
;Automatic register allocation : On
;Use AVR Studio Terminal I/O   : No

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU GICR=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __se_bit=0x80
	.EQU __sm_mask=0x70
	.EQU __sm_adc_noise_red=0x10
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0x60
	.EQU __sm_ext_standby=0x70

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __CLRD1S
	CLR  R30
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+@1)
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+@1)
	LDI  R31,HIGH(@0+@1)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+@1)
	LDI  R31,HIGH(2*@0+@1)
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+@1)
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+@1)
	LDI  R27,HIGH(@0+@1)
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+@1
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	LDS  R22,@0+@1+2
	LDS  R23,@0+@1+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@2,@0+@1
	.ENDM

	.MACRO __GETWRMN
	LDS  R@2,@0+@1
	LDS  R@3,@0+@1+1
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+@1
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+@1
	LDS  R27,@0+@1+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+@1
	LDS  R27,@0+@1+1
	LDS  R24,@0+@1+2
	LDS  R25,@0+@1+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+@1,R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+@1,R30
	STS  @0+@1+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+@1,R30
	STS  @0+@1+1,R31
	STS  @0+@1+2,R22
	STS  @0+@1+3,R23
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+@1,R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+@1,R@2
	STS  @0+@1+1,R@3
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+@1
	LDS  R31,@0+@1+1
	ICALL
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	RCALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	RCALL __PUTDP1
	.ENDM

	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	CLR  R0
	ST   Z+,R0
	ST   Z,R0
	.ENDM

	.MACRO __CLRD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	CLR  R0
	ST   Z+,R0
	ST   Z+,R0
	ST   Z+,R0
	ST   Z,R0
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R@1
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOV  R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOV  R30,R0
	.ENDM

	.CSEG
	.ORG 0

	.INCLUDE "skytslave.vec"
	.INCLUDE "skytslave.inc"

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  GICR,R31
	OUT  GICR,R30
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	LDI  R31,0x10
	OUT  WDTCR,R31

;CLEAR R2-R14
	LDI  R24,13
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(0x400)
	LDI  R25,HIGH(0x400)
	LDI  R26,0x60
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
	SBIW R30,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R24,Z+
	LPM  R25,Z+
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;STACK POINTER INITIALIZATION
	LDI  R30,LOW(0x45F)
	OUT  SPL,R30
	LDI  R30,HIGH(0x45F)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(0x160)
	LDI  R29,HIGH(0x160)

	RJMP _main

	.ESEG
	.ORG 0
	.DB  0 ; FIRST EEPROM LOCATION NOT USED, SEE ATMEL ERRATA SHEETS

	.DSEG
	.ORG 0x160
;       1 /*********************************************
;       2 This program was produced by the
;       3 CodeWizardAVR V1.23.8c Standard
;       4 Automatic Program Generator
;       5 © Copyright 1998-2003 HP InfoTech s.r.l.
;       6 http://www.hpinfotech.ro
;       7 e-mail:office@hpinfotech.ro
;       8 
;       9 Project : SKYT
;      10 Version : 0.01
;      11 Date    : 2006-12-6
;      12 Author  : hlchen                          
;      13 Company :                                 
;      14 Comments: 
;      15 Êý¿ØÔÆÌ¨
;      16 
;      17 
;      18 Chip type           : ATmega8 
;      19 Program type        : Application
;      20 Clock frequency     : 3.690000 MHz
;      21 Memory model        : Small
;      22 External SRAM size  : 0
;      23 Data Stack size     : 256
;      24 *********************************************/
;      25 typedef unsigned char uchar; 
;      26 typedef unsigned int uint;
;      27 #include <mega8.h>  
;      28 #include <math.h>
;      29 #include "macro.h"
;      30 #define RXB8 1
;      31 #define TXB8 0
;      32 #define UPE 2
;      33 #define OVR 3
;      34 #define FE 4
;      35 #define UDRE 5
;      36 #define RXC 7
;      37 #define Light 5
;      38 #define FRAMING_ERROR (1<<FE)
;      39 #define PARITY_ERROR (1<<UPE)
;      40 #define DATA_OVERRUN (1<<OVR)
;      41 #define DATA_REGISTER_EMPTY (1<<UDRE)
;      42 #define RX_COMPLETE (1<<RXC)
;      43 
;      44 // USART Receiver buffer
;      45 #define RX_BUFFER_SIZE 8
;      46 char rx_buffer[RX_BUFFER_SIZE];
_rx_buffer:
	.BYTE 0x8
;      47 unsigned char rx_wr_index,rx_rd_index,rx_counter;
;      48 // This flag is set on USART Receiver buffer overflow
;      49 bit rx_buffer_overflow;
;      50 
;      51 // USART Receiver interrupt service routine
;      52 #pragma savereg-
;      53 interrupt [USART_RXC] void uart_rx_isr(void)
;      54 {

	.CSEG
_uart_rx_isr:
;      55 char status,data;
;      56 #asm
	RCALL __SAVELOCR2
;	status -> R16
;	data -> R17
;      57     push r26
    push r26
;      58     push r27
    push r27
;      59     push r30
    push r30
;      60     push r31
    push r31
;      61     in   r26,sreg
    in   r26,sreg
;      62     push r26
    push r26
;      63 #endasm

;      64 status=UCSRA;
	IN   R16,11
;      65 data=UDR;
	IN   R17,12
;      66 //printf("ok");
;      67 //if (data=="hello")
;      68 	
;      69 if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
	MOV  R30,R16
	ANDI R30,LOW(0x1C)
	BRNE _0x29
;      70    {
;      71    rx_buffer[rx_wr_index]=data;
	MOV  R26,R4
	CLR  R27
	SUBI R26,LOW(-_rx_buffer)
	SBCI R27,HIGH(-_rx_buffer)
	ST   X,R17
;      72    if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
	INC  R4
	LDI  R30,LOW(8)
	CP   R30,R4
	BRNE _0x2A
	CLR  R4
;      73    if (++rx_counter == RX_BUFFER_SIZE)
_0x2A:
	INC  R6
	LDI  R30,LOW(8)
	CP   R30,R6
	BRNE _0x2B
;      74       {
;      75       rx_counter=0;
	CLR  R6
;      76       rx_buffer_overflow=1;
	SET
	BLD  R2,0
;      77       };
_0x2B:
;      78    };
_0x29:
;      79 #asm
;      80     pop  r26
    pop  r26
;      81     out  sreg,r26
    out  sreg,r26
;      82     pop  r31
    pop  r31
;      83     pop  r30
    pop  r30
;      84     pop  r27
    pop  r27
;      85     pop  r26
    pop  r26
;      86 #endasm

;      87 }
	RCALL __LOADLOCR2P
	RETI
;      88 #pragma savereg+
;      89 
;      90 #ifndef _DEBUG_TERMINAL_IO_
;      91 // Get a character from the USART Receiver buffer
;      92 #define _ALTERNATE_GETCHAR_
;      93 #pragma used+
;      94 char getchar(void)
;      95 {
_getchar:
;      96 char data;
;      97 while (rx_counter==0);
	ST   -Y,R16
;	data -> R16
_0x2D:
	TST  R6
	BREQ _0x2D
;      98 data=rx_buffer[rx_rd_index];
	MOV  R30,R5
	CLR  R31
	SUBI R30,LOW(-_rx_buffer)
	SBCI R31,HIGH(-_rx_buffer)
	LD   R16,Z
;      99 if (++rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
	INC  R5
	LDI  R30,LOW(8)
	CP   R30,R5
	BRNE _0x30
	CLR  R5
;     100 #asm("cli")
_0x30:
	cli
;     101 --rx_counter;
	DEC  R6
;     102 #asm("sei")
	sei
;     103 return data;
	MOV  R30,R16
	LD   R16,Y+
	RET
;     104 }
;     105 #pragma used-
;     106 #endif
;     107 
;     108 // USART Transmitter buffer
;     109 #define TX_BUFFER_SIZE 8
;     110 char tx_buffer[TX_BUFFER_SIZE];

	.DSEG
_tx_buffer:
	.BYTE 0x8
;     111 unsigned char tx_wr_index,tx_rd_index,tx_counter;
;     112 
;     113 // USART Transmitter interrupt service routine
;     114 #pragma savereg-
;     115 interrupt [USART_TXC] void uart_tx_isr(void)
;     116 {

	.CSEG
_uart_tx_isr:
;     117 #asm
;     118     push r26
    push r26
;     119     push r27
    push r27
;     120     push r30
    push r30
;     121     push r31
    push r31
;     122     in   r26,sreg
    in   r26,sreg
;     123     push r26
    push r26
;     124 #endasm

;     125 if (tx_counter)
	TST  R9
	BREQ _0x32
;     126    {
;     127    --tx_counter;
	DEC  R9
;     128    UDR=tx_buffer[tx_rd_index];
	MOV  R30,R8
	CLR  R31
	SUBI R30,LOW(-_tx_buffer)
	SBCI R31,HIGH(-_tx_buffer)
	LD   R30,Z
	OUT  0xC,R30
;     129    if (++tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
	INC  R8
	LDI  R30,LOW(8)
	CP   R30,R8
	BRNE _0x33
	CLR  R8
;     130    };
_0x33:
_0x32:
;     131 #asm
;     132     pop  r26
    pop  r26
;     133     out  sreg,r26
    out  sreg,r26
;     134     pop  r31
    pop  r31
;     135     pop  r30
    pop  r30
;     136     pop  r27
    pop  r27
;     137     pop  r26
    pop  r26
;     138 #endasm

;     139 }
	RETI
;     140 #pragma savereg+
;     141 
;     142 #ifndef _DEBUG_TERMINAL_IO_
;     143 // Write a character to the USART Transmitter buffer
;     144 #define _ALTERNATE_PUTCHAR_
;     145 #pragma used+
;     146 void putchar(char c)
;     147 {
_putchar:
;     148 while (tx_counter == TX_BUFFER_SIZE);
_0x35:
	LDI  R30,LOW(8)
	CP   R30,R9
	BREQ _0x35
;     149 #asm("cli")
	cli
;     150 if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
	TST  R9
	BRNE _0x39
	SBIC 0xB,5
	RJMP _0x38
_0x39:
;     151    {
;     152    tx_buffer[tx_wr_index]=c;
	MOV  R26,R7
	CLR  R27
	SUBI R26,LOW(-_tx_buffer)
	SBCI R27,HIGH(-_tx_buffer)
	LD   R30,Y
	ST   X,R30
;     153    if (++tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
	INC  R7
	LDI  R30,LOW(8)
	CP   R30,R7
	BRNE _0x3B
	CLR  R7
;     154    ++tx_counter;
_0x3B:
	INC  R9
;     155    }
;     156 else UDR=c;
	RJMP _0x3C
_0x38:
	LD   R30,Y
	OUT  0xC,R30
_0x3C:
;     157 #asm("sei")
	sei
;     158 }
	ADIW R28,1
	RET
;     159 #pragma used-
;     160 #endif
;     161 // Standard Input/Output functions
;     162 #include <stdio.h>  
;     163 uchar ucInputValue;
;     164 uint uiLastADValue[3];

	.DSEG
_uiLastADValue:
	.BYTE 0x6
;     165 uchar ucInputParam0; 
;     166 uchar ucChannelN; 
;     167 uchar uc_ReceiveSta;
;     168 bit bInputChange,bMotorSpeed,bLight;         
;     169 void inputdeal(void); 
;     170 void Communication(void);
;     171 void TransmitEnable(void);
;     172 void ReceiveEnable(void);
;     173 #define HighSpeed 0x33
;     174 #define SlowSpeed 0x99
;     175 #define ADC_VREF_TYPE 0x00 
;     176 #define RE 2
;     177 #define DE 3
;     178 // ADC interrupt service routine
;     179 interrupt [TIM0_OVF] void timer0_ovf_isr(void)
;     180 {

	.CSEG
_timer0_ovf_isr:
	RCALL __SAVEISR
;     181 // Place your code here 
;     182 TCNT0=0xf0;
	RCALL SUBOPT_0x0
;     183 }
	RCALL __LOADISR
	RETI
;     184 interrupt [ADC_INT] void adc_isr(void)
;     185 {
_adc_isr:
	RCALL __SAVEISR
;     186 uint adc_data;
;     187 // Read the AD conversion result
;     188 adc_data=ADCW;
	RCALL __SAVELOCR2
;	adc_data -> R16,R17
	__INWR 16,17,4
;     189 
;     190 // Place your code here 
;     191 switch (ucChannelN)
	MOV  R30,R12
;     192 {
;     193 case 0:
	CPI  R30,0
	BRNE _0x4F
;     194  	       	if (uiLastADValue[0]!=adc_data)
	LDS  R26,_uiLastADValue
	LDS  R27,_uiLastADValue+1
	CP   R16,R26
	CPC  R17,R27
	BREQ _0x50
;     195  		{
;     196  		uiLastADValue[0]=adc_data;
	__PUTWMRN _uiLastADValue,0,16,17
;     197  		ucInputParam0=uiLastADValue[0]*24/1024;
	LDI  R30,LOW(24)
	LDI  R31,HIGH(24)
	RCALL SUBOPT_0x1
;     198 		//ucInputParam0 = tmp/100;
;     199 		//ucInputParam1 = (tmp%100)/10;
;     200 		//ucInputParam2 = (tmp%100)%10;
;     201 		bInputChange=1;
	BLD  R2,1
;     202 		ucInputValue=0x01;
	LDI  R30,LOW(1)
	MOV  R10,R30
;     203 	       
;     204 		} 
;     205 		ADMUX=0x01;
_0x50:
	LDI  R30,LOW(1)
	OUT  0x7,R30
;     206 		break;  
	RJMP _0x4E
;     207 case 1: 
_0x4F:
	CPI  R30,LOW(0x1)
	BRNE _0x51
;     208         	if (uiLastADValue[1]!=adc_data)
	__GETW2MN _uiLastADValue,2
	CP   R16,R26
	CPC  R17,R27
	BREQ _0x52
;     209  		{
;     210  		uiLastADValue[1]=adc_data;
	__PUTWMRN _uiLastADValue,2,16,17
;     211  		ucInputParam0=uiLastADValue[1]*12/1024;
	__GETW1MN _uiLastADValue,2
	LDI  R26,LOW(12)
	LDI  R27,HIGH(12)
	RCALL SUBOPT_0x1
;     212 		//ucInputParam0 = tmp/100;
;     213 		//ucInputParam1 = (tmp%100)/10;
;     214 		//ucInputParam2 = (tmp%100)%10;
;     215 		bInputChange=1;
	BLD  R2,1
;     216 		ucInputValue=0x02; 
	LDI  R30,LOW(2)
	MOV  R10,R30
;     217 	     
;     218 		} 
;     219 		ADMUX=0x02;
_0x52:
	LDI  R30,LOW(2)
	OUT  0x7,R30
;     220 		break;  
	RJMP _0x4E
;     221 case 2:
_0x51:
	CPI  R30,LOW(0x2)
	BREQ PC+2
	RJMP _0x63
;     222 		if (uiLastADValue[2]!=adc_data)
	__GETW2MN _uiLastADValue,4
	CP   R16,R26
	CPC  R17,R27
	BRNE PC+2
	RJMP _0x54
;     223  		{
;     224  		uiLastADValue[2]=adc_data;
	__PUTWMRN _uiLastADValue,4,16,17
;     225  		//ucInputParam0=uiLastADValue[2]*6/1024; 
;     226  	       	if (abs(uiLastADValue[2]-1023)<100)
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(1023)
	SBCI R31,HIGH(1023)
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0x64)
	LDI  R26,HIGH(0x64)
	CPC  R31,R26
	BRSH _0x55
;     227  	       		 ucInputValue=3;
	LDI  R30,LOW(3)
	MOV  R10,R30
;     228    	        else if (abs(uiLastADValue[2]-465)<50)
	RJMP _0x56
_0x55:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(465)
	SBCI R31,HIGH(465)
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0x32)
	LDI  R26,HIGH(0x32)
	CPC  R31,R26
	BRSH _0x57
;     229  	       		 ucInputValue=4;
	LDI  R30,LOW(4)
	MOV  R10,R30
;     230        		else if (abs(uiLastADValue[2]-292)<25)
	RJMP _0x58
_0x57:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(292)
	SBCI R31,HIGH(292)
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0x19)
	LDI  R26,HIGH(0x19)
	CPC  R31,R26
	BRSH _0x59
;     231  	       		 ucInputValue=5;	 
	LDI  R30,LOW(5)
	MOV  R10,R30
;     232  	       	else if (abs(uiLastADValue[2]-204)<25)
	RJMP _0x5A
_0x59:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(204)
	SBCI R31,HIGH(204)
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0x19)
	LDI  R26,HIGH(0x19)
	CPC  R31,R26
	BRSH _0x5B
;     233  	       		 ucInputValue=6;
	LDI  R30,LOW(6)
	MOV  R10,R30
;     234  	       	else if (abs(uiLastADValue[2]-146)<12)
	RJMP _0x5C
_0x5B:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(146)
	SBCI R31,HIGH(146)
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0xC)
	LDI  R26,HIGH(0xC)
	CPC  R31,R26
	BRSH _0x5D
;     235  	       		 ucInputValue=7;
	LDI  R30,LOW(7)
	MOV  R10,R30
;     236  	       	else if (abs(uiLastADValue[2]-93)<12) 
	RJMP _0x5E
_0x5D:
	__GETW1MN _uiLastADValue,4
	SUBI R30,LOW(93)
	SBCI R31,HIGH(93)
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0xC)
	LDI  R26,HIGH(0xC)
	CPC  R31,R26
	BRSH _0x5F
;     237  	       	         ucInputValue=8;
	LDI  R30,LOW(8)
	MOV  R10,R30
;     238  	       	else if (abs(uiLastADValue[2])<6)
	RJMP _0x60
_0x5F:
	__GETW1MN _uiLastADValue,4
	RCALL SUBOPT_0x2
	CPI  R30,LOW(0x6)
	LDI  R26,HIGH(0x6)
	CPC  R31,R26
	BRSH _0x61
;     239  	       		 ucInputValue=9;
	LDI  R30,LOW(9)
	MOV  R10,R30
;     240  	       	else break;
	RJMP _0x62
_0x61:
	RJMP _0x4E
_0x62:
_0x60:
_0x5E:
_0x5C:
_0x5A:
_0x58:
_0x56:
;     241  	       //	else if (abs(uiLastADValue[2]-512
;     242 		//ucInputParam0 = tmp/100;
;     243 		//ucInputParam1 = (tmp%100)/10;
;     244 		//ucInputParam2 = (tmp%100)%10;
;     245 		bInputChange=1;
	SET
	BLD  R2,1
;     246 //		ucInputValue=ucInputParam0+2; 
;     247 	     
;     248 		} 
;     249 		ADMUX=0x00;
_0x54:
	RCALL SUBOPT_0x3
;     250 		break;              
;     251 default:
_0x63:
;     252 		break;
;     253 }   
_0x4E:
;     254 ADCSRA|=0x40;
	SBI  0x6,6
;     255 //ADMUX^=0x01;   
;     256 if (ucChannelN++==3)    ucChannelN=0;
	MOV  R30,R12
	INC  R12
	CPI  R30,LOW(0x3)
	BRNE _0x64
	CLR  R12
;     257 
;     258 }
_0x64:
	RCALL __LOADLOCR2P
	RCALL __LOADISR
	RETI
;     259 
;     260 // Declare your global variables here
;     261 
;     262 void main(void)
;     263 {
_main:
;     264 // Declare your local variables here
;     265  
;     266  
;     267 // Input/Output Ports initialization
;     268 // Port B initialization
;     269 // Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out Func7=Out 
;     270 // State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 State7=0 
;     271 PORTB=0x00;
	CLR  R30
	OUT  0x18,R30
;     272 DDRB=0xFF;
	LDI  R30,LOW(255)
	OUT  0x17,R30
;     273 
;     274 // Port C initialization
;     275 // Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out 
;     276 // State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 
;     277 PORTC=0x00;
	CLR  R30
	OUT  0x15,R30
;     278 DDRC=0x70;
	LDI  R30,LOW(112)
	OUT  0x14,R30
;     279 
;     280 // Port D initialization
;     281 // Func0=Out Func1=Out Func2=Out Func3=Out Func4=Out Func5=Out Func6=Out Func7=Out 
;     282 // State0=0 State1=0 State2=0 State3=0 State4=0 State5=0 State6=0 State7=0 
;     283 PORTD=0x00;
	CLR  R30
	OUT  0x12,R30
;     284 DDRD=0xff;
	LDI  R30,LOW(255)
	OUT  0x11,R30
;     285 
;     286 // Timer/Counter 0 initialization
;     287 // Clock source: System Clock
;     288 // Clock value: 3690.000 kHz
;     289 TCCR0=0x03;
	LDI  R30,LOW(3)
	OUT  0x33,R30
;     290 TCNT0=0xf0;
	RCALL SUBOPT_0x0
;     291 
;     292 
;     293 // Timer/Counter 1 initialization
;     294 // Clock source: System Clock
;     295 // Clock value: Timer 1 Stopped
;     296 // Mode: Normal top=FFFFh
;     297 // OC1A output: Discon.
;     298 // OC1B output: Discon.
;     299 // Noise Canceler: Off
;     300 // Input Capture on Falling Edge
;     301 //Ä£Ê½1(¼ÆÊýÆ÷ÉÏÏÞÖµ=0xff) PWMÆµÂÊ = ÏµÍ³Ê±ÖÓÆµÂÊ/£¨·ÖÆµÏµÊý*2*¼ÆÊýÆ÷ÉÏÏÞÖµ£©£© 
;     302 TCCR1A=0xF1;
	LDI  R30,LOW(241)
	OUT  0x2F,R30
;     303 //COM1A1,COM1A0,COM1B1,COM1B0=1±íÊ¾ÉýÐò¼ÇÊýÊ±±È½ÏÆ¥Åä½«ÖÃÎ»OC1A/OC1B£¬½µÐò¼ÇÊýÊ±±È½ÏÆ¥Åä½«ÇåÁãOC1A/OC1B
;     304 //¼´OCR1AL<tcnt1<TOP(0xff)Ê± OC1AÎª¸ß tcnt1<OCR1ALÊ±OC1AÎªµÍ
;     305 //WGM11=0 WGM10=1
;     306 TCCR1B=0x03;
	LDI  R30,LOW(3)
	OUT  0x2E,R30
;     307 //WGM13=0 WGM12=0 CS12=1 CS11=0 CS10=0 ·ÖÆµÏµÊý=256
;     308 TCNT1H=0x00;
	CLR  R30
	OUT  0x2D,R30
;     309 TCNT1L=0x00;
	OUT  0x2C,R30
;     310 OCR1AH=0x00;
	OUT  0x2B,R30
;     311 OCR1AL=SlowSpeed; //Õ¼¿Õ±È=40% (0xff-0x99)/0xff=0.4
	LDI  R30,LOW(153)
	OUT  0x2A,R30
;     312 		//Õ¼¿Õ±È=80% 0x33
;     313 OCR1BH=0x00;
	CLR  R30
	OUT  0x29,R30
;     314 OCR1BL=0x30;
	LDI  R30,LOW(48)
	OUT  0x28,R30
;     315 
;     316 // Timer/Counter 2 initialization
;     317 // Clock source: System Clock
;     318 // Clock value: Timer 2 Stopped
;     319 // Mode: Normal top=FFh
;     320 // OC2 output: Disconnected
;     321 ASSR=0x00;
	CLR  R30
	OUT  0x22,R30
;     322 TCCR2=0x00;
	OUT  0x25,R30
;     323 TCNT2=0x00;
	OUT  0x24,R30
;     324 OCR2=0x00;
	OUT  0x23,R30
;     325 
;     326 // External Interrupt(s) initialization
;     327 // INT0: Off
;     328 // INT1: Off
;     329 GICR|=0x00;
	IN   R30,0x3B
	OUT  0x3B,R30
;     330 MCUCR=0x00;
	CLR  R30
	OUT  0x35,R30
;     331 
;     332 // Timer(s)/Counter(s) Interrupt(s) initialization
;     333 TIMSK=0X01;
	LDI  R30,LOW(1)
	OUT  0x39,R30
;     334 
;     335 // USART initialization
;     336 // Communication Parameters: 8 Data, 1 Stop, No Parity
;     337 // USART Receiver: On
;     338 // USART Transmitter: On
;     339 // USART Mode: Asynchronous
;     340 // USART Baud rate: 1200
;     341 
;     342 
;     343 UCSRA=0x00;
	CLR  R30
	OUT  0xB,R30
;     344 UCSRB=0xD8;
	LDI  R30,LOW(216)
	OUT  0xA,R30
;     345 UCSRC=0x86;
	LDI  R30,LOW(134)
	OUT  0x20,R30
;     346 UBRRH=0x00;
	CLR  R30
	OUT  0x20,R30
;     347 UBRRL=0x33;
	LDI  R30,LOW(51)
	OUT  0x9,R30
;     348 // Analog Comparator initialization
;     349 // Analog Comparator: Off
;     350 // Analog Comparator Input Capture by Timer/Counter 1: Off
;     351 // Analog Comparator Output: Off
;     352 ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x8,R30
;     353 SFIOR=0x00;
	CLR  R30
	OUT  0x30,R30
;     354 
;     355 // ADC initialization
;     356 // ADC Clock frequency: 115.313 kHz
;     357 // ADC Voltage Reference: AREF pin
;     358 // ADC High Speed Mode: Off
;     359 // ADC Auto Trigger Source: Timer0 Overflow
;     360 ADMUX=0x00;
	RCALL SUBOPT_0x3
;     361 ADCSRA=0xCD;
	LDI  R30,LOW(205)
	OUT  0x6,R30
;     362 //SFIOR&=0x0F;
;     363 //SFIOR|=0x80;
;     364 
;     365 // Global enable interrupts   
;     366 
;     367 
;     368 
;     369 
;     370 
;     371 #asm("sei") 
	sei
;     372 ReceiveEnable();
	RCALL _ReceiveEnable
;     373 //printf("hellooooo"); 
;     374 while (1)
_0x66:
;     375       {
;     376       // Place your code here
;     377       //inputdeal();
;     378       Communication();
	RCALL _Communication
;     379       //if (UCSRA&0x40) ReceiveEnable();
;     380       };
	RJMP _0x66
;     381 }
_0x69:
	RJMP _0x69
;     382 void TransmitEnable(void)
;     383 {
_TransmitEnable:
;     384 PORTD|=Bit(RE);
	SBI  0x12,2
;     385 PORTD|=Bit(DE);
	SBI  0x12,3
;     386 }
	RET
;     387 void ReceiveEnable(void)
;     388 {
_ReceiveEnable:
;     389 PORTD&=Bit(RE);
	IN   R30,0x12
	ANDI R30,LOW(0x4)
	OUT  0x12,R30
;     390 PORTD&=Bit(DE);
	IN   R30,0x12
	ANDI R30,LOW(0x8)
	OUT  0x12,R30
;     391 } 
	RET
;     392 void TransmitCommand(void)
;     393 {
_TransmitCommand:
;     394 
;     395 }  
	RET
;     396 void Communication(void)
;     397 {
_Communication:
;     398       uint i;
;     399       switch (uc_ReceiveSta)
	RCALL __SAVELOCR2
;	i -> R16,R17
	MOV  R30,R13
;     400       {
;     401       case 0:
	CPI  R30,0
	BRNE _0x71
;     402       		if (getchar()=='R')
	RCALL _getchar
	CPI  R30,LOW(0x52)
	BRNE _0x72
;     403 	       		uc_ReceiveSta++;
	INC  R13
;     404 	        else if (getchar()=='O')
	RJMP _0x73
_0x72:
	RCALL _getchar
	CPI  R30,LOW(0x4F)
	BRNE _0x74
;     405 	        	uc_ReceiveSta++;
	INC  R13
;     406 		break;
_0x74:
_0x73:
	RJMP _0x70
;     407       case 1:
_0x71:
	CPI  R30,LOW(0x1)
	BRNE _0x75
;     408       		if (getchar()=='e')
	RCALL _getchar
	CPI  R30,LOW(0x65)
	BRNE _0x76
;     409 			uc_ReceiveSta++;
	INC  R13
;     410 		else if (getchar()=='k')
	RJMP _0x77
_0x76:
	RCALL _getchar
	CPI  R30,LOW(0x6B)
	BRNE _0x78
;     411 			{
;     412 			uc_ReceiveSta=0;
	CLR  R13
;     413 			TransmitCommand();
	RCALL _TransmitCommand
;     414 			}
;     415 		else 
	RJMP _0x79
_0x78:
;     416 			uc_ReceiveSta=0;
	CLR  R13
_0x79:
_0x77:
;     417 		break; 
	RJMP _0x70
;     418       case 2:
_0x75:
	CPI  R30,LOW(0x2)
	BRNE _0x7A
;     419       		if (getchar()=='a')
	RCALL _getchar
	CPI  R30,LOW(0x61)
	BRNE _0x7B
;     420 			uc_ReceiveSta++;
	INC  R13
;     421 		else
	RJMP _0x7C
_0x7B:
;     422 	       		uc_ReceiveSta=0;
	CLR  R13
_0x7C:
;     423 		break;
	RJMP _0x70
;     424       case 3:
_0x7A:
	CPI  R30,LOW(0x3)
	BRNE _0x7D
;     425       		if (getchar()=='d')
	RCALL _getchar
	CPI  R30,LOW(0x64)
	BRNE _0x7E
;     426 			uc_ReceiveSta++;
	INC  R13
;     427 		else
	RJMP _0x7F
_0x7E:
;     428 			uc_ReceiveSta=0;
	CLR  R13
_0x7F:
;     429        		break;  
	RJMP _0x70
;     430       case 4:
_0x7D:
	CPI  R30,LOW(0x4)
	BRNE _0x70
;     431       		uc_ReceiveSta=0;
	CLR  R13
;     432 	      	if (getchar()=='y')      
	RCALL _getchar
	CPI  R30,LOW(0x79)
	BRNE _0x81
;     433 	      		{
;     434 	      		
;     435 	      		TransmitEnable(); 
	RCALL _TransmitEnable
;     436 	      		for (i=0;i<5000;i++);
	__GETWRN 16,17,0
_0x83:
	__CPWRN 16,17,5000
	BRSH _0x84
	__ADDWRN 16,17,1
	RJMP _0x83
_0x84:
;     437 			printf("ok");
	__POINTW1FN _109,0
	ST   -Y,R31
	ST   -Y,R30
	LDI  R24,0
	RCALL _printf
	ADIW R28,2
;     438 		        
;     439 			}
;     440 		break;
_0x81:
;     441       }	                     
_0x70:
;     442       
;     443      
;     444 }
	RCALL __LOADLOCR2P
	RET
;     445 void inputdeal(void)
;     446 {
;     447 	if (!bInputChange) return;
;     448 	bInputChange=0;
;     449 	switch (ucInputValue)
;     450 	{
;     451 	case 0x01:
;     452 		//printf("%bu,%bu,%bu\n",ucInputParam0,ucInputParam1,ucInputParam2);
;     453 	       //	PaintDegree(ucInputParam0,0);   
;     454 	
;     455 		break;
;     456 	case 0x02:
;     457 	       //	PaintDegree(ucInputParam0,1);
;     458 	
;     459 		break; 
;     460 	case 0x03://key1
;     461 	      	if (!bLight) PORTB|=Bit(Light); 
;     462 	      	else PORTB&=~Bit(Light);
;     463 	      	bLight=!bLight;
;     464 		PORTD|=0x04;
;     465 		break;
;     466 	case 0x04://key2
;     467 	       //	PORTD&=0xc3;
;     468 		PORTD|=0x08;   
;     469 	      //	if (bMotorSpeed)       {Show_Slow();OCR1AL=SlowSpeed;}
;     470 	     //	else   {Show_Quick();OCR1AL=HighSpeed;}
;     471 		bMotorSpeed=!bMotorSpeed;
;     472 		
;     473 		break;  
;     474 	case 0x05://key3
;     475 	       //	PORTD&=0xc3;
;     476 		PORTD|=0x0c;
;     477 		break;
;     478 	case 0x06://key4
;     479 	      //	PORTD&=0xc3;
;     480 		PORTD|=0x10;
;     481 		break;
;     482 	case 0x07://key5
;     483 	       //	PORTD&=0xc3;
;     484 		PORTD|=0x14;
;     485 		break;
;     486 	case 0x08://key6  
;     487 	        //PORTD&=0xc3;
;     488 		PORTD|=0x18;
;     489 		break;
;     490 	case 0x09://keyrelease 
;     491 		PORTD&=0xc3;    
;     492 		break;
;     493 	default:
;     494 		break;
;     495 	}
;     496 }
__put_G3:
	put:
	RCALL SUBOPT_0x4
	SBIW R30,0
	BREQ _0xCA
	RCALL SUBOPT_0x4
	ADIW R30,1
	RCALL __PUTWP1
	SBIW R30,1
	MOVW R26,R30
	LDD  R30,Y+2
	ST   X,R30
	RJMP _0xCB
_0xCA:
	LDD  R30,Y+2
	ST   -Y,R30
	RCALL _putchar
_0xCB:
	ADIW R28,3
	RET
__print_G3:
	SBIW R28,6
	RCALL __SAVELOCR6
	LDI  R16,0
_0xCD:
	LDD  R30,Y+16
	LDD  R31,Y+16+1
	ADIW R30,1
	STD  Y+16,R30
	STD  Y+16+1,R31
	SBIW R30,1
	LPM  R30,Z
	MOV  R19,R30
	CPI  R30,0
	BRNE PC+2
	RJMP _0xCF
	MOV  R30,R16
	CPI  R30,0
	BRNE _0xD3
	CPI  R19,37
	BRNE _0xD4
	LDI  R16,LOW(1)
	RJMP _0xD5
_0xD4:
	RCALL SUBOPT_0x5
_0xD5:
	RJMP _0xD2
_0xD3:
	CPI  R30,LOW(0x1)
	BRNE _0xD6
	CPI  R19,37
	BRNE _0xD7
	RCALL SUBOPT_0x5
	LDI  R16,LOW(0)
	RJMP _0xD2
_0xD7:
	LDI  R16,LOW(2)
	LDI  R21,LOW(0)
	LDI  R17,LOW(0)
	CPI  R19,45
	BRNE _0xD8
	LDI  R17,LOW(1)
	RJMP _0xD2
_0xD8:
	CPI  R19,43
	BRNE _0xD9
	LDI  R21,LOW(43)
	RJMP _0xD2
_0xD9:
	CPI  R19,32
	BRNE _0xDA
	LDI  R21,LOW(32)
	RJMP _0xD2
_0xDA:
	RJMP _0xDB
_0xD6:
	CPI  R30,LOW(0x2)
	BRNE _0xDC
_0xDB:
	LDI  R20,LOW(0)
	LDI  R16,LOW(3)
	CPI  R19,48
	BRNE _0xDD
	ORI  R17,LOW(128)
	RJMP _0xD2
_0xDD:
	RJMP _0xDE
_0xDC:
	CPI  R30,LOW(0x3)
	BREQ PC+2
	RJMP _0xD2
_0xDE:
	CPI  R19,48
	BRLO _0xE1
	CPI  R19,58
	BRLO _0xE2
_0xE1:
	RJMP _0xE0
_0xE2:
	MOV  R26,R20
	LDI  R30,LOW(10)
	MUL  R30,R26
	MOV  R30,R0
	MOV  R20,R30
	MOV  R30,R19
	SUBI R30,LOW(48)
	ADD  R20,R30
	RJMP _0xD2
_0xE0:
	MOV  R30,R19
	CPI  R30,LOW(0x63)
	BRNE _0xE6
	RCALL SUBOPT_0x6
	LD   R30,X
	RCALL SUBOPT_0x7
	RJMP _0xE7
_0xE6:
	CPI  R30,LOW(0x73)
	BRNE _0xE9
	RCALL SUBOPT_0x6
	RCALL SUBOPT_0x8
	RCALL _strlen
	MOV  R16,R30
	RJMP _0xEA
_0xE9:
	CPI  R30,LOW(0x70)
	BRNE _0xEC
	RCALL SUBOPT_0x6
	RCALL SUBOPT_0x8
	RCALL _strlenf
	MOV  R16,R30
	ORI  R17,LOW(8)
_0xEA:
	ORI  R17,LOW(2)
	ANDI R17,LOW(127)
	LDI  R18,LOW(0)
	RJMP _0xED
_0xEC:
	CPI  R30,LOW(0x64)
	BREQ _0xF0
	CPI  R30,LOW(0x69)
	BRNE _0xF1
_0xF0:
	ORI  R17,LOW(4)
	RJMP _0xF2
_0xF1:
	CPI  R30,LOW(0x75)
	BRNE _0xF3
_0xF2:
	LDI  R30,LOW(_tbl10_G3*2)
	LDI  R31,HIGH(_tbl10_G3*2)
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDI  R16,LOW(5)
	RJMP _0xF4
_0xF3:
	CPI  R30,LOW(0x58)
	BRNE _0xF6
	ORI  R17,LOW(8)
	RJMP _0xF7
_0xF6:
	CPI  R30,LOW(0x78)
	BREQ PC+2
	RJMP _0x125
_0xF7:
	LDI  R30,LOW(_tbl16_G3*2)
	LDI  R31,HIGH(_tbl16_G3*2)
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDI  R16,LOW(4)
_0xF4:
	SBRS R17,2
	RJMP _0xF9
	RCALL SUBOPT_0x6
	RCALL SUBOPT_0x9
	LDD  R26,Y+10
	LDD  R27,Y+10+1
	SBIW R26,0
	BRGE _0xFA
	LDD  R30,Y+10
	LDD  R31,Y+10+1
	RCALL __ANEGW1
	STD  Y+10,R30
	STD  Y+10+1,R31
	LDI  R21,LOW(45)
_0xFA:
	CPI  R21,0
	BREQ _0xFB
	SUBI R16,-LOW(1)
	RJMP _0xFC
_0xFB:
	ANDI R17,LOW(251)
_0xFC:
	RJMP _0xFD
_0xF9:
	RCALL SUBOPT_0x6
	RCALL SUBOPT_0x9
_0xFD:
_0xED:
	SBRC R17,0
	RJMP _0xFE
_0xFF:
	CP   R16,R20
	BRSH _0x101
	SBRS R17,7
	RJMP _0x102
	SBRS R17,2
	RJMP _0x103
	ANDI R17,LOW(251)
	MOV  R19,R21
	SUBI R16,LOW(1)
	RJMP _0x104
_0x103:
	LDI  R19,LOW(48)
_0x104:
	RJMP _0x105
_0x102:
	LDI  R19,LOW(32)
_0x105:
	RCALL SUBOPT_0x5
	SUBI R20,LOW(1)
	RJMP _0xFF
_0x101:
_0xFE:
	MOV  R18,R16
	SBRS R17,1
	RJMP _0x106
_0x107:
	CPI  R18,0
	BREQ _0x109
	SBRS R17,3
	RJMP _0x10A
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	ADIW R30,1
	STD  Y+6,R30
	STD  Y+6+1,R31
	SBIW R30,1
	LPM  R30,Z
	RJMP _0x127
_0x10A:
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LD   R30,X+
	STD  Y+6,R26
	STD  Y+6+1,R27
_0x127:
	ST   -Y,R30
	RCALL SUBOPT_0xA
	CPI  R20,0
	BREQ _0x10C
	SUBI R20,LOW(1)
_0x10C:
	SUBI R18,LOW(1)
	RJMP _0x107
_0x109:
	RJMP _0x10D
_0x106:
_0x10F:
	LDI  R19,LOW(48)
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	ADIW R30,2
	STD  Y+6,R30
	STD  Y+6+1,R31
	SBIW R30,2
	RCALL __GETW1PF
	STD  Y+8,R30
	STD  Y+8+1,R31
                                      ldd  r26,y+10  ;R26,R27=n
                                      ldd  r27,y+11
                                  calc_digit:
                                      cp   r26,r30
                                      cpc  r27,r31
                                      brlo calc_digit_done
	SUBI R19,-LOW(1)
	                                  sub  r26,r30
	                                  sbc  r27,r31
	                                  brne calc_digit
                                  calc_digit_done:
                                      std  Y+10,r26 ;n=R26,R27
                                      std  y+11,r27
	LDI  R30,LOW(57)
	CP   R30,R19
	BRSH _0x111
	SBRS R17,3
	RJMP _0x112
	SUBI R19,-LOW(7)
	RJMP _0x113
_0x112:
	SUBI R19,-LOW(39)
_0x113:
_0x111:
	SBRC R17,4
	RJMP _0x115
	LDI  R30,LOW(48)
	CP   R30,R19
	BRLO _0x117
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	CPI  R26,LOW(0x1)
	LDI  R30,HIGH(0x1)
	CPC  R27,R30
	BRNE _0x116
_0x117:
	ORI  R17,LOW(16)
	RJMP _0x119
_0x116:
	CP   R20,R18
	BRLO _0x11B
	SBRS R17,0
	RJMP _0x11C
_0x11B:
	RJMP _0x11A
_0x11C:
	LDI  R19,LOW(32)
	SBRS R17,7
	RJMP _0x11D
	LDI  R19,LOW(48)
	ORI  R17,LOW(16)
_0x119:
	SBRS R17,2
	RJMP _0x11E
	ANDI R17,LOW(251)
	ST   -Y,R21
	RCALL SUBOPT_0xA
	CPI  R20,0
	BREQ _0x11F
	SUBI R20,LOW(1)
_0x11F:
_0x11E:
_0x11D:
_0x115:
	RCALL SUBOPT_0x5
	CPI  R20,0
	BREQ _0x120
	SUBI R20,LOW(1)
_0x120:
_0x11A:
	SUBI R18,LOW(1)
	LDD  R26,Y+8
	LDD  R27,Y+8+1
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	CP   R30,R26
	CPC  R31,R27
	BRSH _0x110
	RJMP _0x10F
_0x110:
_0x10D:
	SBRS R17,0
	RJMP _0x121
_0x122:
	CPI  R20,0
	BREQ _0x124
	SUBI R20,LOW(1)
	LDI  R30,LOW(32)
	RCALL SUBOPT_0x7
	RJMP _0x122
_0x124:
_0x121:
_0x125:
_0xE7:
	LDI  R16,LOW(0)
_0xD2:
	RJMP _0xCD
_0xCF:
	RCALL __LOADLOCR6
	ADIW R28,18
	RET
_printf:
	MOV  R15,R24
	SBIW R28,4
	MOVW R26,R28
	RCALL __ADDW2R15
	STD  Y+2,R26
	STD  Y+2+1,R27
	CLR  R30
	STD  Y+0,R30
	STD  Y+0+1,R30
	MOVW R26,R28
	ADIW R26,4
	RCALL __ADDW2R15
	RCALL __GETW1P
	ST   -Y,R31
	ST   -Y,R30
	LDD  R30,Y+4
	LDD  R31,Y+4+1
	ST   -Y,R31
	ST   -Y,R30
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	RCALL __print_G3
	ADIW R28,4
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x0:
	LDI  R30,LOW(240)
	OUT  0x32,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x1:
	RCALL __MULW12U
	RCALL __LSRW2
	MOV  R30,R31
	CLR  R31
	MOV  R11,R30
	SET
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES
SUBOPT_0x2:
	ST   -Y,R31
	ST   -Y,R30
	RJMP _abs

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x3:
	CLR  R30
	OUT  0x7,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x4:
	LD   R26,Y
	LDD  R27,Y+1
	RCALL __GETW1P
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES
SUBOPT_0x5:
	ST   -Y,R19
	LDD  R30,Y+13
	LDD  R31,Y+13+1
	ST   -Y,R31
	ST   -Y,R30
	RJMP __put_G3

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES
SUBOPT_0x6:
	LDD  R26,Y+14
	LDD  R27,Y+14+1
	SBIW R26,4
	STD  Y+14,R26
	STD  Y+14+1,R27
	ADIW R26,4
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x7:
	ST   -Y,R30
	LDD  R30,Y+13
	LDD  R31,Y+13+1
	ST   -Y,R31
	ST   -Y,R30
	RJMP __put_G3

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x8:
	RCALL __GETD1P
	STD  Y+6,R30
	STD  Y+6+1,R31
	ST   -Y,R31
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0x9:
	RCALL __GETW1P
	STD  Y+10,R30
	STD  Y+10+1,R31
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES
SUBOPT_0xA:
	LDD  R30,Y+13
	LDD  R31,Y+13+1
	ST   -Y,R31
	ST   -Y,R30
	RJMP __put_G3

_abs:
	ld   r30,y+
	ld   r31,y+
	sbiw r30,0
	brpl __abs0
	com  r30
	com  r31
	adiw r30,1
__abs0:
	ret

_strlen:
	ld   r26,y+
	ld   r27,y+
	clr  r30
	clr  r31
__strlen0:
	ld   r22,x+
	tst  r22
	breq __strlen1
	adiw r30,1
	rjmp __strlen0
__strlen1:
	ret

_strlenf:
	clr  r26
	clr  r27
	ld   r30,y+
	ld   r31,y+
__strlenf0:
	lpm  r0,z+
	tst  r0
	breq __strlenf1
	adiw r26,1
	rjmp __strlenf0
__strlenf1:
	movw r30,r26
	ret

__SAVEISR:
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R0,SREG
	ST   -Y,R0
	RET

__LOADISR:
	LD   R0,Y+
	OUT  SREG,R0
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RET

__ADDW2R15:
	CLR  R0
	ADD  R26,R15
	ADC  R27,R0
	RET

__ANEGW1:
	COM  R30
	COM  R31
	ADIW R30,1
	RET

__LSRW2:
	LSR  R31
	ROR  R30
	LSR  R31
	ROR  R30
	RET

__MULW12U:
	MUL  R31,R26
	MOV  R31,R0
	MUL  R30,R27
	ADD  R31,R0
	MUL  R30,R26
	MOV  R30,R0
	ADD  R31,R1
	RET

__GETW1P:
	LD   R30,X+
	LD   R31,X
	SBIW R26,1
	RET

__GETD1P:
	LD   R30,X+
	LD   R31,X+
	LD   R22,X+
	LD   R23,X
	SBIW R26,3
	RET

__PUTWP1:
	ST   X+,R30
	ST   X,R31
	RET

__GETW1PF:
	LPM  R0,Z+
	LPM  R31,Z
	MOV  R30,R0
	RET

__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

__LOADLOCR2P:
	LD   R16,Y+
	LD   R17,Y+
	RET

