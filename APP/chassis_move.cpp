#include "chassis_move.h"
#include "struct_typedef.h"
using namespace std;
void Mec_chassis_wheel_speed(const fp32 vx_set,const fp32 vy_set,const fp32 wz_set,fp32 wheel_speed[4]);

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
void Mec_chassis_wheel_speed(const fp32 vx_set,const fp32 vy_set,const fp32 wz_set,fp32 wheel_speed[4])
{
    wheel_speed[0] = -vx_set - vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[1] = vx_set - vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[2] = vx_set + vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[3] = -vx_set + vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
}



