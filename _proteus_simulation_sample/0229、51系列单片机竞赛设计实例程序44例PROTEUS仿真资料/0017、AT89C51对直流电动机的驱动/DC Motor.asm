ADC		EQU		35H
CLOCK	BIT		P2.4			;定义ADC0808时钟位
ST 		BIT 	P2.5
EOC 	BIT 	P2.6
OE 		BIT 	P2.7
PWM		BIT		P3.7
		ORG 	00H
		SJMP	START
		ORG		0BH
		LJMP	INT_T0

START:	MOV		TMOD,#02H	  	;
		MOV		TH0,#20
		MOV		TL0,#00H
		MOV		IE,#82H
		SETB	TR0

WAIT: 	CLR 	ST			  	
		SETB 	ST
		CLR 	ST				;启动AD转换
 		JNB 	EOC,$			;等待转换结束
		SETB 	OE 
		MOV 	ADC,P1			;读取AD转换结果
		CLR 	OE
		SETB	PWM			   	;PWM输出
		MOV 	A,ADC
		LCALL	DELAY
		CLR		PWM
		MOV		A,#255
		SUBB	A,ADC
		LCALL	DELAY
		SJMP 	WAIT

INT_T0:	CPL		CLOCK		 	;提供ADC0808时钟信号
		RETI

DELAY:	MOV		R6,#1
D1:		DJNZ	R6,D1
		DJNZ	ACC,D1
		RET

		END