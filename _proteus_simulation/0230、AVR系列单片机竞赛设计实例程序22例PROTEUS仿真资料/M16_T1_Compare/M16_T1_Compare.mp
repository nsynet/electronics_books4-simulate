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
                            text   0062   02AA =    682. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0031  __start
       0031  __text_start
       0051  _exit
       0052  _DelayMs
       0060  _Display
       0081  _Key_Process
       00DE  _Set_Process
       010A  _Init_IO
       0115  _Init_Timer1
       0120  _main
       012E  _Compare
       0138  mod16u
       013A  div16u
       013B  xdiv16u
       0154  empy16s
       0164  pop_gset3
       0167  push_gset1
       016A  pop_gset1
       016B  pop
       017E  push_gset2
       0182  push_gset3
       0186  __text_end

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
                             bss   006E   0003 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       006E  __bss_start
       006E  _Key3
       006F  _Key2
       0070  _Key1
       0071  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   001C =     28. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_T1_Compare.o	[ M16_T1_Compare.c ]
<library>	[ div16u.s, emul16s.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

