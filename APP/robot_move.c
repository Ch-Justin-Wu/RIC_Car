#include "robot_move.h"

/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		control_robot();
	
	

	// 电机pid控制部分
	// pid_reset(&pid_angle[1], kp_ang_2, ki_ang_2, kd_ang_2);
	// 角速度计算

	// angle_setspeed_1=pid_calc(&pid_angle[0], (float)moto_chassis[0].total_angle/ 8192.0f * 360.0f-(float)moto_chassis[1].total_angle/ 8192.0f * 360.0f, 0.0f);
	//  PID 电流力矩计算

	short torque1 = pid_calc(&pid_motor[0], (float)moto_chassis[0].speed_rpm, 0);
	// can_cmd_send(torque1, torque2);
	// 角速度计算
	// angle_setspeed_2 = angle_speed_cacl(&moto_chassis[1],1, set_round2);
	// 力反馈角度差计算 PID输出 实现单向力反馈
	// angle_setspeed_2=pid_calc(&pid_angle[1], (float)moto_chassis[1].total_angle/ 8192.0f * 360.0f-(float)moto_chassis[0].total_angle/ 8192.0f * 360.0f, 0.0f);

	//  PID 电流力矩计算

	short torque2 = pid_calc(&pid_motor[1], (float)moto_chassis[1].speed_rpm, 0);
	// real_speed2 = moto_chassis[1].speed_rpm;
}
}


