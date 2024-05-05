
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/*
@file	《嵌入式微控制器原理及设计》书籍（作者:毕盛等 Email:picy@scut.edu.cn  电子工业出版社）配套实例 ch11.1
*/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#define uchar unsigned char
/* USER CODE BEGIN Includes */
uchar DISP_Buffer[]={0,0,0};
uchar i=0;
uint32_t TimeCount;
uint8_t NixieTubeBit[]={0xc0,0xF9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uint8_t DisplayByte[10]={0,1,2,3,4,5,6,7,8,9};
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
#define  DSPORT       GPIOC
#define  DS_COM_PORT  GPIOA
#define  IIC_PORT     GPIOB
#define  COM_PIN_1    GPIO_PIN_0
#define  COM_PIN_2    GPIO_PIN_1
#define  COM_PIN_3    GPIO_PIN_2
#define  COM_PIN_4    GPIO_PIN_3

#define  SDA_PIN GPIO_PIN_7
#define  SCK_PIN GPIO_PIN_6
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END Includes */
/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t j)
* Description    : 输出多个位，GPIO_Pin_Position为要输出的位，PortVal是要输出的端口值
* EntryParameter :(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
* ReturnValue    : NO
**************************************************************************************/
void GPIOSetDir(GPIO_TypeDef *GPIOx,uint32_t GPIO_PIN_x,uint8_t t)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(t)
	{
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;;
	}
	else
	{
		  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	}
	GPIO_InitStruct.Pin = GPIO_PIN_x;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}




/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t j)
* Description    : 输出多个位，GPIO_Pin_Position为要输出的位，PortVal是要输出的端口值
* EntryParameter :(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
* ReturnValue    : NO
**************************************************************************************/
void GPIOSetMutiDir(GPIO_TypeDef *GPIOx,uint32_t GPIO_PIN_x,uint32_t t)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(t)
	{
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;;
	}
	else
	{
		  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	}
	GPIO_InitStruct.Pin = GPIO_PIN_x;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}



/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t j)
* Description    : 输出多个位，GPIO_Pin_Position为要输出的位，PortVal是要输出的端口值
* EntryParameter :(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
* ReturnValue    : NO
**************************************************************************************/
void GPIOSetValue(GPIO_TypeDef *GPIOx,uint32_t GPIO_PIN_x,uint8_t t)
{
	if(t)
	{
		 HAL_GPIO_WritePin(GPIOx,GPIO_PIN_x,GPIO_PIN_SET);
	}
	else
  {
		 HAL_GPIO_WritePin(GPIOx,GPIO_PIN_x,GPIO_PIN_RESET);
	}
}


/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t j)
* Description    : 输出多个位，GPIO_Pin_Position为要输出的位，PortVal是要输出的端口值
* EntryParameter :(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
* ReturnValue    : NO
**************************************************************************************/
void GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
{
	GPIOx->ODR= (PortVal); //数据输出	 
}







/* USER CODE END PFP */

/* USER CODE BEGIN ,0 */
/**************************************************************************************
* FunctionName   : DelayMS(uint x)
* Description    : 延迟毫秒
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void DelayMS(uint8_t x)
{
	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

/**************************************************************************************
* FunctionName   : delay(int t)
* Description    : 延时函数
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void delay(int t)
{
  uint32_t i;
	int j;
	for(j=0;j<t;j++)
	for(i=0;i<250;i++);
}



/**************************************************************************************
* FunctionName   : DelayMS(uint x)
* Description    : 延迟微秒
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void DelayUs(unsigned int d)
{
    int k;
		while(--d)
		{
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;k=1;k=0;
			k=1;k=0;k=1;k=0;k=1;k=0;
		}
}






/**************************************************************************************
* FunctionName   : SET_SDA(uint8_t i)    
* Description    : 设置SDA输出高低电平
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void SET_SDA(uint8_t i)       
{ 
  
	GPIOSetDir(IIC_PORT,SDA_PIN,1);
	if(i)
  {
		
    GPIOSetValue(IIC_PORT,SDA_PIN,1);
	}
	else
	{
		
    GPIOSetValue(IIC_PORT,SDA_PIN,0);
	}
	
	delay(3);
}


/**************************************************************************************
* FunctionName   : SET_SCK(uint8_t i)      
* Description    : 设置SCK输出高低电平
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void SET_SCK(uint8_t i)       
{ 
 
	GPIOSetDir(IIC_PORT,SCK_PIN,1);
	if(i)
  {
	  
    GPIOSetValue(IIC_PORT,SCK_PIN,1);
	}
	else
	{
		
    GPIOSetValue(IIC_PORT,SCK_PIN,0);
	}
	
	delay(3);
}


/**************************************************************************************
* FunctionName   : GET_SDA(void)  
* Description    : 查询SDA
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
uint8_t GET_SDA(void)       
{
	uint8_t k;
	GPIOSetDir(IIC_PORT,SDA_PIN,0);
	k=HAL_GPIO_ReadPin(IIC_PORT,SDA_PIN);
	delay(3);
	return k; 
}




/**************************************************************************************
* FunctionName   : IIC_init(void)
* Description    : 初始化IIC
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void IIC_init(void)
{
	SET_SDA(1); 
	delay(5);
	SET_SCK(1); 
	delay(5);
}




/**************************************************************************************
* FunctionName   : Start(void)
* Description    : 
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void Start(void)
{
 	SET_SDA(1); 
	SET_SCK(1);     
	delay(5);
	SET_SDA(0);
	delay(5);
	SET_SCK(0); 
	
}





/**************************************************************************************
* FunctionName   : Stop(void)
* Description    : 
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void Stop(void)
{
 	SET_SDA(0);
	delay(1);
	SET_SCK(0); 
	delay(5);
	SET_SCK(1); 
	delay(5);
	SET_SDA(1); 
	
}





/**************************************************************************************
* FunctionName   : RACK(void)
* Description    : 
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void RACK(void)
{
 	SET_SDA(1); 
	delay(5);
	SET_SCK(1); 
	delay(5);
	SET_SCK(0); 
	
}






/**************************************************************************************
* FunctionName   : NO_ACK(void)
* Description    : 
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void NO_ACK(void)
{
 	SET_SDA(1);
	delay(1);
	SET_SCK(1); 
	delay(5);
	SET_SCK(0); 
	delay(1);
	SET_SDA(0);
}






/**************************************************************************************
* FunctionName   : Write_A_Byte(uchar b)
* Description    : 写一个字符
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void Write_A_Byte(uchar b)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
		if(b&0x80)
		{
			SET_SDA(1); 
		}
		else
    {
			SET_SDA(0);
	  }
		DelayUs(1);
		SET_SCK(1); 
		DelayUs(1);
		SET_SCK(0); 
		b<<=1;
		DelayUs(1);
	}
	RACK();
}






/**************************************************************************************
* FunctionName   : Write_IIC(uchar addr,uchar dat)
* Description    : 向地址ADDR写一个字节
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
void Write_IIC(uchar addr,uchar dat)
{
 	Start();
	Write_A_Byte(0xa0);
	Write_A_Byte(addr);
	Write_A_Byte(dat);
	Stop();
	DelayUs(100);
}





/**************************************************************************************
* FunctionName   : Receive_A_Byte()
* Description    : 读一个字节
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
uchar Receive_A_Byte()
{
 	uchar i,d=0;
	for(i=0;i<8;i++)
	{
	 	SET_SCK(1); 
		d<<=1;
		d|=GET_SDA();
		SET_SCK(0);
	}
	return d;
}




/**************************************************************************************
* FunctionName   : Read_Current()
* Description    : 读取当前地址
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
uchar Read_Current()
{
 	uchar d;
	Start();
	Write_A_Byte(0xa1);
	d=Receive_A_Byte();
	NO_ACK();
	Stop();
	return d;
}



/**************************************************************************************
* FunctionName   : Random_Read(uchar addr)
* Description    : 读取地址Addr内容
* EntryParameter : NO
* ReturnValue    : NO
**************************************************************************************/
uchar Random_Read(uchar addr)
{
 	Start();
	Write_A_Byte(0xa0);
	Write_A_Byte(addr);
	Stop();
	return Read_Current();		
}


/* USER CODE END 0 */



/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  uint8_t Buff=0,Buff1=0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  IIC_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 
  
			Write_IIC(0X89,21);                  //向地址0x0089写入数据21
      
	    Buff=Random_Read(0X89);              //读地址0x0089数据
			DisplayByte[0]=(Buff/10);
			DisplayByte[1]=(Buff%10);
			Write_IIC(0X78,20);                  //向地址0x0078写入数据20
     
	    Buff=Random_Read(0X78);              //读地址0x0078数据
		  DisplayByte[2]=(Buff/10);
			DisplayByte[3]=(Buff%10);	
      while(1)
			{
			  GPIOSetMutiValue(DS_COM_PORT,COM_PIN_1,0x1);//位选择
			  GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DisplayByte[0]]);//字符显示
			  delay(20);
			        
			  GPIOSetMutiValue(DS_COM_PORT,COM_PIN_2,0x2);//位选择
			  GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DisplayByte[1]]);//字符显示
			  delay(20);
			        
			      
			  GPIOSetMutiValue(DS_COM_PORT,COM_PIN_3,0x4);//位选择
			  GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DisplayByte[2]]);//字符显示
			  delay(20);
			        
			  GPIOSetMutiValue(DS_COM_PORT,COM_PIN_4,0x8);//位选择
			  GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DisplayByte[3]]);//字符显示
				delay(20);
			}

			        
			        
			 	 
  /* USER CODE BEGIN 3 */

  
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
