#include "start.h"
#include "main.h"
#include "usart.h"
#include "string"
using namespace std;

void startup()
{
	
	bool i = true;
	string str = "hello world!\n";
	while (i)
	{
		HAL_Delay(100);
		//HAL_UART_Transmit(&huart1, (uint8_t *)str.data(), str.size(), 0xff);
		HAL_UART_Transmit_DMA(&huart1,(uint8_t *)str.data(),str.size());
	}
}
