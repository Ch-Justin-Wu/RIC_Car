/**
 * ************************************************************************
 *
 * @file init.cpp
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief 初始所有相关的外设、类、结构体
 * @version 1.0
 * @date 2023-11-30
 *
 * ************************************************************************
 * @copyright Copyright (c) 2023 Justin Wu
 * For study and research only, no reprinting
 * ************************************************************************
 */
#include "init.h"

// #define ORANGE
#define BLUE

void Init_all_pid(void);

void Init_all_servos(void);

void Init_all_motors(void);

void Init_all_Controller_Joysticks(void);

/**
 * ************************************************************************
 * @brief 初始化所有外设和所需类、结构体
 *
 *
 * ************************************************************************
 */
void Init_all_func(void)
{
    Xbox.Init();

    for (uint8_t i = 0; i < motor_num; i++)
    {
        kalman_init(&kfp[i]);
    }

    Init_all_Controller_Joysticks();
    My_USART2_Init();

#if defined(ROS)
    My_USART1_Init();
#endif

    Init_all_pid();
    Init_all_motors();
    Init_all_servos();

#if defined(ORANGE)
    RGB_ORANGE(8);
#endif

#if defined(BLUE)
    RGB_SKY(8);
#endif

    // Init_10ms_timer
    HAL_TIM_Base_Start_IT(&htim1);
}

/**
 * ************************************************************************
 * @brief 初始化pid结构体
 *
 *
 * ************************************************************************
 */
void Init_all_pid(void)
{
    pid_init(&pid_motor[0],    // Motor 1 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR1,        // Proportional Coefficient
             KI_MOTOR1,        // Integral Coefficient
             KD_MOTOR1,        // Derivative Coefficient
             SEPA_INTEGRAL);   // Separation Threshold

    pid_init(&pid_motor[1],    // Motor 2 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR2,        // Proportional Coefficient
             KI_MOTOR2,        // Integral Coefficient
             KD_MOTOR2,        // Derivative Coefficient
             SEPA_INTEGRAL);   // Separation Threshold

    pid_init(&pid_motor[2],    // Motor 3 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR3,        // Proportional Coefficient
             KI_MOTOR3,        // Integral Coefficient
             KD_MOTOR3,        // Derivative Coefficient
             SEPA_INTEGRAL);   // Separation Threshold

    pid_init(&pid_motor[3],    // Motor 4 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR4,        // Proportional Coefficient
             KI_MOTOR4,        // Integral Coefficient
             KD_MOTOR4,        // Derivative Coefficient
             SEPA_INTEGRAL);   // Separation Threshold
}
/**
 * ************************************************************************
 * @brief 初始化所有舵机角度
 *
 *
 * ************************************************************************
 */
void Init_all_servos(void)
{
    HAL_Delay(200);
    Servo[1].Init(htim4, TIM_CHANNEL_2, 44); // Servo2 44 ros 44
    Servo[1].control_arm();

    HAL_Delay(200);
    Servo[2].Init(htim4, TIM_CHANNEL_3, 85); // Servo3 74 ros 85
    Servo[2].control_wrist();
    HAL_Delay(200);

    // Servo4 110-60 小->大
    Servo[3].Init(htim4, TIM_CHANNEL_4, 76); // 35 ros 76
    Servo[3].control_claw();

    HAL_Delay(200);                           // Offset angle
    Servo[0].Init(htim4, TIM_CHANNEL_1, 110); // Servo1 120  ros 110
    Servo[0].control_gimbal();
}

/**
 * ************************************************************************
 * @brief 设置电机相关参数
 *
 *
 * ************************************************************************
 */
void Init_all_motors(void)
{
    // Motor1
    motors[0].Init(htim3, TIM_CHANNEL_3, // IN_1
                   htim3, TIM_CHANNEL_4, // IN_2
                   GPIOC, ENCODER1_Pin,
                   NEGATIVE);

    // Motor2
    motors[1].Init(htim2, TIM_CHANNEL_3, // IN_1
                   htim2, TIM_CHANNEL_4, // IN_2
                   GPIOA, ENCODER2_Pin,
                   POSITIVE);

    // Motor3
    motors[2].Init(htim2, TIM_CHANNEL_1, // IN_1
                   htim2, TIM_CHANNEL_2, // IN_2
                   GPIOA, ENCODER3_Pin,
                   POSITIVE);

    // Motor4
    motors[3].Init(htim3, TIM_CHANNEL_1, // IN_1
                   htim3, TIM_CHANNEL_2, // IN_2
                   GPIOB, ENCODER4_Pin,
                   NEGATIVE);
}

/**
 * ************************************************************************
 * @brief 设置手柄死区和默认位置
 *
 *
 * ************************************************************************
 */
void Init_all_Controller_Joysticks(void)
{
    Init_Controller_Joystick(&Left_Joystick, 2000, OFFSET_POSITION, OFFSET_POSITION);

    Init_Controller_Joystick(&Right_Joystick, 2000, OFFSET_POSITION, OFFSET_POSITION);
}