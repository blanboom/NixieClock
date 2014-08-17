/**
 * SD2405ALPI 驱动
 * 芯片简介：
 *       内置电池和晶振和 I2C 总线的实时时钟，数据以 8421BCD 码的形式储存
 * 作者：    Blanboom
 * 最后更新：2014-07-17
 * http://blanboom.org
 *********************************************
 * 使用本程序时，需要在 PinDef.h 中
 * 定义 I2C_SDA 和 I2C_SCL 两个 I2C 引脚
 */
 
#include "SD2405ALPI.h"
#include "delay.h"
#include "Soft_I2C.h"

/**
 * uint32_t SD2405ALPI_GetTime(void)
 * 简介：从 SD2405ALPI 获取当前时间
 * 输入：无
 * 输出：当前时间（HHMMSS）
 */
uint32_t SD2405ALPI_GetTime(void)
{
	uint32_t time = 0;
	uint8_t tmp = 0;
	// 发送需要读取的地址
  // I2C_Send_Start();
  // I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_WRITE);
  // I2C_Write_Byte(SD2405ALPI_SECOND_ADDRESS);
	
	// 开始读取数据
	I2C_Send_Start();
	I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_READ);
	
	tmp = I2C_Read_Byte();
	time += (tmp & 0x0f) + ((tmp & 0xf0) >> 4) * 10;
	I2C_Send_Master_Ack();
	
	tmp = I2C_Read_Byte();
	time += ((tmp & 0x0f) + ((tmp & 0xf0) >> 4) * 10) * 100;
	I2C_Send_Master_Ack();
	
	tmp = I2C_Read_Byte();
	time += ((tmp & 0x0f) + ((tmp & 0x70) >> 4) * 10) * 10000ul;
	
	// 停止
	I2C_Send_Master_Ack();
	I2C_Send_Stop();
	
	return time;
}

/**
 * void SD2405ALPI_SetTime(uint32_t time)
 * 简介：调整 SD2405ALPI 内部时间
 * 输入：当前时间（HHMMSS）
 * 输出：无
 */
void SD2405ALPI_SetTime(uint32_t time)
{
	// 写允许
	I2C_Send_Start();
	I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_WRITE);
	I2C_Write_Byte(SD2405ALPI_CTR2_ADDRESS);
	I2C_Write_Byte(0x80);
	I2C_Send_Stop();
	I2C_Send_Start();
	I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_WRITE);
	I2C_Write_Byte(SD2405ALPI_CTR1_ADDRESS);
	I2C_Write_Byte(0x84);
	I2C_Send_Stop();
	
	
	// 写入时间
	I2C_Send_Start();
	I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_WRITE);
	I2C_Write_Byte(SD2405ALPI_SECOND_ADDRESS);
	I2C_Write_Byte((time % 100) / 10 | (time % 10) << 4);
	I2C_Write_Byte((time % 1000) / 100 | ((time % 10000) / 1000) << 4);
	I2C_Write_Byte((time % 100000ul) / 10000 | ((time / 100000ul)) << 4 | 0x80);
	I2C_Send_Stop();
	
	
	// 写禁止
	I2C_Send_Start();
	I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_WRITE);
	I2C_Write_Byte(SD2405ALPI_CTR1_ADDRESS);
	I2C_Write_Byte(0x00);
	I2C_Send_Stop();
	I2C_Send_Start();
	I2C_Write_Byte(SD2405ALPI_DEVICE_ADDRESS | I2C_WRITE);
	I2C_Write_Byte(SD2405ALPI_CTR2_ADDRESS);
	I2C_Write_Byte(0x00);
	I2C_Send_Stop();
}