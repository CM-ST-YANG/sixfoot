#ifndef __RC_H__
#define __RC_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"
#define TIM4Period 20000
#define GPIO_OFFSET 10
	typedef struct
	{
		short CH[16];            //各个通道的值
		unsigned int timeH[6];	//高电平时间记录
		unsigned int timeL[6];	//低电平时间记录
		unsigned int timemH[6]; //保留
		unsigned int timemL[6]; //保留
		char Status[6];			//等待触发沿状态，1 等待上升沿  0 等待下降沿 
	}RC_TypeDef;

	void RC_init(void);  //接收机接收初始化函数
	void RC_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif