NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0022   0020 =     32. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0022  __lit_start
       002E  _led_tabel
       0042  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0042   0019 =     25. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0042  __idata_start
       005B  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   005C   0748 =   1864. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       002E  __start
       002E  __text_start
       004D  _exit
       004E  _adc_init
       0054  _adc_isr
       00D7  _change_data
       0121  _scan_led
       0138  _delay
       0147  _port_init
       0154  _main
       0167  _dac_init
       017D  _put_to_dac
       01AC  push_arg4
       01AE  push_arg2
       01B1  mod16s
       01B5  div16s
       01CE  mod16u
       01D0  div16u
       01D1  xdiv16u
       01EA  pop_gset2
       01EC  pop_gset3
       01EE  push_gset1
       01F1  pop_gset1
       01F2  pop
       0205  push_gset2
       0208  push_gset3
       020B  neg32
       0214  lpm32
       0228  fp2int
       022F  nojump1
       0233  fp2long
       0238  nojump2
       0239  FTOI
       023B  FTOL
       0266  int2fp
       026C  long2fp
       026F  ITOF
       0291  save_floatregs
       029C  restore_floatregs
       02A7  stk2arg1
       02AC  stk2arg0
       02B1  float_epilog
       02B8  float_prolog
       02BB  add32fs
       02BD  add32f
       02C0  sub32fs
       02C2  sub32f
       02C5  fret2
       02CB  FSUB
       02CC  FADD
       030B  usub24
       030F  cmp32f
       0312  FLTCP
       033E  empy32fs
       0340  empy32f
       0347  eFMUL
       035D  eumul24
       0384  savfacc1
       0387  restorefacc1
       038A  unpackfacc1
       0393  negmant
       0399  maxres
       03A0  minres
       03A6  ac1toac2
       03AC  swapacc
       03B8  unpack
       03CA  repack
       03D2  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0019 =     25. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _disp_buffer
       0064  _sin_tabel
       0079  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0079   0003 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0079  __bss_start
       0079  _adc_val
       007B  _vol_data
       007C  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   001E =     30. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\ICC\lib\crtAVR.o	[ crtavr.s ]
adc.o	[ adc.c ]
led_dsp.o	[ led_dsp.c ]
main.o	[ main.c ]
dac.o	[ dac.c ]
<library>	[ asave.s, div16s.s, div16u.s, gpop2.s, gpop3.s, gpush.s, gpush2.s, gpush3.s, lneg.s, lpm32.s, fp2int.s ]
[ fpint2fp.s, fputil.s, fpadd.s, fpcmp.s, fpemul.s, fputil2.s, fputil3.s ]

User Global Definitions

ram_end = 0x25f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x22
data = 0x60
eeprom:1.512

