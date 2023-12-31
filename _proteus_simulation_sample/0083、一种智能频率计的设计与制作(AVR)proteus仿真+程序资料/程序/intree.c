//SIGNAL 执行时全局中断触发位被清除、其他中断被禁止
//INTERRUPT 执行时全局中断触发位被置位、其他中断可嵌套执

#ifndef interr_c
  #define interr_c
  #include "main.h"

//-------------------------------------------------------------------------
//       //t0中断
//-------------------------------------------------------------------------
  SIGNAL( SIG_OUTPUT_COMPARE0 )
  {
    static uint counter = 0; 

    if ( ++counter == 64000 )
//如果1s到
    {
      TCCR0 = 0; 
      TCCR1B = 0; 
      counter = 0; 
      flg1 = 0xff; //标志

    }
  }
//-------------------------------------------------------------------------
//       //t1中断 
//-------------------------------------------------------------------------
  SIGNAL( SIG_OUTPUT_COMPARE1A ) //T1输出比较A匹配中断
  {
    SREG |= 0X80; //开中断
    ++t1_cont; //累加 

  }

#endif
