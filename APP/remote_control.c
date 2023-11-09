#include "remote_control.h"

Controller_t xbox_t = {0};
ControllerJoystick_t Left_Joystick, Right_Joystick = {0};

void Init_Controller_Joystick(ControllerJoystick_t *Joystick,
							  int __deadband, int __stick_offset_position)
{
	Joystick->deadband = __deadband;
	Joystick->stick_offset_position = __stick_offset_position;
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
enum ButtonState getButtonState(uint8_t data, uint8_t mask)
{
	return (data & mask) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}

/**
 * ************************************************************************
 * @brief Receive data processing 接收数据处理
 *
 * @param[in] ptr  控制器结构体指针
 *
 * ************************************************************************
 */
static void Data_Resolve(Controller_t *ptr)
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
		ptr->L_Joystick_Hor = rx_p[1] | (rx_p[2] << 8);
		// The vertical travel of the left stick
		ptr->L_Joystick_Ver = rx_p[3] | (rx_p[4] << 8);
		// Horizontal stroke of the right stick
		ptr->R_Joystick_Hor = rx_p[5] | (rx_p[6] << 8);
		// The vertical stroke of the right stick
		ptr->R_Joystick_Ver = rx_p[7] | (rx_p[8] << 8);
		// Left trigger travel
		ptr->L_Trigger = rx_p[9] | (rx_p[10] << 8);
		// Right trigger stroke
		ptr->R_Trigger = rx_p[11] | (rx_p[12] << 8);
		// Joystick input combination
		ptr->combination = rx_p[13];
		// Buttons
		// 按键
		ptr->A = getButtonState(rx_p[14], 0x01);	   // 设置按钮 A 的状态
		ptr->B = getButtonState(rx_p[14], 0x02);	   // 设置按钮 B 的状态
		ptr->X = getButtonState(rx_p[14], 0x08);	   // 设置按钮 X 的状态
		ptr->Y = getButtonState(rx_p[14], 0x10);	   // 设置按钮 Y 的状态
		ptr->LB = getButtonState(rx_p[14], 0x40);	   // 设置按钮 LB 的状态
		ptr->LB = getButtonState(rx_p[14], 0x80);	   // 设置按钮 RB 的状态
		ptr->View = getButtonState(rx_p[15], 0x04);	   // 设置按钮 View 的状态
		ptr->Menu = getButtonState(rx_p[15], 0x08);	   // 设置按钮 Menu 的状态
		ptr->Xbox = getButtonState(rx_p[15], 0x10);	   // 设置按钮 Xbox 的状态
		ptr->press_L = getButtonState(rx_p[15], 0x20); // 设置按钮 press_L 的状态
		ptr->press_R = getButtonState(rx_p[15], 0x40); // 设置按钮 press_R 的状态
		ptr->Share = getButtonState(rx_p[16], 0x01);   // 设置按钮 Share 的状态
	}
	else
	{
		err = 1;
	}
}

void controller_data(void)
{
	if (recv_end_flag == 1 && rx_len == DATA_FRAME_LENGTH)
	{
		Data_Resolve(&xbox_t);

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
