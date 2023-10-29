#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f1xx_hal.h"
#include "mytype.h"

#include "pid.h"
#include "bsp_usart.h"

#define motor_num 2
#define FILTER_BUF_LEN 5

#define MAX_OUTPUT_LIMIT 8000
#define INTEGRAL_LIMIT 3000
#define DEADBAND 0
#define MAX_ERROR 0

#define KP_MOTOR1 5.0f
#define KI_MOTOR1 0.8f
#define KD_MOTOR1 0.0f

#define KP_MOTOR2 4.0f
#define KI_MOTOR2 0.02f
#define KD_MOTOR2 1.5f

/*电机的参数结构体*/
typedef struct
{
	int16_t speed_rpm;

	int32_t round_cnt;

	u8 buf_idx;

} moto_measure_t;

typedef struct
{
	float real_total_angle;
	float angle_setspeed;
	float set_angle;
	float actual_round;
	pid_t *pid_angle;
} MotorData_t;
typedef struct motor
{

	int stick_offset_position[motor_num];
	int deadband[motor_num];

	float set_speed[motor_num];

} Con_Speed_t;

extern moto_measure_t moto_chassis[];
extern moto_measure_t moto_info;

#endif
