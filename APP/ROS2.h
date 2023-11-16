#ifndef __ROS_H
#define __ROS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_usart.h"
#include "chassis_move.h"

typedef struct ROS2
{
    int16_t Vx;
    int16_t Vy;
    int16_t Wz;
}Ros_cmd;


#ifdef __cplusplus
}
#endif

#endif