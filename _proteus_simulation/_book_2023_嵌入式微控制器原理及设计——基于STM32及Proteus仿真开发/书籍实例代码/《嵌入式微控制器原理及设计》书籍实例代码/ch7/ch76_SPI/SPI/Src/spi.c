/**
  ******************************************************************************
  * File Name          : SPI.c
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
SPI_HandleTypeDef hspi1;

/* 私有变量 ------------------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SPI1 init function 
* Description    : 初始化设置SPI的模式
* Input          : void
* Return         : void
*******************************************************************************/
void MX_SPI1_Init(void)
{
  
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;//设置SPI工作模式:设置为主SPI
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;//设置SPI的数据大小:SPI发送接收8位帧结构
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;//选择了串行时钟的稳态:时钟悬空高
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;//数据捕获于第二个时钟沿
  hspi1.Init.NSS = SPI_NSS_SOFT;//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;//定义波特率预分频的值:波特率预分频值为256
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;//CRC值计算的多项式
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  
}



/*******************************************************************************
* Function Name  : HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
* Description    : 初始化设置SPI的GPIO口
* Input          : SPI手柄
* Return         : void
*******************************************************************************/
void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */
    __HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
	
  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */

  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
		
		GPIO_InitStruct.Pin = SPI595__SCK_PIN|SPI595__MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI595__GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI595__MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPI595__GPIO_PORT, &GPIO_InitStruct);
    
    HAL_GPIO_WritePin(SPI595__GPIO_PORT, SPI595__SCK_PIN|SPI595__MOSI_PIN, GPIO_PIN_SET);
		

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END   SPI1_MspInit 1 */
  }
}






/*******************************************************************************
* Function Name  : HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
* Description    : SPI初始化默认配置
* Input          : 
* Return         : 
*******************************************************************************/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */





/************************************************************
  * 函数功能: 写入一个字节数据并接收一个字节数据
  * 输入参数: byte：待发送数据
  * 返 回 值: uint8_t：接收到的数据
  * 说    明：无
  **********************************************************/
uint8_t WriteByte(uint8_t byte)
{
  uint8_t d_read,d_send=byte;
  if(HAL_SPI_TransmitReceive(&hspi1,&d_send,&d_read,1,0xFFFFFF)!=HAL_OK)
  return d_read; 
}



/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
