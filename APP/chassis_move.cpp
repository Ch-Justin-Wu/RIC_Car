#include "chassis_move.h"

namespace RobotControl{
    chassis Mec_Chassis;

/**
 * ************************************************************************
 * @brief Controller X Y Z speed set
 * 
 * 
 * 
 * ************************************************************************
 */
void chassis::controller_speed_set()
{
    R_Joystick_Difference(&Right_Joystick);
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
   
    if (Right_Joystick.H_diff)
    {
        vy_set = -(Right_Joystick.H_diff) * K_VY_SET;
    }
    else if (Right_Joystick.H_diff == 0)
    {
        vy_set = 0;
    }
    
    //Wz setting
    L_Joystick_Difference(&Left_Joystick);
    if (Left_Joystick.H_diff==0)
    {
        wz_set = 0;
    }
    
    else if (Left_Joystick.H_diff)
    {
        wz_set = -(Left_Joystick.H_diff)*2.7;
    }
    
    
}

/**
 * ************************************************************************
 * @brief 麦轮正向运动学解算
 * 
 * 
 * ************************************************************************
 */
void chassis::mec_chassis_wheel_speed()
{
    const fp32 k_wz = 0.22f;
    wheel_speed[0] = -vx_set - vy_set - k_wz * wz_set;
    wheel_speed[1] = vx_set - vy_set - k_wz * wz_set;
    wheel_speed[2] = vx_set + vy_set - k_wz * wz_set;
    wheel_speed[3] = -vx_set + vy_set - k_wz * wz_set;
}

// MAX wheel_speed=max_rpm*60 mm*PI

/**
 * ************************************************************************
 * @brief 处理ros速度
 * 
 * @param[in] ptr  ros速度数据结构体指针
 * 
 * ************************************************************************
 */
void chassis::ROS2_Speed_Set(Ros_cmd *ptr)
{
    vx_set = ptr->Vx;
    vy_set = ptr->Vy;
    wz_set = (ptr->Wz)*4;
}
}