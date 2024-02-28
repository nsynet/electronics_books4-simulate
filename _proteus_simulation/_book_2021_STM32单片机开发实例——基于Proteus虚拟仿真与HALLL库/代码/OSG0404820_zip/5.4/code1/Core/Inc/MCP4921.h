/*
 * MCP4921.h
 *
 *  Created on: 2020年9月20日
 *      Author: Administrator
 */

#ifndef INC_MCP4921_H_
#define INC_MCP4921_H_
/*****************************************
写入MCP4921
形参：
Cmd：指令，仅高四位
Dat：数据，12位
*****************************************/
void MCP4921Write(uint8_t Cmd,uint16_t Dat)
{
	uint8_t DatM,DatL;  //数据高字节、低字节
	DatL=(uint8_t)(Dat & 0x00ff);
	DatM=(uint8_t)((Dat>>8) & 0x00ff);
	vSPI_En();
	/* 先写高字节 */
	vSPI_SndByte(0x70|DatM);
	/* 再写低字节 */
	vSPI_SndByte(DatL);
	vSPI_Dis();
}


#endif /* INC_MCP4921_H_ */
