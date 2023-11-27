#include "remote_control.h"
using namespace std;

#define ABS(x) ((x > 0) ? (x) : (-x))

ControllerJoystick_t Left_Joystick, Right_Joystick = {0};
remote_control Xbox;

/**
 * ************************************************************************
 * @brief 控制器摇杆结构体初始化
 *
 * @param[in] Joystick  控制器摇杆结构体指针
 * @param[in] __deadband  摇杆死区
 * @param[in] __H_stick_offset_position  摇杆水平方向初始位置
 * @param[in] __V_stick_offset_position  摇杆垂直方向初始位置
 *
 * ************************************************************************
 */
void Init_Controller_Joystick(ControllerJoystick_t *Joystick,
							  int __deadband, int __H_stick_offset_position, int __V_stick_offset_position)
{
	Joystick->deadband = __deadband;
	Joystick->H_stick_offset_position = __H_stick_offset_position;
	Joystick->V_stick_offset_position = __V_stick_offset_position;
}

/**
 * ************************************************************************
 * @brief 左摇杆变化幅度计算
 *
 * @param[in] Joystick  控制器摇杆结构体指针
 *
 * ************************************************************************
 */
void L_Joystick_Difference(ControllerJoystick_t *Joystick)
{
	// 水平方向
	Joystick->H_diff = Xbox.L_Joystick_Hor - Joystick->H_stick_offset_position;
	// 死区控制
	if (Joystick->H_diff != 0 && ABS(Joystick->H_diff) < Joystick->deadband)
		Joystick->H_diff = 0;
	else if (Joystick->H_diff >= Joystick->deadband)
	{
		Joystick->H_diff = Joystick->H_diff - Joystick->deadband;
	}
	else if (Joystick->H_diff <= -(Joystick->deadband))
	{
		Joystick->H_diff = Joystick->H_diff + Joystick->deadband;
	}

	// 垂直方向
	Joystick->V_diff = Xbox.L_Joystick_Hor - Joystick->V_stick_offset_position;
	// 死区控制
	if (Joystick->V_diff != 0 && ABS(Joystick->V_diff) < Joystick->deadband)
		Joystick->V_diff = 0;
	else if (Joystick->V_diff >= Joystick->deadband)
	{
		Joystick->V_diff = Joystick->V_diff - Joystick->deadband;
	}
	else if (Joystick->V_diff <= -(Joystick->deadband))
	{
		Joystick->V_diff = Joystick->V_diff + Joystick->deadband;
	}
}

/**
 * ************************************************************************
 * @brief 右摇杆变化幅度计算
 *
 * @param[in] Joystick  控制器摇杆结构体指针
 *
 * ************************************************************************
 */
void R_Joystick_Difference(ControllerJoystick_t *Joystick)
{
	// 水平方向
	Joystick->H_diff = Xbox.R_Joystick_Hor - Joystick->H_stick_offset_position;
	// 死区控制
	if (Joystick->H_diff != 0 && ABS(Joystick->H_diff) < Joystick->deadband)
		Joystick->H_diff = 0;
	else if (Joystick->H_diff >= Joystick->deadband)
	{
		Joystick->H_diff = Joystick->H_diff - Joystick->deadband;
	}
	else if (Joystick->H_diff <= -(Joystick->deadband))
	{
		Joystick->H_diff = Joystick->H_diff + Joystick->deadband;
	}

	// 垂直方向
	Joystick->V_diff = Xbox.R_Joystick_Ver - Joystick->V_stick_offset_position;
	// 死区控制
	if (Joystick->V_diff != 0 && ABS(Joystick->V_diff) < Joystick->deadband)
		Joystick->V_diff = 0;
	else if (Joystick->V_diff >= Joystick->deadband)
	{
		Joystick->V_diff = Joystick->V_diff - Joystick->deadband;
	}
	else if (Joystick->V_diff <= -(Joystick->deadband))
	{
		Joystick->V_diff = Joystick->V_diff + Joystick->deadband;
	}
}

/**
 * @brief Get the state of a button from the given data using a bitmask.
 *
 * This function checks whether a specific bit (button) in the data is set (pressed)
 * or clear (not pressed) based on the provided mask.
 *
 * @param[in] data The data containing button states.
 * @param[in] mask The bitmask representing the button to be checked.
 * @return The state of the button (BUTTON_PRESSED or BUTTON_NOT_PRESSED).
 */
// 定义按钮状态的枚举
enum ButtonState
getButtonState(uint8_t data, uint8_t mask)
{
	return (data & mask) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}

/**
 * ************************************************************************
 * @brief 设置摇杆初始值
 * 
 * 
 * ************************************************************************
 */
void remote_control::Init()
{
	L_Joystick_Hor = OFFSET_POSITION;
	L_Joystick_Ver = OFFSET_POSITION;
	R_Joystick_Hor = OFFSET_POSITION;
	R_Joystick_Ver = OFFSET_POSITION;
}

/**
 * ************************************************************************
 * @brief Receive data processing 接收数据处理
 *
 * 
 * ************************************************************************
 */
void remote_control::controller_data_resolve(void)
{

	// 计数
	uint8_t temp_cnt = 0;

	// Takes the cached array address
	uint8_t *rx_p = rx_buffer;

	// Find header 0xA5 with loop optimization
	while (*rx_p != 0xA5 && temp_cnt <= 19)
	{
		temp_cnt++;
		rx_p++;
	}

	// Error flag
	err = 0;
	// Determine the frame header and end of the frame
	// 判断帧头和帧尾
	if (rx_p[0] == 0xA5 && rx_p[17] == 0xA6)
	{

		// Horizontal stroke of the left stick
		L_Joystick_Hor = rx_p[1] | (rx_p[2] << 8);
		// The vertical travel of the left stick
		L_Joystick_Ver = rx_p[3] | (rx_p[4] << 8);
		// Horizontal stroke of the right stick
		R_Joystick_Hor = rx_p[5] | (rx_p[6] << 8);
		// The vertical stroke of the right stick
		R_Joystick_Ver = rx_p[7] | (rx_p[8] << 8);
		// Left trigger travel
		L_Trigger = rx_p[9] | (rx_p[10] << 8);
		// Right trigger stroke
		R_Trigger = rx_p[11] | (rx_p[12] << 8);
		// Joystick input combination
		combination = rx_p[13];
		// Buttons
		// 按键
		A = getButtonState(rx_p[14], 0x01);		  // 设置按钮 A 的状态
		B = getButtonState(rx_p[14], 0x02);		  // 设置按钮 B 的状态
		X = getButtonState(rx_p[14], 0x08);		  // 设置按钮 X 的状态
		Y = getButtonState(rx_p[14], 0x10);		  // 设置按钮 Y 的状态
		LB = getButtonState(rx_p[14], 0x40);	  // 设置按钮 LB 的状态
		RB = getButtonState(rx_p[14], 0x80);	  // 设置按钮 RB 的状态
		View = getButtonState(rx_p[15], 0x04);	  // 设置按钮 View 的状态
		Menu = getButtonState(rx_p[15], 0x08);	  // 设置按钮 Menu 的状态
		Xbox = getButtonState(rx_p[15], 0x10);	  // 设置按钮 Xbox 的状态
		press_L = getButtonState(rx_p[15], 0x20); // 设置按钮 press_L 的状态
		press_R = getButtonState(rx_p[15], 0x40); // 设置按钮 press_R 的状态
		Share = getButtonState(rx_p[16], 0x01);	  // 设置按钮 Share 的状态
	}
	else
	{
		err = 1;
	}
}

/**
 * ************************************************************************
 * @brief 接收手柄数据包
 * 
 * 
 * ************************************************************************
 */
void remote_control::controller_data_rx(void)
{
	if (recv_end_flag == 1 && rx_len == DATA_FRAME_LENGTH)
	{
		controller_data_resolve();

		if (err == 1)
		{
			// printf("The data length is wrong!\n");
		}

		// Clear the count
		//  清除计数
		rx_len = 0;
		// Clear the Receive End flag
		//  清除接收结束标志
		recv_end_flag = 0;

		// Clear the receive cache to set each byte in the receive buffer to 0
		// 清除接收缓存,将接收缓存区的每个字节都置0
		memset(rx_buffer, 0, rx_len);
	}
	// Turn DMA reception back on
	//  重新打开DMA接收
	HAL_UART_Receive_DMA(&c_huart, rx_buffer, BUF_SIZE);
}

// B-red X-blue
// void remote_control::Set_color(void)
// {
	// if (B == 1 && X == 0)
	// {
	// 	Red_flag = 1;
	// 	Blue_flag = 0;
	// }
	// else if (B == 0 && X == 1)
	// {
	// 	Red_flag = 0;
	// 	Blue_flag = 1;
	// }

	// if (Red_flag == 1 && Blue_flag == 0)
	// {
	// 	ws2812_red(LED_NUM);
	// }
	// else if (Red_flag == 0 && Blue_flag == 1)
	// {
	// 	ws2812_blue(LED_NUM);
	// }
// }
