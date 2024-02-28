/*
 * vSPI.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Administrator
 */

#ifndef INC_VSPI_H_
#define INC_VSPI_H_

void delay_us(uint16_t n)
{
	uint16_t i=n*8; //8MHz，对应1/8微秒
	while(i--);
}

/*****************
SPI总线使能
*****************/
void vSPI_En()
{
	HAL_GPIO_WritePin(GPIOA, vCE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);
	delay_us(4);
}

/*****************
SPI总线禁止
*****************/
void vSPI_Dis()
{
	HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, vCE_Pin, GPIO_PIN_RESET);
}

/*****************
SPI主站发送1个字节
形参：
dat——发送的字节
*****************/
void vSPI_SndByte(uint8_t dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);delay_us(4);
		if(dat & 0x80)
			HAL_GPIO_WritePin(GPIOA, vMOSI_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(GPIOA, vMOSI_Pin, GPIO_PIN_RESET);
		dat<<=1;
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);delay_us(4);  //上升沿
	}
}

/*****************
SPI主站接收1个字节
返回值：返回的1个字节数据
*****************/
uint8_t vSPI_RcvByte()
{
	uint8_t i,dat=0;
	for(i=0;i<8;i++)
	{
		delay_us(4);
		dat<<=1;
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_RESET);
		if(HAL_GPIO_ReadPin(GPIOA,vMISO_Pin)==GPIO_PIN_SET)
			dat |= 0x01;
		else
			dat &= 0xfe;
		HAL_GPIO_WritePin(GPIOA, vSCK_Pin, GPIO_PIN_SET);
	}
	return dat;
}

#endif /* INC_VSPI_H_ */
