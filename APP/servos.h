#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#include "remote_control.h"
namespace RobotControl
{

#define ClAW_MAX_ANGLE 85
#define ClAW_MIN_ANGLE 30
#define GIMBAL_MAX_ANGLE 164
#define GIMBAL_MIN_ANGLE 0
#define ARM_MAX_ANGLE 73
#define ARM_MIN_ANGLE 44
#define WRIST_MAX_ANGLE 179
#define WRIST_MIN_ANGLE 1
    class Servos
    {
    public:
        

        void Init(TIM_HandleTypeDef __Servos_TIM, uint32_t __Servos_Channel, float __angle);
        void control_servo(float _angle_);
        void control_claw(void);
        void control_gimbal(void);
        void control_arm(void);
        void control_wrist(void);

    private:
        uint16_t pwmVal;
        float angle;
        TIM_HandleTypeDef Servos_TIM;
        uint32_t Servos_Channel;
    };

    extern Servos Servo[4];
}

#endif
