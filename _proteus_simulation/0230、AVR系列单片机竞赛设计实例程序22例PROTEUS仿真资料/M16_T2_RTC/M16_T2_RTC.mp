NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   000E =     14. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0062  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0062   01B4 =    436. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0031  __start
       0031  __text_start
       0051  _exit
       0052  _DelayMs
       0060  _Display
       0081  _Init_IO
       0089  _Add_Second
       00BB  _main
       00DB  _Timer2
       00E9  pop_gset3
       00EC  push_gset1
       00EF  pop_gset1
       00F0  pop
       0103  push_gset2
       0107  push_gset3
       010B  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   000E =     14. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Table
       0060  __data_start
       006A  _Data
       006E  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   006E   0001 =      1. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       006E  __bss_start
       006E  _CNT
       006F  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_T2_RTC.o	[ M16_T2_RTC.c ]
<library>	[ gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x14

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

