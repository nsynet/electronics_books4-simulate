//-----------------------------------------------------------------
//  名称: 用Tone实现的按键控制多段音乐选播
//-----------------------------------------------------------------
//  说明: 本例内置三段音乐曲目,K1用于控制音乐播放,停止,切换.
//
//-----------------------------------------------------------------
#define K1	   2					//按键引脚
#define BEEP  19					//蜂鸣器引脚
//-----------------------------------------------------------------
const int TONE_FRQ[] =				//C调15个音符频率表
{ 0,262,294,330,349,392,440,494,523,587,659,698,784,880,988,1046 };
//当前曲目索引,音符索引,运行状态
volatile int Song_idx = 3, Tone_idx = 0, running = 0;
//三段曲目音符(这些数据是任意编写的,根据需要可以自行修改)
const int Song[][50] = {
 {1,2,3,1,1,2,3,1,3,4,5,3,4,5,5,6,5,3,5,6,5,3,5,3,2,1,2,1,-1},
 {3,3,3,4,5,5,5,5,6,5,3,5,3,2,1,5,6,5,3,3,2,1,1,-1},
 {3,2,1,3,2,1,1,2,3,1,1,2,3,1,3,4,5,3,4,5,5,6,5,3,5,3,2,1,3,2,1,1,-1}
};
//三段曲目节拍
const int Len[][50] = {
 {1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,2,-1},
 {1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,2,-1},
 {1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,2,-1}
};
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
// 按键中断：控制两个定时器的启停，实现LED滚动及报警声输出的开关控制
//-----------------------------------------------------------------
void ISR_INT0() {	

}