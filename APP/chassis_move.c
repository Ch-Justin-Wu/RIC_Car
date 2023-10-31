#include "chassis_move.h"
#include "struct_typedef.h"

void Mec_chassis_wheel_speed(const fp32 vx_set,const fp32 vy_set,const fp32 wz_set,fp32 wheel_speed[4]);


void Mec_chassis_wheel_speed(const fp32 vx_set,const fp32 vy_set,const fp32 wz_set,fp32 wheel_speed[4])
{
    wheel_speed[0] = -vx_set - vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[1] = vx_set - vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[2] = vx_set + vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
    wheel_speed[3] = -vx_set + vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * wz_set;
}



