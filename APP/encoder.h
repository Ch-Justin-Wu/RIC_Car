/**
 * ************************************************************************
 * 
 * @file encoder.h
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief 编码器信号捕获头文件
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

#include "main.h"
#include "gpio.h"
#define ENCODER_OUTPUT() HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
#ifdef __cplusplus
}
#include "motor.h"
#endif


