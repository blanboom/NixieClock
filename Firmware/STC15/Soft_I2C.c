/**
 * 软件 I2C 函数库
 * 来源：改编自《时间触发嵌入式系统设计模式》中相关章节
 * 最后更新：2014-07-17
 * http://blanboom.org
 *********************************************************
 * 注意：
 *       1. I2C_Delay() 需要根据实际硬件调节延时时间
 *       2. I2C_Sync_The_Clock() 可能会因 I2C 总线错误而占用较长时间
 */
 
#include "Soft_I2C.h"
#include "PinDef.h"   // 需要在此文件中定义 I2C 引脚：I2C_SDA, I2C_SCL

// 私有函数定义
static uint8_t I2C_Get_Ack_From_Slave(void); 
static bit     I2C_Sync_The_Clock(void);   
static void    I2C_Delay(void);  

// 如果不需要 ACK 和 NOT ACK，可以将下面一行注释掉
#define I2C_ACK_NACK

/**
 * void I2C_Send_Start(void)
 * 简介：产生 START 状态
 * 输入：无
 * 输出：无
 */
void I2C_Send_Start(void)
{
	I2C_Delay(); 
	// 初始化总线
	I2C_SCL = 1;
	I2C_SDA = 1;
	I2C_Delay(); 

	// 产生 START 状态
	I2C_SDA = 0;
	I2C_Delay();
	I2C_SCL = 0;
	I2C_Delay();
}


/**
 * void I2C_Send_Stop(void)
 * 简介：产生 STOP 状态
 * 输入：无
 * 输出：无
 */
void I2C_Send_Stop(void)
{
	I2C_Delay(); 
	I2C_SDA = 0; 
	I2C_Delay();   
	I2C_SCL = 1; 
	I2C_Delay();   
	I2C_SDA = 1;   
	I2C_Delay(); 
}

/**
 * uint8_t I2C_Get_Ack_From_Slave(void)
 * 简介：等待从机应答
 * 输入：无
 * 输出：
 *       I2C_OK       - 成功
 *       I2C_ERROR    - 失败
 */
uint8_t I2C_Get_Ack_From_Slave(void)
{
	// 初始化总线
	I2C_SDA = 1; 
	I2C_SCL = 1;

	if(I2C_Sync_The_Clock())
	{
		return I2C_ERROR;  // 出错 - 同步失败
	}

	// 完成时钟同步
	I2C_Delay();       

	if (I2C_SDA)       
	{
		// 产生时钟周期
		I2C_SCL = 0;  

		return I2C_ERROR;  // 出错 -  从机无应答
	}

	I2C_SCL = 0; // 产生时钟周期

	return I2C_OK;     // 成功 - 从机有应答
}


/**
 * uint8_t I2C_Write_Byte(uint8_t Data)
 * 简介：发送一个字节到从机
 * 功能：
 *     发送一个字节到从机。通过允许“时钟延伸”来支持低速从机
 *     运行时间 ~100 微秒（除非发生总线错误）
 * 输入：Data: 需要发送的字节
 * 输出：
 *     I2C_OK - 成功
 *     I2C_ERROR    - 失败   
 */
uint8_t I2C_Write_Byte(uint8_t Data)
{
	uint8_t Bit = 0;  

	// 每次发送一位数据（高位先发送）
	for (Bit = 0; Bit < 8; Bit++ )
	{
		I2C_Delay();
		I2C_SDA = (bit)((Data & 0x80) >> 7); 
		I2C_SCL = 1;  

		if (I2C_Sync_The_Clock() == I2C_ERROR)
		{
			return I2C_ERROR; // 出错 - 同步失败
		}

		I2C_Delay(); 

		// 产生时钟周期
		I2C_SCL = 0;                        

		// 准备发送下一位
		Data <<= 1;                    
	}

	// 确定从机有应答
	return(I2C_Get_Ack_From_Slave());
}


/**
 * uint8_t I2C_Read_Byte(void)
 * 简介：从从机读取一个字节
 * 功能：
 *       从从机读取一个字节的数据。通过允许“时钟延伸”来支持低速从机
 * 输入：无
 * 输出：
 *       读取的 I2C 字节，若失败则返回 I2C_ERROR
 */
uint8_t I2C_Read_Byte(void)
{
	uint8_t result  = 0;  // 返回读取的 I2C 字节
	uint8_t Bit = 0;      // 位计数器

	for(Bit = 0; Bit < 8; Bit++)
	{
		I2C_SDA = 1;           // 释放 SDA
		I2C_SCL = 1;           // 释放 SCL

		if (I2C_Sync_The_Clock() == I2C_ERROR)
		{
			return I2C_ERROR;     // 出错 - 同步失败
		}

		I2C_Delay(); 

		result <<= 1;      // 结果左移

		if (I2C_SDA)
		{
			result |= 0x01;  // 最低位设置为实际的 SDA 状态
		}

		I2C_SCL = 0;       // 强制时钟周期
		I2C_Delay();       
	}
	
	return result;
}

/**
 * bit I2C_Sync_The_Clock(void)
 * 简介：I2C 时钟同步
 * 功能：
 *       同步 I2C 时钟，I2C 数据传输使用的底层函数
 * 输入：无
 * 输出：
 *       I2C_ERROR - 出错（时钟未同步）
 *       I2C_OK    - 成功（时钟同步）
 */
bit I2C_Sync_The_Clock(void)
{
	uint16_t i;
	i = MAIN_Fosc / 13000;
	
	// 试图同步时钟
	while((I2C_SCL == 0) && (i != 0))
	{
		i--;
	}

	if (i == 0)
	{
		return I2C_ERROR;  // 错误 - 超时条件不满足
	}

	return I2C_OK;       // 成功 - 时钟同步
}

/**
 * void I2C_Delay(void)
 * 简介：I2C 延时
 * 功能：较短的软件延迟，应至少为 5.425 微秒
 * 输入：无
 * 输出：无
 */
void I2C_Delay(void)
{
	//@24MHz
	uint8_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 50;
	while (--i);
}

#ifdef I2C_ACK_NACK

/**
 * void I2C_Send_Master_Ack(void)
 * 简介：产生 ACK 状态
 * 输入：无
 * 输出：无
 */
void I2C_Send_Master_Ack(void)
{
  I2C_SDA = 0; 
  I2C_SCL = 1;

  I2C_Sync_The_Clock();

  I2C_Delay();  
  I2C_SCL = 0;  
}


/**
 * void I2C_Send_Master_Ack(void)
 * 简介：产生 NOT ACK 状态
 * 输入：无
 * 输出：无
 */
void I2C_Send_Master_NAck(void)
{
	I2C_SDA = 1; 
	I2C_SCL = 1; 

	I2C_Sync_The_Clock();

	I2C_Delay();
	I2C_SCL = 0;
} 
#endif