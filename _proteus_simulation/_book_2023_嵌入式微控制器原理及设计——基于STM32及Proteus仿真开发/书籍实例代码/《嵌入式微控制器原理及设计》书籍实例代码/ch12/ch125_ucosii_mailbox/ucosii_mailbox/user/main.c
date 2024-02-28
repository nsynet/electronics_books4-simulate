/**
@file	main.c
@brief	消息邮箱实例
@author	Zev
@note	
*/
/*
@file	《嵌入式微控制器原理及设计》书籍（作者:毕盛等 Email:picy@scut.edu.cn  电子工业出版社）配套实例12.5 STM32标准库版本
*/

#include "includes.h"
#include "usart.h"

#define TASK_STK_SIZE	80			//任务栈的大小
#define LED_ON			0x55		//表示打开LED灯
#define LED_OFF			0x88		//表示关闭LED灯

OS_STK switch_stk[TASK_STK_SIZE];	//检测开关任务栈
OS_STK led_stk[TASK_STK_SIZE];		//控制LED任务栈
OS_STK usart_stk[TASK_STK_SIZE];	//串口任务栈

OS_EVENT *pmailbox;					//消息邮箱指针

static void systick_config(void);
static void switch_task(void *pdata);
static void led_task(void *pdata);
static void usart_task(void *pdata);

/**
@brief	创建任务
@param	None
@retval	如果程序正常结束返回0
*/
int main(void){
	systick_config();
	
	OSInit();
	OSTaskCreate(led_task,(void*)0,led_stk+(TASK_STK_SIZE-1),5);
	OSTaskCreate(switch_task,(void*)0,switch_stk+(TASK_STK_SIZE-1),6);
	OSTaskCreate(usart_task,(void*)0,usart_stk+(TASK_STK_SIZE-1),7);
	OSStart();
	
	return 0;
}
/**
@brief	检测开关PB2是否按下,并群邮消息
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void switch_task(void *pdata){
	INT8U data;
	GPIO_InitTypeDef gpio_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init.GPIO_Pin=GPIO_Pin_2;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_init);
	
	while(1){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)){	//按钮没按
			data=LED_OFF;
		}else{	//按钮按下
			data=LED_ON;
		}
		OSMboxPostOpt(pmailbox,&data,OS_POST_OPT_BROADCAST);	//群邮消息
		OSTimeDly(1);
	}
}
/**
@brief	根据收到的邮箱消息，控制LED的亮灭
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void led_task(void *pdata){
	INT8U err;
	INT8U *pd;
	GPIO_InitTypeDef gpio_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_1;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	
	pmailbox=OSMboxCreate(NULL);
	
	while(1){
		pd=(INT8U*)OSMboxPend(pmailbox,0,&err);
		if(*pd==LED_ON){
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}else{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}
		OSTimeDly(1);
	}
	
}
/**
@brief	通过串口向上位机发送接收到的邮箱消息
@param	pdata 创建任务时传入的数据
@retval	None
*/
static void usart_task(void *pdata){
	INT8U err;
	INT8U *pd;
	
	usart_config();
	
	while(1){
		pd=(INT8U*)OSMboxPend(pmailbox,0,&err);
		usart_send_char(*pd);
		OSTimeDly(1);
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
	//printf("Error:in file %s, at line %d",file,line);
	while(1);
}
#endif
