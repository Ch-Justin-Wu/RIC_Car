/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_usart.h"
#include <stdio.h>
#include "pid.h"
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

float setspeed = 1000;
float kp = 5;
float ki = 0.8;
float kd = 0;

float kp_ang_1 = 5.0f;
float ki_ang_1 = 0;
float kd_ang_1 = 0;

float kp_ang_2 = 17.0f;
float ki_ang_2 = 0;
float kd_ang_2 = 0;

float set_round1 = 3; //????
float set_round2 = 5; //????


float angle_setspeed_1;
float angle_setspeed_2;

int real_speed2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  // Rx_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  // CAN??????

  // PID?????
  // motor1
  // 初始�? PID 控制器参�?
  pid_init(&pid_angle[0], // Motor 1 Angle PID
           1500,          // Max Output Limit
           0,             // Integral Limit
           5,             // Deadband
           0,             // Max Error
           5.0f,          // Proportional Coefficient
           0.0f,          // Integral Coefficient
           0.0f);         // Derivative Coefficient

  pid_init(&pid_motor[0], // Motor 1 Motor PID
           8000,          // Max Output Limit
           3000,          // Integral Limit
           0,             // Deadband
           0,             // Max Error
           5.0f,          // Proportional Coefficient
           0.8f,          // Integral Coefficient
           0.0f);         // Derivative Coefficient
  // motor2
  pid_init(&pid_angle[1], // Motor 2 Angle PID
           2000,          // Max Output Limit
           0,             // Integral Limit
           5,             // Deadband
           0,             // Max Error
           17.0f,         // Proportional Coefficient
           0.0f,          // Integral Coefficient
           0.0f);         // Derivative Coefficient

  pid_init(&pid_motor[1], // Motor 2 Motor PID
           8000,          // Max Output Limit
           3000,          // Integral Limit
           0,             // Deadband
           0,             // Max Error
           4.0f,          // Proportional Coefficient
           0.02f,         // Integral Coefficient
           1.5f);         // Derivative Coefficient


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // Receive the Receive End flag
    // 接收完成标志

    if (recv_end_flag == 1 && rx_len == DATA_FRAME_LENGTH)
    {
      Data_Resolve(&xbox_t);

      if (err == 1)
      {
        printf("The data length is wrong!\n");
      }

      // Clear the count
      //  清除计数
      rx_len = 0;
      // Clear the Receive End flag
      //  清除接收结束标志
      recv_end_flag = 0;

      // Clear the receive cache to set each byte in the receive buffer to 0
      // 清除接收缓存,将接收缓存区�??的每�??字节都�?�置�??0
      memset(rx_buffer, 0, rx_len);
    }
    // Turn DMA reception back on
    //  重新打开DMA接收
    HAL_UART_Receive_DMA(&c_huart, rx_buffer, BUF_SIZE);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
