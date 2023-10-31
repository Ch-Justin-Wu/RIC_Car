#include "init.h"

void init_all_pid(void);
void init_all_servos(void);
void init_all_motors(void);
void init_10ms_timer(void);

void init_all_func(void)
{
    init_all_pid();
    init_all_servos();
    init_all_motors();
    init_10ms_timer();
}

void init_all_pid(void)
{
    pid_init(&pid_motor[0],    // Motor 1 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR1,        // Proportional Coefficient
             KI_MOTOR1,        // Integral Coefficient
             KD_MOTOR1);       // Derivative Coefficient

    pid_init(&pid_motor[1],    // Motor 2 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR2,        // Proportional Coefficient
             KI_MOTOR2,        // Integral Coefficient
             KD_MOTOR2);       // Derivative Coefficient

    pid_init(&pid_motor[2],    // Motor 3 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR3,        // Proportional Coefficient
             KI_MOTOR3,        // Integral Coefficient
             KD_MOTOR3);       // Derivative Coefficient

    pid_init(&pid_motor[3],    // Motor 4 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR4,        // Proportional Coefficient
             KI_MOTOR4,        // Integral Coefficient
             KD_MOTOR4);       // Derivative Coefficient
}

void init_all_servos(void)
{
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // SERVO1
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2); // SERVO2
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); // SERVO3
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4); // SERVO4
}

void init_all_motors(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//MOTO1_IN1
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//MOTO1_IN2

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//MOTO2_IN1
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//MOTO2_IN2

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);//MOTO3_IN1
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//MOTO3_IN2

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//MOTO4_IN1
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//MOTO4_IN2
}

void init_10ms_timer(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
}
