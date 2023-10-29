#include "pid.h"
#include <math.h>
#include "motor.h"
#define ABS(x) ((x > 0) ? (x) : (-x))
// 电机速度 PID 结构体定义
pid_t pid_motor[motor_num] = {0}; //速度环
pid_t pid_angle[motor_num] = {0}; //角度环
// pid_t pid_motor2 = {0};
// pid_t pid_angle2 = {0};

void abs_limit(float *a, float ABS_MAX)
{
    if (*a > ABS_MAX)
        *a = ABS_MAX;
    if (*a < -ABS_MAX)
        *a = -ABS_MAX;
}

/**
 * @brief 初始化PID控制器参数
 *
 * @param pid       要初始化的PID控制器
 * @param max_out   最大输出限制
 * @param integral_limit 积分限制
 * @param Deadband  死区值
 * @param Max_err   最大误差
 * @param kp        比例系数
 * @param ki        积分系数
 * @param kd        微分系数
 */
void pid_init(pid_t *pid, uint32_t max_out, uint32_t intergral_limit, float Deadband, float Max_err, float kp, float ki, float kd)
{
    pid->integral_limit = intergral_limit;
    pid->max_output = max_out;
    pid->deadband = Deadband;
    pid->max_err = Max_err;

    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
}

/**
 * @brief     PID 计算函数，使用位置式 PID 计算
 * @param[in] pid: PID 结构体
 * @param[in] get: 反馈数据
 * @param[in] set: 目标数据
 * @retval    PID 计算输出
 */
float pid_calc(pid_t *pid, float get, float set)
{
    // Set the current error value
    pid->get = get;
    pid->set = set;
    pid->err[NOW] = set - get;

    // Check if the current error is beyond the maximum error limit
    if (pid->max_err != 0 && ABS(pid->err[NOW]) > pid->max_err)
        return 0;

    // Check if the current error is within the deadband range
    if (pid->deadband != 0 && ABS(pid->err[NOW]) < pid->deadband)
        return 0;  // Deadband control

    // Calculate the proportional component
    pid->pout = pid->p * pid->err[NOW];

    // Update the integral component
    pid->iout += pid->i * pid->err[NOW];

    // Calculate the derivative component
    pid->dout = pid->d * (pid->err[NOW] - pid->err[LAST]);

    // Limit the integral component
    abs_limit(&(pid->iout), pid->integral_limit);

    // Calculate the total control output
    pid->out = pid->pout + pid->iout + pid->dout;

    // Limit the total control output
    abs_limit(&(pid->out), pid->max_output);

    // Update the error for the next iteration
    pid->err[LAST] = pid->err[NOW];

    return pid->out;
}


/**
 * @brief     PID 参数复位函数
 * @param[in] pid: PID 结构体
 * @param[in] kp/ki/kd: 具体 PID 参数
 */
void pid_reset(pid_t *pid, float kp, float ki, float kd)
{
    pid->p = kp;
    pid->i = ki;
    pid->d = kd;

    // pid->pout = 0;
    // pid->iout = 0;
    // pid->dout = 0;
    // pid->out = 0;
}


