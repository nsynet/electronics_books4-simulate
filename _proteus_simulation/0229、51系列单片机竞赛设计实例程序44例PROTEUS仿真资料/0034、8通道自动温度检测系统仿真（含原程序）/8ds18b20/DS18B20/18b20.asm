     CLR P3.7
MAIN:MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER 
     LCALL   TEMPRRO
     MOV P2,#06H
     LCALL PRO
;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER2 
     LCALL   TEMPRRO
     MOV P2,#5BH
     LCALL PRO
;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER3
     LCALL   TEMPRRO
     MOV P2,#4FH
     LCALL PRO

;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER4
     LCALL   TEMPRRO
     MOV P2,#66H
     LCALL PRO
;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER5
     LCALL   TEMPRRO
     MOV P2,#6DH
     LCALL PRO
;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER6
     LCALL   TEMPRRO
     MOV P2,#7DH
     LCALL PRO
;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER7
     LCALL   TEMPRRO
     MOV P2,#07H
     LCALL PRO
;------------------------------------------------------

     MOV 38H,#00H
     MOV 39H,#00H
     MOV 3AH,#00H
     MOV 3BH,#00H
     LCALL   GET_TEMPER8
     LCALL   TEMPRRO
     MOV P2,#7FH
     LCALL PRO
      LJMP  MAIN
    


;==============================================CHL1
GET_TEMPER: 
          SETB      P1.0H ; ��ʱ��� 
BCD:      LCALL     INIT_1820 
          JB        00H,S22 
          LJMP      BCD ; ��DS18B20�������򷵻� 

S22:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_1820 
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_1820 
NOP 
LCALL DELAY1 
CBA:LCALL INIT_1820 
JB 00H,ABC 
LJMP CBA 
ABC:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_1820 
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_1820 
LCALL READ_18200 ;READ_1820 
RET 
;==============================
READ_1820: 
MOV R2,#8 
RE1: 
CLR C 
SETB P1.0H 
NOP 
NOP 
CLR P1.0H 
NOP 
NOP 
NOP 
SETB P1.0H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.0H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE1 
RET 
;=============================
WRITE_1820: 
MOV R2,#8 
CLR C 
WR1: 
CLR P1.0H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.0H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.0H 
NOP 
DJNZ R2,WR1 
SETB P1.0H 
RET
;=======================================
READ_18200: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE00: 
MOV R2,#8 
RE01: 
CLR C 
SETB P1.0H 
NOP 
NOP 
CLR P1.0H 
NOP 
NOP 
NOP 
SETB P1.0H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.0H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE01 
MOV @R1,A 
DEC R1 
DJNZ R4,RE00 
RET 
;=======================================
INIT_1820: 
SETB P1.0H 
NOP 
CLR P1.0H 
MOV R0,#250
TSR1: 
DJNZ R0,TSR1 ; ��ʱ520us 
SETB P1.0H 
MOV R0,#25H ;96US-25H 
TSR2: 
DJNZ R0,TSR2 
JNB P1.0H,TSR3;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR4 ; ��ʱ 
TSR3: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR5 
TSR4: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR7 
TSR5: 
MOV R0,#06BH ;200US 
TSR6: 
DJNZ R0,TSR6 ; ��ʱ 
TSR7: 
SETB P1.0H ;��������
RET
;=============================== 
GET_TEMPER2: 
          SETB      P1.1H ; ��ʱ��� 
BCD2:      LCALL     INIT_18202 
          JB        00H,S222 
          LJMP      BCD2 ; ��DS18B20�������򷵻� 

S222:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18202 
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18202 
NOP 
LCALL DELAY1 
CBA2:LCALL INIT_18202 
JB 00H,ABC2 
LJMP CBA2 
ABC2:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18202 
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18202 
LCALL READ_182002 ;READ_1820 
RET 
;==============================
READ_18202: 
MOV R2,#8 
RE12: 
CLR C 
SETB P1.1H 
NOP 
NOP 
CLR P1.1H 
NOP 
NOP 
NOP 
SETB P1.1H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.1H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE12 
RET 
;=============================
WRITE_18202: 
MOV R2,#8 
CLR C 
WR12: 
CLR P1.1H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.1H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.1H 
NOP 
DJNZ R2,WR12 
SETB P1.1H 
RET
;=======================================
READ_182002: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE002: 
MOV R2,#8 
RE012: 
CLR C 
SETB P1.1H 
NOP 
NOP 
CLR P1.1H 
NOP 
NOP 
NOP 
SETB P1.1H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.1H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE012 
MOV @R1,A 
DEC R1 
DJNZ R4,RE002 
RET 
;=======================================
INIT_18202: 
SETB P1.1H 
NOP 
CLR P1.1H 
MOV R0,#250
TSR12: 
DJNZ R0,TSR12 ; ��ʱ520us 
SETB P1.1H 
MOV R0,#25H ;96US-25H 
TSR22: 
DJNZ R0,TSR22 
JNB P1.1H,TSR32;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR42 ; ��ʱ 
TSR32: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR52 
TSR42: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR72 
TSR52: 
MOV R0,#06BH ;200US 
TSR62: 
DJNZ R0,TSR62 ; ��ʱ 
TSR72: 
SETB P1.1H ;��������
RET
;=============================== 
GET_TEMPER3: 
          SETB      P1.2H ; ��ʱ��� 
BCD3:      LCALL     INIT_18203 
          JB        00H,S223 
          LJMP      BCD3 ; ��DS18B20�������򷵻� 

S223:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18203
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18203
NOP 
LCALL DELAY1 
CBA3:LCALL INIT_18203
JB 00H,ABC3 
LJMP CBA3
ABC3:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18203
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18203
LCALL READ_182003 ;READ_1820 
RET 
;==============================
READ_18203: 
MOV R2,#8 
RE13: 
CLR C 
SETB P1.2H 
NOP 
NOP 
CLR P1.2H 
NOP 
NOP 
NOP 
SETB P1.2H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.2H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE13
RET 
;=============================
WRITE_18203: 
MOV R2,#8 
CLR C 
WR13: 
CLR P1.2H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.2H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.2H 
NOP 
DJNZ R2,WR13
SETB P1.2H 
RET
;=======================================
READ_182003: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE003: 
MOV R2,#8 
RE013: 
CLR C 
SETB P1.2H 
NOP 
NOP 
CLR P1.2H 
NOP 
NOP 
NOP 
SETB P1.2H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.2H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE013
MOV @R1,A 
DEC R1 
DJNZ R4,RE003 
RET 
;=======================================
INIT_18203: 
SETB P1.2H 
NOP 
CLR P1.2H 
MOV R0,#250
TSR13: 
DJNZ R0,TSR13 ; ��ʱ520us 
SETB P1.2H 
MOV R0,#25H ;96US-25H 
TSR23: 
DJNZ R0,TSR23 
JNB P1.2H,TSR33;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR43 ; ��ʱ 
TSR33: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR53 
TSR43: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR73
TSR53: 
MOV R0,#06BH ;200US 
TSR63: 
DJNZ R0,TSR63 ; ��ʱ 
TSR73: 
SETB P1.2H ;��������
RET
;=============================== 
GET_TEMPER4: 
          SETB      P1.3H ; ��ʱ��� 
BCD4:      LCALL     INIT_18204
          JB        00H,S224 
          LJMP      BCD4 ; ��DS18B20�������򷵻� 

S224:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18204
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18204
NOP 
LCALL DELAY1 
CBA4:LCALL INIT_18204
JB 00H,ABC4
LJMP CBA4
ABC4:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18204
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18204
LCALL READ_182004 ;READ_1820 
RET 
;==============================
READ_18204: 
MOV R2,#8 
RE14: 
CLR C 
SETB P1.3H 
NOP 
NOP 
CLR P1.3H 
NOP 
NOP 
NOP 
SETB P1.3H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.3H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE14
RET 
;=============================
WRITE_18204: 
MOV R2,#8 
CLR C 
WR14: 
CLR P1.3H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.3H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.3H 
NOP 
DJNZ R2,WR14
SETB P1.3H 
RET
;=======================================
READ_182004: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE004: 
MOV R2,#8 
RE014: 
CLR C 
SETB P1.3H 
NOP 
NOP 
CLR P1.3H 
NOP 
NOP 
NOP 
SETB P1.3H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.3H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE014
MOV @R1,A 
DEC R1 
DJNZ R4,RE004
RET 
;=======================================
INIT_18204: 
SETB P1.3H 
NOP 
CLR P1.3H 
MOV R0,#250
TSR14: 
DJNZ R0,TSR14 ; ��ʱ520us 
SETB P1.3H 
MOV R0,#25H ;96US-25H 
TSR24: 
DJNZ R0,TSR24
JNB P1.3H,TSR34;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR44 ; ��ʱ 
TSR34: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR54 
TSR44: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR74
TSR54: 
MOV R0,#06BH ;200US 
TSR64: 
DJNZ R0,TSR64 ; ��ʱ 
TSR74: 
SETB P1.3H ;��������
RET
;=============================== 
GET_TEMPER5: 
          SETB      P1.4H ; ��ʱ��� 
BCD5:      LCALL     INIT_18205
          JB        00H,S225
          LJMP      BCD5 ; ��DS18B20�������򷵻� 

S225:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18205
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18205
NOP 
LCALL DELAY1 
CBA5:LCALL INIT_18205
JB 00H,ABC5
LJMP CBA5
ABC5:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18205
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18205
LCALL READ_182005 ;READ_1820 
RET 
;==============================
READ_18205: 
MOV R2,#8 
RE15: 
CLR C 
SETB P1.4H 
NOP 
NOP 
CLR P1.4H 
NOP 
NOP 
NOP 
SETB P1.4H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.4H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE15
RET 
;=============================
WRITE_18205: 
MOV R2,#8 
CLR C 
WR15: 
CLR P1.4H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.4H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.4H 
NOP 
DJNZ R2,WR15
SETB P1.4H 
RET
;=======================================
READ_182005: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE005: 
MOV R2,#8 
RE015: 
CLR C 
SETB P1.4H 
NOP 
NOP 
CLR P1.4H 
NOP 
NOP 
NOP 
SETB P1.4H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.4H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE015
MOV @R1,A 
DEC R1 
DJNZ R4,RE005
RET 
;=======================================
INIT_18205: 
SETB P1.4H 
NOP 
CLR P1.4H 
MOV R0,#250
TSR15: 
DJNZ R0,TSR15 ; ��ʱ520us 
SETB P1.4H 
MOV R0,#25H ;96US-25H 
TSR25: 
DJNZ R0,TSR25
JNB P1.4H,TSR35;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR45 ; ��ʱ 
TSR35: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR55 
TSR45: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR75
TSR55: 
MOV R0,#06BH ;200US 
TSR65: 
DJNZ R0,TSR65 ; ��ʱ 
TSR75: 
SETB P1.4H ;��������
RET
;=============================== 
GET_TEMPER6: 
          SETB      P1.5H ; ��ʱ��� 
BCD6:      LCALL     INIT_18206
          JB        00H,S226
          LJMP      BCD6; ��DS18B20�������򷵻� 

S226:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18206
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18206
NOP 
LCALL DELAY1 
CBA6:LCALL INIT_18206
JB 00H,ABC6
LJMP CBA6
ABC6:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18206
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18206
LCALL READ_182006 ;READ_1820 
RET 
;==============================
READ_18206: 
MOV R2,#8 
RE16: 
CLR C 
SETB P1.5H 
NOP 
NOP 
CLR P1.5H 
NOP 
NOP 
NOP 
SETB P1.5H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.5H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE16
RET 
;=============================
WRITE_18206: 
MOV R2,#8 
CLR C 
WR16: 
CLR P1.5H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.5H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.5H 
NOP 
DJNZ R2,WR16
SETB P1.5H 
RET
;=======================================
READ_182006: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE006: 
MOV R2,#8 
RE016: 
CLR C 
SETB P1.5H 
NOP 
NOP 
CLR P1.5H 
NOP 
NOP 
NOP 
SETB P1.5H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.5H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE016
MOV @R1,A 
DEC R1 
DJNZ R4,RE006
RET 
;=======================================
INIT_18206: 
SETB P1.5H 
NOP 
CLR P1.5H 
MOV R0,#250
TSR16: 
DJNZ R0,TSR16 ; ��ʱ520us 
SETB P1.5H 
MOV R0,#25H ;96US-25H 
TSR26: 
DJNZ R0,TSR26
JNB P1.5H,TSR36;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR46 ; ��ʱ 
TSR36: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR56 
TSR46: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR76
TSR56: 
MOV R0,#06BH ;200US 
TSR66: 
DJNZ R0,TSR66 ; ��ʱ 
TSR76: 
SETB P1.5H ;��������
RET
;=============================== 
GET_TEMPER7: 
          SETB      P1.6H ; ��ʱ��� 
BCD7:      LCALL     INIT_18207
          JB        00H,S227
          LJMP      BCD7; ��DS18B20�������򷵻� 

S227:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18207
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18207
NOP 
LCALL DELAY1 
CBA7:LCALL INIT_18207
JB 00H,ABC7
LJMP CBA7
ABC7:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18207
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18207
LCALL READ_182007 ;READ_1820 
RET 
;==============================
READ_18207: 
MOV R2,#8 
RE17: 
CLR C 
SETB P1.6H 
NOP 
NOP 
CLR P1.6H 
NOP 
NOP 
NOP 
SETB P1.6H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.6H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE17
RET 
;=============================
WRITE_18207: 
MOV R2,#8 
CLR C 
WR17: 
CLR P1.6H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.6H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.6H 
NOP 
DJNZ R2,WR17
SETB P1.6H 
RET
;=======================================
READ_182007: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE007: 
MOV R2,#8 
RE017: 
CLR C 
SETB P1.6H 
NOP 
NOP 
CLR P1.6H 
NOP 
NOP 
NOP 
SETB P1.6H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.6H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE017
MOV @R1,A 
DEC R1 
DJNZ R4,RE007
RET 
;=======================================
INIT_18207: 
SETB P1.6H 
NOP 
CLR P1.6H 
MOV R0,#250
TSR17: 
DJNZ R0,TSR17 ; ��ʱ520us 
SETB P1.6H 
MOV R0,#25H ;96US-25H 
TSR27: 
DJNZ R0,TSR27
JNB P1.6H,TSR37;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR47; ��ʱ 
TSR37: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR57 
TSR47: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR77
TSR57: 
MOV R0,#06BH ;200US 
TSR67: 
DJNZ R0,TSR67; ��ʱ 
TSR77: 
SETB P1.6H ;��������
RET
;=============================== 
GET_TEMPER8: 
          SETB      P1.7H ; ��ʱ��� 
BCD8:      LCALL     INIT_18208
          JB        00H,S228
          LJMP      BCD8; ��DS18B20�������򷵻� 

S228:     LCALL     DELAY1 
         MOV        A,#0CCH ; ����ROMƥ��------0CC����
         LCALL     WRITE_18208
MOV A,#44H ; �����¶�ת������ 
LCALL WRITE_18208
NOP 
LCALL DELAY1 
CBA8:LCALL INIT_18208
JB 00H,ABC8
LJMP CBA8
ABC8:LCALL DELAY1 
MOV A,#0CCH ; ����ROMƥ�� 
LCALL WRITE_18208
MOV A,#0BEH ; �������¶����� 
LCALL WRITE_18208
LCALL READ_182008 ;READ_1820 
RET 
;==============================
READ_18208: 
MOV R2,#8 
RE18: 
CLR C 
SETB P1.7H 
NOP 
NOP 
CLR P1.7H 
NOP 
NOP 
NOP 
SETB P1.7H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.7H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE18
RET 
;=============================
WRITE_18208: 
MOV R2,#8 
CLR C 
WR18: 
CLR P1.7H 
MOV R3,#6 
DJNZ R3,$ 
RRC A 
MOV P1.7H,C 
MOV R3,#23 
DJNZ R3,$ 
SETB P1.7H 
NOP 
DJNZ R2,WR18
SETB P1.7H 
RET
;=======================================
READ_182008: 
MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж��� 
MOV R1,#31H ; ��λ����30H(TEMPER_L),��λ����31H(TEMPER_H) 
RE008: 
MOV R2,#8 
RE018: 
CLR C 
SETB P1.7H 
NOP 
NOP 
CLR P1.7H 
NOP 
NOP 
NOP 
SETB P1.7H 
MOV R3,#7 
DJNZ R3,$ 
MOV C,P1.7H 
MOV R3,#23 
DJNZ R3,$ 
RRC A 
DJNZ R2,RE018
MOV @R1,A 
DEC R1 
DJNZ R4,RE008
RET 
;=======================================
INIT_18208: 
SETB P1.7H 
NOP 
CLR P1.7H 
MOV R0,#250
TSR18: 
DJNZ R0,TSR18 ; ��ʱ520us 
SETB P1.7H 
MOV R0,#25H ;96US-25H 
TSR28: 
DJNZ R0,TSR28
JNB P1.7H,TSR38;��D0Ϊ����λ�ɹ���DS18B20���� 
LJMP TSR48; ��ʱ 
TSR38: 
SETB 00H ; �ñ�־λ,��ʾDS1820���� 
LJMP TSR58
TSR48: 
CLR 00H ; ���־λ,��ʾDS1820������ 
LJMP TSR78
TSR58: 
MOV R0,#06BH ;200US 
TSR68: 
DJNZ R0,TSR68; ��ʱ 
TSR78: 
SETB P1.7H ;��������
RET
;=============================== 
;======================================
DELAY1:MOV R7,#20H 
DJNZ R7,$ 
RET

;====================================
TEMPRRO:MOV 33H,#00H;��ʼ��0
MOV A,30H
ANL A,#0FH
SWAP A
MOV 33H,A
MOV A,31H
ANL A,#0F0H
SWAP A
ORL 33H,A;������ϳɵĴ��������ݣ��������֣�
MOV A,33H
ANL A,#80H;�жϷ���

JZ TEMPP
MOV A,33H
CPL A
;ADD A,#01H
SJMP TEMPP1
TEMPP:MOV A,33H;�����������
      LCALL HBCD
      MOV A,31H
      ANL A,#0FH
      MOV DPTR,#TEMPTAB;С�����
      MOVC A,@A+DPTR
      MOV 36H,A
      CLR P3.7;��ʾ����
      SJMP EXIT
TEMPP1:LCALL HBCD;�����������
       MOV A,31H
       ANL A,#0FH
       ORL A,#0F0H
       CPL A
       ADD A,#01H
       MOV DPTR,#TEMPTAB
       MOVC A,@A+DPTR;С�����
       MOV 36H,A
       SETB P3.7;��ʾ����
EXIT:RET

HBCD:	MOV	B,#100	;�������λ�������R3��
	DIV	AB
	MOV	R3,A
	MOV	A,#10	;������������ʮλ�͸�λ
	XCH	A,B
	DIV	AB
	SWAP	A
	ORL	A,B	;��ʮλ�͸�λƴװ�ɣ£ã���
	MOV 34H,R3
	MOV 35H,A
	RET
TEMPTAB:DB 00H,01H,01H,02H,03H,03H,04H,04H
        DB 05H,06H,06H,07H,08H,08H,09H,09H;0~16*0.0652
;==================================================
CBCD:;MOV R2,#04H;5���������BCD
CL:MOV A,@R1     ;�����ռ10����Ԫ
   MOV B,A
   ANL A,#0F0H
   SWAP A
   MOV 4CH,A
   MOV A,B
   ANL A,#0FH
   MOV 4DH,A
   MOV @R0,4CH
   INC R0
   MOV @R0,4DH
   INC R0
   INC R1
   DJNZ R2,CL
   RET
;===================================================
DISPLAY:MOV R0,#38H;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;��ʾ�������׵�ַ
        MOV R2,#04
DISP_LOOP:MOV A,@R0
          LCALL DISP
          INC R0
	  DJNZ R2,DISP_LOOP
          CLR  P0.2
          NOP
          NOP
          SETB P0.2      ;�����ؽ������͵����������
          NOP
          NOP
          NOP
          CLR  P0.2
          RET
DISP:MOV R4,#08H;��λ�Ĵ�����������
WR_LOOP: RLC A
         MOV P0.1,C
         SETB P0.0        ;�����ط�����λ
         NOP
         NOP
         CLR P0.0
         DJNZ R4,WR_LOOP
	 RET
;=============================
PRO: MOV R2,#03H;N���������BCD
     MOV R0,#37H;�����BCD�׵�ַ
     MOV R1,#34H;������BCD�׵�ַ
     LCALL CBCD;����ѹ����BCD��
     MOV 3BH,3CH;С������

     MOV R0,#38H;��ʾ�����׵�ַ
     MOV R1,#38H;��ʾ�������׵�ַ
     MOV R2,#04;���ݸ���
RES_LOOP:MOV A,@R0
         LCALL RES
         MOV @R1,A
	 INC R0
	 INC R1
	 DJNZ R2,RES_LOOP  
      ORL 3AH,#80H;С����
      LCALL DISPLAY
LCALL DELAYS
LCALL DELAYS
LCALL DELAYS
LCALL DELAYS
LCALL DELAYS
LCALL DELAYS
RET
;==============================
RES:MOV DPTR,#TAB
    MOVC A,@A+DPTR
    RET
TAB: DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH
;======================================
DELAYS:MOV R5,#0FFH
LOOP2:MOV R4,#0FFH
LOOP1:NOP
      NOP
      DJNZ R4,LOOP1
      DJNZ R5,LOOP2
      RET
                END
