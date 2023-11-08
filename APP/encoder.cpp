#include "encoder.h"
using namespace std;

// 电机方向
enum
{
    Negative = 0,
    Positive
};

// 编码器脉冲记录
void ENCODER_OUTPUT()
{
    switch (GPIO_Pin)
    {
    case ENCODER1_Pin:
        if (HAL_GPIO_ReadPin(motors[0].encoder.Speed_Direction_GPIOx,
                             motors[0].encoder.Speed_Direction_GPIO_Pin) == Positive)
        {
            motors[0].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[0].encoder.Hall_Encoder_Count--;
        }
        break;
    case ENCODER2_Pin:
        if (HAL_GPIO_ReadPin(motors[1].encoder.Speed_Direction_GPIOx,
                             motors[1].encoder.Speed_Direction_GPIO_Pin) == Negative)
        {
            motors[1].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[1].encoder.Hall_Encoder_Count--;
        }
        break;
    case ENCODER3_Pin:
        if (HAL_GPIO_ReadPin(motors[2].encoder.Speed_Direction_GPIOx,
                             motors[2].encoder.Speed_Direction_GPIO_Pin) == Positive)
        {
            motors[2].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[2].encoder.Hall_Encoder_Count--;
        }
        break;
    case ENCODER4_Pin:
        if (HAL_GPIO_ReadPin(motors[3].encoder.Speed_Direction_GPIOx,
                             motors[3].encoder.Speed_Direction_GPIO_Pin) == Negative)
        {
            motors[3].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[3].encoder.Hall_Encoder_Count--;
        }
        break;
    default:
        break;
    }
}
