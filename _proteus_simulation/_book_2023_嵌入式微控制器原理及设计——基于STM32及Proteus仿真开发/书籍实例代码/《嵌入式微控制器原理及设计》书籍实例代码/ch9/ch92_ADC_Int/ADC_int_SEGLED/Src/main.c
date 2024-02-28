/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
	/*
@file	��Ƕ��ʽ΢������ԭ����ơ��鼮������:��ʢ�� Email:picy@scut.edu.cn  ���ӹ�ҵ�����磩����ʵ�� ch9.2
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "gpio.h"
#define  DSPORT GPIOA

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
 int8_t DISPLAY_Buffer[]={0,0,0,0};
 uint8_t NixieTubeBit[]={0xc0,0xF9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
 uint16_t ADC_Value=0;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
float Value=0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 
/**************************************************************************************
* FunctionName   : GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t j)
* Description    : ������λ��GPIO_Pin_PositionΪҪ�����λ��PortVal��Ҫ����Ķ˿�ֵ
* EntryParameter :(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
* ReturnValue    : NO
**************************************************************************************/
void GPIOSetMutiValue(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Position ,uint16_t PortVal)
{
	uint8_t i=0;
	uint16_t k=0;
	uint16_t b=0x0001;
	k=GPIO_Pin_Position & PortVal;
	for(i=0;i<8;i++)
	{
	  if(k&(0x01))
		{
			HAL_GPIO_WritePin(GPIOx,b,GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOx,b,GPIO_PIN_RESET);
		}
		b<<=1;
		k>>=1;
	}		 
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
 uint8_t k,l;
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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_Delay(10);
  /* USER CODE END 2 */
   HAL_ADC_Start_IT(&hadc1);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_Delay(12);
    Value =(float)ADC_Value*3.3/4096;  /* 3.3ΪADת���Ĳο���ѹֵ��stm32��ADת��Ϊ12bit��2^12=4096����������Ϊ3.3Vʱ��ADת�����Ϊ4096 */
		
		k=(uint8_t)Value;//ת����ֵ������ʾ
		l=(uint8_t)((Value-k)*100);//��ʾ��������
		DISPLAY_Buffer[0]=k/10;//ʮλ
		DISPLAY_Buffer[1]=k%10;	//��λ
		DISPLAY_Buffer[2]=l/10;//С����1λ
		DISPLAY_Buffer[3]=l%10;//С����2λ
		GPIOSetMutiValue(GPIOB,0XFF,0x1);//�ַ���ʾ
		GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DISPLAY_Buffer[0]]);//�ַ���ʾ
		HAL_Delay(12);
			   
		GPIOSetMutiValue(GPIOB,0XFF,0x2);//�ַ���ʾ
		GPIOSetMutiValue(DSPORT,0XFF,(NixieTubeBit[DISPLAY_Buffer[1]])&0x7F);//�ַ���ʾ
		HAL_Delay(12);
		
		GPIOSetMutiValue(GPIOB,0XFF,0x8);//�ַ���ʾ
		GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DISPLAY_Buffer[2]]);//�ַ���ʾ
		HAL_Delay(12);
			   
		GPIOSetMutiValue(GPIOB,0XFF,0x10);//�ַ���ʾ
		GPIOSetMutiValue(DSPORT,0XFF,NixieTubeBit[DISPLAY_Buffer[3]]);//�ַ���ʾ
		HAL_Delay(8);
  }
  /* USER CODE END 3 */
}
/*********************************************************************
  * ��������: ADת�������ص�����
  * �������: hadc��AD�豸���;��
  * �� �� ֵ: ��
  * ˵    ��: ��
  ********************************************************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  ADC_Value = HAL_ADC_GetValue(&hadc1);
} 

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
