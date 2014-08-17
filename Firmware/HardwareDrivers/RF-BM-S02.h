/**
 * RF-BM-S02 驱动
 * 模块简介：
 *     蓝牙4.0模块，可通过串口与 MCU 通信
 * 作者：    Blanboom
 * 最后更新：2014-07-20
 * http://blanboom.org
 ***************************************
 * 模块 RX 接单片机 P3.7，模块 TX 接单片机 P3.6
 * 同时需要在 "PinDef.h" 中定义引脚 EN, BRTS 和 BCTS，即：
 *         RF_BM_S02_EN
 *         RF_BM_S02_BRTS
 *         RF_BM_S02_BCTS
 * 使用了单片机的 UART1 和 定时器 2
 * 接收到的数据存储在 UART1 的 Buffer 中，具体见 "USART.h"
 */
 
#ifndef __RF_BM_S02_H
#define __RF_BM_S02_H

#include "config.h"

#define RF_BM_S02_OK      0
#define RF_BM_S02_ERROR   1
#define RF_BM_S02_NO_DATA 2

uint8_t RF_BM_S02_Init(void);


#endif