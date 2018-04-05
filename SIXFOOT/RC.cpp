#include "RC.h"

extern "C" void EXTI15_10_IRQHandler();

void tim4_init(void);

RC_TypeDef RC;				//���ջ����ݽṹ�壬�ɹ��ⲿʹ��
TIM_HandleTypeDef htim4;	//��ʱ������ṹ��


//���ջ�PWM����˿ڵ�ѡ��
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

	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;		//��һ��Ϊ�����ش���
	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;          //������С��������
	GPIO_InitStructure.Alternate = GPIO_AF2_TIM4;		
	__HAL_RCC_GPIOB_CLK_ENABLE();		//����GPIOBʱ��
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	for (char i = 0; i < 6; i++)
	{
		RC.CH[i] = 1100;		//��ͨ����ȡֵһ����ֵ
		RC.Status[i] = 1;		//��״̬Ϊ1���ȴ������ش���
	}


	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0f, 0);	//�����ж����ȼ� 0x00��� 0x0f���
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);				//�����ж�
}

void tim4_init(void)				//ʹ�ö�ʱ��4��������ȡ�ߵ�ƽʱ�䳤��
{
	uint16_t prescalervalue = 0;
	uint32_t tmpvalue = 0;

	__HAL_RCC_TIM4_CLK_ENABLE();

	tmpvalue = HAL_RCC_GetPCLK1Freq();
	prescalervalue = (uint16_t)((tmpvalue * 2) / 1000000) - 1;	//1MHZ��Ƶ��

	/* Time base configuration */
	htim4.Instance = TIM4;
	htim4.Init.Period = TIM4Period;							//������100MS
	htim4.Init.Prescaler = prescalervalue;				//���÷�Ƶֵ�������õ�Ƶ��������
	htim4.Init.ClockDivision = 0;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;		//���ϼ���
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK)			//��ʼ����ʱ��
	{
		/* Initialization Error */
		//   Error_Handler();
		asm("bkpt 255");
	}
	if (HAL_TIM_Base_Start(&htim4) != HAL_OK)			//������ʱ��
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

void RC_Callback(uint16_t GPIO_Pin)				//����ص�����
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char PortNum = __CLZ((__RBIT(GPIO_Pin)));				//�������ǰ������� ����������ֵ
	GPIO_TypeDef * UsePort = PortSelected[PortNum];			//ѡ�����Ŷ�Ӧѡ��Ķ˿�

	GPIO_InitStructure.Pin = GPIO_Pin;
	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN; //IO���³�ʼ��

	if (status == 1) {					//�ȴ������ش���
			
		timh = TIM4->CNT;				//��ȡ������ʱ��

		GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;		//���³�ʼ��Ϊ�½��ؽ���
		status = 0;
		HAL_GPIO_Init(UsePort, &GPIO_InitStructure);
	}
	else if (status == 0)					//�ȴ��½��ش���
	{
		
		timl = TIM4->CNT;					//��ȡ�½���ʱ��
		int data = (int)(timl - timh);

		ALLTIM = data > 0 ? data : data + TIM4Period;			//����ߵ�ƽʱ��
		status = 1;
		GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;		//���³�ʼ��Ϊ�����ؽ���
		HAL_GPIO_Init(UsePort, &GPIO_InitStructure);
		
	}

}


void EXTI15_10_IRQHandler()			//�ⲿ�жϵĴ���
{

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);

}