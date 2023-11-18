#include "robot_move.h"
using namespace std;

#define OPEN
// #define PID

uint16_t color_cnt = 0;
uint16_t K_Claw = 0;
uint16_t K_Gimbal = 0;
uint16_t K_Arm = 0;
uint16_t K_Wrist = 0;

void Control_Robotic_Arm();

/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{
		// color_cnt++;
		K_Claw++;
		K_Gimbal++;
		K_Arm++;
		K_Wrist++;
#if defined(Controller)
		Xbox.Controller_Data_Rx();
#endif
#if defined(ROS)
		ROS2_Data_Rx();
#endif
		// if (color_cnt == 50)
		// {
		// 	// Xbox.Set_color();
		// 	color_cnt = 0;
		// }
#if defined(OPEN)
		{
			// ROS2_Data_Rx();
			Mec_Chassis.XYZ_speed_set();
			Mec_Chassis.Mec_chassis_wheel_speed();
			for (uint8_t i = 0; i < 4; i++)
			{
				motors[i].wheel_speed_to_pwm(i);
			}
		}
#endif

// J-Scope
//  uint8_t i = 1;
//  Test_M1.get = motors[i].get_rpm;
//  Test_M1.set = motors[i].set_rpm;

// pid control
#if defined(PID)
		for (uint8_t i = 0; i < 4; i++)
		{
			Mec_Chassis.XYZ_speed_set();
			Mec_Chassis.Mec_chassis_wheel_speed();
			motors[i].Wheel_Linear_Speed_to_RPM(i);
			motors[i].Motor_PWM_Tx(i);
		}
#endif
		Control_Robotic_Arm();
		// open control
	}
}

inline void Control_Robotic_Arm()
{

	// 控制机械爪
	if (K_Claw == 1)
	{
		Servo[3].Control_Claw();
		K_Claw = 0;
	}
	// 控制云台
	if (K_Gimbal == 4)
	{
		Servo[0].Control_Gimbal();
		K_Gimbal = 0;
	}
	// 控制臂
	if (K_Arm == 3)
	{
		Servo[1].Control_Arm();
		K_Arm = 0;
	}
	// 控制腕
	if (K_Wrist == 3)
	{
		Servo[2].Control_Wrist();
		K_Wrist = 0;
	}
}
