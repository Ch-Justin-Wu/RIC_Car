#include "init.h"
using namespace std;
void Init_all_pid(void);
void Init_all_servos(void);
void Init_all_motors(void);
void Init_10ms_timer(void);
void Init_all_Controller_Joysticks(void);

void Init_all_func(void)
{
    Init_all_pid();
    Init_all_servos();
    Init_all_motors();
    Init_10ms_timer();
    Init_all_Controller_Joysticks();
}

void Init_all_pid(void)
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

void Init_all_servos(void)
{

    Servo[0].Init(htim4, TIM_CHANNEL_1); // Servo1
    Servo[1].Init(htim4, TIM_CHANNEL_2); // Servo2
    Servo[2].Init(htim4, TIM_CHANNEL_3); // Servo3
    Servo[3].Init(htim4, TIM_CHANNEL_4); // Servo4
}

void Init_all_motors(void)
{
    // Motor1
    motors[0].Init(htim2, TIM_CHANNEL_1,
                   htim2, TIM_CHANNEL_2,
                   GPIOC, ENCODER1_Pin,
                   GPIOC, SPEED_DIRECTION1_Pin,
                   Positive);
    // Motor2
    motors[1].Init(htim3, TIM_CHANNEL_1,
                   htim3, TIM_CHANNEL_2,
                   GPIOA, ENCODER2_Pin,
                   GPIOA, SPEED_DIRECTION2_Pin,
                   Negative);
    // Motor3
    motors[2].Init(htim3, TIM_CHANNEL_3,
                   htim3, TIM_CHANNEL_4,
                   GPIOA, ENCODER3_Pin,
                   GPIOB, SPEED_DIRECTION3_Pin,
                   Positive);
    // Motor4
    motors[3].Init(htim2, TIM_CHANNEL_3,
                   htim2, TIM_CHANNEL_4,
                   GPIOB, ENCODER4_Pin,
                   GPIOB, SPEED_DIRECTION4_Pin,
                   Negative);
}

void Init_10ms_timer(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
}

void Init_all_Controller_Joysticks(void)
{
    Init_Controller_Joystick(&Left_Joystick,2000,32768);
    Init_Controller_Joystick(&Right_Joystick,2000,32768);
}