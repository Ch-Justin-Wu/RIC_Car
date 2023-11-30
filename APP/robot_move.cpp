#include "robot_move.h"

// #define OPEN
#define pid_enabled
#define xbox_enabled

namespace RobotControl
{
	volatile uint8_t k_claw = 0;
	volatile uint8_t k_gimbal = 0;
	volatile uint8_t k_arm = 0;
	volatile uint8_t k_wrist = 0;

	void one_key_control_robotic_arm()
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
	}

	void control_robotic_arm()
	{
		const uint8_t claw_angle_period = 1;
		const uint8_t gimbal_angle_period = 4;
		const uint8_t arm_angle_period = 2;
		const uint8_t wrist_angle_period = 1;
		// 控制机械爪
		k_claw++;
		if (k_claw == claw_angle_period)
		{
			Servo[3].Control_Claw();
			k_claw = 0;
		}
		// 控制云台
		k_gimbal++;
		if (k_gimbal == gimbal_angle_period)
		{
			Servo[0].Control_Gimbal();
			k_gimbal = 0;
		}
		// 控制臂
		k_arm++;
		if (k_arm == arm_angle_period)
		{
			Servo[1].Control_Arm();
			k_arm = 0;
		}
		// 控制腕
		k_wrist++;
		if (k_wrist == wrist_angle_period)
		{
			Servo[2].Control_Wrist();
			k_wrist = 0;
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

		RobotControl::one_key_control_robotic_arm();
		RobotControl::control_robotic_arm();
#if defined(xbox_enabled)
		Xbox.controller_data_rx();
		RobotControl::Mec_Chassis.controller_speed_set();
#endif
#if defined(ROS)
		ROS2_data_rx();
		RobotControl::Mec_Chassis.ROS2_Speed_Set(&Ros2);
#endif

		// J-Scope
		// for (uint8_t i = 0; i < 4; i++)
		// {
		// 	Test_moto[i].get = motors[i].get_rpm;
		// 	Test_moto[i].set = motors[i].set_rpm;
		// 	Test_moto[i].before_filter_get = motors[i].ori_rpm;
		// 	motors[i].motor_pwm_tx(i);
		// }

#if defined(pid_enabled)

		RobotControl::Mec_Chassis.mec_chassis_wheel_speed();
		for (uint8_t i = 0; i < 4; i++)
		{
			motors[i].motor_pwm_tx(i);
		}
#endif

#if defined(OPEN)
		{

			RobotControl::Mec_Chassis.mec_chassis_wheel_speed();
			for (uint8_t i = 0; i < 4; i++)
			{
				motors[i].wheel_speed_to_pwm(i);
			}
		}
#endif
	}
}
