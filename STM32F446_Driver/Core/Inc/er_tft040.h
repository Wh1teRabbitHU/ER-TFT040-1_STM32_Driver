#ifndef ER_TFT040_H
#define ER_TFT040_H

// #include "default_font.h"
#include <stdlib.h>

#include "main.h"

#define ER_TFT040_SCREEN_WIDTH 480
#define ER_TFT040_SCREEN_HEIGHT 800
#define ER_TFT040_RESET_DATA_MASK (0xFFFF)
#define ER_TFT040_CONVERT_DATA(dataHigh, dataLow) ((dataHigh << 8) | dataLow)

#define CONVERT_24BIT_COLOR(rgbValue) \
    (((rgbValue >> 19) & 0b111111) << 11) | (((rgbValue >> 10) & 0b111111) << 5) | ((rgbValue >> 3) & 0b111111)

typedef struct ER_TFT040_textProps {
    uint8_t *font;
    char *text;
    uint16_t posX;
    uint16_t posY;
    uint16_t fontSize;
    uint16_t fontColor;
    uint16_t backgroundColor;
} ER_TFT040_textProps;

void ER_TFT040_writeCommand(uint16_t data);
void ER_TFT040_writeData(uint16_t data);
void ER_TFT040_repeatData();
void ER_TFT040_setCursorToPixel(uint16_t xStart, uint16_t yStart);
void ER_TFT040_setCursorToRange(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd);

void ER_TFT040_init(void);
void ER_TFT040_clearLCD(uint16_t i);

void ER_TFT040_drawPixel(int16_t x, int16_t y, uint16_t color);
void ER_TFT040_drawLine(int16_t xStart, int16_t yStart, int16_t xEnd, int16_t yEnd, uint16_t color);
void ER_TFT040_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ER_TFT040_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ER_TFT040_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ER_TFT040_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ER_TFT040_drawText(ER_TFT040_textProps *textProps);
void ER_TFT040_drawPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t picture[]);

#endif