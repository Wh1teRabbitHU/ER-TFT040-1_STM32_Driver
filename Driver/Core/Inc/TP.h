#include "er_tft040.h"
#include "stdint.h"
#include "word.h"

unsigned int TP_X, TP_Y;

void inttostr(int dd, unsigned char *str) {
    str[0] = dd / 10000 + 48;
    str[1] = (dd / 1000) - ((dd / 10000) * 10) + 48;
    str[2] = (dd / 100) - ((dd / 1000) * 10) + 48;
    str[3] = (dd / 10) - ((dd / 100) * 10) + 48;
    str[4] = dd - ((dd / 10) * 10) + 48;
    str[5] = 0;
}

// show one character
// dcolor:character colour��gbcolor: background color
void showzifu(unsigned int x, unsigned int y, unsigned char value, unsigned int dcolor, unsigned int bgcolor) {
    unsigned char i, j;
    unsigned char *temp = zifu;
    ER_TFT040_setCursor(x, x + 7, y, y + 11);
    temp += (value - 32) * 12;
    for (j = 0; j < 12; j++) {
        for (i = 0; i < 8; i++) {
            if ((*temp & (1 << (7 - i))) != 0) {
                ER_TFT040_writeData(dcolor);
            } else {
                ER_TFT040_writeData(bgcolor);
            }
        }
        temp++;
    }
}

void showzifustr(unsigned int x, unsigned int y, unsigned char *str, unsigned int dcolor, unsigned int bgcolor) {
    unsigned int x1, y1;
    x1 = x;
    y1 = y;
    while (*str != '\0') {
        showzifu(x1, y1, *str, dcolor, bgcolor);
        x1 += 7;
        str++;
    }
}

void TPTEST(void) {
    unsigned char ss[6];
    unsigned int lx, ly, k, h;

    ER_TFT040_clearLCD(0xffff);
    showzifustr(30, 5, "HELLOW!PLEASE TOUCH ME!  Welcome used 4 inch TFT LCD module", 0xF800, 0xffff);
    showzifustr(80, 100, "TP TEST!", 0x00FF00, 0xf800);
    inttostr(TP_X, ss);
    showzifustr(10, 305, "X:", 0x001f, 0xffff);
    showzifustr(25, 305, ss, 0xf800, 0xffff);
    inttostr(TP_Y, ss);
    showzifustr(80, 305, "Y:", 0xf800, 0xffff);
    showzifustr(95, 305, ss, 0xf800, 0xffff);
    lx = (((TP_X - 150)) * 10 / 77);
    ly = (((TP_Y - 150)) * 10 / 46);

    ER_TFT040_writeCommand(0x3600);
    ER_TFT040_writeData(0x00);
    ER_TFT040_setCursor(lx, lx + 1, ly, ly + 1);
    for (k = 0; k < 2; k++) {
        for (h = 0; h < 2; h++) {
            ER_TFT040_writeData(ER_TFT040_CONVERT_DATA(0xf1, 0x00));
        }
    }
}
