/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */



	 
#define SPI595_x                                 SPI1
#define SPI595_x_RCC_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPI595_x_RCC_CLK_DISABLE()               __HAL_RCC_SPI1_CLK_DISABLE()

#define SPI595__GPIO_ClK_ENABLE()                __HAL_RCC_GPIOA_CLK_ENABLE() 
#define SPI595__GPIO_PORT                        GPIOA
#define SPI595__SCK_PIN                          GPIO_PIN_5
#define SPI595__MISO_PIN                         GPIO_PIN_6
#define SPI595__MOSI_PIN                         GPIO_PIN_7

#define SPI595__CS_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()    
#define SPI595__CS_PORT                          GPIOA
#define SPI595__CS_PIN                           GPIO_PIN_4

#define SPI595__CS_ENABLE()                      HAL_GPIO_WritePin(SPI595__CS_PORT, SPI595__CS_PIN, GPIO_PIN_RESET)
#define SPI595__CS_DISABLE()                     HAL_GPIO_WritePin(SPI595__CS_PORT, SPI595__CS_PIN, GPIO_PIN_SET)	 
	 
 extern uint8_t TMP_Buffer[256];
 extern uint16_t Buffer_LEN;
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_SPI1_Init(void);
uint8_t WriteByte(uint8_t byte);
uint8_t Read_SPI_Status(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
