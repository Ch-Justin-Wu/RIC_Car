#ifndef ROBOT_MOVE_H
#define ROBOT_MOVE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "pid.h"
#include "main.h"
#include "ws2812.h"
#include "ROS2.h"

#ifdef __cplusplus
}

#include "chassis_move.h"
#include "remote_control.h"
#include "servos.h"
#include "motor.h"

namespace RobotControl
{
    extern volatile uint8_t K_Claw;
    extern volatile uint8_t K_Gimbal;
    extern volatile uint8_t K_Arm;
    extern volatile uint8_t K_Wrist;

    void control_robotic_arm();

}

#endif

#endif
