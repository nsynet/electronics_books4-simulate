//-----------------------------------------------------------------
//  名称: TIMER1、TIMER2及INT0控制报警器与旋转灯
//-----------------------------------------------------------------
//  说明: 定时器控制报警灯旋转显示,并发出仿真警报声.
//
//-----------------------------------------------------------------
#define BEEP 19
const uint8_t LED_Pins[] = { 3, 4, 5, 6, 7, 8, 9, 10 };
uint16_t FRQ = 255; //64分频：250000HZ：256->976HZ，128->976HZ
volatile uint8_t LED_x = B11100000;		//LED滚动特征定义（3只相邻LED）
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
// TIMER1比较匹配中断：控制报警器声音输出
//-----------------------------------------------------------------
ISR(TIMER1_COMPA_vect) {

}
//-----------------------------------------------------------------
// TIMER2比较匹配中断：控制LED旋转
//-----------------------------------------------------------------
ISR (TIMER2_COMPA_vect ) {	

}
//-----------------------------------------------------------------
// 按键中断：控制两个定时器的启停，实现LED滚动及报警声输出的开关控制
//-----------------------------------------------------------------
void ISR_INT0() {

}