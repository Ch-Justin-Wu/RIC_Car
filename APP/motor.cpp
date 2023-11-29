
#include "motor.h"

using namespace std;

motor motors[motor_num];
pid_test Test_moto[motor_num] = {0};

// 初始化电机类
/**
 * ************************************************************************
 * @brief 初始化电机类
 *
 * @param[in] __Driver_PWM1_TIM  PWM1定时器
 * @param[in] __Driver_PWM1_TIM_Channel_x  PWM1的通道
 * @param[in] __Driver_PWM2_TIM  PWM2定时器
 * @param[in] __Driver_PWM2_TIM_Channel_x  PWM2的通道
 * @param[in] __Encoder_GPIOx  编码器脉冲引脚组
 * @param[in] __Encoder_GPIO_Pin  编码器脉冲引脚号
 * @param[in] __Speed_Direction_GPIOx  电机速度方向引脚组
 * @param[in] __Speed_Direction_GPIO_Pin  电机速度方向引脚号
 * @param[in] __Speed_Default_Direction 电机默认方向
 *
 * ************************************************************************
 */
void motor::Init(TIM_HandleTypeDef __Driver_PWM1_TIM, uint8_t __Driver_PWM1_TIM_Channel_x,
				 TIM_HandleTypeDef __Driver_PWM2_TIM, uint8_t __Driver_PWM2_TIM_Channel_x,
				 GPIO_TypeDef *__Encoder_GPIOx, uint16_t __Encoder_GPIO_Pin,
				 uint8_t __Speed_Default_Direction)
{
	Driver_PWM1_TIM = __Driver_PWM1_TIM;
	Driver_PWM1_TIM_Channel_x = __Driver_PWM1_TIM_Channel_x;
	Driver_PWM2_TIM = __Driver_PWM2_TIM;
	Driver_PWM2_TIM_Channel_x = __Driver_PWM2_TIM_Channel_x;
	Encoder_GPIOx = __Encoder_GPIOx;
	Encoder_GPIO_Pin = __Encoder_GPIO_Pin;
	Speed_Default_Direction = __Speed_Default_Direction;
	HAL_TIM_PWM_Start(&__Driver_PWM1_TIM, __Driver_PWM1_TIM_Channel_x);
	HAL_TIM_PWM_Start(&__Driver_PWM2_TIM, __Driver_PWM2_TIM_Channel_x);
}


#define ABS(x) ((x > 0) ? (x) : (-x))
/**
 * ************************************************************************
 * @brief 设置电机转速，pid计算输出PWM
 *	IN1		IN2		功能
 *	0		0		滑行，休眠
 *	1		0		正向
 *	0		1		反向
 *	1		1		刹车
 *
 * PWM		0		正转PWM，快衰减
 * 1		PWM		正转PWM，慢衰减
 * 0		PWM		反转PWM，快衰减
 * PWM		1		反转PWM，慢衰减
 *
 * @param[in] i  电机编号
 * ************************************************************************
 */
void motor::motor_pwm_tx(uint8_t i)
{
	int16_t tempVAL = 0;
	int16_t const_VAL = 1800;

	// Real_rpm
	ori_rpm = Hall_Encoder_Count / 13.0 / 2.0 / 30.0 * 100 * 60;
	Hall_Encoder_Count = 0;

	
	// Kalman filter
	get_rpm = kalman_filter(&kfp[i], ori_rpm);

	tempVAL = pid_calc(&pid_motor[i], (float)get_rpm, (float)set_rpm);

	pwmVal = tempVAL;

	// 快衰减
	if (set_rpm - get_rpm > RPM_DEADBAND)
	{

		Set_speed_direction = 1;
	}
	else if (set_rpm - get_rpm < -RPM_DEADBAND)
	{

		Set_speed_direction = -1;
	}

	else if (ABS(set_rpm - get_rpm) <= RPM_DEADBAND)
	{
		if (set_rpm > 0)
		{
			Set_speed_direction = 1;
		}
		else if (set_rpm < 0)
		{
			Set_speed_direction = -1;
		}
		// else if (set_rpm==0||ABS(get_rpm)<=1)
		// {
		// 	Set_speed_direction = 0;
		// }
		
	}

	// else if (!set_rpm)
	// {
	// 	Set_speed_direction = 0;
	// }

	switch (Set_speed_direction)
	{
		// 反转
	case -1:
		switch (Speed_Default_Direction)
		{
		case POSITIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, -tempVAL + const_VAL);
			break;
		case NEGATIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, -tempVAL + const_VAL);
			break;
		default:
			break;
		}
		break;
		// 正转
	case 1:
		switch (Speed_Default_Direction)
		{
		case POSITIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, tempVAL + const_VAL);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
			break;
		case NEGATIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, tempVAL + const_VAL);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
			break;
		default:
			break;
		}
		break;
	case 0:
		// // 电机无力
		__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
		__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
		// 电机刹车
		// __HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 3600);
		// __HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 3600);
		break;
	default:
		break;
	}
}

/**
 * ************************************************************************
 * @brief 编码器脉冲数设置
 *
 *
 * ************************************************************************
 */
void motor::Encoder_Count()
{

	if (Set_speed_direction>0)
	{
		Hall_Encoder_Count++;
	}
	else if (Set_speed_direction<0)
	{
		Hall_Encoder_Count--;
	}
}

/**
 * ************************************************************************
 * @brief 
 * 
 * @param[in] i  电机编号
 * 
 * ************************************************************************
 */
void motor::wheel_linear_speed_to_rpm(uint8_t i)
{

	set_rpm = Mec_Chassis.wheel_speed[i] / 25000.0 * MAX_RPM;
	if (set_rpm >= MAX_RPM)
	{
		set_rpm = MAX_RPM;
	}
	else if (set_rpm <= -MAX_RPM)
	{
		set_rpm = -MAX_RPM;
	}
}

#define ABS(x) ((x > 0) ? (x) : (-x))

/**
 * ************************************************************************
 * @brief 开环控制设置pwm
 *
 * @param[in] i  电机编号
 *
 * ************************************************************************
 */
void motor::wheel_speed_to_pwm(uint8_t i)
{
	pwmVal = ABS(Mec_Chassis.wheel_speed[i]) / 25000 * 3600;
	if (pwmVal >= 3600)
	{
		pwmVal = 3600;
	}

	if (Mec_Chassis.wheel_speed[i] > 0)
	{
		switch (Speed_Default_Direction)
		{
		case POSITIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, pwmVal);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
			break;
		case NEGATIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, pwmVal);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
			break;
		default:
			break;
		}
	}
	else if (Mec_Chassis.wheel_speed[i] < 0)
	{
		switch (Speed_Default_Direction)
		{
		case POSITIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, pwmVal);
			break;
		case NEGATIVE:
			__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, pwmVal);
			break;
		default:
			break;
		}
	}
	else if (Mec_Chassis.wheel_speed[i] == 0)
	{
		// 电机无力
		__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
		__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
	}
}
