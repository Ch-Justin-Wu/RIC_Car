/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENCODER_A1_Pin GPIO_PIN_0
#define ENCODER_A1_GPIO_Port GPIOA
#define ENCODER_B1_Pin GPIO_PIN_1
#define ENCODER_B1_GPIO_Port GPIOA
#define ENCODER_A2_Pin GPIO_PIN_6
#define ENCODER_A2_GPIO_Port GPIOA
#define ENCODER_B2_Pin GPIO_PIN_7
#define ENCODER_B2_GPIO_Port GPIOA
#define IN2_2_Pin GPIO_PIN_12
#define IN2_2_GPIO_Port GPIOB
#define IN2_1_Pin GPIO_PIN_13
#define IN2_1_GPIO_Port GPIOB
#define IN1_2_Pin GPIO_PIN_14
#define IN1_2_GPIO_Port GPIOB
#define IN1_1_Pin GPIO_PIN_15
#define IN1_1_GPIO_Port GPIOB
#define PWMA_1_Pin GPIO_PIN_8
#define PWMA_1_GPIO_Port GPIOA
#define PWMA_2_Pin GPIO_PIN_9
#define PWMA_2_GPIO_Port GPIOA
#define PWMB_1_Pin GPIO_PIN_10
#define PWMB_1_GPIO_Port GPIOA
#define PWMB_2_Pin GPIO_PIN_11
#define PWMB_2_GPIO_Port GPIOA
#define SERVO1_Pin GPIO_PIN_6
#define SERVO1_GPIO_Port GPIOB
#define SERVO2_Pin GPIO_PIN_7
#define SERVO2_GPIO_Port GPIOB
#define SERVO3_Pin GPIO_PIN_8
#define SERVO3_GPIO_Port GPIOB
#define SERVO4_Pin GPIO_PIN_9
#define SERVO4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
