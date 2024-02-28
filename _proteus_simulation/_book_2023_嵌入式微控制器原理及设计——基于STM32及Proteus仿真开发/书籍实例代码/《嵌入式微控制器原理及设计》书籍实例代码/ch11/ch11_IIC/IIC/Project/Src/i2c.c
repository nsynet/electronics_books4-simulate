/**
  ******************************************************************************
  * File Name          : I2C.c
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

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c_eeprom;
#define EVAL_I2Cx_TIMEOUT_MAX                   3000
uint32_t I2cxTimeout = EVAL_I2Cx_TIMEOUT_MAX;



/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c_eeprom.Instance = I2C1;
  hi2c_eeprom.Init.ClockSpeed = I2C_SPEEDCLOCK;
  hi2c_eeprom.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c_eeprom.Init.OwnAddress1 = 0;
  hi2c_eeprom.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c_eeprom.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c_eeprom.Init.OwnAddress2 = 0;
  hi2c_eeprom.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c_eeprom.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c_eeprom) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}



void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}



void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
} 



/* USER CODE BEGIN 1 */
/**
  * 函数功能: I2C通信错误处理函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 一般在I2C通信超时时调用该函数
  */
static void I2C_EEPROM_Error (void)
{
  /* 反初始化I2C通信总线 */
  HAL_I2C_DeInit(&hi2c_eeprom);
  
  /* 重新初始化I2C通信总线*/
  MX_I2C1_Init();
}



/**
  * 函数功能: 通过I2C写入一个值到指定寄存器内
  * 输入参数: Addr：I2C设备地址
  *           Reg：目标寄存器
  *           Value：值
  * 返 回 值: 无
  * 说    明: 无
  */
void I2C_EEPROM_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&hi2c_eeprom, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout);
  
  /* 检测I2C通信状态 */
  if(status != HAL_OK)
  {
    /* 调用I2C通信错误处理函数 */
    I2C_EEPROM_Error();
  }
}




/**
  * 函数功能: 通过I2C读取一个指定寄存器内容
  * 输入参数: Addr：I2C设备地址
  *           Reg：目标寄存器
  * 返 回 值: uint8_t：寄存器内容
  * 说    明: 无
  */
uint8_t I2C_EEPROM_ReadData(uint16_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;
  
  status = HAL_I2C_Mem_Read(&hi2c_eeprom, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, I2cxTimeout);
 
  /* 检测I2C通信状态 */
  if(status != HAL_OK)
  {
    /* 调用I2C通信错误处理函数 */
    I2C_EEPROM_Error();
  
  }
  return value;
}



/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
