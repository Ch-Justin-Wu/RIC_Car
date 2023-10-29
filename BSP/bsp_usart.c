/**
 * ************************************************************************
 *
 * @file bsp_usart.c
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief 数据包接收处理和打印
 * @version 1.0
 * @date 2023-10-16
 *
 * ************************************************************************
 * @copyright Copyright (c) 2023 Justin Wu
 * For study and research only, no reprinting
 * ************************************************************************
 */
#include "bsp_usart.h"
#include "stm32f1xx_it.h"
#include "stdio.h"

#include "main.h"
#include "pid.h"
#include "motor.h"
Controller_t xbox_t = {0};

// Error flag
// 错误标志位
uint8_t err;
// The length of one frame of data received
// 接收一帧数据的长度
volatile uint8_t rx_len = 0;
// A frame of data reception completion flag
// 一帧数据接收完成标志
volatile uint8_t recv_end_flag = 0;

// Define the serial port receiving buffer
//  定义串口接收缓存区
uint8_t rx_buffer[BUF_SIZE] = {0};

void DMA_Usart_Rx(uint8_t *Data, uint8_t len);
void Data_Resolve(Controller_t *ptr);
void Print_Controller_Data(Controller_t *ptr);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

/**
 * ************************************************************************
 * @brief Serial port receive function 串口接收封装
 *
 * @param[in] Data 数据地址 Data address
 * @param[in] len  数据长度 Data length
 *
 * ************************************************************************
 */
void DMA_Usart_Rx(uint8_t *Data, uint8_t len)
{
	// Turn DMA reception back on
	//  重新打开DMA接收
	HAL_UART_Receive_DMA(&c_huart, Data, len);
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART2_IRQHandler(void)
{

	uint32_t tmp_flag = 0;
	uint32_t temp;

	// Get the IDLE flag bit
	tmp_flag = __HAL_UART_GET_FLAG(&c_huart, UART_FLAG_IDLE);

	if (tmp_flag != RESET)
	{
		// Clear the IDLE flag in UART
		__HAL_UART_CLEAR_IDLEFLAG(&c_huart);

		// Clear the status register (SR)
		temp = c_huart.Instance->SR;

		// Read data from DR (Data Register)
		temp = c_huart.Instance->DR;

		HAL_UART_DMAStop(&c_huart); // Stop DMA transfer

		// Get the number of untransmitted data in DMA
		temp = c_dma.Instance->CNDTR;

		// Calculate the number of received data by subtracting the total count from the untransmitted data count
		rx_len = BUF_SIZE - temp;

		// Set the receive completion flag to 1
		recv_end_flag = 1;
	}

	HAL_UART_IRQHandler(&c_huart);
}

int fputc(int ch, FILE *f)

{

	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);

	return ch;
}

// 定义按钮名称的数组
const char *buttonNames[] = {
	"A", "B", "X", "Y", "LB", "RB", "View", "Menu", "Xbox", "press_L", "press_R", "Share"};

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
 *
 * ************************************************************************
 */
void Data_Resolve(Controller_t *ptr)
{

	// 计数
	uint8_t temp0 = 0;

	// Takes the cached array address
	uint8_t *rx_p = rx_buffer;

	// Find header 0xA5 with loop optimization
	while (*rx_p != 0xA5 && temp0 <= 19)
	{
		temp0++;
		rx_p++;
	}

	// Error flag
	err = 0;
	// Determine the frame header and end of the frame
	// 判断帧头和帧尾
	if (rx_p[0] == 0xA5 && rx_p[17] == 0xA6)
	{
		// Data_flag = 1;

		// Horizontal stroke of the left stick
		ptr->L_Joystick[0] = rx_p[1] | (rx_p[2] << 8);
		// The vertical travel of the left stick
		ptr->L_Joystick[1] = rx_p[3] | (rx_p[4] << 8);
		// Horizontal stroke of the right stick
		ptr->R_Joystick[0] = rx_p[5] | (rx_p[6] << 8);
		// The vertical stroke of the right stick
		ptr->R_Joystick[1] = rx_p[7] | (rx_p[8] << 8);
		// Left trigger travel
		ptr->L_Trigger = rx_p[9] | (rx_p[10] << 8);
		// Right trigger stroke
		ptr->R_Trigger = rx_p[11] | (rx_p[12] << 8);
		// Joystick input combination
		ptr->combination = rx_p[13];
		// Buttons
		// 按键
		ptr->buttons[0] = getButtonState(rx_p[14], 0x01);  // 设置按钮 A 的状态
		ptr->buttons[1] = getButtonState(rx_p[14], 0x02);  // 设置按钮 B 的状态
		ptr->buttons[2] = getButtonState(rx_p[14], 0x08);  // 设置按钮 X 的状态
		ptr->buttons[3] = getButtonState(rx_p[14], 0x10);  // 设置按钮 Y 的状态
		ptr->buttons[4] = getButtonState(rx_p[14], 0x40);  // 设置按钮 LB 的状态
		ptr->buttons[5] = getButtonState(rx_p[14], 0x80);  // 设置按钮 RB 的状态
		ptr->buttons[6] = getButtonState(rx_p[15], 0x04);  // 设置按钮 View 的状态
		ptr->buttons[7] = getButtonState(rx_p[15], 0x08);  // 设置按钮 Menu 的状态
		ptr->buttons[8] = getButtonState(rx_p[15], 0x10);  // 设置按钮 Xbox 的状态
		ptr->buttons[9] = getButtonState(rx_p[15], 0x20);  // 设置按钮 press_L 的状态
		ptr->buttons[10] = getButtonState(rx_p[15], 0x40); // 设置按钮 press_R 的状态
		ptr->buttons[11] = getButtonState(rx_p[16], 0x01); // 设置按钮 Share 的状态
	}
	else
	{
		err = 1;
	}
}

/**
 * ************************************************************************
 * @brief @brief Print Controller Data 打印控制器数据
 *
 *
 * ************************************************************************
 */
void Print_Controller_Data(Controller_t *ptr)
{

	// 打印摇杆和扳机数据
	printf("摇杆水平行程:\n");
	printf("左: %d\n", ptr->L_Joystick[0]);
	printf("右: %d\n", ptr->R_Joystick[0]);
	printf("摇杆垂直行程:\n");
	printf("左: %d\n", ptr->L_Joystick[1]);
	printf("右: %d\n", ptr->R_Joystick[1]);

	// 打印扳机行程
	printf("扳机行程:\n");
	printf("左: %d\n", ptr->L_Trigger);
	printf("右: %d\n", ptr->R_Trigger);

	// 打印按钮状态
	printf("按键输入情况:\n");
	for (int i = 0; i < sizeof(buttonNames) / sizeof(buttonNames[0]); i++)
	{
		if (ptr->buttons[i] == BUTTON_PRESSED)
		{
			printf("按下 %s\n", buttonNames[i]);
		}
	}

	printf("Gamepad arrow keys input combination:\n");
	switch (ptr->combination)
	{
	case 0:
		printf("无输入\n");
		break;
	case 1:
		printf("上\n");
		break;
	case 2:
		printf("右+上\n");
		break;
	case 8:
		printf("左+上\n");
		break;
	case 5:
		printf("下\n");
		break;
	case 4:
		printf("右+下\n");
		break;
	case 6:
		printf("左+下\n");
		break;
	case 3:
		printf("右\n");
		break;
	case 7:
		printf("左\n");
		break;
	default:
		printf("Data error!\n");
		break;
	}
}

/**
 * @brief Timer interrupt callback function
 *
 * @param htim Timer handle structure pointer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{

		static uint16_t timer_num = 0; // static variables to maintain their values
		static uint16_t print_count = 0;

		timer_num++;

		if (timer_num == 40 && err == 0)
		{
			print_count++;
			printf("--------------------------\n");
			printf("counts:%d\n", print_count);
			Print_Controller_Data(&xbox_t);
			if (print_count == 9)
			{
				print_count = 0;
			}
			timer_num = 0;
		}

		// 电机pid控制部分
		// pid_reset(&pid_angle[1], kp_ang_2, ki_ang_2, kd_ang_2);
		// 角速度计算

		// angle_setspeed_1=pid_calc(&pid_angle[0], (float)moto_chassis[0].total_angle/ 8192.0f * 360.0f-(float)moto_chassis[1].total_angle/ 8192.0f * 360.0f, 0.0f);
		//  PID 电流力矩计算

		short torque1 = pid_calc(&pid_motor[0], (float)moto_chassis[0].speed_rpm, 0);
		// can_cmd_send(torque1, torque2);
		// 角速度计算
		// angle_setspeed_2 = angle_speed_cacl(&moto_chassis[1],1, set_round2);
		// 力反馈角度差计算 PID输出 实现单向力反馈
		// angle_setspeed_2=pid_calc(&pid_angle[1], (float)moto_chassis[1].total_angle/ 8192.0f * 360.0f-(float)moto_chassis[0].total_angle/ 8192.0f * 360.0f, 0.0f);

		//  PID 电流力矩计算

		short torque2 = pid_calc(&pid_motor[1], (float)moto_chassis[1].speed_rpm, 0);
		// real_speed2 = moto_chassis[1].speed_rpm;
	}
}
