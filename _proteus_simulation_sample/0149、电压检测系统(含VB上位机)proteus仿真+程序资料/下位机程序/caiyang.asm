
;ADCS BIT P3.5 ;ʹ�ܽӿ�
;ADCLK BIT P3.6 ;ʱ�ӽӿ�
;ADDO BIT P3.7 ;��������ӿڣ����ã�
;ADDI BIT P3.7 ;��������ӿ�
ORG     0000H
LJMP INITOUT
ORG 0023H
LJMP SERVE
ORG 30H
INITOUT:
MOV SP,#60H   ;ջ����ַ
MOV TMOD,#20H  ;��ʱ��1��ʼ��
MOV TH1,#0F3H  ;���ò�����Ϊ1200MHz��6MHz�ľ���
MOV TL1,#0F3H  ;
MOV SCON,#50H  ;���ڳ�ʼ��Ϊ���Խ���
MOV PCON,#00H  ;�����ʲ�����
SETB TR1   ;������ʱ��
SETB EA   ;���ж�
SETB ES   ;�������ж�
MainProgram:    
NOP    ;��������Ҫ�ǵ��ж�
NOP
LCALL CONV
SJMP Mainprogram
;=======================================================
SERVE:
PUSH PSW        ;������״̬��ѹ���ջ 
PUSH ACC        ;���ۼ���ѹ���ջ 
CLR EA        ;�ر�ϵͳ�ж�          
CLR RI          ;����жϱ�־λ 
MOV A,SBUF
CJNE A,#01,NEXTI;�жϣ�01�ŵ�Ƭ��

MOV SBUF,31H


wait:jnb ti,wait
     clr ti

CLR RI          ;����жϱ�־λ 
SETB EA         ;��ϵͳ�ж� 
POP ACC         ;�ۼ�����ջ 
POP PSW         ;����״̬�ֳ�ջ 
NEXTI:RETI            ;�жϳ��򷵻� 



;==============================================
     
CONV:MOV 30H,#02H;��ʽ��ѡ��
     MOV R0,#31H;���ݴ洢�׵�ַ
     LCALL ADC0832;����A/Dת���ӳ���

     RET
;========================================
ADC0832:SETB P3.7 ;��ʼ��ͨ��ѡ��
        NOP
        NOP
        CLR P3.5 ;����/CS��
        NOP
        NOP
        SETB P3.6 ;����CLK��
        NOP
        NOP
        CLR P3.6 ;����CLK��,�γ��½���
        MOV A,30H
        MOV C,ACC.1 ;ȷ��ȡֵͨ��ѡ��
        MOV P3.7,C
        NOP
        NOP
        SETB P3.6 ;����CLK��
        NOP
        NOP
        CLR P3.6 ;����CLK��,�γ��½���2
        MOV A,30H
        MOV C,ACC.0 ;ȷ��ȡֵͨ��ѡ��
        MOV P3.7,C
        NOP
        NOP
        SETB P3.6 ;����CLK��
        NOP
        NOP
        CLR P3.6 ;����CLK��,�γ��½���3
        SETB P3.7
        NOP
        NOP
    MOV R7,#8 ;׼�����º�8��ʱ������
ADH:MOV C,P3.7 ;��������
    MOV ACC.0,C
    RL A ;����һ��
    SETB P3.6
    NOP
    NOP
    CLR P3.6 ;�γ�һ��ʱ������
    NOP
    NOP
    DJNZ R7,ADH ;ѭ��8��
    MOV C,P3.7 ;��������
    MOV ACC.0,C
    MOV @R0,A
    MOV R7,#8
ADL:MOV C,P3.7 ;��������
    MOV ACC.0,C
    RR A ;����һ��
    SETB P3.6
    NOP
    NOP
    CLR P3.6 ;�γ�һ��ʱ������
    NOP
    NOP
    DJNZ R7,ADL ;ѭ��8��
    MOV B,@R0
    CJNE A,B,ADC0832 ;����У��
    SETB P3.5 ;����/CS��
    CLR P3.6 ;����CLK��
    SETB P3.7 ;�������ݶ�,�ص���ʼ״̬
    RET
;=======================================

