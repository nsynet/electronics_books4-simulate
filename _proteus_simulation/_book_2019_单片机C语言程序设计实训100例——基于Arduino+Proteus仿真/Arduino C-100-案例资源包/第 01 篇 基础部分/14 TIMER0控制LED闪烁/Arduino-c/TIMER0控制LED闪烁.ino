//-----------------------------------------------------------------
//  名称: TIMER0控制LED闪烁
//-----------------------------------------------------------------
//  说明: 本例用TIMER0定时器溢出中断控制实现,开始编译前要按后面的说明屏蔽
//       wiring.c中的有关内容，否则将导致编译失败。
//       另外要注意在编译通过后，一定要将wiring.c还原到原始状态，以免影响
//       延时函数的应用。
//
//-----------------------------------------------------------------
// 初始配置
//-----------------------------------------------------------------
void setup() {

}
//-----------------------------------------------------------------
// 主循环
//-----------------------------------------------------------------
void loop() {							//与控制两组LED闪烁的定时中断“并行”

}
 //-----------------------------------------------------------------
 // 定时器初始配置
 //-----------------------------------------------------------------
void Init_TIMER0() {
							//使能中断
}
//-----------------------------------------------------------------
// TIMER0中断函数
//-----------------------------------------------------------------
ISR(TIMER0_OVF_vect) {

}
