#ifndef INIT_H
#define INIT_H

#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart.h"
#include <stdio.h>
#include "pid.h"
#include "motor.h"

#ifdef __cplusplus
extern "C"
{
#endif
void init_all_func(void);
#ifdef __cplusplus
}
#endif



#endif
