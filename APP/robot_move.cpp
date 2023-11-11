#include "robot_move.h"
using namespace std;

uint16_t color_cnt=0;
uint16_t K_Claw = 0;
uint16_t K_Gimbal = 0;
uint16_t K_Arm = 0;
uint16_t K_Wrist = 0;
/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{
		K_Claw++;
		K_Gimbal++;
		K_Arm++;
		color_cnt++;
		K_Wrist++;
		Xbox.Controller_Data_Rx();

		if (color_cnt==50)
		{
			Xbox.Set_color();
			color_cnt=0;
		}
		Servo[2].Control_Servo(Servo[2].angle);
		//控制机械爪
		if (K_Claw==1)
		{
			Servo[3].Control_Claw();
			K_Claw = 0;
		}
		// 控制云台
		if (K_Gimbal==2)
		{
			Servo[0].Control_Gimbal();
            K_Gimbal=0;
		}
		//控制臂
		if (K_Arm==2)
		{
			Servo[1].Control_Arm();
			K_Arm = 0;
		}
		if (K_Wrist==2)
		{
			Servo[2].Control_Wrist();
			K_Wrist = 0;
		}
		
		
}
}


