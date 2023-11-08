#include "init.h"
using namespace std;
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

    motors[0].Init(htim2, TIM_CHANNEL_1,
                   htim2, TIM_CHANNEL_2,
                   GPIOC, ENCODER1_Pin,
                   GPIOC, SPEED_DIRECTION1_Pin);

    motors[1].Init(htim3, TIM_CHANNEL_1,
                   htim3, TIM_CHANNEL_2,
                   GPIOA, ENCODER2_Pin,
                   GPIOA, SPEED_DIRECTION2_Pin);

    motors[2].Init(htim3, TIM_CHANNEL_3,
                   htim3, TIM_CHANNEL_4,
                   GPIOA, ENCODER3_Pin,
                   GPIOB, SPEED_DIRECTION3_Pin);

    motors[3].Init(htim2, TIM_CHANNEL_3,
                   htim2, TIM_CHANNEL_4,
                   GPIOB, ENCODER4_Pin,
                   GPIOB, SPEED_DIRECTION4_Pin);
}

void init_10ms_timer(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
}
