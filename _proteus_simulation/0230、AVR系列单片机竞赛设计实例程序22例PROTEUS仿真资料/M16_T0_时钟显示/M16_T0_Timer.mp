NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0011 =     17. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0065  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0066   01E2 =    482. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0033  __text_start
       0033  __start
       0053  _exit
       0054  _DelayMs
       0063  _Display
       007F  _Process
       00A2  _Init_IO
       00A8  _main
       00BD  _Timer0
       00E7  mod8u
       00E9  div8u
       00EA  xdiv8u
       00FF  pop_gset2
       0102  pop_gset3
       0105  push_gset1
       0108  pop_gset1
       0109  pop
       011C  push_gset2
       0120  push_gset3
       0124  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0011 =     17. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Table
       0060  __data_start
       006A  _Data
       006E  _Time
       0070  _CNT
       0071  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0028 =     40. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_T0_Timer.o	[ M16_T0_Timer.c ]
<library>	[ div8u.s, gpop2.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x14

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

