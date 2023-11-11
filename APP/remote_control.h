#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_usart.h"
#include "usart.h"
#include "ws2812.h"
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
        PRESS_UP = 1,
        PRESS_RIGHT_AND_UP,
        PRESS_RIGHT = 3,
        PRESS_RIGHT_AND_DOWM,
        PRESS_DOWN = 5,
        PRESS_LEFT_AND_DOWN,
        PRESS_LEFT = 7,
        PRESS_LEFT_AND_UP
    };

    typedef struct
    {
        int H_diff;
        int V_diff;
        int H_stick_offset_position;
        int V_stick_offset_position;
        int deadband;
    } ControllerJoystick_t;

    extern ControllerJoystick_t Left_Joystick, Right_Joystick;

    void Init_Controller_Joystick(ControllerJoystick_t *Joystick,
                                  int __deadband, int __H_stick_offset_position, int __V_stick_offset_position);

    void DMA_Usart_Rx(uint8_t *Data, uint8_t len);

    void L_Joystick_Difference(ControllerJoystick_t *L_Joystick);
    
    void R_Joystick_Difference(ControllerJoystick_t *R_Joystick);
#ifdef __cplusplus
}
using namespace std;
class remote_control
{

public:
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

    uint8_t Red_flag;
    uint8_t Blue_flag;
    // Error flag
    // 错误标志位
    uint8_t err;

    enum ButtonState getButtonState(uint8_t data, uint8_t mask);
    void Controller_Data_Resolve(void);
    void Controller_Data_Rx(void);
    void Set_color(void);
};

extern remote_control Xbox;

#endif

#endif
