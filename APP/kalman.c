#include "kalman.h"

kalman kfp[motor_num] = {0};

/**
 * ************************************************************************
 * @brief 卡尔曼结构体初始化
 *
 * @param[in] ptr  卡尔曼结构体指针
 *
 * ************************************************************************
 */
void kalman_init(kalman *ptr)
{
    // 初始化P矩阵，用于存储上一次的值
    ptr->Last_P = 0.001;
    // 初始化P矩阵，用于存储当前的值
    ptr->Now_P = 0;
    // 初始化输出值
    ptr->out = 0;
    // 初始化Kg，用于存储Kalman增益
    ptr->Kg = 0;
    // 初始化Q矩阵，用于存储状态转移矩阵的协方差
    ptr->Q = 0.0001;
    // 初始化R矩阵，用于存储测量噪声的协方差
    ptr->R = 0.0005;
}
/**
 *@brief  卡尔曼滤波器
 *@param kfp 卡尔曼结构体参数
 *@param input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float kalman_filter(kalman *kfp, float input)
{
    // 预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    kfp->Now_P = kfp->Last_P + kfp->Q;
    // 卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
    kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
    // 更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    kfp->out = kfp->out + kfp->Kg * (input - kfp->out); // 因为这一次的预测值就是上一次的输出值
    // 更新协方差方程: 本次的系统协方差付给 kfp->LastP 威下一次运算准备。
    kfp->Last_P = (1 - kfp->Kg) * kfp->Now_P;
    return kfp->out;
}
