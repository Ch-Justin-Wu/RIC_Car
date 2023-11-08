#include "servos.h"
using namespace std;
//Servo_t Servo[4] = {0};

// class Servos
// {

// public:
//     uint16_t pwmVal;
//     float angle;
//     TIM_HandleTypeDef *ServosTIM;
//     uint32_t ServosChannel;
//     void Init();
//     void PWM_Val_Cacl(float _angle_);
//     void Control_Servo();
// };

Servos Servo[4]={0};

void Servos::Init(TIM_HandleTypeDef *__Servos_TIM,uint32_t __Servos_Channel)
{
    Servos_TIM=__Servos_TIM;
    Servos_Channel=__Servos_Channel;
}

void Servos::PWM_Val_Cacl(float _angle_)
{
    angle = _angle_;
    pwmVal = 500 + 2000.0f * _angle_ / 180.0f;
}

void Servos::Control_Servo()
{
    HAL_TIM_PWM_Start(Servos_TIM,Servos_Channel);
}
