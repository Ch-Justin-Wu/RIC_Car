#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H
/* Includes ------------------------------------------------------------------*/
#include "bsp_usart.h"
#include "usart.h"

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
    enum ButtonState buttons[12]; // 使用枚举类型存储按钮状态

    // Joystick input combination
    // 输入组合
    uint8_t combination;
} Controller_t;

extern Controller_t xbox_t;

void DMA_Usart_Rx(uint8_t *Data, uint8_t len);
void Data_Resolve(Controller_t *ptr);
void controller_data(void);
#endif
