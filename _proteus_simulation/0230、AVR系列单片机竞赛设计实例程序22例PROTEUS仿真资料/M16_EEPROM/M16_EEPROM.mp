NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0010 =     16. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0064  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0064   01CA =    458. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0032  __start
       0032  __text_start
       0052  _exit
       0053  _DelayMs
       0066  _Display
       0088  _Init_IO
       008E  _Write_EEPROM
       00A7  _Read_EEPROM
       00BF  _main
       00F2  pop_gset2
       00F5  pop_gset3
       00F8  push_gset1
       00FB  pop_gset1
       00FC  pop
       010F  push_gset2
       0113  push_gset3
       0117  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0010 =     16. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _Table
       0060  __data_start
       0070  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0070   0006 =      6. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0070  __bss_start
       0070  _p1
       0072  _Read_Data
       0076  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_EEPROM.o	[ M16_EEPROM.C ]
<library>	[ gpop2.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x14

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

