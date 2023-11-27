#include "robot_move.h"
using namespace std;

// #define OPEN
#define PID
#define xbox
// uint16_t color_cnt = 0;
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
#if defined(xbox)
		Xbox.controller_data_rx();
		Mec_Chassis.controller_speed_set();
#endif
#if defined(ROS)
		ROS2_data_rx();
		Mec_Chassis.ROS2_Speed_Set(&Ros2);
#endif

		// J-Scope
		// uint8_t i = 3;
		// Test_M1.get = motors[i].get_rpm;
		// Test_M1.set = motors[i].set_rpm;
		// Test_M1.before_filter_get = motors[i].ori_rpm;
		// motors[i].Motor_PWM_Tx(i);

#if defined(PID)

		Mec_Chassis.mec_chassis_wheel_speed();
		for (uint8_t i = 0; i < 4; i++)
		{

			motors[i].wheel_linear_speed_to_rpm(i);
			motors[i].motor_pwm_tx(i);
		}
#endif
		// if (color_cnt == 50)
		// {
		// 	// Xbox.Set_color();
		// 	color_cnt = 0;
		// }
#if defined(OPEN)
		{

			Mec_Chassis.mec_chassis_wheel_speed();
			for (uint8_t i = 0; i < 4; i++)
			{
				motors[i].wheel_speed_to_pwm(i);
			}
		}
#endif

		Control_Robotic_Arm();
		// open control
	}
}

inline void Control_Robotic_Arm()
{
	//一键准备抓取/复位
if (Xbox.Share)
{
	Servo[0].Control_Servo(120);
	Servo[1].Control_Servo(44);
	Servo[2].Control_Servo(74);
	
}
//一键云台复位
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
