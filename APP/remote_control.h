#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif
#include "bsp_usart.h"
#include "usart.h"
    // 定义按钮状态的枚举
    enum ButtonState
    {
        BUTTON_NOT_PRESSED,
        BUTTON_PRESSED
    };
    // 方向键组合
    enum DirectionCombination
    {
        NO_PRESS = 0,
        PRESS_UP,
        PRESS_RIGHT_AND_UP,
        PRESS_RIGHT,
        PRESS_RIGHT_AND_DOWM,
        PRESS_DOWN,
        PRESS_LEFT_AND_DOWN,
        PRESS_LEFT,
        PRESS_LEFT_AND_UP
    };

    // Remote control data structure
    // 遥控器数据结构体
    typedef __packed struct
    {
        // Joystick horizontal stroke[0] + vertical stroke[1]
        // 摇杆 水平行程[0]+垂直行程[1]

        uint16_t L_Joystick_Hor; // 0--65535
        uint16_t L_Joystick_Ver; // 65535--0
        uint16_t R_Joystick_Hor; // 0--65535
        uint16_t R_Joystick_Ver; // 65535--0
        // trigger
        // 扳机
        uint16_t L_Trigger; // 0--1023
        uint16_t R_Trigger; // 0--1023
        // Buttons
        // 按键
        uint8_t A;
        uint8_t B;
        uint8_t X;
        uint8_t Y;
        uint8_t LB;
        uint8_t RB;
        uint8_t View;
        uint8_t Menu;
        uint8_t Xbox;
        uint8_t Share;
        // Joystick buttons
        // 摇杆按键
        uint8_t press_L;
        uint8_t press_R;
        // Joystick input combination
        // 输入组合
        uint8_t combination; // 0--8
    } Controller_t;

    extern Controller_t xbox_t;

    void DMA_Usart_Rx(uint8_t *Data, uint8_t len);

    void controller_data(void);
#ifdef __cplusplus
}
#endif

#endif
