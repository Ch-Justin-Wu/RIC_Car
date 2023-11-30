#pragma once

#include "motor.h"
#include "servos.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "ws2812.h"
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "pid.h"
#include "kalman.h"
    void Init_all_func(void);
#ifdef __cplusplus
}
#endif

