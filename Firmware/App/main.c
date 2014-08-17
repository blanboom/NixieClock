/**
 * 主程序
 * 作者：    Blanboom
 * 最后更新：2014-08-18
 * http://blanboom.org
 */

#include "Display.h"
#include "TimeUpdate.h"
#include "app.h"
#include "delay.h"
#include "timer.h"
#include "Bluetooth.h"
#include "RTC.h"
#include "Sound.h"

// 储存当前时间、闹钟、工作模式的全局变量，在 "app.h" 中声明
// 时间
uint8_t hour = 12;
uint8_t minute = 59;
uint8_t second = 59;
uint8_t per25ms = 0;
// 闹钟
uint8_t hour_alarm = 12;
uint8_t minute_alarm = 1;
uint8_t second_alarm = 1;
uint8_t alarmEnable = 0;
// 自定义显示模式下，要显示的数字
uint32_t numbertoDisplay = 0;
// 模式，有时钟模式和自定义显示模式
uint8_t mode = MODE_CLOCK;


int main(void)
{
	// 各种初始化
	uint8_t second_tmp = 0;
	EA = 0;
	bluetoothInit();
	displayInit();
	timerInit();
	soundInit();
	Delay_ms(250);
	Delay_ms(250);
	Delay_ms(250);
	Delay_ms(250);
	getTime();
	EA = 1;
	playSound(3);
	
	
  while(1)
	{
		if(second_tmp != second && mode == MODE_CLOCK)  // 时钟模式，每秒刷新一次显示
		{
			displayTime();
			if(second % 2 == 0)
			{
				displayDots(DISPLAY_DOTS_ALL);
			}
			else
			{
				displayDots(DISPLAY_DOTS_NONE);
			}
			second_tmp = second;
		}
		
		if(second_tmp != second && mode == MODE_DISPLAY)  // 自定义显示模式，每秒刷新一次
		{
			displayNumber(numbertoDisplay);
			second_tmp = second;
    }
		
		bluetoothCheck();  // 蓝牙检测
		
		alarmDispatcher(); // 闹钟检测与处理
		
		if((minute % 10 == 0) && (second < 10))  // 每隔 10 分钟循环显示所有数字，防止阴极中毒
		{
			displayNumber(000000);
			Delay_ms(50);
			displayNumber(111111);
			Delay_ms(50);
			displayNumber(222222);
			Delay_ms(50);
			displayNumber(333333);
			Delay_ms(50);
			displayNumber(444444);
			Delay_ms(50);
			displayNumber(555555);
			Delay_ms(50);
			displayNumber(666666);
			Delay_ms(50);
			displayNumber(777777);
			Delay_ms(50);
			displayNumber(888888);
			Delay_ms(50);
			displayNumber(999999);
			Delay_ms(50);
		}
	}
	//return 0;
}