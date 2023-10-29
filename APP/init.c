#include "init.h"



void init_all_pid(void)
{
    pid_init(&pid_motor[0],    // Motor 1 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR1,        // Proportional Coefficient
             KI_MOTOR1,        // Integral Coefficient
             KD_MOTOR1);       // Derivative Coefficient
    // motor2

    pid_init(&pid_motor[1],    // Motor 2 Motor PID
             MAX_OUTPUT_LIMIT, // Max Output Limit
             INTEGRAL_LIMIT,   // Integral Limit
             DEADBAND,         // Deadband
             MAX_ERROR,        // Max Error
             KP_MOTOR2,        // Proportional Coefficient
             KI_MOTOR2,        // Integral Coefficient
             KD_MOTOR2);
} // Derivative Coefficient

void init_all_func(void)
{
    init_all_pid();
}
