#include "PWM.h"
#include "RC.h"

PWM_TypeDef PWM;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim12;

extern RC_TypeDef RC;

void PWM_init(void)
{
	GPIO_InitTypeDef gpio_init;
	TIM_OC_InitTypeDef oc_init;


	
	__HAL_RCC_TIM1_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM5_CLK_ENABLE();
	__HAL_RCC_TIM8_CLK_ENABLE();
	__HAL_RCC_TIM9_CLK_ENABLE();
	__HAL_RCC_TIM12_CLK_ENABLE();
	
	gpio_init.Pin = GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14; //TIM1
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF1_TIM1;
	__HAL_RCC_GPIOE_CLK_ENABLE();
	HAL_GPIO_Init(GPIOE, &gpio_init);
	
	gpio_init.Pin = GPIO_PIN_6 | GPIO_PIN_7;  //TIM3
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF2_TIM3;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &gpio_init);
	
	gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	gpio_init.Mode = GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF2_TIM3;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init(GPIOB, &gpio_init);
	
	gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;  //TIM5
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF2_TIM5;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &gpio_init);
	
	gpio_init.Pin = GPIO_PIN_6 | GPIO_PIN_9;  //TIM8
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF3_TIM8;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(GPIOC, &gpio_init);
	
	gpio_init.Pin = GPIO_PIN_5 | GPIO_PIN_6;  //TIM9
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF3_TIM9;
	__HAL_RCC_GPIOE_CLK_ENABLE();
	HAL_GPIO_Init(GPIOE, &gpio_init);
	
	gpio_init.Pin = GPIO_PIN_14 | GPIO_PIN_15;  //TIM12
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Alternate = GPIO_AF9_TIM12;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init(GPIOB, &gpio_init);

	htim1.Instance					= TIM1;
	htim1.Init.Prescaler			= SystemCoreClock / PWM_CLOCK - 1;
	htim1.Init.Period				= PWM_Period - 1;
	htim1.Init.CounterMode			= TIM_COUNTERMODE_UP;
	htim1.Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter	= 0;

	
	
	htim3							= htim1;
	htim3.Instance					= TIM3;
	
	htim5                           =htim1;
	htim5.Instance					= TIM5;
	
	htim8                           = htim1;
	htim8.Instance	                         = TIM8;	
	
	htim9                           = htim1;
	htim9.Instance					= TIM9;
	
	htim12                           = htim1;
	htim12.Instance					= TIM12;
	
	HAL_TIM_PWM_Init(&htim1); //定时器1 PWM输出初始化
	HAL_TIM_PWM_Init(&htim3); //定时器3 PWM输出初始化
	HAL_TIM_PWM_Init(&htim5); //定时器5 PWM输出初始化
	HAL_TIM_PWM_Init(&htim8); //定时器8 PWM输出初始化
	HAL_TIM_PWM_Init(&htim9); //定时器9 PWM输出初始化
	HAL_TIM_PWM_Init(&htim12); //定时器12 PWM输出初始化
	
	oc_init.OCMode			= TIM_OCMODE_PWM1;			//输出捕获方式设置
	oc_init.OCPolarity		= TIM_OCPOLARITY_HIGH;
	oc_init.OCNPolarity		= TIM_OCNPOLARITY_LOW;
	oc_init.OCFastMode		= TIM_OCFAST_DISABLE;
	oc_init.OCNIdleState	= TIM_OCNIDLESTATE_RESET;
	oc_init.OCIdleState		= TIM_OCIDLESTATE_RESET;
	oc_init.Pulse			= 0;

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_1); //定时器1 PWM CH1-CH4 初始化
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

//	oc_init.OCMode			= TIM_OCMODE_PWM2; //输出捕获方式设置
//	oc_init.OCPolarity		= TIM_OCPOLARITY_LOW;
//	oc_init.OCNPolarity		= TIM_OCNPOLARITY_LOW;

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_1); //定时器3 PWM CH1-CH4 初始化
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_3); 
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	HAL_TIM_PWM_ConfigChannel(&htim5, &oc_init, TIM_CHANNEL_1); //定时器5 PWM CH1-CH4 初始化
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim5, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&htim5, &oc_init, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);

	HAL_TIM_PWM_ConfigChannel(&htim5, &oc_init, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_ConfigChannel(&htim8, &oc_init, TIM_CHANNEL_1); //定时器8 PWM CH1和CH4 初始化
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim8, &oc_init, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_ConfigChannel(&htim9, &oc_init, TIM_CHANNEL_1); //定时器9 PWM CH1-CH2 初始化
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim9, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&htim12, &oc_init, TIM_CHANNEL_1); //定时器12 PWM CH1-CH2 初始化
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim12, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	
	for (char i = 0; i < 18; i++)
	{
		PWM.CH[i] = 1500;				//设置PWM输出的初始值
		set_pwm_val(i, PWM.CH[i]);
	}

}

void set_pwm_val(char CH, uint32_t val)  //设置PWM输出值
{
	switch (CH)
	{	
	case 0:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;  //PE9
	case 1:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;  //PE11
	case 2:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (val > PWM_Period ? PWM_Period : val)); break;  //PE13
	case 3:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (val > PWM_Period ? PWM_Period : val)); break;  //PE14
	case 4:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;  //PA6
	case 5:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;  //PA7
	case 6:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, (val > PWM_Period ? PWM_Period : val)); break;  //PB1
	case 7:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, (val > PWM_Period ? PWM_Period : val)); break;  //PB2	
	case 8:__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;  //PA0
	case 9:__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;  //PA1
	case 10:__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, (val > PWM_Period ? PWM_Period : val)); break;  //PA2
	case 11:__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_4, (val > PWM_Period ? PWM_Period : val)); break;  //PA3
	case 12:__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;  //PC6
//	case 13:__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;  //PC7
//	case 14:__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, (val > PWM_Period ? PWM_Period : val)); break;  //PC8
	case 13:__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, (val > PWM_Period ? PWM_Period : val)); break;  //PC9
	case 14:__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;  //PE5
	case 15:__HAL_TIM_SetCompare(&htim9, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;  //PE6
	case 16:__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;  //PB15
	case 17:__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;  //PB14
	default:
		break;
	}
}

void all_pwm_set()  //设置PWM所有输出值，方便定时器调用
{
	for (char i = 0; i < 18; i++)
	{
		PWM.CH[i] = RC.CH[i];
		set_pwm_val(i, PWM.CH[i]);
	}
}

