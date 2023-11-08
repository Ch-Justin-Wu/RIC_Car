#ifndef __MOTOR_H
#define __MOTOR_H

#include "encoder.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_usart.h"
#include "stm32f1xx_hal.h"
#include "mytype.h"
#include "pid.h"

#define motor_num 4
#define FILTER_BUF_LEN 5

// PID param
#define MAX_OUTPUT_LIMIT 1000
#define INTEGRAL_LIMIT 300
#define DEADBAND 0
#define MAX_ERROR 0

#define KP_MOTOR1 5.0f
#define KI_MOTOR1 0.8f
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
		int diff[motor_num];
		int stick_offset_position[motor_num];
		int deadband[motor_num];

	} ControllerJoystick_t;

#ifdef __cplusplus
}

using namespace std;

class motor
{

public:
	int16_t rpm;
	int16_t set_rpm;
	uint16_t pwmVal;

	// 电机驱动定时器编号
	TIM_HandleTypeDef Driver_PWM1_TIM;
	TIM_HandleTypeDef Driver_PWM2_TIM;
	// 定时器通道
	uint8_t Driver_PWM1_TIM_Channel_x;
	uint8_t Driver_PWM2_TIM_Channel_x;

	struct
	{
		int32_t pulse;
		int32_t Hall_Encoder_Count;
		uint8_t speed_position;
		// 编码器脉冲引脚编号
		GPIO_TypeDef *Encoder_GPIOx;
		uint16_t Encoder_GPIO_Pin;
		// 运动方向引脚
		GPIO_TypeDef *Speed_Direction_GPIOx;
		uint16_t Speed_Direction_GPIO_Pin;
	} encoder;

	void Init(TIM_HandleTypeDef __Driver_PWM1_TIM, uint8_t __Driver_PWM1_TIM_Channel_x,
			  TIM_HandleTypeDef __Driver_PWM2_TIM, uint8_t __Driver_PWM2_TIM_Channel_x,
			  GPIO_TypeDef *__Encoder_GPIOx, uint16_t __Encoder_GPIO_Pin,
			  GPIO_TypeDef *__Speed_Direction_GPIOx, uint16_t __Speed_Direction_GPIO_Pin);
	void Get_rpm();
	void Set_rpm();
};

extern motor motors[motor_num];
#endif

#endif
