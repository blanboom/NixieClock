/**
 * SD2405ALPI 驱动
 * 芯片简介：
 *       内置电池和晶振和 I2C 总线的实时时钟，数据以 8421BCD 码的形式储存
 * 作者： Blanboom
 * 最后更新：2014-07-17
 * http://blanboom.org
 *********************************************
 * 使用本程序时，需要在 PinDef.h 中
 * 定义 I2C_SDA 和 I2C_SCL 两个 I2C 引脚
 */
 
#ifndef __SD2405ALPI_H
#define __SD2405ALPI_H

#include "config.h"

/**
 * SD2405ALPI 设备地址
 * 最后一位为 0，使用时要与 I2C_READ 或 I2C_WRITE 进行按位或运算
 */
#define SD2405ALPI_DEVICE_ADDRESS 0x64

// SD2405ALPI 内部寄存器地址
// 实时时钟寄存器
#define SD2405ALPI_SECOND_ADDRESS 0x00
#define SD2405ALPI_MINUTE_ADDRESS 0x01
#define SD2405ALPI_HOUR_ADDRESS   0x02
#define SD2405ALPI_WEEK_ADDRESS   0x03
#define SD2405ALPI_DAY_ADDRESS    0x04
#define SD2405ALPI_MONTH_ADDRESS  0x05
#define SD2405ALPI_YEAR_ADDRESS   0x06
// 时间报警寄存器
#define SD2405ALPI_SECOND_ALARM_ADDRESS 0x07
#define SD2405ALPI_MINUTE_ALARM_ADDRESS 0x08
#define SD2405ALPI_HOUR_ALARM_ADDRESS   0x09
#define SD2405ALPI_WEEK_ALARM_ADDRESS   0x0A
#define SD2405ALPI_DAY_ALARM_ADDRESS    0x0B
#define SD2405ALPI_MONTH_ALARM_ADDRESS  0x0C
#define SD2405ALPI_YEAR_ALARM_ADDRESS   0x0D
#define SD2405ALPI_ALARM_ENABLE_ADDRESS 0x0E
// 控制寄存器
#define SD2405ALPI_CTR1_ADDRESS            0x0F
#define SD2405ALPI_CTR2_ADDRESS            0x10
#define SD2405ALPI_CTR3_ADDRESS            0x11
#define SD2405ALPI_TIME_SETTING_ADDRESS    0x12
#define SD2405ALPI_COUNTING_DOWN_ADDRESS   0x13


uint32_t SD2405ALPI_GetTime(void);
void  SD2405ALPI_SetTime(uint32_t);

#endif