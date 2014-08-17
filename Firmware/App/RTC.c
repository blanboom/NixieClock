/**
 * 实时时钟读写相关函数
 * 作者：    Blanboom
 * 最后更新：2014-07-21
 * http://blanboom.org
 */
 
#include "RTC.h"
#include "SD2405ALPI.h"
#include "app.h"

/**
 * void getTime(void)
 * 简介：将实时时钟的时间发送至单片机
 * 输入：无
 * 输出：无
 */
void getTime(void)
{
	uint32_t time = 0;
	time = SD2405ALPI_GetTime();
	hour = (time / 100000ul) * 10 + (time % 100000ul) / 10000ul;
	minute = ((time % 10000ul) / 1000)* 10 + (time % 1000) / 100;
	second = ((time % 100) / 10)* 10 + (time % 10);
}

/**
 * void syncTime(void)
 * 简介：将单片机的时间同步到实时时钟
 * 输入：无
 * 输出：无
 */
void syncTime(void)
{
	SD2405ALPI_SetTime(hour * 10000ul + minute * 100 + second);
}