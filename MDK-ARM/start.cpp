#include "start.h"
#include "main.h"
#include "usart.h"
#include "string"
using namespace std;

//StringContainer container("Hello\n", "World\n", "NEUQ\n");



void startup()
{
	
	//bool i = true;
	//string str = "hello world!\n";
	while (1)
	{
		
		// //HAL_UART_Transmit(&huart1, (uint8_t *)str.data(), str.size(), 0xff);
		// HAL_UART_Transmit_DMA(&huart1,(uint8_t *)container.str1.data(),container.str1.size());
		// HAL_Delay(100);
		// HAL_UART_Transmit_DMA(&huart1,(uint8_t *)container.str2.data(),container.str2.size());
		// HAL_Delay(100);
		// HAL_UART_Transmit_DMA(&huart1,(uint8_t *)container.str3.data(),container.str3.size());
	}
}
