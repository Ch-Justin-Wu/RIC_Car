/**
 * ************************************************************************
 * 
 * @file pid.h
 * @author Justin Wu (justin.wu@zllcrm.org)
 * @brief pid结构体定义
 * @version 1.0
 * @date 2023-11-30
 * 
 * ************************************************************************
 * @copyright Copyright (c) 2023 Justin Wu 
 * For study and research only, no reprinting
 * ************************************************************************
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f1xx_hal.h"
  // 枚举
  enum
  {
    LAST = 0,
    NOW = 1,
  };

  enum Flag
  {
    OFF = 0,
    ON = 1
  };
  /**
   * @brief     PID 结构体
   */
  typedef struct
  {
    /* p、i、d参数 */
    float p;
    float i;
    float d;

    /* 目标值、反馈值、误差值 */
    float set;
    float get;
    float err[2];

    /* p、i、d各项计算出的输出 */
    float pout;
    float iout;
    float dout;

    /* pid公式计算出的总输出 */
    float out;

    float max_err;
    float deadband; // err < deadband return
    /* pid最大输出限制  */
    float max_output;

    /* pid积分输出项限幅 */
    float integral_limit;
    /* pid积分分离设置 */
    float separationThreshold;
    // 自适应Kp
    float k1;
    float k2;
    float k3;
  } pid_t;

  void pid_init(pid_t *pid, uint32_t max_out, uint32_t intergral_limit, float Deadband, float Max_err, float kp, float ki, float kd, uint16_t __separationThreshold);

  // void pid_reset(pid_t *pid, float kp, float ki, float kd);

  float pid_calc(pid_t *pid, float get, float set);

  extern pid_t pid_motor[];

#ifdef __cplusplus
}
#endif
