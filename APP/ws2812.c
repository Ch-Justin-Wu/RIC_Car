#include "ws2812.h"
#include "dma.h"

uint8_t BLACK[3] = {0, 0, 0};
uint8_t RED[3] = {30, 0, 0};
uint8_t GREEN[3] = {0, 30, 0};
uint8_t BLUE[3] = {0, 0, 30};
uint8_t LED_BUFFER[24 * LED_NUM + 10];

static void ws2812_set_color(uint8_t ID, uint8_t color[3])
{
    int i = 0;
    for (i = 0; i < LED_NUM; i++)
    { // red
        LED_BUFFER[ID * 24 + LED_NUM + i] = ((color[0] << i) & 0x80) ? CODE_1 : CODE_0;
    }

    for (i = 0; i < LED_NUM; i++)
    { // green
        LED_BUFFER[ID * 24 + i] = ((color[1] << i) & 0x80) ? CODE_1 : CODE_0;
    }

    for (i = 0; i < LED_NUM; i++)
    { // blue
        LED_BUFFER[ID * 24 + 2 * LED_NUM + i] = ((color[2] << i) & 0x80) ? CODE_1 : CODE_0;
    }
}

// SPI_DMA·¢ËÍ
void ws2812_reflash(uint8_t reflash_num)
{
    while (HAL_DMA_GetState(&hdma_spi1_tx) != HAL_DMA_STATE_READY)
        ;
    HAL_SPI_Transmit_DMA(&hspi1, LED_BUFFER, 24 * reflash_num);
}

void ws2812_black(uint8_t led_num)
{
    for (int i = 0; i < led_num; i++)
    {
        ws2812_set_color(i, BLACK);
        ws2812_reflash(led_num);
    }
}

void ws2812_red(uint8_t led_num)
{
    for (int i = 0; i < led_num; i++)
    {
        ws2812_set_color(i, RED);
        ws2812_reflash(led_num);
    }
}

void ws2812_green(uint8_t led_num)
{
    for (int i = 0; i < led_num; i++)
    {
        ws2812_set_color(i, GREEN);
        ws2812_reflash(led_num);
    }
}

void ws2812_blue(uint8_t led_num)
{
    for (int i = 0; i < led_num; i++)
    {
        ws2812_set_color(i, BLUE);
        ws2812_reflash(led_num);
    }
}
