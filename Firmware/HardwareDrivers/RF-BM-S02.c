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
 
#include "RF-BM-S02.h"

#include "delay.h"
#include "USART.h"
#include "PinDef.h"
#include "stdio.h"

/**
 * uint8_t RF_BM_S02_Init(void)
 * 简介：初始化 RF_BM_S02 及其所需的硬件资源
 * 功能：初始化串口 1， 波特率为 9600，是用定时器 2 作为波特率发生器，同时初始化相关引脚
 * 输入：无
 * 输出：
 *       RF_BM_S02_ERROR - 初始化错误
 *       RF_BM_S02_OK    - 初始化成功
 */
uint8_t RF_BM_S02_Init(void)
{
	COMx_InitDefine		COMx_InitStructure;					
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;
	COMx_InitStructure.UART_BaudRate  = 115200ul;
	COMx_InitStructure.UART_RxEnable  = ENABLE;
	COMx_InitStructure.BaudRateDouble = DISABLE;
	COMx_InitStructure.UART_Interrupt = ENABLE;
	COMx_InitStructure.UART_Polity    = PolityHigh;
	COMx_InitStructure.UART_P_SW      = UART1_SW_P36_P37;
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;
	if(USART_Configuration(USART1, &COMx_InitStructure) != 0)
	{
		return RF_BM_S02_ERROR;
	}
	
	RF_BM_S02_EN   = 0;
	RF_BM_S02_BCTS = 1;
	RF_BM_S02_BRTS = 1;
	
	return RF_BM_S02_OK;
}