#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "encoder.h"
#include "bsp_usart.h"
#include "stm32f1xx_hal.h"
#include "mytype.h"
#include "pid.h"
#include "chassis_move.h"

#define motor_num 4
#define FILTER_BUF_LEN 5

// PID param
#define MAX_OUTPUT_LIMIT 3600
#define INTEGRAL_LIMIT 1000
#define DEADBAND 0
#define MAX_ERROR 0

#define KP_MOTOR1 1.0f
#define KI_MOTOR1 0.1f
#define KD_MOTOR1 0.0f

#define KP_MOTOR2 4.0f
#define KI_MOTOR2 0.02f
#define KD_MOTOR2 1.5f

#define KP_MOTOR3 4.0f
#define KI_MOTOR3 0.02f
#define KD_MOTOR3 1.5f

#define KP_MOTOR4 4.0f
#define KI_MOTOR4 0.02f
#define KD_MOTOR4 1.5f

#define SEPA_INTEGRAL 100
	// typedef struct
	// {
	// 	float real_total_angle;
	// 	float angle_setspeed;
	// 	float set_angle;
	// 	float actual_round;
	// 	pid_t *pid_angle;
	// } MotorData_t;

typedef struct 
{
	int16_t set;
	int16_t get;
}pid_test;

extern pid_test Test_M1, Test_M2, Test_M3, Test_M4;
#ifdef __cplusplus
}

using namespace std;
#define PI 3.143592f
// 电机默认方向

#define NEGATIVE 0
#define POSITIVE 1

class motor
{

public:
	int16_t get_rpm;
	int16_t set_rpm;
	int16_t pwmVal;

	int8_t Set_speed_direction;
	int8_t Get_speed_direction;
	
	struct
	{
		int32_t pulse;
		int32_t Hall_Encoder_Count;

	} encoder;

	void Init(TIM_HandleTypeDef __Driver_PWM1_TIM, uint8_t __Driver_PWM1_TIM_Channel_x,
			  TIM_HandleTypeDef __Driver_PWM2_TIM, uint8_t __Driver_PWM2_TIM_Channel_x,
			  GPIO_TypeDef *__Encoder_GPIOx, uint16_t __Encoder_GPIO_Pin,
			  GPIO_TypeDef *__Speed_Direction_GPIOx, uint16_t __Speed_Direction_GPIO_Pin,
			  uint8_t __Speed_Default_Direction);
	void Real_rpm();
	void Motor_PWM_Tx(uint8_t i);
	void Encoder_Count();
	void Wheel_Linear_Speed_to_RPM(uint8_t i);

protected:
	// 电机驱动定时器编号
	TIM_HandleTypeDef Driver_PWM1_TIM;
	TIM_HandleTypeDef Driver_PWM2_TIM;
	// 定时器通道
	uint8_t Driver_PWM1_TIM_Channel_x;
	uint8_t Driver_PWM2_TIM_Channel_x;
	// 编码器脉冲引脚编号
	GPIO_TypeDef *Encoder_GPIOx;
	uint16_t Encoder_GPIO_Pin;
	// 运动方向引脚
	GPIO_TypeDef *Speed_Direction_GPIOx;
	uint16_t Speed_Direction_GPIO_Pin;
	uint8_t Speed_Default_Direction;
};

extern motor motors[motor_num];
#endif

#endif
