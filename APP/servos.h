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

#define Claw_MAX_ANGLE 85
#define Claw_MIN_ANGLE 55
#define Gimbal_MAX_ANGLE 180
#define Gimbal_MIN_ANGLE 0
#define Arm_MAX_ANGLE 73
#define Arm_MIN_ANGLE 44
#define Wrist_MAX_ANGLE 179
#define Wrist_MIN_ANGLE 1
class Servos
{
public:
    uint16_t pwmVal;
    float angle;

    void Init(TIM_HandleTypeDef __Servos_TIM, uint32_t __Servos_Channel, float __angle);
     void Control_Servo(float _angle_);
    void Control_Claw(void);
    void Control_Gimbal(void);
    void Control_Arm(void);
    void Control_Wrist(void);

protected:
    TIM_HandleTypeDef Servos_TIM;
    uint32_t Servos_Channel;
};

extern Servos Servo[4];
#endif

#endif
