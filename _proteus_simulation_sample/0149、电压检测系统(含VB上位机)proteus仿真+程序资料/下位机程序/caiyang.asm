
;ADCS BIT P3.5 ;使能接口
;ADCLK BIT P3.6 ;时钟接口
;ADDO BIT P3.7 ;数据输出接口（复用）
;ADDI BIT P3.7 ;数据输入接口
ORG     0000H
LJMP INITOUT
ORG 0023H
LJMP SERVE
ORG 30H
INITOUT:
MOV SP,#60H   ;栈顶地址
MOV TMOD,#20H  ;定时器1初始化
MOV TH1,#0F3H  ;设置波特率为1200MHz，6MHz的晶振
MOV TL1,#0F3H  ;
MOV SCON,#50H  ;串口初始化为可以接收
MOV PCON,#00H  ;波特率不倍增
SETB TR1   ;启动定时器
SETB EA   ;开中断
SETB ES   ;允许串口中断
MainProgram:    
NOP    ;主程序主要是等中断
NOP
LCALL CONV
SJMP Mainprogram
;=======================================================
SERVE:
PUSH PSW        ;将程序状态字压入堆栈 
PUSH ACC        ;将累加器压入堆栈 
CLR EA        ;关闭系统中断          
CLR RI          ;清除中断标志位 
MOV A,SBUF
CJNE A,#01,NEXTI;判断，01号单片机

MOV SBUF,31H


wait:jnb ti,wait
     clr ti

CLR RI          ;清除中断标志位 
SETB EA         ;打开系统中断 
POP ACC         ;累加器出栈 
POP PSW         ;程序状态字出栈 
NEXTI:RETI            ;中断程序返回 



;==============================================
     
CONV:MOV 30H,#02H;方式字选择
     MOV R0,#31H;数据存储首地址
     LCALL ADC0832;调用A/D转换子程序

     RET
;========================================
ADC0832:SETB P3.7 ;初始化通道选择
        NOP
        NOP
        CLR P3.5 ;拉低/CS端
        NOP
        NOP
        SETB P3.6 ;拉高CLK端
        NOP
        NOP
        CLR P3.6 ;拉低CLK端,形成下降沿
        MOV A,30H
        MOV C,ACC.1 ;确定取值通道选择
        MOV P3.7,C
        NOP
        NOP
        SETB P3.6 ;拉高CLK端
        NOP
        NOP
        CLR P3.6 ;拉低CLK端,形成下降沿2
        MOV A,30H
        MOV C,ACC.0 ;确定取值通道选择
        MOV P3.7,C
        NOP
        NOP
        SETB P3.6 ;拉高CLK端
        NOP
        NOP
        CLR P3.6 ;拉低CLK端,形成下降沿3
        SETB P3.7
        NOP
        NOP
    MOV R7,#8 ;准备送下后8个时钟脉冲
ADH:MOV C,P3.7 ;接收数据
    MOV ACC.0,C
    RL A ;左移一次
    SETB P3.6
    NOP
    NOP
    CLR P3.6 ;形成一次时钟脉冲
    NOP
    NOP
    DJNZ R7,ADH ;循环8次
    MOV C,P3.7 ;接收数据
    MOV ACC.0,C
    MOV @R0,A
    MOV R7,#8
ADL:MOV C,P3.7 ;接收数据
    MOV ACC.0,C
    RR A ;左移一次
    SETB P3.6
    NOP
    NOP
    CLR P3.6 ;形成一次时钟脉冲
    NOP
    NOP
    DJNZ R7,ADL ;循环8次
    MOV B,@R0
    CJNE A,B,ADC0832 ;数据校验
    SETB P3.5 ;拉高/CS端
    CLR P3.6 ;拉低CLK端
    SETB P3.7 ;拉高数据端,回到初始状态
    RET
;=======================================

