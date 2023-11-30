#pragma once

#include "main.h"

typedef struct // 颜色结构体
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} RGBColor_TypeDef;

#define RGB_NUM 30 // RGB灯的数量，即为缓冲区长度

// 复位函数
void RGB_RST(void);
// 颜色设置函数
void RGB_Set_Color(uint8_t LedId, RGBColor_TypeDef Color);
// RGB 刷新函数
void RGB_Reflash(uint8_t reflash_num);

// 各种颜色测试
void RGB_RED(uint16_t RGB_LEN);		// 红
void RGB_GREEN(uint16_t RGB_LEN);	// 绿
void RGB_BLUE(uint16_t RGB_LEN);	// 蓝
void RGB_YELLOW(uint16_t RGB_LEN);	// 黄
//void RGB_MAGENTA(uint16_t RGB_LEN); // 紫
//void RGB_BLACK(uint16_t RGB_LEN);	// 黑
void RGB_WHITE(uint16_t RGB_LEN);	// 白
void RGB_SKY(uint16_t RGB_LEN);		// 淡蓝
void RGB_ORANGE(uint16_t RGB_LEN);	// 橙
							/* __WS2812_H */