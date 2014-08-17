/**
 * 时间更新相关函数
 * 作者：    Blanboom
 * 最后更新：2014-07-21
 * http://blanboom.org
 **************************
 * 使用时应根据时钟频率调整定时器初值
 */
 
#include "TimeUpdate.h"

#include "timer.h"
#include "app.h"

/**
 * void timerInit(void)
 * 简介：初始化计时用的定时器
 * 输入：无
 * 输出：无
 */
void timerInit(void)
{
	TIM_InitTypeDef		TIM_InitStructure;
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReloadNoMask; // 16 位自动重装，不可屏蔽中断
	TIM_InitStructure.TIM_Polity    = PolityLow;			
	TIM_InitStructure.TIM_Interrupt = ENABLE;
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;  // 12T 模式
	TIM_InitStructure.TIM_ClkOut    = DISABLE;
	TIM_InitStructure.TIM_Value     = 0x3cb0;         // 25ms @ 24.000MHz
	TIM_InitStructure.TIM_Run       = ENABLE;
	Timer_Inilize(Timer0, &TIM_InitStructure);
}

/**
 * void timeUpdate_ISR(void)
 * 简介：计时用的定时器的 ISR
 * 输入：无
 * 输出：无
 */
void timeUpdate_ISR(void) interrupt TIMER0_VECTOR
{
	per25ms++;
	if(per25ms >= 40)
	{
    per25ms = 0;
		second++;
	}
	if(second >= 60)
	{
		second = 0;
		minute++;
	}
	if(minute >= 60)
	{
		minute = 0;
		hour++;
	}
	if(hour >= 24)
	{
		hour = 0;
	}
}