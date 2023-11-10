#include "robot_move.h"
using namespace std;

uint16_t color_cnt;
/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{
		color_cnt++;
		controller_data();
		
		if (color_cnt==50)
		{
			Set_color();
            color_cnt=0;
		}
		Servo[0].Control_Servo(Servo[0].angle);
}
}


