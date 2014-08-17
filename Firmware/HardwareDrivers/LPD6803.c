/**
 * LPD6803 驱动
 * 芯片简介：
 *     3 路 LED 控制芯片
 * 来源：程序来自 LPD6803 数据手册
 * 最后更新：2014-07-18
 * http://blanboom.org
 *********************************************
 * 使用本程序时，需要在 PinDef.h 中
 * 定义 HV57708 的各个引脚，具体请参考 LPD6803.h
 *********************************************
 * 本程序只适合单片 LPD6803，不适合多片芯片级联的情况
 */
 
#include "LPD6803.h"

#include "PinDef.h"

/**
 * void LPD6803_LEDLightUp(uint8_t dr, uint8_t dg, uint8_t db)
 * 简介：以指定的参数点亮 LED
 * 功能：向 LPD6803 发送三路 LED 的亮度数据，并点亮 LED
 * 输入：
 *       dr, dg, db 分别为三路 LED 的亮度数据，范围是 0 ~ 31
 * 输出：无
 */
void LPD6803_LEDLightUp(uint8_t dg, uint8_t dr, uint8_t db)
{
	uint8_t j;
	uint16_t mask;
	
	// first output 32 start frame
	LPD6803_DCLK = 0;
	LPD6803_DIN = 0;
	
	for(j = 0; j < 32; j++)
	{
		LPD6803_DCLK = 1;
		LPD6803_DCLK = 0;
	}

	LPD6803_DIN  = 1;
	LPD6803_DCLK = 1;
	LPD6803_DCLK = 0;

	// output 5 bits red data 
	mask = 0x10;
	for(j = 0; j < 5; j++)
	{
		if(mask & dr)
		{
			LPD6803_DIN = 1;
		}
		else
		{
			LPD6803_DIN = 0;
		}
		LPD6803_DCLK = 1;
		LPD6803_DCLK = 0;
		mask >>= 1;
	}

	// output 5 bits green data 
	mask=0x10;
	for(j = 0; j < 5; j++)
	{
		if(mask & dg)
		{
			LPD6803_DIN = 1;
		}
		else
		{		
			LPD6803_DIN = 0;
		}
		LPD6803_DCLK = 1;
		LPD6803_DCLK = 0;
		mask >>= 1;
	}


	// output 5bits blue data
	mask = 0x10;
	for(j = 0; j < 5; j++)
	{
		if(mask & db)
		{
			LPD6803_DIN = 1;
		}
		else
		{
			LPD6803_DIN = 0;
		}
		LPD6803_DCLK = 1;
		LPD6803_DCLK = 0;
		mask >>= 1;
	}

	LPD6803_DIN = 0;
	LPD6803_DCLK = 1;
	LPD6803_DCLK = 0;
	// transport data finish
	_nop_();
	_nop_();
	_nop_();
}