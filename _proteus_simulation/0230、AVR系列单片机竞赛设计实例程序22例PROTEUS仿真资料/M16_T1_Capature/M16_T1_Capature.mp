NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   001B =     27. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       006F  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0070   02DA =    730. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0038  __start
       0038  __text_start
       0058  _exit
       0059  _DelayMs
       006C  _Pre_Display
       0083  _Display
       00A2  _HZ
       00E1  _Init_IO
       00EA  _Init_Timer1
       00F5  _main
       0157  mod16u
       0159  div16u
       015A  xdiv16u
       0173  empy16s
       0183  pop_gset3
       0186  push_gset1
       0189  pop_gset1
       018A  pop
       019D  push_gset2
       01A1  push_gset3
       01A5  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   001B =     27. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Flag
       0060  __data_start
       0061  _Table
       0075  _Data
       0079  _CNT
       007B  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   007B   0004 =      4. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       007B  __bss_start
       007B  _CNT2
       007D  _CNT1
       007F  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_T1_Capature.o	[ M16_T1_Capature.c ]
<library>	[ div16u.s, emul16s.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

