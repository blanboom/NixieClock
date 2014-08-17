/**
 * 显示相关函数, 包括数字及小数点的显示，以及全彩 LED 颜色的控制
 * 作者：    Blanboom
 * 最后更新：2014-07-21
 * http://blanboom.org
 */
 
#include "Display.h"
#include "app.h"
#include "PinDef.h"
#include "delay.h"
#include "HV57708.h"
#include "LPD6803.h"

// 要显示的数字所在位置
const uint8_t numbers[][10] = {
	{24, 25, 26, 27, 20, 21, 22, 23, 16, 17},
  {18, 19, 12, 13, 14, 15, 8,  9,  10, 11},
  {4,  5,  6,  7,  0,  1,  2,  3,  60, 61},
  {62, 63, 56, 57, 58, 59, 52, 53, 54, 55},
  {48, 49, 50, 51, 44, 45, 46, 47, 40, 41},
  {42, 43, 36, 37, 38, 39, 32, 33, 34, 35}
};


/**
 * void displayInit(void)
 * 简介：显示初始化
 * 输入：无
 * 输出：无
 */
void displayInit(void)
{
	HV57708_Init(HV57708_MODE_INVERTION);  // 将 HV57708 初始化为反相输出模式
	
	// 闪烁一下氖灯
  NEON |= DISPLAY_DOTS_ALL;
	
	LPD6803_LEDLightUp(0, 0, 31);
	//displayNumber(654321);
}

/**
 * void displayNumber(uint32_t)
 * 简介：显示数字
 * 功能：发送数字到 HV57708
 * 输入：6 位十进制数
 * 输出：无
 */
void displayNumber(uint32_t number)
{
	uint32_t data_part2  = 0;
	uint32_t data_part1  = 0;
	uint8_t tmp_number = 0;
	
	tmp_number = numbers[0][number / 100000ul];
	data_part1 |= 1ul << tmp_number;
	
	tmp_number = numbers[1][(number % 100000ul) / 10000ul];
	data_part1 |= 1ul << tmp_number;
	
	tmp_number = numbers[2][(number % 10000ul) / 1000ul];
	if(tmp_number < 32)
	{
		data_part1 |= 1ul << tmp_number;
	}
	else
	{
		data_part2 |= 1ul << (tmp_number - 32);
	}
		
	tmp_number = numbers[3][(number % 1000) / 100];
  data_part2 |= 1ul << (tmp_number - 32);
	
	tmp_number = numbers[5][(number % 100) / 10];
	data_part2 |= 1ul << (tmp_number - 32);
	
	tmp_number = numbers[4][number % 10];       // 在数组中调换两行的位置不行，不知道是哪里出问题了
	data_part2 |= 1ul << (tmp_number - 32);
	
	HV57708_SendData(data_part2, data_part1);
	HV57708_OutputData();
}

/**
 * void displayTime(void)
 * 简介：显示时间
 * 功能：发送时间显示数据到 HV57708，时间在全局变量中储存
 * 输入：无
 * 输出：无
 */
void displayTime(void)
{
	displayNumber(hour * 10000ul + minute * 100ul + second);
}

/**
 * void displayDots(uint8_t dots)
 * 简介：显示点
 * 输入：要显示的点，具体请参考 "Display.h"
 * 输出：无
 */
void displayDots(uint8_t dots)
{
	NEON &= 0xf0;
	NEON |= dots;
}


/**
 * void ledUpdate(uint8_t dg, uint8_t dr, uint8_t db)
 * 简介：LED 颜色更新函数
 * 输入：dr, dg, db 分别为三路 LED 的亮度数据，范围是 0 ~ 31
 * 输出：无
 */
void ledUpdate(uint8_t dg, uint8_t dr, uint8_t db)
{
	LPD6803_LEDLightUp(dg, dr, db);
}