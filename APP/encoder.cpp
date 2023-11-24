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

/**
 * @brief This function handles EXTI line[9:5] interrupts.
 */
void EXTI9_5_IRQHandler(void)
{

    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8) != RESET)
    { // Çå³ýÖÐ¶Ï±êÖ¾
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);
        EXTI_IRQ(LL_EXTI_LINE_8);
    }
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void EXTI15_10_IRQHandler(void)
{

    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
        EXTI_IRQ(LL_EXTI_LINE_11);
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
        EXTI_IRQ(LL_EXTI_LINE_12);
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
        EXTI_IRQ(LL_EXTI_LINE_14);
    }
}
