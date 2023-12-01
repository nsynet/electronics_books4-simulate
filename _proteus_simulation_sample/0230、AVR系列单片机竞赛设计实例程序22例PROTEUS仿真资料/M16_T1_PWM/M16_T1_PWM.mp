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
                            text   0068   02A2 =    674. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0034  __start
       0034  __text_start
       0054  _exit
       0055  _DelayMs
       0063  _Display
       0084  _Add_Process
       009C  _Sub_Process
       00B8  _Key_Process
       00DF  _Set_Process
       0100  _Init_IO
       010B  _main
       011C  mod16u
       011E  div16u
       011F  xdiv16u
       0138  mod8u
       013A  div8u
       013B  xdiv8u
       0150  empy16s
       0160  pop_gset2
       0163  pop_gset3
       0166  push_gset1
       0169  pop_gset1
       016A  pop
       017D  push_gset2
       0181  push_gset3
       0185  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0014 =     20. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _Table
       006C  _Data1
       0070  _Data2
       0074  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0074   0002 =      2. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0074  __bss_start
       0074  _Key2
       0075  _Key1
       0076  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\icc\lib\crtatmega.o	[ crtatmega.s ]
M16_T1_PWM.o	[ M16_T1_PWM.c ]
<library>	[ div16u.s, div8u.s, emul16s.s, gpop2.s, gpop3.s, gpush.s, gpush2.s, gpush3.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

