/**
  ******************************************************************************
  * File Name          : I2C.h
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#ifndef __i2c_H
#define __i2c_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */
#define I2C_OWN_ADDRESS                            0x0A              // stm32本机I2C地址
#define EEPROM_I2C_ADDRESS                         0xA0
#define I2C_SPEEDCLOCK                             4000 //400000            // I2C通信速率(最大为400K)
#define I2C_DUTYCYCLE                              I2C_DUTYCYCLE_2   // I2C占空比模式：1/2 

#define EEPROM_I2Cx                                I2C1
#define EEPROM_I2C_RCC_CLK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define EEPROM_I2C_RCC_CLK_DISABLE()               __HAL_RCC_I2C1_CLK_DISABLE()

#define EEPROM_I2C_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOB_CLK_ENABLE()
#define EEPROM_I2C_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOB_CLK_DISABLE()   
#define EEPROM_I2C_GPIO_PORT                       GPIOB   
#define EEPROM_I2C_SCL_PIN                         GPIO_PIN_6
#define EEPROM_I2C_SDA_PIN                         GPIO_PIN_7
/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c_eeprom;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_I2C1_Init(void);

/* USER CODE BEGIN Prototypes */
/* 扩展变量 ------------------------------------------------------------------*/


/* 函数声明 ------------------------------------------------------------------*/
void               I2C_EEPROM_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value);
uint8_t            I2C_EEPROM_ReadData(uint16_t Addr, uint8_t Reg);
HAL_StatusTypeDef  I2C_EEPROM_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
