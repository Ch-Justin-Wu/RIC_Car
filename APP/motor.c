
#include "motor.h"
#include "pid.h"
#include "bsp_usart.h"
moto_measure_t moto_chassis[motor_num] = {0}; // 4 chassis moto
moto_measure_t moto_info;





// MotorData_t motors[motor_num];

// /**
//  * @brief 初始化电机数据
//  */
// void init_motor_data() {
//     for (int i = 0; i < motor_num; i++) {
//         motors[i].real_total_angle = 0.0f;
//         motors[i].angle_setspeed = 0.0f;
//         motors[i].set_angle = 0.0f;
//         motors[i].actual_round = 0.0f;
//         motors[i].pid_angle = &pid_angle[i];
//     }
// }

// /**
//  * @brief 角速度计算
//  *
//  * @param moto_chassis
//  * @param k
//  * @param set_round
//  * @return float
//  */
// float angle_speed_cacl(moto_measure_t moto_chassis[], u8 k, float set_round)
// {
//     MotorData_t* motor = &motors[k];
    
//     get_total_angle(&moto_chassis[k]);
//     // 减速比3591/187  计算设定总角度
//     motor->set_angle = (float)set_round * 360.0f * 3591.0f / 187.0f;
    
//     // 换算实际总角度
//     motor->real_total_angle = (float)moto_chassis[k].total_angle / 8192.0f * 360.0f;

//     motor->actual_round = (float)moto_chassis[k].total_angle / 8192.0f * 187.0f / 3591.0f;
    
//     // 通过角度环计算设定(角)速度
//     motor->angle_setspeed = pid_calc(motor->pid_angle, motor->real_total_angle, motor->set_angle);

//     return motor->angle_setspeed;
// }


// float real_total_angle[motor_num];
// float angle_setspeed[motor_num];
// float set_angle[motor_num];
// // float actual_round;

// /**
//  * @brief 角速度计算
//  *
//  * @param set_round
//  * @return float
//  */
// float angle_speed_cacl(moto_measure_t moto_chassis[], u8 k, float set_round)
// {
    
//     set_angle[k] = set_round * 360.0f * 3591.0f / 187.0f;                  // 减速比3591/187  计算设定总角度 36.0f/1.0f
//     real_total_angle[k] = moto_chassis[k].total_angle / 8192.0f * 360.0f; // 换算实际总角度
//     actual_round[k] = (float)moto_chassis[k].total_angle / 8192.0f * 187.0f / 3591.0f;
//     angle_setspeed[k] = pid_calc(&pid_angle[k], real_total_angle[k], set_angle[k]); // 通过角度环计算设定(角)速度
//     return angle_setspeed[k];
// }





