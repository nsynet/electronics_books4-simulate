/*
 * TC72.h
 *
 *  Created on: Sep 19, 2020
 *      Author: Administrator
 */

#ifndef INC_TC72_H_
#define INC_TC72_H_

/* 宏定义 */
#define _TC72_CTRL_R  0x00  //控制寄存器地址（读）
#define _TC72_CTRL_W  0x80  //控制寄存器地址（写）
#define _TC72_Dat_LSB 0x01  //温度低字节地址（读）
#define _TC72_Dat_MSB 0x02  //温度高字节地址（读）
#define _TC72_ID      0x03  //制造商ID（读）
#define _TC72_OnceCnv      0x15  //单次转化指令
#define _TC72_ContinueCnv  0x05  //连续转化指令

/*****************
发送转化指令
形参：
Instr——指令
*****************/
void TC72_Convert(uint8_t Instr)
{
	vSPI_En();
	vSPI_SndByte(_TC72_CTRL_W);
	vSPI_SndByte(Instr);
	vSPI_Dis();
}

/*****************
读温度
返回值：温度值
*****************/
float TC72_TemperatureRd()
{
	uint8_t DatL,DatM;
	int16_t Dat;
	float t;
	vSPI_En();
	vSPI_SndByte(_TC72_Dat_MSB);
	DatM=vSPI_RcvByte();
	DatL=vSPI_RcvByte();
	vSPI_Dis();
	Dat=DatM;
	Dat<<=8;
	Dat+=DatL;
	t=((float)(Dat))/256;
	return t;
}

#endif /* INC_TC72_H_ */
