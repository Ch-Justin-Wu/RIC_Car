#ifndef CHASSIS_MOVE_H
#define CHASSIS_MOVE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "struct_typedef.h"
#include "motor.h"
#include "remote_control.h"
#include "pid.h"

#define CHASSIS_WZ_SET_SCALE 0.1f
#define MOTOR_DISTANCE_TO_CENTER 0.2f

#ifdef __cplusplus
}
using namespace std;

class chassis
{
private:
public:
    fp32 vx_set;
    fp32 vy_set;
    fp32 wz_set;
    fp32 wheel_speed[4];
    void XYZ_speed_set();
    void Mec_chassis_wheel_speed(fp32 vx_set,fp32 vy_set,fp32 wz_set);
};

#endif

#endif
