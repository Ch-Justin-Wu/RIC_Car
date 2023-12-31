#include "chassis_move.h"

using namespace std;
chassis Mec_Chassis;

/**
 * ************************************************************************
 * @brief 
 * 
 * @param[in] ptr  手柄结构体指针
 * 
 * 
 * ************************************************************************
 */
inline void chassis::XYZ_speed_set()
{
    //Vx setting
    if (Xbox.R_Trigger == 0 && Xbox.L_Trigger==0)
    {
        vx_set = 0;
    }

    else if ((Xbox.R_Trigger) > 0 && Xbox.L_Trigger == 0)
    {
        vx_set=(Xbox.R_Trigger)*K_VX_SET;
    }
    //-x方向速度设置
    else if ((Xbox.L_Trigger) > 0 && Xbox.R_Trigger == 0)
    {
        vx_set = -(Xbox.L_Trigger) * K_VX_SET;
    }
    //Vy setting

    //Wz setting
    L_Joystick_Difference(&Left_Joystick);
    if (Left_Joystick.H_diff==0)
    {
        wz_set = 0;
    }
    
    else if (Left_Joystick.H_diff)
    {
        wz_set = -(Left_Joystick.H_diff);
    }
    
}

/**
 * ************************************************************************
 * @brief 
 * 
 * @param[in] vx_set  x轴线速度
 * @param[in] vy_set  y轴线速度
 * @param[in] wz_set  z轴角速度
 * @param[in] wheel_speed  轮子线速度
 * 
 * ************************************************************************
 */
inline void chassis::Mec_chassis_wheel_speed(fp32 vx_set,fp32 vy_set,fp32 wz_set)
{
    wheel_speed[0] = -vx_set - vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[1] = vx_set - vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[2] = vx_set + vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[3] = -vx_set + vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
}

// MAX wheel_speed=300 RPM*60 mm*PI
