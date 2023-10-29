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
#define ENC_A1_Pin GPIO_PIN_13
#define ENC_A1_GPIO_Port GPIOC
#define ENC_B1_Pin GPIO_PIN_14
#define ENC_B1_GPIO_Port GPIOC
#define ENC_A2_Pin GPIO_PIN_4
#define ENC_A2_GPIO_Port GPIOA
#define ENC_B2_Pin GPIO_PIN_5
#define ENC_B2_GPIO_Port GPIOA
#define IN4_1_Pin GPIO_PIN_1
#define IN4_1_GPIO_Port GPIOB
#define IN4_2_Pin GPIO_PIN_2
#define IN4_2_GPIO_Port GPIOB
#define IN3_1_Pin GPIO_PIN_10
#define IN3_1_GPIO_Port GPIOB
#define IN3_2_Pin GPIO_PIN_11
#define IN3_2_GPIO_Port GPIOB
#define IN2_2_Pin GPIO_PIN_12
#define IN2_2_GPIO_Port GPIOB
#define IN2_1_Pin GPIO_PIN_13
#define IN2_1_GPIO_Port GPIOB
#define IN1_2_Pin GPIO_PIN_14
#define IN1_2_GPIO_Port GPIOB
#define IN1_1_Pin GPIO_PIN_15
#define IN1_1_GPIO_Port GPIOB
#define motor1_pwm_Pin GPIO_PIN_8
#define motor1_pwm_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define motor_num 2

  extern float setspeed;
  extern float kp;
  extern float ki;
  extern float kd;

  extern float kp_ang_1;
  extern float ki_ang_1;
  extern float kd_ang_1;

  extern float kp_ang_2;
  extern float ki_ang_2;
  extern float kd_ang_2;

  extern float set_round1; //设置圈数
  extern float set_round2; //设置圈数
  extern float actual_round[motor_num];
  extern float angle_setspeed_1;
  extern float angle_setspeed_2;
  extern int real_speed2;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
