/**
 * 软件 I2C 函数库
 * 来源：改编自《时间触发嵌入式系统设计模式》中相关章节
 * 最后更新：2014-07-17
 * http://blanboom.org
 */

#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H

#include "config.h"

#define I2C_READ      0x01    // Read command
#define I2C_WRITE     0x00    // Write command

#define I2C_OK         0
#define I2C_ERROR      1

void  I2C_Send_Start(void);        
void  I2C_Send_Stop(void);         

uint8_t I2C_Write_Byte(uint8_t); 
uint8_t I2C_Read_Byte(void);

void I2C_Send_Master_Ack(void);
void I2C_Send_Master_NAck(void);

#endif