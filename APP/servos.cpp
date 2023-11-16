#include "servos.h"
using namespace std;

Servos Servo[4];

/**
 * ************************************************************************
 * @brief 舵机类初始化
 *
 * @param[in] __Servos_TIM  舵机定时器
 * @param[in] __Servos_Channel  PWM通道
 *
 * ************************************************************************
 */
void Servos::Init(TIM_HandleTypeDef __Servos_TIM, uint32_t __Servos_Channel, float __angle)
{
    angle = __angle;
    pwmVal = 500 + 2000.0f * __angle / 180.0f;
    Servos_TIM = __Servos_TIM;
    Servos_Channel = __Servos_Channel;
    HAL_TIM_PWM_Start(&__Servos_TIM, __Servos_Channel);
}

/**
 * ************************************************************************
 * @brief 计算输出的PWM
 *
 * @param[in] _angle_  设定的角度
 *
 * ************************************************************************
 */
void Servos::PWM_Val_Cacl(float _angle_)
{
    angle = _angle_;
    pwmVal = 500 + 2000.0f * _angle_ / 180.0f;
}

/**
 * ************************************************************************
 * @brief 舵机控制
 *
 *
 * ************************************************************************
 */
void Servos::Control_Servo(float _angle_)
{
    angle = _angle_;
    pwmVal = 500 + 2000.0f * _angle_ / 180.0f;
    __HAL_TIM_SET_COMPARE(&Servos_TIM, Servos_Channel, pwmVal);
}

// #define K_Claw 0.001
// PB9
void Servos::Control_Claw(void)
{
    if (Xbox.RB && angle <= Claw_MAX_ANGLE)
    {
        angle += 1;
        if (angle > Claw_MAX_ANGLE)
        {
            angle = Claw_MAX_ANGLE;
        }
    }

    else if (Xbox.LB && angle >= Claw_MIN_ANGLE)
    {
        angle -= 1;
        if (angle < Claw_MIN_ANGLE)
        {
            angle = Claw_MIN_ANGLE;
        }
    }
    Control_Servo(angle);
}

// PB6 Servo[0]
void Servos::Control_Gimbal(void)
{
    if ((Xbox.combination == PRESS_LEFT || Xbox.combination == PRESS_LEFT_AND_UP || Xbox.combination == PRESS_LEFT_AND_DOWN) && angle <= Gimbal_MAX_ANGLE)
    {
        angle += 1;
        if (angle > Gimbal_MAX_ANGLE)
        {
            angle = Gimbal_MAX_ANGLE;
        }
    }
    else if ((Xbox.combination == PRESS_RIGHT || Xbox.combination == PRESS_RIGHT_AND_DOWM || Xbox.combination == PRESS_RIGHT_AND_UP) && angle >= Gimbal_MIN_ANGLE)
    {
        angle -= 1;
    }
    if (angle < Gimbal_MIN_ANGLE)
    {
        angle = Gimbal_MIN_ANGLE;
    }
    Control_Servo(angle);
}

// PB7
void Servos::Control_Arm(void)
{
    // R_Joystick_Difference(&Right_Joystick);

    if ((Xbox.combination == PRESS_DOWN || Xbox.combination == PRESS_LEFT_AND_DOWN || Xbox.combination == PRESS_RIGHT_AND_DOWM) && angle <= Arm_MAX_ANGLE)
    {
        angle += 1;
        if (angle > Arm_MAX_ANGLE)
        {
            angle = Arm_MAX_ANGLE;
        }
    }
    else if ((Xbox.combination == PRESS_UP || Xbox.combination == PRESS_LEFT_AND_UP || Xbox.combination == PRESS_RIGHT_AND_UP) && angle >= Arm_MIN_ANGLE)
    {
        angle -= 1;
    }
    if (angle < Arm_MIN_ANGLE)
    {
        angle = Arm_MIN_ANGLE;
    }
    Control_Servo(angle);
}

//PB8
void Servos::Control_Wrist(void)
{
    
    if (Xbox.A && angle <= Wrist_MAX_ANGLE)
    {
        angle += 1;
        if (angle > Wrist_MAX_ANGLE)
        {
            angle = Wrist_MAX_ANGLE;
        }
    }

    else if (Xbox.Y && angle >= Wrist_MIN_ANGLE)
    {
        angle -= 1;
        if (angle < Wrist_MIN_ANGLE)
        {
            angle = Wrist_MIN_ANGLE;
        }
    }
    Control_Servo(angle);
}