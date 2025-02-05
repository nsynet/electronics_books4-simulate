/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//共阳极数码管0~f的段码
const uint8_t SegmentCodes[]=
{
0xc0,0xf9,0xa4,0xb0,0x99,
0x92,0x82,0xf8,0x80,0x90,
0x88,0x83,0xc6,0xa1,0x86,0x8e
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void ByteOut2PC(uint8_t dat);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t KeyValue=0x10;  //按下的键码
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //扫描第一行
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,0);
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=0;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=1;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=2;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=3;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0);
		  HAL_Delay(20);
	  }
	  //扫描第二行
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,1);
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,0);
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=4;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=5;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=6;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=7;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0);
		  HAL_Delay(20);
	  }
	  //扫描第三行
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,1);
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,0);
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=8;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=9;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=10;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=11;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0);
		  HAL_Delay(20);
	  }
	  //扫描第四行
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,1);
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=12;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=13;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=14;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==0);
		  HAL_Delay(20);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0)
	  {
		  HAL_Delay(20);
		  KeyValue=15;
		  while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==0);
		  HAL_Delay(20);
	  }
	  if(KeyValue>=0 && KeyValue<=0xf)ByteOut2PC(SegmentCodes[KeyValue]);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_SET);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3 
                           PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//自定义函数，将1个字节的数据输出到PC端口的PC0~PC7
void ByteOut2PC(uint8_t dat)
{
	if(dat & 0x01)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,0);
	if(dat & 0x02)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,0);
	if(dat & 0x04)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,0);
	if(dat & 0x08)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,0);
	if(dat & 0x10)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,0);
	if(dat & 0x20)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,0);
	if(dat & 0x40)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,0);
	if(dat & 0x80)HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,1);
	else          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,0);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
