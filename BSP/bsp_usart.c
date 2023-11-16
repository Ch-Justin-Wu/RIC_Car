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

#if defined(Controller)
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
#endif

#if defined(ROS)
volatile uint8_t rx_len1 = 0;
volatile uint8_t recv_end_flag1 = 0;
uint8_t rx_buffer1[BUF_SIZE1] = {0};
#endif

#if defined(Controller)
void My_USART2_Init(void)
{
	// 不加收不到数据
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart2, rx_buffer, BUF_SIZE);
}
#endif

#if defined(ROS)
void My_USART1_Init(void)
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1, rx_buffer1, BUF_SIZE1);
}
#endif
#if defined(Controller)
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
 * @brief This function handles USART2 global interrupt.
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
#endif

#if defined(ROS)

void USART1_IRQHandler(void)
{

	uint32_t tmp_flag = 0;
	uint32_t temp;

	// Get the IDLE flag bit
	tmp_flag = __HAL_UART_GET_FLAG(&c_huart1, UART_FLAG_IDLE);

	if (tmp_flag != RESET)
	{
		// Clear the IDLE flag in UART
		__HAL_UART_CLEAR_IDLEFLAG(&c_huart1);

		// Clear the status register (SR)
		temp = c_huart1.Instance->SR;

		// Read data from DR (Data Register)
		temp = c_huart1.Instance->DR;

		HAL_UART_DMAStop(&c_huart1); // Stop DMA transfer

		// Get the number of untransmitted data in DMA
		temp = c_dma1.Instance->CNDTR;

		// Calculate the number of received data by subtracting the total count from the untransmitted data count
		rx_len = BUF_SIZE1 - temp;

		// Set the receive completion flag to 1
		recv_end_flag1 = 1;
	}

	HAL_UART_IRQHandler(&c_huart1);
}

#endif
