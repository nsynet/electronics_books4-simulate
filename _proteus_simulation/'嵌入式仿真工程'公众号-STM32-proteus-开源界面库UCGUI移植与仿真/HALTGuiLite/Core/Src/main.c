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
#include "GUI.h"
#include "math.h"
#include <stdio.h>
#include <string.h>
#include "button.h"
//#include "GUI_Window.h"
//#define GUILITE_ON	//Do not define this macro once more!!!
//#include "GuiLite.h"
/* USER CODE BEGIN Includes */
////#include "key.h"
////#include "led.h"
//#include "../../ICore/print/print.h"
//#include "../../ICore/usart/usart.h"
//#include "../../ICore/oled/oled.h"
/* USER CODE END Includes */
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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE BEGIN 0 */
//Transfer GuiLite 32 bits color to your LCD color
#define GL_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))
//Encapsulate your LCD driver:
void gfx_draw_pixel(int x, int y, unsigned int rgb)
{
    //LCD_Fast_DrawPoint(x, y, GL_RGB_32_to_16(rgb));//注释参考样例的
	ILI9341_DrawPixel((uint16_t)x, (uint16_t)y, GL_RGB_32_to_16(rgb));//新增本工程支持绘制点函数调用(oled.h)
}
//Implement it, if you have more fast solution than drawing pixels one by one.
//void gfx_fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb){}
 
//UI entry
struct DISPLAY_DRIVER
{
	void (*draw_pixel)(int x, int y, unsigned int rgb);
	void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} my_driver;
extern void startHello3D(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver);
/* USER CODE END 0 */
void Display_init() {
    ILI9341_Unselect();
    ILI9341_TouchUnselect();
    ILI9341_Init();
}

void ILI9341_Show_Chinese( uint16_t x, uint16_t y, uint8_t* font, uint8_t size, uint32_t fColor, uint32_t bColor)
{
    uint8_t temp;
	uint16_t y0=y;   
	uint8_t csize=(size/8+((size%8)?1:0))*(size);	// 得到字体一个字符对应点阵集所占的字节数	
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
void ShowColorBar(void)
 {
     int x0 = 60, y0 = 40, yStep = 15, i;
     int NumColors = LCD_GetDevCap(LCD_DEVCAP_NUMCOLORS);
     int xsize = LCD_GetDevCap(LCD_DEVCAP_XSIZE) - x0;
     GUI_SetFont(&GUI_Font13HB_1);
     GUI_DispStringHCenterAt("μC/GUI-sample:Show color bars", 160, 0);
     GUI_SetFont(&GUI_Font8x8);
     GUI_SetColor(GUI_WHITE);
     GUI_SetBkColor(GUI_BLACK);
     #if(LCD_FIXEDPALETTE)
         GUI_DispString("Fixed palette: ");
         GUI_DispDecMin(LCD_FIXEDPALETTE);
     #endif
     GUI_DispStringAt("Red", 0, y0 + yStep);
     GUI_DispStringAt("Green", 0, y0 + 3 * yStep);
     GUI_DispStringAt("Blue", 0, y0 + 5 * yStep);
     GUI_DispStringAt("Grey", 0, y0 + 6 * yStep);
     GUI_DispStringAt("Yellow", 0, y0 + 8 * yStep);
     GUI_DispStringAt("Cyan", 0, y0 + 10 * yStep);
     GUI_DispStringAt("Magenta", 0, y0 + 12 * yStep);
     for(i=0; i < xsize; i++)
     {
         U16 cs =(255 *(U32)i) / xsize;
         U16 x = x0 + i;
         /* 红色 */
         GUI_SetColor(cs);
         GUI_DrawVLine(x, y0, y0 +yStep - 1);
         GUI_SetColor(0xff +(255 - cs) * 0x10100L);
         GUI_DrawVLine(x, y0 +yStep, y0 + 2 * yStep - 1);
         /* 绿色 */
         GUI_SetColor(cs<<8);
         GUI_DrawVLine(x, y0 + 2 * yStep, y0 + 3 * yStep - 1);
         GUI_SetColor(0xff00 +(255 - cs) * 0x10001L);
         GUI_DrawVLine(x, y0 + 3 * yStep, y0 + 4 * yStep - 1);
         /* 蓝色 */
         GUI_SetColor(cs * 0x10000L);
         GUI_DrawVLine(x, y0 + 4 * yStep, y0 + 5 * yStep - 1);
         GUI_SetColor(0xff0000 +(255 - cs) * 0x101L);
         GUI_DrawVLine(x, y0 + 5 * yStep, y0 + 6 * yStep - 1);
         /* 灰色 */
         GUI_SetColor((U32)cs * 0x10101L);
         GUI_DrawVLine(x, y0 + 6 * yStep, y0 + 7 * yStep - 1);
         /* 黄色 */
         GUI_SetColor(cs * 0x101);
         GUI_DrawVLine(x, y0 + 7 * yStep, y0 + 8 * yStep - 1);
         GUI_SetColor(0xffff +(255 - cs) * 0x10000L);
         GUI_DrawVLine(x, y0 + 8 * yStep, y0 + 9 * yStep - 1);
         /* 青色 */
         GUI_SetColor(cs * 0x10100L);
         GUI_DrawVLine(x, y0 + 9 * yStep, y0 + 10 * yStep - 1);
         GUI_SetColor(0xffff00 +(255 - cs) * 0x1L);
         GUI_DrawVLine(x, y0 + 10 * yStep, y0 + 11 * yStep - 1);
         /* 洋红 */
         GUI_SetColor(cs * 0x10001);
         GUI_DrawVLine(x, y0 + 11 * yStep, y0 + 12 * yStep - 1);
         GUI_SetColor(0xff00ff +(255 - cs) * 0x100L);
         GUI_DrawVLine(x, y0 + 12 * yStep, y0 + 13 * yStep - 1);
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
   BUTTON_Handle hButton;//按钮句柄
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  Display_init(); 
	//ILI9341_FillScreen(ILI9341_CYAN);
	GUI_Init();//GUI初始化
		GUI_SetBkColor(GUI_CYAN); // 背景颜色
	GUI_SetColor(GUI_RED);     // 画笔颜色
	GUI_Clear();               // 清屏
	 ShowColorBar();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
