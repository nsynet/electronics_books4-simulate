/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdarg.h>
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"
#include "hanzi.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

//#include "lv_font.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define LV_USE_GAUGE 1
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim10;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

void DashBoard(void) {
	//ʱ��
	  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(0,0,255), LV_PART_MAIN);//���ó�ʼ����Ļ��ɫ
    lv_obj_t* meter = lv_meter_create(lv_scr_act());  //���岢�����Ǳ�
    lv_obj_set_size(meter, 180, 180);       //�����Ǳ��ȸ߶�
    lv_obj_set_x(meter, 30);
    lv_obj_set_y(meter, 95);
	  lv_obj_set_style_bg_color(meter, lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_meter_scale_t* scale_min = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_min, 61, 1, 5, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);
    lv_meter_scale_t* scale_hour = lv_meter_add_scale(meter);   //���岢��ӿ̶�
    lv_meter_set_scale_ticks(meter, scale_hour, 12, 1, 1, lv_palette_main(LV_PALETTE_PINK));    //����С�̶�
    lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 2, 10, lv_color_hex(0x00ff00), 10);          //�������̶�
    lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);
    lv_meter_indicator_t* indic_hour;
    indic_hour = lv_meter_add_needle_line(meter, scale_hour, 6,lv_palette_main(LV_PALETTE_BLUE), -30); 
	//����Ǳ�ָ��
    lv_meter_set_indicator_value(meter, indic_hour,11);      //����ָ��ָ�����ֵ
    lv_meter_indicator_t* indic_min;
    indic_min = lv_meter_add_needle_line(meter, scale_min, 3,lv_palette_main(LV_PALETTE_RED), -10);
    lv_meter_set_indicator_value(meter, indic_min,59);

//	  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(0,0,255), LV_PART_MAIN);//���ó�ʼ����Ļ��ɫ
//    lv_obj_t* meter = lv_meter_create(lv_scr_act());  //�����Ǳ� 
//    lv_obj_set_width(meter, scr_act_height() * 0.4);  //�����Ǳ���    
//    lv_obj_set_height(meter, scr_act_height() * 0.4); //�����Ǳ�߶� 
//    
//    lv_obj_center(meter);
//    //lv_obj_set_style_bg_color(meter, lv_color_make(0,0,0), LV_PART_MAIN);//���ÿؼ�����ɫ
//	  lv_obj_set_style_bg_color(meter, lv_color_hex(0x00ff00), LV_PART_MAIN);
//    //�����Ǳ�̶� 
//    lv_meter_scale_t* scale = lv_meter_add_scale(meter); //��ӿ̶� 
//    lv_meter_set_scale_ticks(meter, scale, 41, 1, scr_act_height() / 80,
//                             lv_color_hex(0xdf5345));//LV_PALETTE_GREY));
//    lv_meter_set_scale_major_ticks(meter, scale, 8, 1, scr_act_height() / 60,
//                                   lv_color_hex(0x00ff00), scr_act_height() / 30);
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Display_init() {
    ILI9341_Unselect();
    ILI9341_TouchUnselect();
    ILI9341_Init();
}

void ILI9341_Show_Chinese( uint16_t x, uint16_t y, uint8_t* font, uint8_t size, uint32_t fColor, uint32_t bColor)
{
    uint8_t temp;
	uint16_t y0=y;   
	uint8_t csize=(size/8+((size%8)?1:0))*(size);	// �õ�����һ���ַ���Ӧ������ռ���ֽ���	
	for(uint8_t t=0; t<csize; t++)
	{   												   
		temp = font[t];			                                          
		for(uint8_t t1=0; t1<8; t1++)
		{
			if(temp&0x80)   ILI9341_DrawPixel(x, y, fColor);	
            else            ILI9341_DrawPixel(x, y, bColor);            
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}      
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM10)                     // �ж����ĸ�TIM�������ж�
    {
    	 // ���������LVGL����������
        lv_tick_inc(1);                             // ��LVGL�ṩ1ms������ʱ��

    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
  Display_init(); 
	lv_init();                  // lvgl��ʼ
  lv_port_disp_init();        // ��ʾ����ʼ��
  lv_port_indev_init();       // �����豸��ʼ
   HAL_TIM_Base_Init(&htim10);
   HAL_TIM_Base_Start_IT(&htim10); // ʹ���ж�ģʽ����TIM10
	 DashBoard();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
		lv_task_handler();
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 24-1;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 240-1;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
