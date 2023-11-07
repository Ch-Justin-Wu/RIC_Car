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
	/*电机的参数结构体*/
	typedef struct
	{
		int16_t speed_rpm;
		int16_t set_rpm;
	struct
	{
		int16_t pulse;
		uint8_t speed_position;
	} encoder;
	} moto_measure_t;

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

	extern moto_measure_t moto_chassis[];

#ifdef __cplusplus
}

using namespace std;

class motor
{
private:
public:
	int16_t speed_rpm;
	int16_t set_rpm;
	struct
	{
		int32_t pulse;
		int32_t Hall_Encoder_Count;
		uint8_t speed_position;
	} encoder;
	
	void Init(int16_t __speed_rpm, int16_t __set_rpm);
};


extern motor motors[motor_num];
#endif

#endif
