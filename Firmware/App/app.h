/**
 * 主程序相关变量定义
 * 作者：    Blanboom
 * 最后更新：2014-07-21
 * http://blanboom.org
 */

#ifndef __APP_H
#define __APP_H

// 工作模式
// 分别为闹钟模式和自定义显示模式
#define MODE_CLOCK    0
#define MODE_DISPLAY  1
extern uint8_t mode;

// 时间、闹钟、自定义显示模式下要显示的内容， 在 "main.c" 中定义
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t second;
extern uint8_t per25ms;

extern uint8_t hour_alarm;
extern uint8_t minute_alarm;
extern uint8_t second_alarm;
extern uint8_t alarmEnable;

extern uint8_t sleepMode;

extern uint8_t numbertoDisplay[];

#endif