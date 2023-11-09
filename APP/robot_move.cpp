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
	if (htim->Instance == TIM2)
	{
		color_cnt++;

		controller_data();
		if (color_cnt==50)
		{
			Set_color();
		}
		
	
	

	
}
}


