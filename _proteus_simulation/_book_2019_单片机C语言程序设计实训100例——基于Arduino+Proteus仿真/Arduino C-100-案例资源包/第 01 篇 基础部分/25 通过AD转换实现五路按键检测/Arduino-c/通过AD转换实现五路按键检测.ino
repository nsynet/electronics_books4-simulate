//-----------------------------------------------------------------
//  名称: 通过A/D转换实现五路按键检测
//-----------------------------------------------------------------
//  说明: 电路设计中添加了一组分压电阻，各按键连接在不同的分压电阻位置，在按下
//       不同按键时，输入到A0引脚的模拟电压也不同，由此通过A/D转换即可实现
//       按键扫描判断。
//
//-----------------------------------------------------------------
//电阻	阻值		按键	A0输入电压	计算公式	A0输入电压	推算AD值
//R1	2000	K1	0			0			0
//R2	330		K2	R2/(R1+R2)*5 0.708154506	145.0300429
//R3	620		K3	(R2+R3)/(R1+R2+R3)*5 1.610169492	329.7627119
//R4	1000	K4	(R2+R3+R4)/(R1+R2+R3+R4)*5	2.46835443	505.5189873
//R5	3300	K5	(R2+R3+R4+R5)/(R1+R2+R3+R4+R5)*5	3.620689655	741.5172414
//const uint16_t  KEY_ADC[] ={0, 145, 330,  506, 741, 1023 }; 
//取相邻AD值的中间点以消除噪声及电阻误差
const uint16_t KEY_ADC[] ={ 0, 73, 237, 417, 623, 882 };
int Key_ADC;		//各按键按下时对应的A/D值（无键按下时AD值为1023）
int NUM_KEYS = 5;	//按键个数（对应K1～K5）
int key = -1;		//按键序号
int oldkey = -1;
//-----------------------------------------------------------------
// 初始配置
//-----------------------------------------------------------------
void setup() {

}
//-----------------------------------------------------------------
// 主循环
//-----------------------------------------------------------------
void loop() {

}
//-----------------------------------------------------------------
// 根据A/D值获取按键序号
//-----------------------------------------------------------------
void scan_keys() {
	//从A0通道读取A/D转换值（0～1023）
	int Key_ADC = analogRead(0);



 
}
//-----------------------------------------------------------------
// 根据A/D值数据查表返回按键索引(返回K1~K5)
//-----------------------------------------------------------------
int get_key(uint16_t _ADCx) {

}