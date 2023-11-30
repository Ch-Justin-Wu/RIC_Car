#include "encoder.h"
#include "motor.h"


/**
 * ************************************************************************
 * @brief ±àÂëÆ÷Âö³å¼ÇÂ¼ Encoder pulses recording
 *
 *
 * ************************************************************************
 */
void ENCODER_OUTPUT()
{
    switch (GPIO_Pin)
    {
    case ENCODER1_Pin:

        motors[0].Encoder_Count();
        break;
    case ENCODER2_Pin:

        motors[1].Encoder_Count();
        break;
    case ENCODER3_Pin:

        motors[2].Encoder_Count();
        break;
    case ENCODER4_Pin:

        motors[3].Encoder_Count();
        break;
    default:
        break;
    }
}
