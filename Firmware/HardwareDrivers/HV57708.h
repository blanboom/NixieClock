/**
 * HV57708驱动
 * 芯片简介：
 *     32MHz, 64通道推挽输出串入并出芯片
 *     内有 4 个 并行的 16 位移位寄存器
 * 作者：    Blanboom
 * 最后更新：2014-07-17
 * http://blanboom.org
 */

#ifndef __HV57708_H
#define __HV57708_H

#include "config.h"

#define HV57708_MODE_NORMAL 1
#define HV57708_MODE_INVERTION 0

void HV57708_Init(uint8_t HV57708_Mode);
void HV57708_SendData(uint32_t datapart1, uint32_t datapart2);
void HV57708_OutputData(void);

#endif