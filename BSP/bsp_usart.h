#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#ifdef __cplusplus


extern "C"
{
#endif
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "dma.h"
#define ROS
// Defines the serial port receive buff length
//  定义串口接收buff长度,防止DMA传输越界
#define BUF_SIZE 36u
#define DATA_FRAME_LENGTH 18u

#define BUF_SIZE1 16u
#define DATA_FRAME_LENGTH1 8u

// Use DEFINE to improve code portability
// 用define提高代码易移植性
#define c_huart huart2
#define c_UART USART2
#define c_dma hdma_usart2_rx

#define c_huart1 huart1
#define c_UART1 USART1
#define c_dma1 hdma_usart1_rx

    void My_USART2_Init(void);

    extern DMA_HandleTypeDef c_dma;
    extern DMA_HandleTypeDef hdma_usart1_rx;
    
    extern uint8_t err;
    extern volatile uint8_t rx_len;
    extern volatile uint8_t recv_end_flag;
    extern uint8_t rx_buffer[BUF_SIZE];
#ifdef __cplusplus
}

#endif

#endif
