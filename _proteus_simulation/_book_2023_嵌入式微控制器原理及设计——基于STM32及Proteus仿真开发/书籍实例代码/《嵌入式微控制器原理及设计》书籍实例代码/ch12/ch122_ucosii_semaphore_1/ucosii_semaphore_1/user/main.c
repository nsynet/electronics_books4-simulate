/**
@file	main.c
@brief	信号量实例1
@author	Zev
*/
/*
@file	《嵌入式微控制器原理及设计》书籍（作者:毕盛等 Email:picy@scut.edu.cn  电子工业出版社）配套实例12.2  STM32标准库版本
*/
#include "includes.h"
#include "usart.h"

#define TASK_STK_SIZE	80		///<定义任务栈大小
#define USE_SEM		0		///<0为不使用信号量，否则使用信号量

OS_STK   Stk1[TASK_STK_SIZE];	///<定义Task1堆栈
OS_STK   Stk2[TASK_STK_SIZE];	///<定义Task1堆栈
OS_EVENT *psem;					///<定义信号量指针

static void systick_config(void);
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
@brief	向串口发送'A'和'B'
@param	pdata 创建任务时传入的数据
@retval	None
@note	这是一个私有函数;根据USE_SEM的值对应生成使用信号量和不使用信号量的代码
*/
static void task_1(void *pdata){
#if USE_SEM
	INT8U err;
	
	psem=OSSemCreate(1);	//创建信号量,初始化为1
	while(1){
		OSSemPend(psem,0,&err);
		usart_send_char('A');
		OSTimeDly(10);
		usart_send_char('B');
		OSTimeDly(10);
		OSSemPost(psem);
	}
#else
	while(1){
		usart_send_char('A');
		OSTimeDly(1);
		usart_send_char('B');
		OSTimeDly(1);
	}
#endif
}
/**
@brief	先串口发送'C'和'D'
@param	pdata 创建任务时传入的数据
@retval	None
@note	这是一个私有函数;根据USE_SEM的值对应生成使用信号量和不使用信号量的代码
*/
static void task_2(void *pdata){
#if USE_SEM
	INT8U err;
	
	while(1){
		OSSemPend(psem,0,&err);
		usart_send_char('C');
		OSTimeDly(2);
		usart_send_char('D');
		OSTimeDly(2);
		OSSemPost(psem);
	}
#else
	while(1){
		usart_send_char('C');
		OSTimeDly(2);
		usart_send_char('D');
		OSTimeDly(2);
	}
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
