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


