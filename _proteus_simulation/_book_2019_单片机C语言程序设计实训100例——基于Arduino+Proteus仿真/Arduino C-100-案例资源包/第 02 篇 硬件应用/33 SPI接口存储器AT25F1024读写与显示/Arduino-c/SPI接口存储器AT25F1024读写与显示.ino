//-----------------------------------------------------------------
//  名称: SPI接口存储器AT25F1024读写与显示
//-----------------------------------------------------------------
//  说明: 程序运行时,按下K1~K4所执行的操作如下:
//        K1: 先清除数据,然后在前面写入256个字节(0x00-0xFF)
//            最末尾写入256个随机字节(中间部分不写入)
//        K2: 读取并显示最前面256个字节(有序)
//        K3: 读取并显示最后面256个字节(无序)
//        K4: 读取并显示厂家/设备ID(AT25F1024A: VID/PID=1F60)
//
//-----------------------------------------------------------------
#include <SPI.h>
SPISettings SPISettings(10000000, MSBFIRST, SPI_MODE0);
#define CS				10		//从机选择控制引脚(对应SS)
#define DATAOUT			11		//MOSI
#define DATAIN			12		//MISO
#define SPICLOCK		13		//SCK
//SPI接口存储器操作命令定义
#define WREN			0x06	//使能写
#define WRDI			0x04	//禁止写
#define RDSR			0x05	//读状态
#define WRSR			0x01	//写状态
#define READ			0x03	//读字节
#define WRITE			0x02	//写字节
#define SECTOR_ERASE	0x52	//删除区域数据
#define CHIP_ERASE		0x62	//删除芯片数据
#define RDID			0x15	//读厂商与产品ID
//按键操作定义
#define K1_DOWN() ((PIND & (1<<4)) == 0x00)	//写入两组字节
#define K2_DOWN() ((PIND & (1<<5)) == 0x00)	//读前20字节并显示
#define K3_DOWN() ((PIND & (1<<6)) == 0x00)	//读后20字节并显示
#define K4_DOWN() ((PIND & (1<<7)) == 0x00)	//显示厂家和产品ID
//LED操作定义
#define LED 8
#define LED_ON()	digitalWrite(LED,LOW)	//LED点亮
#define LED_OFF()	digitalWrite(LED,HIGH)	//LED熄灭
#define LED_BLINK()	PORTB ^=  (1<<0)		//LED闪烁
//读写字节数据的临时存放空间及有效数据长度
uint8_t  TMP_Buffer[256];
uint8_t  Current_Data,Current_Disp_Index = 0,LOOP_SHOW_FLAG = 0, k;
uint16_t Buffer_LEN = 256;
uint32_t i;
//-----------------------------------------------------------------
// 初始配置
//-----------------------------------------------------------------
void setup() {

}
//-----------------------------------------------------------------
// AT25F1024A忙等待
//-----------------------------------------------------------------
void Busy_Wait(){ while(Read_SPI_Status() & 0x01);}	//忙等待
//-----------------------------------------------------------------
// 使能编程
//-----------------------------------------------------------------
void EnableProgramming(){

}
//-----------------------------------------------------------------
// 主循环
//-----------------------------------------------------------------
void loop() {

	
}
//-----------------------------------------------------------------
// 删除AT25F1024A芯片所有区域数据
//-----------------------------------------------------------------
void ChipErase() {

}
//-----------------------------------------------------------------
// 读AT25F1024A芯片状态
//-----------------------------------------------------------------
uint8_t Read_SPI_Status() {

}
//-----------------------------------------------------------------
// 向AT25F1024A写入三个字节的地址0x000000-0x01FFFF 
//-----------------------------------------------------------------
void Write_3_Bytes_SPI_Address(uint32_t addr) {

}
//-----------------------------------------------------------------
// 从指定地址读多字节到缓冲
//-----------------------------------------------------------------
void Read_Bytes_From_AT25F1024A(uint32_t addr, uint8_t *p, uint16_t len){

}
//-----------------------------------------------------------------
// 向AT25F1024A指定地址开始写入多字节数据
//-----------------------------------------------------------------
void Write_Bytes_To_AT25F1024A(uint32_t addr,uint8_t *p,uint16_t len){	

}
//-----------------------------------------------------------------
// 读取AT25F1024A的厂商和产品ID
//-----------------------------------------------------------------
void Get_VID_PID(){ 
	Busy_Wait();							//忙等待
	digitalWrite(CS,LOW);					//片选
	SPI.transfer(RDID);						//发送读取ID指令
	TMP_Buffer[0] = SPI.transfer(0);		//读取厂商代码VID
	TMP_Buffer[1] = SPI.transfer(0);		//读取产品代码PID
	digitalWrite(CS,HIGH);					//禁止片选
}