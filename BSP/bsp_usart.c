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

/**
 * ************************************************************************
 * @brief @brief Print Controller Data 打印控制器数据
 *
 *
 * ************************************************************************
 */
// void Print_Controller_Data(Controller_t *ptr)
// {

// 	// 打印摇杆和扳机数据
// 	printf("摇杆水平行程:\n");
// 	printf("左: %d\n", ptr->L_Joystick[0]);
// 	printf("右: %d\n", ptr->R_Joystick[0]);
// 	printf("摇杆垂直行程:\n");
// 	printf("左: %d\n", ptr->L_Joystick[1]);
// 	printf("右: %d\n", ptr->R_Joystick[1]);

// 	// 打印扳机行程
// 	printf("扳机行程:\n");
// 	printf("左: %d\n", ptr->L_Trigger);
// 	printf("右: %d\n", ptr->R_Trigger);

// 	// 打印按钮状态
// 	printf("按键输入情况:\n");
// 	for (int i = 0; i < sizeof(buttonNames) / sizeof(buttonNames[0]); i++)
// 	{
// 		if (ptr->buttons[i] == BUTTON_PRESSED)
// 		{
// 			printf("按下 %s\n", buttonNames[i]);
// 		}
// 	}

// 	printf("Gamepad arrow keys input combination:\n");
// 	switch (ptr->combination)
// 	{
// 	case 0:
// 		printf("无输入\n");
// 		break;
// 	case 1:
// 		printf("上\n");
// 		break;
// 	case 2:
// 		printf("右+上\n");
// 		break;
// 	case 8:
// 		printf("左+上\n");
// 		break;
// 	case 5:
// 		printf("下\n");
// 		break;
// 	case 4:
// 		printf("右+下\n");
// 		break;
// 	case 6:
// 		printf("左+下\n");
// 		break;
// 	case 3:
// 		printf("右\n");
// 		break;
// 	case 7:
// 		printf("左\n");
// 		break;
// 	default:
// 		printf("Data error!\n");
// 		break;
// 	}
// }

