
#include "motor.h"

using namespace std;

motor motors[motor_num];
pid_test Test_M1 = {0};

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

/**
 * ************************************************************************
 * @brief 编码器脉冲数换算为实际转速
 *
 *
 * ************************************************************************
 */
// inline void motor::Real_rpm()
// {

// 	get_rpm = encoder.Hall_Encoder_Count / 13.0 / 30.0 / 2.0 * 100 * 60;

// 	encoder.Hall_Encoder_Count = 0;
// }

/**
 * ************************************************************************
 * @brief 设置电机转速
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
 * ************************************************************************
 */
void motor::Motor_PWM_Tx(uint8_t i)
{
	int16_t tempVAL = 0;
	int16_t const_VAL = 1800;

	// Real_rpm
	get_rpm = encoder.Hall_Encoder_Count / 13.0 /2.0/ 30.0 * 100 * 60;
	encoder.Hall_Encoder_Count = 0;

	tempVAL = pid_calc(&pid_motor[i], (float)get_rpm, (float)set_rpm);

	pwmVal = tempVAL;

	// 快衰减
	if (set_rpm > 0)
	{

		Set_speed_direction = 1;
	}
	else if (set_rpm < 0)
	{

		Set_speed_direction = -1;
	}
	else if (!set_rpm)
	{
		Set_speed_direction = 0;
	}

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
			__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x,0);
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
// 编码器脉冲数设置
void motor::Encoder_Count()
{

	if (Set_speed_direction == 1)
	{
		encoder.Hall_Encoder_Count++;
	}
	else if (Set_speed_direction == -1)
	{
		encoder.Hall_Encoder_Count--;
	}
}

void motor::Wheel_Linear_Speed_to_RPM(uint8_t i)
{

	set_rpm = Mec_Chassis.wheel_speed[i] / 25000.0*300;
	if (set_rpm>=MAX_RPM)
	{
		set_rpm = MAX_RPM;
	}
	else if (set_rpm <= -MAX_RPM)
	{
		set_rpm = -MAX_RPM;
	}
	
	
}

#define ABS(x) ((x > 0) ? (x) : (-x))
void motor::wheel_speed_to_pwm(uint8_t i)
{
	pwmVal = ABS(Mec_Chassis.wheel_speed[i]) / 25000 * 3600;
	if (pwmVal>=3600)
	{
		pwmVal = 3600;
	}
	
	if (Mec_Chassis.wheel_speed[i]>0)
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
	else if (Mec_Chassis.wheel_speed[i] ==0)
	{
		//电机无力
		__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
		__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
	}
	
	
}

// void motor::Speed_test(uint8_t i)
// {
// 	if (i == 1)
// 	{
// 		__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 3600);
// 		__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
// 	}
// 	else if (i == 0) //
// 	{
// 		__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
// 		__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 3600);
// 	}
// 	else if (i == 2)
// 	{
// 		__HAL_TIM_SET_COMPARE(&Driver_PWM1_TIM, Driver_PWM1_TIM_Channel_x, 0);
// 		__HAL_TIM_SET_COMPARE(&Driver_PWM2_TIM, Driver_PWM2_TIM_Channel_x, 0);
// 	}
// }

// MotorData_t motors[motor_num];

// /**
//  * @brief 初始化电机数据
//  */
// void init_motor_data() {
//     for (int i = 0; i < motor_num; i++) {
//         motors[i].real_total_angle = 0.0f;
//         motors[i].angle_setspeed = 0.0f;
//         motors[i].set_angle = 0.0f;
//         motors[i].actual_round = 0.0f;
//         motors[i].pid_angle = &pid_angle[i];
//     }
// }

// /**
//  * @brief 角速度计算
//  *
//  * @param moto_chassis
//  * @param k
//  * @param set_round
//  * @return float
//  */
// float angle_speed_cacl(moto_measure_t moto_chassis[], u8 k, float set_round)
// {
//     MotorData_t* motor = &motors[k];

//     get_total_angle(&moto_chassis[k]);
//     // 减速比3591/187  计算设定总角度
//     motor->set_angle = (float)set_round * 360.0f * 3591.0f / 187.0f;

//     // 换算实际总角度
//     motor->real_total_angle = (float)moto_chassis[k].total_angle / 8192.0f * 360.0f;

//     motor->actual_round = (float)moto_chassis[k].total_angle / 8192.0f * 187.0f / 3591.0f;

//     // 通过角度环计算设定(角)速度
//     motor->angle_setspeed = pid_calc(motor->pid_angle, motor->real_total_angle, motor->set_angle);

//     return motor->angle_setspeed;
// }

// float real_total_angle[motor_num];
// float angle_setspeed[motor_num];
// float set_angle[motor_num];
// // float actual_round;

// /**
//  * @brief 角速度计算
//  *
//  * @param set_round
//  * @return float
//  */
// float angle_speed_cacl(moto_measure_t moto_chassis[], u8 k, float set_round)
// {

//     set_angle[k] = set_round * 360.0f * 3591.0f / 187.0f;                  // 减速比3591/187  计算设定总角度 36.0f/1.0f
//     real_total_angle[k] = moto_chassis[k].total_angle / 8192.0f * 360.0f; // 换算实际总角度
//     actual_round[k] = (float)moto_chassis[k].total_angle / 8192.0f * 187.0f / 3591.0f;
//     angle_setspeed[k] = pid_calc(&pid_angle[k], real_total_angle[k], set_angle[k]); // 通过角度环计算设定(角)速度
//     return angle_setspeed[k];
// }
