#ifndef SERVOS_H
#define SERVOS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "remote_control.h"

#ifdef __cplusplus
}
using namespace std;

class Servos
{
public:
    uint16_t pwmVal;
    float angle;

    void Init(TIM_HandleTypeDef __Servos_TIM, uint32_t __Servos_Channel);
    void PWM_Val_Cacl(float _angle_);
    void Control_Servo();

protected:
    TIM_HandleTypeDef Servos_TIM;
    uint32_t Servos_Channel;
};

extern Servos Servo[4];
#endif

#endif
