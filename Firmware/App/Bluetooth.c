/**
 * 蓝牙相关函数
 * 作者：    Blanboom
 * 最后更新：2014-08-18
 * http://blanboom.org
 **************************
 * 蓝牙指令:
 *     TIMShhmmss    -  设置时间，hhmmss 为 24 时制时间
 *     TIMAhhmmss    -  设置闹钟，hhmmss 为 24 时制时间
 *     TIMLggrrbb    -  设置 LED 颜色，ggrrbb 为 LED 的 RGB 颜色
 *     TIMMx         -  打开/关闭闹钟，x = 0 时打开，x = 1 时关闭
 *     TIMDxxxxxxdd  -  进入自定义显示模式并显示内容，xxxxxx 为要显示的数字
 *                      dd 范围是 0 ~ 15，控制四个点的显示，具体见 "Display.h"
 *     TIMT          -  切换回时钟模式
 */

#include "Bluetooth.h"
#include "RF-BM-S02.h"
#include "USART.h"
#include "app.h"
#include "Display.h"
#include "RTC.h" 
#include "delay.h"
#include "Sound.h"

/**
 * void bluetoothInit(void)
 * 简介：蓝牙初始化
 * 输入：无
 * 输出：无
 */
void bluetoothInit(void)
{
	RF_BM_S02_Init();
}

/**
 * void bluetoothCheck(void)
 * 简介：检查并执行蓝牙指令
 * 输入：无
 * 输出：无
 */
void bluetoothCheck(void)
{
	uint8_t i, j;
	if(COM1.RX_TimeOut > 0)		// 超时计数
	{
		Delay_ms(2);
		if(--COM1.RX_TimeOut == 0)
		{
			if(COM1.RX_Cnt > 0)
			{
				for(i=0; i<COM1.RX_Cnt; i++)
				{
					if(RX1_Buffer[i] == 'T' && i < (COM_RX1_Lenth - 15))
					{
						if(RX1_Buffer[i + 1] == 'I' && RX1_Buffer[i + 2] == 'M')    // 接收到 "TIM" 开头的数据
						{
							if(RX1_Buffer[i + 3] == 'S')    // 设置时间
							{
								mode = MODE_CLOCK;
								hour   = (RX1_Buffer[i + 4] - '0') * 10 + (RX1_Buffer[i + 5] - '0');
								minute = (RX1_Buffer[i + 6] - '0') * 10 + (RX1_Buffer[i + 7] - '0');
								second = (RX1_Buffer[i + 8] - '0') * 10 + (RX1_Buffer[i + 9] - '0');
								EA = 0;
								syncTime();
								EA = 1;
								playSound(10);
								break;
							}
							else if(RX1_Buffer[i + 3] == 'A')    // 设置闹钟
							{
								mode = MODE_CLOCK;
								hour_alarm   = (RX1_Buffer[i + 4] - '0') * 10 + (RX1_Buffer[i + 5] - '0');
								minute_alarm = (RX1_Buffer[i + 6] - '0') * 10 + (RX1_Buffer[i + 7] - '0');
								second_alarm = (RX1_Buffer[i + 8] - '0') * 10 + (RX1_Buffer[i + 9] - '0');
								playSound(10);
								break;
							}
							else if(RX1_Buffer[i + 3] == 'M')    // 闹钟开关
							{
								mode = MODE_CLOCK;
								alarmEnable   = RX1_Buffer[i + 4] - '0';
								if(alarmEnable)
								{
									ledUpdate(31, 0, 31);
								}
								else
								{
									ledUpdate(0, 0, 31);
								}
								playSound(10);
								break;
							}
							else if(RX1_Buffer[i + 3] == 'L')     // 设置 LED 颜色
							{
								ledUpdate((RX1_Buffer[i + 4] - '0') * 10 + (RX1_Buffer[i + 5] - '0'),
													(RX1_Buffer[i + 6] - '0') * 10 + (RX1_Buffer[i + 7] - '0'),
													(RX1_Buffer[i + 8] - '0') * 10 + (RX1_Buffer[i + 9] - '0'));
								break;
							}
							else if(RX1_Buffer[i + 3] == 'D')     // 自定义显示
							{
								mode = MODE_DISPLAY;                // 进入自定义显示模式
								for(j = 0; j < 6; j++)
								{
									numbertoDisplay[j] = RX1_Buffer[i + j + 4];
								}
								displayUserNumber(numbertoDisplay);
								displayDots((RX1_Buffer[i + 10] - '0') * 10 + (RX1_Buffer[i + 11] - '0'));
								break;
							}
							else if(RX1_Buffer[i + 3] == 'T')     // 切换回时钟模式
							{
								mode = MODE_CLOCK;                // 进入自定义显示模式
							}
						}
					}
				}
			}
			COM1.RX_Cnt = 0;
		}
	}
}