/**
 * ************************************************************************
 *
 * @file chassis_move.h
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief 底盘控制类定义
 * @version 1.0
 * @date 2023-11-30
 *
 * ************************************************************************
 * @copyright Copyright (c) 2023 Justin Wu
 * For study and research only, no reprinting
 * ************************************************************************
 */
#pragma once

#include "motor.h"
#include "remote_control.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "struct_typedef.h"
#include "pid.h"
#include "ROS2.h"

#ifdef __cplusplus
}

#define BASE 82.0f
#define TRACK 125.0f
#define WHEEL_R 30.0f
#define WHEEL_D 60.0f
#define K_VX_SET 24.5f
#define K_VY_SET 0.82f

namespace RobotControl
{
    class chassis
    {

    public:
        fp32 vx_set;
        fp32 vy_set;
        fp32 wz_set;
        fp32 wheel_speed[4];
        void controller_speed_set();
        void mec_chassis_wheel_speed();
        void ROS2_Speed_Set(Ros_cmd *ptr);
    };
    extern chassis Mec_Chassis;

} /* namespace RobotControl */
#endif
