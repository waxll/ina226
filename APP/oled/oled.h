#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

#define high 1
#define low 0
#define OLED_MODE 0
#define SIZE 1
#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64
extern uint8_t OLED_GRAM[128][64];
void OLED_Init(void);
uint32_t oled_pow(uint8_t m, uint8_t n);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr);
void OLED_P6x8Str(uint8_t x, uint8_t y, uint8_t ch[]);
void OLED_P8x16Str(uint8_t x, uint8_t y, uint8_t ch[]);
void OLED_P16x16Ch(uint8_t x, uint8_t y, uint32_t N);
void OLED_P16x32Ch(uint8_t x, uint8_t y, uint32_t N);
void OLED_P32x32Ch(uint8_t x, uint8_t y, uint32_t N);
void OLED_P128x48Ch(uint8_t x, uint8_t y, uint32_t N);
void OLED_WrDat(uint8_t dat);
void OLED_WrCmd(uint8_t cmd);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_Fill(uint8_t bmp_dat);
void OLED_CLS(void);
void OLED_OFF(void);
void OLED_ReShow(uint8_t l, uint8_t h, uint8_t x);
void OLED_Refresh(void);
void OLED_PartClear(u8 x0,u8 y0,u8 x1,u8 y1);

void OLED_ON(void);

#endif // !__OLED_H
