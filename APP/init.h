#ifndef INIT_H
#define INIT_H

#include "motor.h"
#include "servos.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart.h"
#include <stdio.h>
#include "pid.h"
    void Init_all_func(void);
#ifdef __cplusplus
}
#endif

#endif
