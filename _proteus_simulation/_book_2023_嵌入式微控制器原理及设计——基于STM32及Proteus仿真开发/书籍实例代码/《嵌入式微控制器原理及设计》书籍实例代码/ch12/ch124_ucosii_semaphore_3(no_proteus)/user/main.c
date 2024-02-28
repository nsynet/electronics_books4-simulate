/**
@file	main.c
@brief	信号量实例3
@author	Zev
*/
/*
@file	《嵌入式微控制器原理及设计》书籍（作者:毕盛等 Email:picy@scut.edu.cn  电子工业出版社）配套实例12.4 STM32标准库版本 无proteus仿真
*/
#include "stm32f10x_it.h"
#include "includes.h"
#include "usart.h"
#include "exti.h"
#include "itm.h"

#define TASK_STK_SIZE	80		///<任务的栈大小

INT8U buf;						///<定义buf变量
OS_EVENT *psem;					///<定义信号量指针
#if USE_SEM_IN_IRQ				//USE_SEM_IN_IRQ在stm32f10x_it.h中定义，是否在中断中使用信号量进行同步
OS_EVENT *psem1;				///<定义在中断中使用的信号量指针
#endif
OS_STK   Stk1[TASK_STK_SIZE];	///<定义task_1堆栈

static void systick_config(void);
static void task_1(void *pdata);

/**
@brief	配置系统滴答，串口，外部中断，并创建任务
@param	None
@retval	如果程序正常结束返回0
*/
int main(void){
	systick_config();
	usart_config();
	exti_config();
	
	OSInit();
	OSTaskCreate(task_1,(void*)0,Stk1+(TASK_STK_SIZE-1),6);	//创建任务1，优先级为6
	OSStart();
	
	return 0;
}
/**
@brief	将变量buf发送给串口
@param	pdata 创建任务时传入的数据
@retval	None
@note	上位机的串口调试助手需要以十六进制显示才能正常显示数据
*/
static void task_1(void *pdata){
	INT8U err;
	
#if USE_SEM_IN_IRQ
	psem1=OSSemCreate(1);	//创建信号量，并初始化为1
#endif
	
	psem=OSSemCreate(0);	//创建信号量，并初始化为0
	while(1){
		OSSemPend(psem,0,&err);	//等待外部中断发送信号量
		usart_send_char(buf);
		OSTimeDly(1);
#if USE_SEM_IN_IRQ
		OSSemPost(psem1);	//发送信号量给外部中断
#endif
	}
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
	printf("Error:in file %s, at line %d",file,line);
	while(1);
}
#endif
