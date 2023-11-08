
#include "motor.h"

using namespace std;

motor motors[motor_num] = {0};

// 初始化电机
void motor::Init(TIM_HandleTypeDef __Driver_PWM1_TIM, uint8_t __Driver_PWM1_TIM_Channel_x,
				 TIM_HandleTypeDef __Driver_PWM2_TIM, uint8_t __Driver_PWM2_TIM_Channel_x,
				 GPIO_TypeDef *__Encoder_GPIOx, uint16_t __Encoder_GPIO_Pin,
				 GPIO_TypeDef *__Speed_Direction_GPIOx, uint16_t __Speed_Direction_GPIO_Pin)
{
	Driver_PWM1_TIM = __Driver_PWM1_TIM;
	Driver_PWM1_TIM_Channel_x = __Driver_PWM1_TIM_Channel_x;
	Driver_PWM2_TIM = __Driver_PWM2_TIM;
	Driver_PWM2_TIM_Channel_x = __Driver_PWM2_TIM_Channel_x;
	encoder.Encoder_GPIOx = __Encoder_GPIOx;
	encoder.Encoder_GPIO_Pin = __Encoder_GPIO_Pin;
	encoder.Speed_Direction_GPIOx = __Speed_Direction_GPIOx;
	encoder.Speed_Direction_GPIO_Pin = __Speed_Direction_GPIO_Pin;
	HAL_TIM_PWM_Start(&__Driver_PWM1_TIM, __Driver_PWM1_TIM_Channel_x);
	HAL_TIM_PWM_Start(&__Driver_PWM2_TIM, __Driver_PWM2_TIM_Channel_x);
}

// 换算为实际转速
void motor::Get_rpm()
{
	for (uint8_t i = 0; i < motor_num; i++)
	{
		motors[i].rpm = motors[i].encoder.Hall_Encoder_Count / 13.0 / 2.0 * 100 * 60;
		motors[i].encoder.Hall_Encoder_Count = 0;
	}
}
// 设置电机转速
void motor::Set_rpm()
{

	short pwmVal[motor_num] = {0};

	for (uint8_t i = 0; i < motor_num; i++)
	{
		pwmVal[i] = pid_calc(&pid_motor[i], (float)motors[i].rpm, (float)motors[i].set_rpm);
	}
}

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
