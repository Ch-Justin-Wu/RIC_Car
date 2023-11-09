#ifndef WS2812_H
#define WS2812_H

#include "stdint.h"
#include "spi.h"
#include "remote_control.h"
//            ±àÂë 0
#define CODE_0 0xC0
//            ±àÂë 1
#define CODE_1 0xF0
/*ws2812bµÆÖéÊıÁ¿*/
#define LED_NUM 8

typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} RGBColor_TypeDef;

extern SPI_HandleTypeDef hspi1;

void ws2812_reflash(uint8_t reflash_num);
void ws2812_blue(uint8_t led_num);
void ws2812_red(uint8_t led_num);
void Set_color(void);

#endif
