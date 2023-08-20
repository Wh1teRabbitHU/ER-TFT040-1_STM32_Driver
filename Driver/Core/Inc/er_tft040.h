#ifndef ER_TFT040_H
#define ER_TFT040_H

// #include "default_font.h"
#include "main.h"

#define ER_TFT040_SCREEN_WIDTH 480
#define ER_TFT040_SCREEN_HEIGHT 800
#define ER_TFT040_DATA_MASK ((1 << 16) - 1)
#define ER_TFT040_CONVERT_DATA(dataHigh, dataLow) ((dataHigh << 8) | dataLow)

void ER_TFT040_writeCommand(uint16_t data);
void ER_TFT040_writeData(uint16_t data);

void ER_TFT040_init(void);
void ER_TFT040_clearLCD(uint16_t i);
void ER_TFT040_setCursor(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd);

void ER_TFT040_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint16_t fontColor,
                             uint16_t bgcolor);
void ER_TFT040_drawText(uint8_t *font, uint8_t *str, uint16_t x, uint16_t y, uint16_t fontColor, uint16_t bgcolor);
void ER_TFT040_drawPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t picture[]);

void ER_TFT040_textTest(uint8_t *font);

#endif