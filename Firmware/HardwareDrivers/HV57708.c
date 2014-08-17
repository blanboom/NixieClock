/**
 * HV57708驱动
 * 芯片简介：
 *     32MHz, 64通道推挽输出串入并出芯片
 *     内有 4 个 并行的 16 位移位寄存器
 * 作者：    Blanboom
 * 最后更新：2014-07-17
 * http://blanboom.org
 *****************************************************************************
 * 使用本程序时，需要在此处或 PinDef.h 中定义 HV57708 的各个引脚，具体包括：
 *     HV57708_CLK - CLK
 *     HV57708_LE  - LE
 *     HV57708_POL - POL
 *     HV57708_DI1 - Din1/Dout4(A)
 *     HV57708_DI2 - Din2/Dout3(A)
 *     HV57708_DI3 - Din3/Dout2(A)
 *     HV67708_DI4 - Din4/Dout1(A)
 *****************************************************************************
 *     HG57708 的 BL 接高电平，DIR 接低电平时逆时针移存，接高电平时顺时针移存
 */
 
#include "HV57708.h"
#include "PinDef.h"
#include "delay.h"

/**
 * void HV57708_Init(bool HV57708_Mode)
 * 简介：HV57708 初始化
 * 功能：HV57708 初始化，并设置输出模式
 * 输入：
 *       HV57708_Mode:
 *           HV57708_MODE_NORMAL    - 标准输出模式
 *           HV57708_MODE_INVERTION - 反相输出模式
 * 输出：无
 */
void HV57708_Init(uint8_t HV57708_Mode)
{
	 HV57708_CLK = 0;
   HV57708_LE  = 1;
   HV75508_POL = HV57708_Mode;
   HV75508_DI1 = 0;
   HV75508_DI2 = 0;
   HV75508_DI3 = 0;
   HV75508_DI4 = 0;
}

/**
 * void HV57708_SendData(uint32_t datapart1, uint32_t datapart2)
 * 简介：向 HV57708 发送数据
 * 功能：向 HV57708 发送 64 位的数据
 * 输入：
 *       datapart1 - 第一部分数据，32位
 *       datapart2 - 第二部分数据，32位
 * 输出：无
 */
void HV57708_SendData(uint32_t datapart1, uint32_t datapart2)
{
	uint8_t i = 0;
	uint32_t tmp = 0;
	tmp = datapart1;
  for(i = 0; i < 8; i++)
	{
		HV57708_CLK = 0;
		HV75508_DI1 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV75508_DI2 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV75508_DI3 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV75508_DI4 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_CLK = 1;
		_nop_();
		_nop_();
		HV57708_CLK = 0;
		_nop_();
		_nop_();
	}
	tmp = datapart2;
  for(i = 0; i < 8; i++)
	{
		HV57708_CLK = 0;
		HV75508_DI1 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV75508_DI2 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV75508_DI3 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV75508_DI4 = tmp & 0x0001;
		tmp = tmp >> 1;
		HV57708_CLK = 1;
		_nop_();
		_nop_();
		HV57708_CLK = 0;
		_nop_();
		_nop_();
	}
}

/**
 * void HV57708_OutputData(void)
 * 简介：将 HV57708 寄存器中的数据输出至引脚
 * 功能：将 HV57708 寄存器中的数据输出至引脚
 * 输入：无
 * 输出：无
 */
void HV57708_OutputData(void)
{
	HV57708_LE  = 0;
	_nop_();
  _nop_();
	HV57708_LE  = 1;
	_nop_();
  _nop_();
}