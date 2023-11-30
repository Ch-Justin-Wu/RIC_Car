/**
 * ************************************************************************
 * 
 * @file ROS2.h
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief ros数据结构体定义
 * @version 1.0
 * @date 2023-11-30
 * 
 * ************************************************************************
 * @copyright Copyright (c) 2023 Justin Wu 
 * For study and research only, no reprinting
 * ************************************************************************
 */
#pragma once

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
    } Ros_cmd;

    extern Ros_cmd Ros2;
    void ROS2_data_rx(void);
#ifdef __cplusplus
}
#endif
