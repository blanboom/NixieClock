/**
 * 软件延时程序
 * 来源：STC 官方函数库
 * 最后更新：2014-07-18
 * http://blanboom.org
 */

#include	"delay.h"


/**
 * void  Delay_ms(uint8_t ms)
 * 简介：1ms 延时函数，自动适应主时钟
 * 输入：ms: 要延时的 ms 数
 * 输出：无
 */
void Delay_ms(uint8_t ms)
{
	uint16_t i;
	do
	{
		i = MAIN_Fosc / 13000;
		while(--i)	;   //14T per loop
	}while(--ms);
}
