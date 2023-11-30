#include "robot_move.h"


// #define OPEN
#define PID
#define xbox

namespace RobotControl
{
	volatile uint8_t K_Claw = 0;
	volatile uint8_t K_Gimbal = 0;
	volatile uint8_t K_Arm = 0;
	volatile uint8_t K_Wrist = 0;

	void control_robotic_arm()
	{
		// 一键准备抓取/复位
		if (Xbox.Share)
		{
			Servo[0].Control_Servo(120);
			Servo[1].Control_Servo(44);
			Servo[2].Control_Servo(74);
		}
		// 一键云台复位
		if (Xbox.X)
		{
			Servo[1].Control_Servo(44);
			Servo[0].Control_Servo(120);
		}
		// 一键云台右摆
		if (Xbox.B)
		{
			Servo[1].Control_Servo(44);
			Servo[0].Control_Servo(33);
		}
		// 一键放入矿仓
		if (Xbox.Menu)
		{
			Servo[1].Control_Servo(44);
			Servo[2].Control_Servo(13);
			Servo[0].Control_Servo(30);
		}

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
		if (K_Arm == 2)
		{
			Servo[1].Control_Arm();
			K_Arm = 0;
		}
		// 控制腕
		if (K_Wrist == 1)
		{
			Servo[2].Control_Wrist();
			K_Wrist = 0;
		}
	}
}



/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{

		RobotControl::K_Claw++;
		RobotControl::K_Gimbal++;
		RobotControl::K_Arm++;
		RobotControl::K_Wrist++;
		RobotControl::control_robotic_arm();
#if defined(xbox)
			Xbox.controller_data_rx();
		Mec_Chassis.controller_speed_set();
#endif
#if defined(ROS)
		ROS2_data_rx();
		Mec_Chassis.ROS2_Speed_Set(&Ros2);
#endif

		// J-Scope
		// for (uint8_t i = 0; i < 4; i++)
		// {
		// 	Test_moto[i].get = motors[i].get_rpm;
		// 	Test_moto[i].set = motors[i].set_rpm;
		// 	Test_moto[i].before_filter_get = motors[i].ori_rpm;
		// 	motors[i].motor_pwm_tx(i);
		// }

#if defined(PID)

		Mec_Chassis.mec_chassis_wheel_speed();
		for (uint8_t i = 0; i < 4; i++)
		{

			motors[i].wheel_linear_speed_to_rpm(i);
			motors[i].motor_pwm_tx(i);
		}
#endif

#if defined(OPEN)
		{

			Mec_Chassis.mec_chassis_wheel_speed();
			for (uint8_t i = 0; i < 4; i++)
			{
				motors[i].wheel_speed_to_pwm(i);
			}
		}
#endif
		
	}
}


