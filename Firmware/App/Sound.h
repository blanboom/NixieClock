/**
 * 声音与闹钟相关函数
 * 作者：    Blanboom
 * 最后更新：2014-08-18
 * http://blanboom.org
 */
 
#ifndef __SOUND_H
#define __SOUND_H

#include "config.h"

void soundInit(void);
void tone(uint16_t);
void noTone(void);
void playSound(uint8_t var);
void alarmDispatcher(void);
void timer1_int(void);

#endif