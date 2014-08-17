/**
 * 单片机配置
 * 作者：    Blanboom
 * 最后更新：2014-07-17
 * http://blanboom.org
 */

#ifndef		__CONFIG_H
#define		__CONFIG_H


/*********************************************************/

//#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
#define MAIN_Fosc		24000000L	//定义主时钟


/*********************************************************/

#include	"STC15Fxxxx.H"


/**************************************************************************/

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

/***********************************************************/
typedef 	unsigned char	uint8_t;
typedef 	unsigned int	uint16_t;
typedef 	unsigned long	uint32_t;


#endif
