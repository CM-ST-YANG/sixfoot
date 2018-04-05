#include "RC.h"

extern "C" void EXTI15_10_IRQHandler();

void tim4_init(void);

RC_TypeDef RC;				//接收机数据结构体，可供外部使用
TIM_HandleTypeDef htim4;	//定时器处理结构体


//接收机PWM捕获端口的选择
GPIO_TypeDef *PortSelected[16] = {
	GPIOB,  /* Pin 0 selected    */
	GPIOB,  /* Pin 1 selected    */
	GPIOB,  /* Pin 2 selected    */
	GPIOB,  /* Pin 3 selected    */
	GPIOB,  /* Pin 4 selected    */
	GPIOB,  /* Pin 5 selected    */
	GPIOB,  /* Pin 6 selected    */
	GPIOB,  /* Pin 7 selected    */
	GPIOB,  /* Pin 8 selected    */
	GPIOB,  /* Pin 9 selected    */
	GPIOB,  /* Pin 10 selected   */
	GPIOB,  /* Pin 11 selected   */
	GPIOB,  /* Pin 12 selected   */
	GPIOB,  /* Pin 13 selected   */
	GPIOB,  /* Pin 14 selected   */
	GPIOB   /* Pin 15 selected   */
};

void RC_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	tim4_init();



	GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
							 GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;		//第一次为上升沿触发
	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;          //下拉减小噪声干扰
	GPIO_InitStructure.Alternate = GPIO_AF2_TIM4;		
	__HAL_RCC_GPIOB_CLK_ENABLE();		//开启GPIOB时钟
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	for (char i = 0; i < 6; i++)
	{
		RC.CH[i] = 1100;		//给通道获取值一个初值
		RC.Status[i] = 1;		//置状态为1，等待上升沿触发
	}


	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0f, 0);	//设置中断优先级 0x00最高 0x0f最低
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);				//开启中断
}

void tim4_init(void)				//使用定时器4，用来读取高电平时间长度
{
	uint16_t prescalervalue = 0;
	uint32_t tmpvalue = 0;

	__HAL_RCC_TIM4_CLK_ENABLE();

	tmpvalue = HAL_RCC_GetPCLK1Freq();
	prescalervalue = (uint16_t)((tmpvalue * 2) / 1000000) - 1;	//1MHZ的频率

	/* Time base configuration */
	htim4.Instance = TIM4;
	htim4.Init.Period = TIM4Period;							//最大计数100MS
	htim4.Init.Prescaler = prescalervalue;				//设置分频值，由设置的频率来计算
	htim4.Init.ClockDivision = 0;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;		//向上计数
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK)			//初始化定时器
	{
		/* Initialization Error */
		//   Error_Handler();
		asm("bkpt 255");
	}
	if (HAL_TIM_Base_Start(&htim4) != HAL_OK)			//开启定时器
	{
		/* Start Error */
		//   Error_Handler();
		asm("bkpt 255");
	}
}



#define  timh	RC.timeH	[PortNum-GPIO_OFFSET]
#define  timmh	RC.timemH	[PortNum-GPIO_OFFSET]
#define  timl	RC.timeL	[PortNum-GPIO_OFFSET]
#define  timml	RC.timemL	[PortNum-GPIO_OFFSET]
#define  ALLTIM RC.CH		[PortNum-GPIO_OFFSET]
#define  status RC.Status	[PortNum-GPIO_OFFSET]

void RC_Callback(uint16_t GPIO_Pin)				//处理回掉函数
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char PortNum = __CLZ((__RBIT(GPIO_Pin)));				//倒序后求前导零个数 ，计算引脚值
	GPIO_TypeDef * UsePort = PortSelected[PortNum];			//选择引脚对应选择的端口

	GPIO_InitStructure.Pin = GPIO_Pin;
	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN; //IO重新初始化

	if (status == 1) {					//等待上升沿处理
			
		timh = TIM4->CNT;				//获取上升沿时间

		GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;		//重新初始化为下降沿接收
		status = 0;
		HAL_GPIO_Init(UsePort, &GPIO_InitStructure);
	}
	else if (status == 0)					//等待下降沿处理
	{
		
		timl = TIM4->CNT;					//获取下降沿时间
		int data = (int)(timl - timh);

		ALLTIM = data > 0 ? data : data + TIM4Period;			//计算高电平时间
		status = 1;
		GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;		//重新初始化为上升沿接收
		HAL_GPIO_Init(UsePort, &GPIO_InitStructure);
		
	}

}


void EXTI15_10_IRQHandler()			//外部中断的处理
{

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);

}