/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VLD_Pin GPIO_PIN_0
#define VLD_GPIO_Port GPIOC
#define VLM_Pin GPIO_PIN_1
#define VLM_GPIO_Port GPIOC
#define VLU_Pin GPIO_PIN_2
#define VLU_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_0
#define LED0_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOA
#define LED5_Pin GPIO_PIN_5
#define LED5_GPIO_Port GPIOA
#define LED6_Pin GPIO_PIN_6
#define LED6_GPIO_Port GPIOA
#define HDLM_Pin GPIO_PIN_0
#define HDLM_GPIO_Port GPIOB
#define HDLU_Pin GPIO_PIN_1
#define HDLU_GPIO_Port GPIOB
#define HDRD_Pin GPIO_PIN_2
#define HDRD_GPIO_Port GPIOB
#define VDLD_Pin GPIO_PIN_10
#define VDLD_GPIO_Port GPIOB
#define HLD_Pin GPIO_PIN_12
#define HLD_GPIO_Port GPIOB
#define HLM_Pin GPIO_PIN_13
#define HLM_GPIO_Port GPIOB
#define HLU_Pin GPIO_PIN_14
#define HLU_GPIO_Port GPIOB
#define HDLD_Pin GPIO_PIN_15
#define HDLD_GPIO_Port GPIOB
#define HDRM_Pin GPIO_PIN_3
#define HDRM_GPIO_Port GPIOB
#define HDRU_Pin GPIO_PIN_4
#define HDRU_GPIO_Port GPIOB
#define VDRD_Pin GPIO_PIN_5
#define VDRD_GPIO_Port GPIOB
#define VDRM_Pin GPIO_PIN_6
#define VDRM_GPIO_Port GPIOB
#define VDRU_Pin GPIO_PIN_7
#define VDRU_GPIO_Port GPIOB
#define VDLU_Pin GPIO_PIN_8
#define VDLU_GPIO_Port GPIOB
#define VDLM_Pin GPIO_PIN_9
#define VDLM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
