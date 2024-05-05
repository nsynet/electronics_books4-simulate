
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
@file	��Ƕ��ʽ΢������ԭ����ơ��鼮������:��ʢ�� Email:picy@scut.edu.cn  ���ӹ�ҵ�����磩����ʵ��ch7.6
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#define u8 unsigned char
#define u16 uint16_t

#define	HC595_nCS	 	  GPIO_PIN_4			//HC595_nCS = PA4
#define	HC595_RCK 		GPIO_PIN_1		  //HC595_RCK = PA1

#define	COM1	 		GPIO_PIN_8			//COM1 = PB8
#define	COM2 			GPIO_PIN_9			//COM2 = PB9
#define	COM3	 		GPIO_PIN_10			//COM3 = PB10
#define	COM4 			GPIO_PIN_11			//COM4 = PB11


/* USER CODE BEGIN Includes */
/* USER CODE END Includes */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

u8 const NixieTubeBit[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//�����0~9




/*******************************************************************************
* Function Name  : ��ʱ����
* Description    : SEG��������ţ�SPI1���ų�ʼ��
* Input          : None
* Return         : None
*******************************************************************************/
void Delay_Ms2(u16 time)  
{ 
	u16 i,j;
	for(i=0;i<time;i++)
  		for(j=1000;j>0;j--);
}


/*******************************************************************************
* Function Name  : Delay_Ms
* Description    : delay 1 ms.
* Input          : time (ms)
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_Ms(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  for(j=1000;j>0;j--);
}



/*******************************************************************************

* Function Name  : SEG_Init
* Description    : SEG��������ţ�SPI1���ų�ʼ��
* Input          : None
* Return         : None
*******************************************************************************/
void	SEG_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;	// ����һ��IO�ڽṹ�����
    //==========PA��IO�ṹ���ʼ��============
  	GPIO_InitStruct.Pin	= HC595_nCS|HC595_RCK;	  //ѡ��PA.0��PA.1
  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;	//�ܽ�Ƶ��Ϊ50MHZ
  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	  //ģʽΪ�������
  	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);   		//��ʼ��GPIOA�Ĵ���
	
	  //==========PB��IO�ṹ���ʼ��============
  	GPIO_InitStruct.Pin	= COM1|COM3|COM2|COM4;	  //ѡ��PB.15
  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;	//�ܽ�Ƶ��Ϊ50MHZ
  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	  //ģʽΪ�������
  	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);   	  //��ʼ��GPIOB�Ĵ���

	  //==========PA��IO�ṹ���ʼ�����
    HAL_GPIO_WritePin(GPIOA, HC595_nCS, GPIO_PIN_RESET);
}	




/*******************************************************************************
* Function Name  : SEG_BitSelect
* Description    : ѡ������ܵ�λѡ
* Input          : data  ѡ����	��data��ȡֵΪ0x01,0x02,0x04,0x08
* Return         : None
*******************************************************************************/
void SEG_BitSelect(u8 data)
{
	if((data & 0x01) != 0)	HAL_GPIO_WritePin(GPIOB, COM1,GPIO_PIN_SET);	// ����smgA1 = PC8
	else		HAL_GPIO_WritePin(GPIOB, COM1,GPIO_PIN_RESET);
	if((data & 0x02) != 0)	HAL_GPIO_WritePin(GPIOB, COM2,GPIO_PIN_SET);	// ����smgA2 = PB15
	else		HAL_GPIO_WritePin(GPIOB, COM2,GPIO_PIN_RESET);
	if((data & 0x04) != 0)	HAL_GPIO_WritePin(GPIOB, COM3,GPIO_PIN_SET);	// ����smgA3 = PC9
	else		HAL_GPIO_WritePin(GPIOB, COM3,GPIO_PIN_RESET);
	if((data & 0x08) != 0)	HAL_GPIO_WritePin(GPIOB, COM4,GPIO_PIN_SET);	// ����smgA4 = PE8
	else		HAL_GPIO_WritePin(GPIOB, COM4,GPIO_PIN_RESET);
}



/*******************************************************************************
* Function Name  : SEG_Display
* Description    : �������ʾ4λ����
* Input          : data		��Ҫ��ʾ������
*			             radix_point	С�����λ�ã�ȡֵ��ΧΪ4��3��2
* Return         : None
*******************************************************************************/
void	SEG_Display(u16 data,u8 radix_point)
{
	u16 one,ten,hundred,thousand;		//����ʮ���٣�ǧ���ı�������
	thousand = data / 1000;					//����ǧλ
	if(thousand != 0)   data -= thousand*1000;
	hundred = data / 100;					//�����λ
	if(hundred != 0) data -= hundred*100; 	
	ten = data / 10;					//����ʮλ
	if(ten != 0) data -= ten*10; 		
	one = data % 10;					//�����λ
	//-------------------��ʾǧλ����----------------
	
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_RESET);
 	if(radix_point==4)		WriteByte(NixieTubeBit[thousand]& 0x7f);
 	else			WriteByte(NixieTubeBit[thousand] );
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_SET);
	
	SEG_BitSelect(0x01);	//�������λѡ��
	
	Delay_Ms2(100); //С����ʱ
	SEG_BitSelect(0x00);	//�ر���ʾ
	//-------------------��ʾ��λ����----------------
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_RESET);
	if(radix_point==3)		WriteByte(NixieTubeBit[hundred] & 0x7f);
	else			WriteByte(NixieTubeBit[hundred] );
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_SET);
	SEG_BitSelect(0x02);		
	Delay_Ms2(100);
	SEG_BitSelect(0x00);	//�ر���ʾ

	//-------------------��ʾʮλ����----------------
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_RESET);
	if(radix_point==2)		WriteByte(NixieTubeBit[ten] & 0x7f);
	else			WriteByte(NixieTubeBit[ten] );
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_SET);
	SEG_BitSelect(0x04);
	Delay_Ms2(100);
	SEG_BitSelect(0x00);	//�ر���ʾ	

	//-------------------��ʾ��λ����----------------
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_RESET);
 	WriteByte(NixieTubeBit[one] );
	HAL_GPIO_WritePin(GPIOA, HC595_RCK,GPIO_PIN_SET);
	SEG_BitSelect(0x08);
	Delay_Ms2(500);
	SEG_BitSelect(0x00);	//�ر���ʾ
}	


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */



/* USER CODE END 0 */






/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
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
  MX_GPIO_Init();//ʹ��IOʱ��
  MX_SPI1_Init();//��ʼ��SPI1������
  SEG_Init();    //�������ʾ��ʼ��
	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
		
		SEG_Display(2021,0);  //��ʾ����2021
		//SEG_Display(0505,0);  //��ʾ����10.08
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

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
void assert_failed(uint8_t* file, uint32_t line)
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
