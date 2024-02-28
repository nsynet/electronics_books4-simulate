//-----------------------------------------------------------------
// 名称: SD卡驱动程序
//-----------------------------------------------------------------
#include "sd.h"
#include "myfun.h" 
#include "uart.h"
//变量定义
//-----------------------------------------------------------------
bit is_init;
u8 Addr_Mode = 0;
u8 SD_Ver = SD_VER_ERR;
//-----------------------------------------------------------------
u8 bdata _dat;
sbit _dat7 = _dat ^ 7;
sbit _dat6 = _dat ^ 6;
sbit _dat5 = _dat ^ 5;
sbit _dat4 = _dat ^ 4;
sbit _dat3 = _dat ^ 3;
sbit _dat2 = _dat ^ 2;
sbit _dat1 = _dat ^ 1;
sbit _dat0 = _dat ^ 0;
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void Delay5us() {	//@22.1184MHz
	u8 i = 52;	while (--i);
}
void Delay3us() {			//@22.1184MHz/STC15W
	//u8 i = 30; while (--i);
}
void Delay220us() {		//@22.1184MHz/STC15W
	u8 i = 10, j = 60;
	do {
		while (--j);
	} while (--i);
}
void Delay130us() {		//@22.1184MHz/STC15W
	u8 i = 6, j = 150;
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
#define MAIN_Fosc 21118400L
void delay_ms(u8 ms) {
	u16 i;
	do {
		i = MAIN_Fosc / 13000;
		while (--i) ;
	} while (--ms);
}
void Delay1ms() {	//@22.1184MHz
	u8 i = 46, j = 128;	_nop_();	_nop_();
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
//根据is_init值决定延时长延时或短延时
#define DL() {if(is_init) Delay220us(); else Delay3us();}
//-----------------------------------------------------------------
u8 IO_SPI_Init() {	// 对SPI有关初始化 
	P1M1 = 0xF0;			// 1111 0000	 // 设置P1.5.6.7.8 开漏输出
	P1M0 = 0xF0;			// 1111 0000	
	SPI_CLK 	= 1;
	SPI_MISO	= 1;
	return 0;
}
//-----------------------------------------------------------------
// 向SPI写一个字节x，t控制时钟
//-----------------------------------------------------------------
void W_BYTE(u8 x) {
	u8 i = 0;
	for (i = 0x80; i != 0x00; i >>= 1) 	{
		SPI_CLK = 1; DL();
		if (x & i) SPI_MOSI = 1; else SPI_MOSI = 0; DL();
		SPI_CLK = 0; DL();
	}
	SPI_CLK = 1;
}
//-----------------------------------------------------------------
// 从SPI读一个字节并返回
//-----------------------------------------------------------------
u8 R_BYTE() {
	u8 i, x = 0x00;
	DL(); SPI_CLK = 1; DL();
	for (i = 0x80; i != 0x00; i >>= 1) {
		SPI_CLK = 0; DL();
		SPI_CLK = 1; DL();
		if (SPI_MISO) x |= i; DL();
	}
	SPI_CLK = 1; DL();
	return x;
}
//-----------------------------------------------------------------
// 向SD卡写6字节命令
//-----------------------------------------------------------------
u8 SD_Write_Cmd(u8* pcmd) {
	u8 temp, time = 0;
	SPI_CS = 1;
	W_BYTE(0xFF);
	SPI_CS = 0;
	while (0xFF != R_BYTE());
	W_BYTE(pcmd[0]);
	W_BYTE(pcmd[1]);
	W_BYTE(pcmd[2]);
	W_BYTE(pcmd[3]);
	W_BYTE(pcmd[4]);
	W_BYTE(pcmd[5]);
	if (pcmd[0] == 0x1C) R_BYTE();
	do {
		temp = R_BYTE();
		time++;
	} while ((temp == 0xFF) && (time < TRY_TIME));
	return (temp);
}
//-----------------------------------------------------------------
// SD卡初始化
//-----------------------------------------------------------------
u8 SD_Init() {
	u8 time = 0, temp = 0, i = 0;
	u8 rbuf[4] = { 0 }; 
//CMD0，将SD卡从默认上电后的SD模式切换到SPI模式，使SD卡进入IDLE状态
	u8 pCMD0[6] = { 0x40, 0x00, 0x00, 0x00, 0x00, 0x95 };
	//CMD1，MMC卡使用CMD1命令进行初始化
	u8 pCMD1[6] = { 0x41, 0x00, 0x00, 0x00, 0x00, 0x01 };
	//CMD8，鉴别SD卡版本
	u8 pCMD8[6] = { 0x48, 0x00, 0x00, 0x01, 0xAA, 0x87 };
	//CMD16，设置扇区大小为512字节
	u8 pCMD16[6] = { 0x50, 0x00, 0x00, 0x02, 0x00, 0x01 };
	//CMD55，告知SD卡后面是ACMD
	u8 pCMD55[6] = { 0x77, 0x00, 0x00, 0x00, 0x00, 0x01 }; 
	//ACMD41,检测SD卡是否初始化完成
	u8 pACMD41H[6] = { 0x69, 0x40, 0x00, 0x00, 0x00, 0x01 };
	//ACMD41,检测SD卡是否初始化完成
	u8 pACMD41S[6] = { 0x69, 0x00, 0x00, 0x00, 0x00, 0x01 };
	//CMD58，SD2.0底是SDHC，还是普通的SD卡
	u8 pCMD58[6] = { 0x7A, 0x00, 0x00, 0x00, 0x00, 0x01 }; 
	//--------------SD卡开始复位，使用CMD0命令 --------------------
	IO_SPI_Init();
	is_init = 1;
	SPI_CS = 1;
	for (i = 0; i < 15; i++) W_BYTE(0xFF);
	time = 0;
	do {
		temp = SD_Write_Cmd(pCMD0);
		if (++time == TRY_TIME) {
			return (INIT_CMD0_ERROR);	
		}
	} while (temp != 0x01); 
	//--------------------- SD卡复位结束 ---------------------------
	//写入CMD8，如果返回值为1，则SD卡版本为2.0
	if (1 == SD_Write_Cmd(pCMD8))	{
		rbuf[0] = R_BYTE(); rbuf[1] = R_BYTE(); 
		rbuf[2] = R_BYTE(); rbuf[3] = R_BYTE();
		if (rbuf[2] == 0x01 && rbuf[3] == 0xAA) {
			time = 0;
			do {
				SD_Write_Cmd(pCMD55);
				temp = SD_Write_Cmd(pACMD41H);
				time++;
				if (time >= TRY_TIME) {
					return (INIT_SDV2_ACMD41_ERROR);
				}
			} while (temp != 0x00);

			if (0 == SD_Write_Cmd(pCMD58)) {
				rbuf[0] = R_BYTE(); rbuf[1] = R_BYTE();
				rbuf[2] = R_BYTE(); rbuf[3] = R_BYTE();
				if (rbuf[0] & 0x40) {
					SD_Ver = SD_VER_V2HC;
					Addr_Mode = 1; 
				}
				else SD_Ver = SD_VER_V2;
			}
		}
	}
	else {//SD V1.0或MMC 
		SD_Write_Cmd(pCMD55);
		temp = SD_Write_Cmd(pACMD41S); 
		if (temp <= 1)
		{
			SD_Ver = SD_VER_V1; 
			time = 0;
			do
			{
				SD_Write_Cmd(pCMD55);
				temp = SD_Write_Cmd(pACMD41S);
				time++;
				if (time >= TRY_TIME)	{
					return (INIT_SDV1_ACMD41_ERROR);
				}
			} while (temp != 0);
		}
		else
		{
			SD_Ver = SD_VER_MMC;
			time = 0;
			do
			{
				temp = SD_Write_Cmd(pCMD1);
				time++;
				if (time >= TRY_TIME)
				{
					return (INIT_CMD1_ERROR);
				}
			} while (temp != 0);
		}
	}
	if (0 != SD_Write_Cmd(pCMD16))
	{
		SD_Ver = SD_VER_ERR;
		return INIT_ERROR;
	}
	SPI_CS = 1;
	W_BYTE(0xFF);
	is_init = 0;
	return 0;
}
//-----------------------------------------------------------------
// 向指定扇区地址写入512字节数据
//-----------------------------------------------------------------
u8 SD_Write_Sector(u32 addr, u8* buffer) {
	u8 temp, time; u16 i;
	u8 pCMD24[] = { 0x58, 0x00, 0x00, 0x00, 0x00, 0xff }; 
	if (!Addr_Mode) addr <<= 9; 
	pCMD24[1] = addr >> 24;
	pCMD24[2] = addr >> 16;
	pCMD24[3] = addr >> 8;
	pCMD24[4] = addr;
	time = 0;
	do {
		temp = SD_Write_Cmd(pCMD24);
		time++;
		if (time == TRY_TIME)	{
			return (temp);
		}
	} while (temp != 0);
	while (0xFF != R_BYTE());
	W_BYTE(0xFE);
	for (i = 0; i < 512; i++) W_BYTE(buffer[i]);
	W_BYTE(0xFF); W_BYTE(0xFF);
	temp = R_BYTE();
	if ((temp & 0x1F) != 0x05){
		return (WRITE_BLOCK_ERROR);
	}
	while (0xFF != R_BYTE()) ; 
	SPI_CS = 1;
	W_BYTE(0xFF);
	return 0;
}
//-----------------------------------------------------------------
// 从指定扇区地址读取512字节数据
//-----------------------------------------------------------------
u8 SD_Read_Sector(u32 addr, u8* buffer) {
	u16 i;
	u8 time, temp;
	u8 pCMD17[] = { 0x51, 0x00, 0x00, 0x00, 0x00, 0x01 }; 
	if (!Addr_Mode) addr <<= 9; 
	pCMD17[1] = addr >> 24;
	pCMD17[2] = addr >> 16;
	pCMD17[3] = addr >> 8;
	pCMD17[4] = addr;
	time = 0;
	do {
		temp = SD_Write_Cmd(pCMD17); 
		time++;
		if (time == TRY_TIME) {
			return (READ_BLOCK_ERROR);
		}
	} while (temp != 0);
	while (R_BYTE() != 0xFE) ;
	for (i = 0; i < 512; i++) buffer[i] = R_BYTE();
	R_BYTE();	R_BYTE();
	SPI_CS = 1;
	W_BYTE(0xFF);
	return 0;
}
