#ifndef __PWM_H_
#define __PWM_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f4xx_hal.h"
#define PWM_freq	50							//PWMƵ������
#define PWM_Period	20000						//����Ƶ������
#define PWM_CLOCK (PWM_freq*PWM_Period)			//PWMʱ��Ƶ�ʼ���
	typedef struct
	{
		short CH[14];
	}PWM_TypeDef;

	void PWM_init(void);
	void set_pwm_val(char CH, uint32_t val);
	void all_pwm_set();

#ifdef __cplusplus
}
#endif

#endif
