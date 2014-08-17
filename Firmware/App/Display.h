/**
 * 显示相关函数, 包括数字及小数点的显示，以及全彩 LED 颜色的控制
 * 作者：    Blanboom
 * 最后更新：2014-07-21
 * http://blanboom.org
 */
 
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "config.h"

// 用于氖灯（四个小数点）显示函数
// 其中，DISPLAY_DOTS_ 后面的四位数分别代表四个点，1 为亮，0 为灭
#define DISPLAY_DOTS_ALL  0x0f
#define DISPLAY_DOTS_NONE 0x00
#define DISPLAY_DOTS_0000 0x00
#define DISPLAY_DOTS_0001 0x01
#define DISPLAY_DOTS_0010 0x02
#define DISPLAY_DOTS_0011 0x03
#define DISPLAY_DOTS_0100 0x04
#define DISPLAY_DOTS_0101 0x05
#define DISPLAY_DOTS_0110 0x06
#define DISPLAY_DOTS_0111 0x07
#define DISPLAY_DOTS_1000 0x08
#define DISPLAY_DOTS_1001 0x09
#define DISPLAY_DOTS_1010 0x0a
#define DISPLAY_DOTS_1011 0x0b
#define DISPLAY_DOTS_1100 0x0c
#define DISPLAY_DOTS_1101 0x0d
#define DISPLAY_DOTS_1110 0x0e
#define DISPLAY_DOTS_1111 0x0f

void displayInit(void);
void displayNumber(uint32_t);
void displayTime(void);
void displayDots(uint8_t);
void ledUpdate(uint8_t, uint8_t, uint8_t);
void displayNumber(uint32_t number);

#endif