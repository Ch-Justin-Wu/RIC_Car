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

  /**
   * @brief     PID 初始化函数
   * @param[in] pid: PID 结构体
   * @param[in] max_out: 最大输出
   * @param[in] intergral_limit: 积分限幅
   * @param[in] kp/ki/kd: 具体 PID 参数
   */
  void pid_init(pid_t *pid, uint32_t max_out, uint32_t intergral_limit, float Deadband, float Max_err, float kp, float ki, float kd, uint16_t __separationThreshold);

  /**
   * @brief     PID 参数复位函数
   * @param[in] pid: PID 结构体
   * @param[in] kp/ki/kd: 具体 PID 参数
   */
  // void pid_reset(pid_t *pid, float kp, float ki, float kd);

  /**
   * @brief     PID 计算函数，使用位置式 PID 计算
   * @param[in] pid: PID 结构体
   * @param[in] get: 反馈数据
   * @param[in] set: 目标数据
   * @retval    PID 计算输出
   */
  float pid_calc(pid_t *pid, float get, float set);

  extern pid_t pid_motor[];

// extern pid_t pid_motor2;
// extern pid_t pid_angle2;
#ifdef __cplusplus
}
#endif
