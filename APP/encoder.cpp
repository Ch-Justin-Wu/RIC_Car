#include "encoder.h"
#include "motor.h"
using namespace std;

// ±àÂëÆ÷Âö³å¼ÇÂ¼
void ENCODER_OUTPUT()
{
    uint8_t i = 0;
    uint8_t k = 1;
    uint8_t m = 2;
    uint8_t n = 3;
    switch (GPIO_Pin)
    {
    case ENCODER1_Pin:
        
        if (HAL_GPIO_ReadPin(motors[i].Speed_Direction_GPIOx,
                             motors[i].Speed_Direction_GPIO_Pin) == motors[i].Speed_Default_Direction)
        {
            motors[i].encoder.Hall_Encoder_Count++;
            motors[i].Get_speed_direction = 1;
        }
        else
        {
            motors[i].encoder.Hall_Encoder_Count--;
            motors[i].Get_speed_direction = -1;
        }
        break;
    case ENCODER2_Pin:
        
        if (HAL_GPIO_ReadPin(motors[k].Speed_Direction_GPIOx,
                             motors[k].Speed_Direction_GPIO_Pin) == motors[k].Speed_Default_Direction)
        {
            motors[k].encoder.Hall_Encoder_Count++;
            motors[k].Get_speed_direction = 1;
        }
        else
        {
            motors[k].encoder.Hall_Encoder_Count--;
            motors[k].Get_speed_direction = -1;
        }
        break;
    case ENCODER3_Pin:
        
        if (HAL_GPIO_ReadPin(motors[m].Speed_Direction_GPIOx,
                             motors[m].Speed_Direction_GPIO_Pin) == motors[m].Speed_Default_Direction)
        {
            motors[m].encoder.Hall_Encoder_Count++;
            motors[m].Get_speed_direction = 1;
        }
        else
        {
            motors[m].encoder.Hall_Encoder_Count--;
            motors[m].Get_speed_direction = -1;
        }
        break;
    case ENCODER4_Pin:
        
        if (HAL_GPIO_ReadPin(motors[n].Speed_Direction_GPIOx,
                             motors[n].Speed_Direction_GPIO_Pin) == motors[n].Speed_Default_Direction)
        {
            motors[n].encoder.Hall_Encoder_Count++;
            motors[n].Get_speed_direction = 1;
        }
        else
        {
            motors[n].encoder.Hall_Encoder_Count--;
            motors[n].Get_speed_direction = -1;
        }
        break;
    default:
        break;
    }
}
