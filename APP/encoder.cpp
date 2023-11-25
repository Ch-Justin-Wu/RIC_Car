#include "encoder.h"
#include "motor.h"
using namespace std;

// ±àÂëÆ÷Âö³å¼ÇÂ¼

/**
 * ************************************************************************
 * @brief ±àÂëÆ÷Âö³å¼ÇÂ¼ Encoder pulses recording
 *
 *
 * ************************************************************************
 */
void EXTI_IRQ(uint32_t ExtiLine)
{

    switch (ExtiLine)
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

