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
		short CH[16];            //����ͨ����ֵ
		unsigned int timeH[6];	//�ߵ�ƽʱ���¼
		unsigned int timeL[6];	//�͵�ƽʱ���¼
		unsigned int timemH[6]; //����
		unsigned int timemL[6]; //����
		char Status[6];			//�ȴ�������״̬��1 �ȴ�������  0 �ȴ��½��� 
	}RC_TypeDef;

	void RC_init(void);  //���ջ����ճ�ʼ������
	void RC_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif