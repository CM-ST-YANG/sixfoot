#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
#include <PWM.h>
#ifdef __cplusplus
extern "C"
#endif
int ST=0;
void setSystemClock();
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int main(void)
{
	SystemCoreClockUpdate();
	HAL_Init();
	PWM_init();
	while (1)
	{
		set_pwm_val(0, 600);
		set_pwm_val(1, 700);
		set_pwm_val(2, 800);
		set_pwm_val(3, 900);
		set_pwm_val(4, 1000);
		set_pwm_val(5, 1100);
		set_pwm_val(6, 1200);
		set_pwm_val(7, 1300);
		set_pwm_val(8, 1400);
		set_pwm_val(9, 1500);
		set_pwm_val(10, 1600);
		set_pwm_val(11, 1700);
		set_pwm_val(12, 1800);
		set_pwm_val(13, 1900);
		set_pwm_val(14, 2000);
		set_pwm_val(15, 2100);
		set_pwm_val(16, 2200);
		set_pwm_val(17, 2300);
//		set_pwm_val(14, 2000);
//		set_pwm_val(15, 2100);
	}
}


