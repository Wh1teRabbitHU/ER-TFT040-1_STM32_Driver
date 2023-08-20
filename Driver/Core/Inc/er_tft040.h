#ifndef ER_TFT040_H
#define ER_TFT040_H

#define ER_TFT040_DATA_MASK ((1 << 16) - 1)
#define ER_TFT040_CONVERT_DATA(dataHigh, dataLow) ((dataHigh << 8) | dataLow)

#include "stdint.h"

void Write_Command(uint16_t data);
void Write_Data_int(uint16_t data);

void nt35510_Initial(void);
void LCD_clear(unsigned int i);
void LCD_SetPos_Vertical(unsigned int xs, unsigned int xe, unsigned int ys, unsigned int ye);
void LCD_SetPos_Horizontal(unsigned int xs, unsigned int xe, unsigned int ys, unsigned int ye);

#endif