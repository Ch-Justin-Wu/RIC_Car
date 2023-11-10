#include "robot_move.h"
using namespace std;

uint16_t color_cnt;
uint16_t K_Claw = 0;
/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{
		K_Claw+=1;
		color_cnt++;
		Xbox.Controller_Data_Rx();
		
		if (color_cnt==50)
		{
			Xbox.Set_color();
			color_cnt=0;
		}
		//Servo[0].Control_Servo(Servo[0].angle);
		//¿ØÖÆ»úÐµ×¦
		if (K_Claw==1)
		{
			Servo[3].Control_Claw();
			K_Claw = 0;
		}
		
		
}
}


