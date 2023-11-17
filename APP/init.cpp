#include "init.h"
using namespace std;

void Init_all_pid(void);
void Init_all_servos(void);
void Init_all_motors(void);
void Init_10ms_timer(void);
void Init_all_Controller_Joysticks(void);

void Init_all_func(void)
{
    Xbox.Init();
    Init_all_Controller_Joysticks();
    My_USART2_Init();

    Init_all_pid();

    Init_all_motors();

    Init_all_servos();
    RGB_RED(8);
    Init_10ms_timer();
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
             KD_MOTOR1, 0);    // Derivative Coefficient

    pid_init(&pid_motor[1],    // Motor 2 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR2,        // Proportional Coefficient
             KI_MOTOR2,        // Integral Coefficient
             KD_MOTOR2, 0);    // Derivative Coefficient

    pid_init(&pid_motor[2],    // Motor 3 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR3,        // Proportional Coefficient
             KI_MOTOR3,        // Integral Coefficient
             KD_MOTOR3, 0);    // Derivative Coefficient

    pid_init(&pid_motor[3],    // Motor 4 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR4,        // Proportional Coefficient
             KI_MOTOR4,        // Integral Coefficient
             KD_MOTOR4,
             0); // Derivative Coefficient
}

void Init_all_servos(void)
{

    HAL_Delay(100);                          // Offset angle
    Servo[0].Init(htim4, TIM_CHANNEL_1, 78); // Servo1
    Servo[0].Control_Gimbal();
    HAL_Delay(100);
    Servo[1].Init(htim4, TIM_CHANNEL_2, 64); // Servo2
    Servo[1].Control_Arm();
    HAL_Delay(100);
    Servo[2].Init(htim4, TIM_CHANNEL_3, 117); // Servo3
    Servo[2].Control_Wrist();
    HAL_Delay(100);
    // Servo4 110-60 ะก->ด๓
    Servo[3].Init(htim4, TIM_CHANNEL_4, 70);
    Servo[3].Control_Claw();
}

void Init_all_motors(void)
{
    // Motor1
    motors[0].Init(htim3, TIM_CHANNEL_3,
                   htim3, TIM_CHANNEL_4,
                   GPIOC, ENCODER1_Pin,
                   GPIOC, SPEED_DIRECTION1_Pin,
                   NEGATIVE);
    // Motor2
    motors[1].Init(htim2, TIM_CHANNEL_3,
                   htim2, TIM_CHANNEL_4,
                   GPIOA, ENCODER2_Pin,
                   GPIOA, SPEED_DIRECTION2_Pin,
                   POSITIVE);
    // Motor3
    motors[2].Init(htim2, TIM_CHANNEL_1,
                   htim2, TIM_CHANNEL_2,
                   GPIOA, ENCODER3_Pin,
                   GPIOB, SPEED_DIRECTION3_Pin,
                   POSITIVE);
    // Motor4
    motors[3].Init(htim3, TIM_CHANNEL_1,
                   htim3, TIM_CHANNEL_2,
                   GPIOB, ENCODER4_Pin,
                   GPIOB, SPEED_DIRECTION4_Pin,
                   NEGATIVE);
}

void Init_10ms_timer(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
}

void Init_all_Controller_Joysticks(void)
{
    Init_Controller_Joystick(&Left_Joystick, 2000, OFFSET_POSITION, OFFSET_POSITION);
    Init_Controller_Joystick(&Right_Joystick, 2000, OFFSET_POSITION, OFFSET_POSITION);
}