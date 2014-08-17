/**
 * LPD6803 驱动
 * 芯片简介：
 *     3 路 LED 控制芯片
 * 来源：程序来自 LPD6803 数据手册
 * 最后更新：2014-07-18
 * http://blanboom.org
 **********************************************
 * 本程序只适合单片 LPD6803，不适合多片芯片级联的情况
 */
 
#ifndef __LPD6803_H
#define __LPD6803_H

#include "config.h"

void LPD6803_LEDLightUp(uint8_t dr, uint8_t dg, uint8_t db);

#endif