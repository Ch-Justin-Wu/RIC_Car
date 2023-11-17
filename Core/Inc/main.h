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
#define ENCODER3_Pin GPIO_PIN_13
#define ENCODER3_GPIO_Port GPIOC
#define SPEED_DIRECTION3_Pin GPIO_PIN_14
#define SPEED_DIRECTION3_GPIO_Port GPIOC
#define MOTO3_IN1_Pin GPIO_PIN_0
#define MOTO3_IN1_GPIO_Port GPIOA
#define MOTO3_IN2_Pin GPIO_PIN_1
#define MOTO3_IN2_GPIO_Port GPIOA
#define RX_ESP32_Pin GPIO_PIN_3
#define RX_ESP32_GPIO_Port GPIOA
#define MOTO4_IN1_Pin GPIO_PIN_6
#define MOTO4_IN1_GPIO_Port GPIOA
#define MOTO4_IN2_Pin GPIO_PIN_7
#define MOTO4_IN2_GPIO_Port GPIOA
#define MOTO1_IN1_Pin GPIO_PIN_0
#define MOTO1_IN1_GPIO_Port GPIOB
#define MOTO1_IN2_Pin GPIO_PIN_1
#define MOTO1_IN2_GPIO_Port GPIOB
#define MOTO2_IN1_Pin GPIO_PIN_10
#define MOTO2_IN1_GPIO_Port GPIOB
#define MOTO2_IN2_Pin GPIO_PIN_11
#define MOTO2_IN2_GPIO_Port GPIOB
#define SPEED_DIRECTION2_Pin GPIO_PIN_13
#define SPEED_DIRECTION2_GPIO_Port GPIOB
#define ENCODER2_Pin GPIO_PIN_14
#define ENCODER2_GPIO_Port GPIOB
#define SPEED_DIRECTION1_Pin GPIO_PIN_15
#define SPEED_DIRECTION1_GPIO_Port GPIOB
#define ENCODER1_Pin GPIO_PIN_8
#define ENCODER1_GPIO_Port GPIOA
#define TX_TO_ROS_Pin GPIO_PIN_9
#define TX_TO_ROS_GPIO_Port GPIOA
#define RX_ROS_Pin GPIO_PIN_10
#define RX_ROS_GPIO_Port GPIOA
#define SPEED_DIRECTION4_Pin GPIO_PIN_11
#define SPEED_DIRECTION4_GPIO_Port GPIOA
#define ENCODER4_Pin GPIO_PIN_12
#define ENCODER4_GPIO_Port GPIOA
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
