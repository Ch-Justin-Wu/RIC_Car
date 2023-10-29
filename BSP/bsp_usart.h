/**
 * ************************************************************************
 *
 * @file bsp_usart.h
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief 遥控器数据结构体,变量和函数声明
 * @version 1.0
 * @date 2023-10-16
 *
 * ************************************************************************
 * @copyright Copyright (c) 2023 Justin Wu
 * For study and research only, no reprinting
 * ************************************************************************
 */

#ifndef __BSP_USART_H__
#define __BSP_USART_H__

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "dma.h"

// Defines the serial port receive buff length
//  定义串口接收buff长度,防止DMA传输越界
#define BUF_SIZE 36u
#define DATA_FRAME_LENGTH 18u

// Use DEFINE to improve code portability
// 用define提高代码易移植性
#define c_huart huart2
#define c_UART USART2
#define c_dma hdma_usart2_rx


extern DMA_HandleTypeDef c_dma;

// 定义按钮状态的枚举
enum ButtonState
{
	BUTTON_NOT_PRESSED,
	BUTTON_PRESSED
};

// Remote control data structure
// 遥控器数据结构体
typedef __packed struct
{
    // Joystick horizontal stroke[0] + vertical stroke[1]
    // 摇杆 水平行程[0]+垂直行程[1]
    uint16_t L_Joystick[2];
    uint16_t R_Joystick[2];
    // trigger
    // 扳机
    uint16_t L_Trigger;
    uint16_t R_Trigger;
    // Buttons
    // 按键
    enum ButtonState buttons[12];  // 使用枚举类型存储按钮状态
    
    // Joystick input combination
    // 输入组合
    uint8_t combination;
} Controller_t;



extern uint8_t *rx_p;
extern uint8_t err;
extern volatile uint8_t rx_len;
extern volatile uint8_t recv_end_flag;
extern uint8_t rx_buffer[BUF_SIZE];
extern Controller_t xbox_t;

// void Rx_Init(void);
void DMA_Usart_Rx(uint8_t *Data, uint8_t len);
void Data_Resolve(Controller_t* ptr);
void Print_Controller_Data(Controller_t* ptr);

#endif
