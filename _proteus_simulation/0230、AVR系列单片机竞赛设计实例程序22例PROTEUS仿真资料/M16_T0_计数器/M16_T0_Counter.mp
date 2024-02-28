NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0014 =     20. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0068  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0068   01B2 =    434. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0034  __text_start
       0034  __start
       0054  _exit
       0055  _DelayMs
       0064  _Display
       0082  _Process
       00B4  _Init_IO
       00BD  _main
       00CC  mod16u
       00CE  div16u
       00CF  xdiv16u
       00E8  pop_gset2
       00EB  pop_gset3
       00EE  push_gset1
       00F1  pop_gset1
       00F2  pop
       0105  push_gset2
       0109  push_gset3
       010D  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0014 =     20. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Table
       0060  __data_start
       006A  _Data
       0072  _CNT
       0074  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_T0_Counter.o	[ M16_T0_Counter.c ]
<library>	[ div16u.s, gpop2.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x14

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

