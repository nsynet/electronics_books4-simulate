/*
 * vI2C.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Administrator
 */

#ifndef VI2C_H_
#define VI2C_H_

void delay_us(uint16_t n)
{
	uint16_t i=n*8; //8MHz，对应1/8微秒
	while(i--);
}

void Pin_vSDA_Mode(char status)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(GPIOB, vSDA_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = vSDA_Pin;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	if(status=='I') //Input
	{
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	}
	else if(status=='O') //Output
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	}
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void vSCL_Out(uint8_t dat)
{
	switch(dat)
	{
		//case 1:HAL_GPIO_WritePin(GPIOB, vSCL_Pin, GPIO_PIN_SET)  ;break;
		case  0:HAL_GPIO_WritePin(GPIOB, vSCL_Pin, GPIO_PIN_RESET);break;
		default:HAL_GPIO_WritePin(GPIOB, vSCL_Pin, GPIO_PIN_SET)  ;
	}
}

void vSDA_Out(uint8_t dat)
{
	//Pin_vSDA_Mode('O');
	switch(dat)
	{
		//case 1:HAL_GPIO_WritePin(GPIOB, vSDA_Pin, GPIO_PIN_SET)  ;break;
		case  0:HAL_GPIO_WritePin(GPIOB, vSDA_Pin, GPIO_PIN_RESET);break;
		default:HAL_GPIO_WritePin(GPIOB, vSDA_Pin, GPIO_PIN_SET)  ;
	}
}

uint8_t vSDA_In()
{
	GPIO_PinState PinState;
	uint8_t rt;
	//Pin_vSDA_Mode('I');
	PinState=HAL_GPIO_ReadPin(GPIOB,vSDA_Pin);
	switch(PinState)
	{
		//case GPIO_PIN_SET  :rt=1;break;
		case GPIO_PIN_RESET:rt=0;break;
		default:rt=1;
	}
	return rt;
}

//启动I2C通信
void I2C_Start()
{
	Pin_vSDA_Mode('O');
	vSDA_Out(1);
	delay_us(6);//至少延时4.7us
	vSCL_Out(1);
	delay_us(6);//至少延时4.7us
	vSDA_Out(0);
	delay_us(6);//至少延时4us
	vSCL_Out(0);
}

//停止I2C通信
void I2C_Stop()
{
	Pin_vSDA_Mode('O');
	vSDA_Out(0);
	delay_us(6);//至少延时4us
	vSCL_Out(1);
	delay_us(6);//至少延时4us
	vSDA_Out(1);
	delay_us(6);//至少延时4.7us
}

//发送应答
void I2C_Ack()
{
	Pin_vSDA_Mode('O');
	vSDA_Out(0);
	delay_us(6);
	vSCL_Out(1);
	delay_us(6);
    vSCL_Out(0);
    delay_us(6);
    vSDA_Out(1);
    delay_us(6);
}

//写1个字节数据
void I2C_WtByte(uint8_t Dat)
{
    uint8_t i,tmp;
    Pin_vSDA_Mode('O');
    for(i = 0; i < 8; i++)
    {
        tmp=Dat&(0x80>>i);
        vSCL_Out(0);
        delay_us(6);
        (tmp==0)?(vSDA_Out(0)):(vSDA_Out(1));
        delay_us(6);
        vSCL_Out(1);
        delay_us(6);
    }
    vSCL_Out(0);
    delay_us(6);
    vSDA_Out(1);
    delay_us(6);
}

//读1个字节数据
uint8_t I2C_RdByte()
{
    uint8_t Dat = 0, tmp, i;
    Pin_vSDA_Mode('I');
    vSCL_Out(0);
    delay_us(6);
    for(i = 0; i < 8; i++)
    {
    	vSCL_Out(1);
    	delay_us(6);
        tmp = vSDA_In();
        Dat = Dat << 1;
        Dat = Dat | tmp;
        delay_us(6);
        vSCL_Out(0);
        delay_us(6);
    }
    return Dat;
}


#endif /* VI2C_H_ */
