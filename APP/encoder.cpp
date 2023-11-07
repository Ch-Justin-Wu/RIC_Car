#include "encoder.h"
using namespace std;

//电机方向
enum
{
    Negative = 0,
    Positive
};

void ENCODER_OUTPUT()
{
    switch (GPIO_Pin)
    {
    case ENCODER1_Pin:
        if (HAL_GPIO_ReadPin(GPIOC, SPEED_DIRECTION1_Pin) == Positive)
        {
            motors[0].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[0].encoder.Hall_Encoder_Count--;
        }
        break;
    case ENCODER2_Pin:
        if (HAL_GPIO_ReadPin(GPIOC, SPEED_DIRECTION2_Pin) == Positive)
        {
            motors[1].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[1].encoder.Hall_Encoder_Count--;
        }
        break;
    case ENCODER3_Pin:
        if (HAL_GPIO_ReadPin(GPIOC, SPEED_DIRECTION3_Pin) == Positive)
        {
            motors[2].encoder.Hall_Encoder_Count++;
        }
        else
        {
            motors[2].encoder.Hall_Encoder_Count--;
        }
        break;
    case ENCODER4_Pin:
        if (HAL_GPIO_ReadPin(GPIOC, SPEED_DIRECTION4_Pin) == Positive)
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
