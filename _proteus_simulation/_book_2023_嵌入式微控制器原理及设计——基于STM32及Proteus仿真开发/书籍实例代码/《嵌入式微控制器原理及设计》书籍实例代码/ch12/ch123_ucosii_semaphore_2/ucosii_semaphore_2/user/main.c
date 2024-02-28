/**
@file	main.c
@brief	信号量实例2
@author	Zev
*/
/*
@file	《嵌入式微控制器原理及设计》书籍（作者:毕盛等 Email:picy@scut.edu.cn  电子工业出版社）配套实例12.3 STM32标准库版本
*/
#include "includes.h"
#include "usart.h"

#define TASK_STK_SIZE	80		///<任务的栈大小
#define USE_SEM			0		///<是否使用信号量

OS_STK   Stk1[TASK_STK_SIZE];	///<定义task_1堆栈
OS_STK   Stk2[TASK_STK_SIZE];	///<定义task_2堆栈
OS_EVENT *psem;					///<定义互斥信号量指针

static void systick_config(void);
static void send_buf(void);
static void task_1(void *pdata);
static void task_2(void *pdata);

/**
@brief	创建task_1和task_2
@param	None
@retval	如果程序正常结束返回0
*/
int main(void){
	systick_config();
	usart_config();
	
	OSInit();
	OSTaskCreate(task_1,(void*)0,Stk1+(TASK_STK_SIZE-1),6);	//创建task_1
	OSTaskCreate(task_2,(void*)0,Stk2+(TASK_STK_SIZE-1),8);	//创建task_2
	OSStart();
	
	return 0;
}

/**
@brief	不断地调用函数send_buf
@param	pdata 创建任务时传入的数据
@retval	None
@note	这是一个私有函数；根据USE_SEM的值生成使用信号量和不使用信号量的代码
*/
static void task_1(void *pdata){
#if USE_SEM
	INT8U err;
	psem=OSSemCreate(1);	//创建信号量，初始化为1
#endif
	while(1){
		send_buf();
		OSTimeDly(1);
	}
}
/**
@brief	不断地调用函数send_buf
@param	pdata 创建任务时传入的数据
@retval	None
@note	这是一个私有函数；根据USE_SEM的值生成使用信号量和不使用信号量的代码
*/
static void task_2(void *pdata){
	while(1){
		send_buf();
		OSTimeDly(1);
	}
}

/**
@brief	通过串口向上位机发送"Hello\n"
@param	None
@retval	None
@note	这是一个私有函数；根据USE_SEM的值生成使用信号量和不使用信号量的代码
*/
static void send_buf(void){
#if USE_SEM
	INT8U err;
	OSSemPend(psem,0,&err);		//等待信号量
#endif
	
	usart_send_char('H');
	OSTimeDly(1);				//因为延时导致系统切换另一个任务
	usart_send_char('e');
	OSTimeDly(1);
	usart_send_char('l');
	OSTimeDly(1);
	usart_send_char('l');
	OSTimeDly(1);
	usart_send_char('o');
	usart_send_char('\r');
	usart_send_char('\n');
	OSTimeDly(1);
	
#if USE_SEM
	OSSemPost(psem);			//发送信号量
#endif
}

/**
@brief	配置每一次ucos系统滴答调用一次SysTick_Handler
@param	None
@retval	None
@note	这是一个私有函数
*/
static void systick_config(void){
	RCC_ClocksTypeDef rcc_clk;
	
	RCC_GetClocksFreq(&rcc_clk);
	SysTick_Config(rcc_clk.SYSCLK_Frequency/OS_TICKS_PER_SEC);
}

#ifdef  USE_FULL_ASSERT
/**
@brief	如果传递给库函数的参数错误将会调用此函数，指出出错的文件名以及行数
@param	None
@retval	None
@note	库函数会调用此函数，不需要自己调用
*/
void assert_failed(uint8_t* file, uint32_t line){
	//没有包含itm.h头文件不能使用printf
	//printf("Error:in file %s, at line %d",file,line);
	while(1);
}
#endif
