#include "er_tft040.h"

static void ER_TFT040_setDataPort(uint16_t data) {
    uint32_t resetData = (data ^ ER_TFT040_RESET_DATA_MASK) << 16U;
    uint32_t setData = resetData | data;
    uint8_t d11 = (data >> 11) & 1;

    GPIOB->BSRR = setData;

    // There is no PB11 on the STM32F446, so it is routed to PA11
    HAL_GPIO_WritePin(DISPLAY_D11_GPIO_Port, DISPLAY_D11_Pin, d11);
}

static void swap(int16_t *a, int16_t *b) {
    int16_t t = *a;
    *a = *b;
    *b = t;
}

void ER_TFT040_writeCommand(uint16_t command) {
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 0);

    ER_TFT040_setDataPort(command);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void ER_TFT040_writeData(uint16_t data) {
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    ER_TFT040_setDataPort(data);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void ER_TFT040_repeatData() {
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void ER_TFT040_setCursorToPixel(uint16_t xStart, uint16_t yStart) {
    ER_TFT040_writeCommand(0x2A00);
    ER_TFT040_writeData(xStart >> 8);
    ER_TFT040_writeCommand(0x2A02);
    ER_TFT040_repeatData();

    ER_TFT040_writeCommand(0x2A01);
    ER_TFT040_writeData(xStart & 0x00ff);
    ER_TFT040_writeCommand(0x2A03);
    ER_TFT040_repeatData();

    ER_TFT040_writeCommand(0x2B00);
    ER_TFT040_writeData(yStart >> 8);
    ER_TFT040_writeCommand(0x2B02);
    ER_TFT040_repeatData();

    ER_TFT040_writeCommand(0x2B01);
    ER_TFT040_writeData(yStart & 0x00ff);
    ER_TFT040_writeCommand(0x2B03);
    ER_TFT040_repeatData();

    ER_TFT040_writeCommand(0x2C00);
}

void ER_TFT040_setCursorToRange(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd) {
    ER_TFT040_writeCommand(0x2A00);
    ER_TFT040_writeData(xStart >> 8);
    ER_TFT040_writeCommand(0x2A01);
    ER_TFT040_writeData(xStart & 0x00ff);
    ER_TFT040_writeCommand(0x2A02);
    ER_TFT040_writeData(xEnd >> 8);
    ER_TFT040_writeCommand(0x2A03);
    ER_TFT040_writeData(xEnd & 0x00ff);
    ER_TFT040_writeCommand(0x2B00);
    ER_TFT040_writeData(yStart >> 8);
    ER_TFT040_writeCommand(0x2B01);
    ER_TFT040_writeData(yStart & 0x00ff);
    ER_TFT040_writeCommand(0x2B02);
    ER_TFT040_writeData(yEnd >> 8);
    ER_TFT040_writeCommand(0x2B03);
    ER_TFT040_writeData(yEnd & 0x00ff);

    ER_TFT040_writeCommand(0x2C00);
}

void ER_TFT040_init(void) {
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(10);

    // 35510h
    ER_TFT040_writeCommand(0xF000);
    ER_TFT040_writeData(0x55);
    ER_TFT040_writeCommand(0xF001);
    ER_TFT040_writeData(0xAA);
    ER_TFT040_writeCommand(0xF002);
    ER_TFT040_writeData(0x52);
    ER_TFT040_writeCommand(0xF003);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xF004);
    ER_TFT040_writeData(0x01);

    // #AVDD Set AVDD 5.2V
    ER_TFT040_writeCommand(0xB000);
    ER_TFT040_writeData(0x0D);
    ER_TFT040_writeCommand(0xB001);
    ER_TFT040_writeData(0x0D);
    ER_TFT040_writeCommand(0xB002);
    ER_TFT040_writeData(0x0D);

    // #AVDD ratio
    ER_TFT040_writeCommand(0xB600);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xB601);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xB602);
    ER_TFT040_writeData(0x34);

    // #AVEE  -5.2V
    ER_TFT040_writeCommand(0xB100);
    ER_TFT040_writeData(0x0D);
    ER_TFT040_writeCommand(0xB101);
    ER_TFT040_writeData(0x0D);
    ER_TFT040_writeCommand(0xB102);
    ER_TFT040_writeData(0x0D);

    // #AVEE ratio
    ER_TFT040_writeCommand(0xB700);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xB701);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xB702);
    ER_TFT040_writeData(0x34);

    // #VCL  -2.5V
    ER_TFT040_writeCommand(0xB200);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xB201);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xB202);
    ER_TFT040_writeData(0x00);

    // #VCL ratio
    ER_TFT040_writeCommand(0xB800);
    ER_TFT040_writeData(0x24);
    ER_TFT040_writeCommand(0xB801);
    ER_TFT040_writeData(0x24);
    ER_TFT040_writeCommand(0xB802);
    ER_TFT040_writeData(0x24);

    // #VGH  15V
    ER_TFT040_writeCommand(0xBF00);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xB300);
    ER_TFT040_writeData(0x0F);
    ER_TFT040_writeCommand(0xB301);
    ER_TFT040_writeData(0x0F);
    ER_TFT040_writeCommand(0xB302);
    ER_TFT040_writeData(0x0F);

    // #VGH  ratio
    ER_TFT040_writeCommand(0xB900);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xB901);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xB902);
    ER_TFT040_writeData(0x34);

    // #VGL_REG  -10V
    ER_TFT040_writeCommand(0xB500);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xB500);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xB501);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xC200);
    ER_TFT040_writeData(0x03);

    // #VGLX  ratio
    ER_TFT040_writeCommand(0xBA00);
    ER_TFT040_writeData(0x24);
    ER_TFT040_writeCommand(0xBA01);
    ER_TFT040_writeData(0x24);
    ER_TFT040_writeCommand(0xBA02);
    ER_TFT040_writeData(0x24);

    // #VGMP/VGSP 4.5V/0V
    ER_TFT040_writeCommand(0xBC00);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xBC01);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xBC02);
    ER_TFT040_writeData(0x00);

    // #VGMN/VGSN -4.5V/0V
    ER_TFT040_writeCommand(0xBD00);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xBD01);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xBD02);
    ER_TFT040_writeData(0x00);

    // #VCOM  -1.325V
    ER_TFT040_writeCommand(0xBE00);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xBE01);
    ER_TFT040_writeData(0x89);  // 69

    // Gamma Setting
    ER_TFT040_writeCommand(0xD100);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD101);
    ER_TFT040_writeData(0x2D);
    ER_TFT040_writeCommand(0xD102);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD103);
    ER_TFT040_writeData(0x2E);
    ER_TFT040_writeCommand(0xD104);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD105);
    ER_TFT040_writeData(0x32);
    ER_TFT040_writeCommand(0xD106);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD107);
    ER_TFT040_writeData(0x44);
    ER_TFT040_writeCommand(0xD108);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD109);
    ER_TFT040_writeData(0x53);
    ER_TFT040_writeCommand(0xD10A);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD10B);
    ER_TFT040_writeData(0x88);
    ER_TFT040_writeCommand(0xD10C);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD10D);
    ER_TFT040_writeData(0xB6);
    ER_TFT040_writeCommand(0xD10E);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD10F);
    ER_TFT040_writeData(0xF3);  //
    ER_TFT040_writeCommand(0xD110);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD111);
    ER_TFT040_writeData(0x22);
    ER_TFT040_writeCommand(0xD112);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD113);
    ER_TFT040_writeData(0x64);
    ER_TFT040_writeCommand(0xD114);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD115);
    ER_TFT040_writeData(0x92);
    ER_TFT040_writeCommand(0xD116);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD117);
    ER_TFT040_writeData(0xD4);
    ER_TFT040_writeCommand(0xD118);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD119);
    ER_TFT040_writeData(0x07);
    ER_TFT040_writeCommand(0xD11A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD11B);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xD11C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD11D);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xD11E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD11F);
    ER_TFT040_writeData(0x5F);  //
    ER_TFT040_writeCommand(0xD120);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD121);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xD122);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD123);
    ER_TFT040_writeData(0x94);
    ER_TFT040_writeCommand(0xD124);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD125);
    ER_TFT040_writeData(0xA6);
    ER_TFT040_writeCommand(0xD126);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD127);
    ER_TFT040_writeData(0xBB);
    ER_TFT040_writeCommand(0xD128);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD129);
    ER_TFT040_writeData(0xCA);
    ER_TFT040_writeCommand(0xD12A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD12B);
    ER_TFT040_writeData(0xDB);
    ER_TFT040_writeCommand(0xD12C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD12D);
    ER_TFT040_writeData(0xE8);
    ER_TFT040_writeCommand(0xD12E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD12F);
    ER_TFT040_writeData(0xF9);  //
    ER_TFT040_writeCommand(0xD130);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD131);
    ER_TFT040_writeData(0x1F);
    ER_TFT040_writeCommand(0xD132);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD133);
    ER_TFT040_writeData(0x7F);

    ER_TFT040_writeCommand(0xD200);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD201);
    ER_TFT040_writeData(0x2D);
    ER_TFT040_writeCommand(0xD202);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD203);
    ER_TFT040_writeData(0x2E);
    ER_TFT040_writeCommand(0xD204);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD205);
    ER_TFT040_writeData(0x32);
    ER_TFT040_writeCommand(0xD206);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD207);
    ER_TFT040_writeData(0x44);
    ER_TFT040_writeCommand(0xD208);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD209);
    ER_TFT040_writeData(0x53);
    ER_TFT040_writeCommand(0xD20A);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD20B);
    ER_TFT040_writeData(0x88);
    ER_TFT040_writeCommand(0xD20C);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD20D);
    ER_TFT040_writeData(0xB6);
    ER_TFT040_writeCommand(0xD20E);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD20F);
    ER_TFT040_writeData(0xF3);  //
    ER_TFT040_writeCommand(0xD210);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD211);
    ER_TFT040_writeData(0x22);
    ER_TFT040_writeCommand(0xD212);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD213);
    ER_TFT040_writeData(0x64);
    ER_TFT040_writeCommand(0xD214);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD215);
    ER_TFT040_writeData(0x92);
    ER_TFT040_writeCommand(0xD216);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD217);
    ER_TFT040_writeData(0xD4);
    ER_TFT040_writeCommand(0xD218);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD219);
    ER_TFT040_writeData(0x07);
    ER_TFT040_writeCommand(0xD21A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD21B);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xD21C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD21D);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xD21E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD21F);
    ER_TFT040_writeData(0x5F);  //
    ER_TFT040_writeCommand(0xD220);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD221);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xD222);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD223);
    ER_TFT040_writeData(0x94);
    ER_TFT040_writeCommand(0xD224);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD225);
    ER_TFT040_writeData(0xA6);
    ER_TFT040_writeCommand(0xD226);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD227);
    ER_TFT040_writeData(0xBB);
    ER_TFT040_writeCommand(0xD228);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD229);
    ER_TFT040_writeData(0xCA);
    ER_TFT040_writeCommand(0xD22A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD22B);
    ER_TFT040_writeData(0xDB);
    ER_TFT040_writeCommand(0xD22C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD22D);
    ER_TFT040_writeData(0xE8);
    ER_TFT040_writeCommand(0xD22E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD22F);
    ER_TFT040_writeData(0xF9);  //
    ER_TFT040_writeCommand(0xD230);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD231);
    ER_TFT040_writeData(0x1F);
    ER_TFT040_writeCommand(0xD232);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD233);
    ER_TFT040_writeData(0x7F);

    ER_TFT040_writeCommand(0xD300);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD301);
    ER_TFT040_writeData(0x2D);
    ER_TFT040_writeCommand(0xD302);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD303);
    ER_TFT040_writeData(0x2E);
    ER_TFT040_writeCommand(0xD304);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD305);
    ER_TFT040_writeData(0x32);
    ER_TFT040_writeCommand(0xD306);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD307);
    ER_TFT040_writeData(0x44);
    ER_TFT040_writeCommand(0xD308);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD309);
    ER_TFT040_writeData(0x53);
    ER_TFT040_writeCommand(0xD30A);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD30B);
    ER_TFT040_writeData(0x88);
    ER_TFT040_writeCommand(0xD30C);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD30D);
    ER_TFT040_writeData(0xB6);
    ER_TFT040_writeCommand(0xD30E);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD30F);
    ER_TFT040_writeData(0xF3);  //
    ER_TFT040_writeCommand(0xD310);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD311);
    ER_TFT040_writeData(0x22);
    ER_TFT040_writeCommand(0xD312);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD313);
    ER_TFT040_writeData(0x64);
    ER_TFT040_writeCommand(0xD314);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD315);
    ER_TFT040_writeData(0x92);
    ER_TFT040_writeCommand(0xD316);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD317);
    ER_TFT040_writeData(0xD4);
    ER_TFT040_writeCommand(0xD318);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD319);
    ER_TFT040_writeData(0x07);
    ER_TFT040_writeCommand(0xD31A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD31B);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xD31C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD31D);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xD31E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD31F);
    ER_TFT040_writeData(0x5F);  //
    ER_TFT040_writeCommand(0xD320);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD321);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xD322);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD323);
    ER_TFT040_writeData(0x94);
    ER_TFT040_writeCommand(0xD324);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD325);
    ER_TFT040_writeData(0xA6);
    ER_TFT040_writeCommand(0xD326);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD327);
    ER_TFT040_writeData(0xBB);
    ER_TFT040_writeCommand(0xD328);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD329);
    ER_TFT040_writeData(0xCA);
    ER_TFT040_writeCommand(0xD32A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD32B);
    ER_TFT040_writeData(0xDB);
    ER_TFT040_writeCommand(0xD32C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD32D);
    ER_TFT040_writeData(0xE8);
    ER_TFT040_writeCommand(0xD32E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD32F);
    ER_TFT040_writeData(0xF9);  //
    ER_TFT040_writeCommand(0xD330);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD331);
    ER_TFT040_writeData(0x1F);
    ER_TFT040_writeCommand(0xD332);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD333);
    ER_TFT040_writeData(0x7F);

    ER_TFT040_writeCommand(0xD400);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD401);
    ER_TFT040_writeData(0x2D);
    ER_TFT040_writeCommand(0xD402);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD403);
    ER_TFT040_writeData(0x2E);
    ER_TFT040_writeCommand(0xD404);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD405);
    ER_TFT040_writeData(0x32);
    ER_TFT040_writeCommand(0xD406);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD407);
    ER_TFT040_writeData(0x44);
    ER_TFT040_writeCommand(0xD408);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD409);
    ER_TFT040_writeData(0x53);
    ER_TFT040_writeCommand(0xD40A);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD40B);
    ER_TFT040_writeData(0x88);
    ER_TFT040_writeCommand(0xD40C);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD40D);
    ER_TFT040_writeData(0xB6);
    ER_TFT040_writeCommand(0xD40E);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD40F);
    ER_TFT040_writeData(0xF3);  //
    ER_TFT040_writeCommand(0xD410);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD411);
    ER_TFT040_writeData(0x22);
    ER_TFT040_writeCommand(0xD412);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD413);
    ER_TFT040_writeData(0x64);
    ER_TFT040_writeCommand(0xD414);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD415);
    ER_TFT040_writeData(0x92);
    ER_TFT040_writeCommand(0xD416);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD417);
    ER_TFT040_writeData(0xD4);
    ER_TFT040_writeCommand(0xD418);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD419);
    ER_TFT040_writeData(0x07);
    ER_TFT040_writeCommand(0xD41A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD41B);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xD41C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD41D);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xD41E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD41F);
    ER_TFT040_writeData(0x5F);  //
    ER_TFT040_writeCommand(0xD420);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD421);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xD422);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD423);
    ER_TFT040_writeData(0x94);
    ER_TFT040_writeCommand(0xD424);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD425);
    ER_TFT040_writeData(0xA6);
    ER_TFT040_writeCommand(0xD426);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD427);
    ER_TFT040_writeData(0xBB);
    ER_TFT040_writeCommand(0xD428);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD429);
    ER_TFT040_writeData(0xCA);
    ER_TFT040_writeCommand(0xD42A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD42B);
    ER_TFT040_writeData(0xDB);
    ER_TFT040_writeCommand(0xD42C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD42D);
    ER_TFT040_writeData(0xE8);
    ER_TFT040_writeCommand(0xD42E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD42F);
    ER_TFT040_writeData(0xF9);  //
    ER_TFT040_writeCommand(0xD430);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD431);
    ER_TFT040_writeData(0x1F);
    ER_TFT040_writeCommand(0xD432);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD433);
    ER_TFT040_writeData(0x7F);

    ER_TFT040_writeCommand(0xD500);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD501);
    ER_TFT040_writeData(0x2D);
    ER_TFT040_writeCommand(0xD502);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD503);
    ER_TFT040_writeData(0x2E);
    ER_TFT040_writeCommand(0xD504);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD505);
    ER_TFT040_writeData(0x32);
    ER_TFT040_writeCommand(0xD506);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD507);
    ER_TFT040_writeData(0x44);
    ER_TFT040_writeCommand(0xD508);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD509);
    ER_TFT040_writeData(0x53);
    ER_TFT040_writeCommand(0xD50A);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD50B);
    ER_TFT040_writeData(0x88);
    ER_TFT040_writeCommand(0xD50C);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD50D);
    ER_TFT040_writeData(0xB6);
    ER_TFT040_writeCommand(0xD50E);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD50F);
    ER_TFT040_writeData(0xF3);  //
    ER_TFT040_writeCommand(0xD510);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD511);
    ER_TFT040_writeData(0x22);
    ER_TFT040_writeCommand(0xD512);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD513);
    ER_TFT040_writeData(0x64);
    ER_TFT040_writeCommand(0xD514);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD515);
    ER_TFT040_writeData(0x92);
    ER_TFT040_writeCommand(0xD516);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD517);
    ER_TFT040_writeData(0xD4);
    ER_TFT040_writeCommand(0xD518);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD519);
    ER_TFT040_writeData(0x07);
    ER_TFT040_writeCommand(0xD51A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD51B);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xD51C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD51D);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xD51E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD51F);
    ER_TFT040_writeData(0x5F);  //
    ER_TFT040_writeCommand(0xD520);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD521);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xD522);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD523);
    ER_TFT040_writeData(0x94);
    ER_TFT040_writeCommand(0xD524);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD525);
    ER_TFT040_writeData(0xA6);
    ER_TFT040_writeCommand(0xD526);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD527);
    ER_TFT040_writeData(0xBB);
    ER_TFT040_writeCommand(0xD528);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD529);
    ER_TFT040_writeData(0xCA);
    ER_TFT040_writeCommand(0xD52A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD52B);
    ER_TFT040_writeData(0xDB);
    ER_TFT040_writeCommand(0xD52C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD52D);
    ER_TFT040_writeData(0xE8);
    ER_TFT040_writeCommand(0xD52E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD52F);
    ER_TFT040_writeData(0xF9);  //
    ER_TFT040_writeCommand(0xD530);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD531);
    ER_TFT040_writeData(0x1F);
    ER_TFT040_writeCommand(0xD532);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD533);
    ER_TFT040_writeData(0x7F);

    ER_TFT040_writeCommand(0xD600);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD601);
    ER_TFT040_writeData(0x2D);
    ER_TFT040_writeCommand(0xD602);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD603);
    ER_TFT040_writeData(0x2E);
    ER_TFT040_writeCommand(0xD604);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD605);
    ER_TFT040_writeData(0x32);
    ER_TFT040_writeCommand(0xD606);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD607);
    ER_TFT040_writeData(0x44);
    ER_TFT040_writeCommand(0xD608);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD609);
    ER_TFT040_writeData(0x53);
    ER_TFT040_writeCommand(0xD60A);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD60B);
    ER_TFT040_writeData(0x88);
    ER_TFT040_writeCommand(0xD60C);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD60D);
    ER_TFT040_writeData(0xB6);
    ER_TFT040_writeCommand(0xD60E);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xD60F);
    ER_TFT040_writeData(0xF3);  //
    ER_TFT040_writeCommand(0xD610);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD611);
    ER_TFT040_writeData(0x22);
    ER_TFT040_writeCommand(0xD612);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD613);
    ER_TFT040_writeData(0x64);
    ER_TFT040_writeCommand(0xD614);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD615);
    ER_TFT040_writeData(0x92);
    ER_TFT040_writeCommand(0xD616);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xD617);
    ER_TFT040_writeData(0xD4);
    ER_TFT040_writeCommand(0xD618);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD619);
    ER_TFT040_writeData(0x07);
    ER_TFT040_writeCommand(0xD61A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD61B);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xD61C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD61D);
    ER_TFT040_writeData(0x34);
    ER_TFT040_writeCommand(0xD61E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD61F);
    ER_TFT040_writeData(0x5F);  //
    ER_TFT040_writeCommand(0xD620);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD621);
    ER_TFT040_writeData(0x78);
    ER_TFT040_writeCommand(0xD622);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD623);
    ER_TFT040_writeData(0x94);
    ER_TFT040_writeCommand(0xD624);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD625);
    ER_TFT040_writeData(0xA6);
    ER_TFT040_writeCommand(0xD626);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD627);
    ER_TFT040_writeData(0xBB);
    ER_TFT040_writeCommand(0xD628);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD629);
    ER_TFT040_writeData(0xCA);
    ER_TFT040_writeCommand(0xD62A);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD62B);
    ER_TFT040_writeData(0xDB);
    ER_TFT040_writeCommand(0xD62C);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD62D);
    ER_TFT040_writeData(0xE8);
    ER_TFT040_writeCommand(0xD62E);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xD62F);
    ER_TFT040_writeData(0xF9);  //
    ER_TFT040_writeCommand(0xD630);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD631);
    ER_TFT040_writeData(0x1F);
    ER_TFT040_writeCommand(0xD632);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xD633);
    ER_TFT040_writeData(0x7F);

    // #LV2 Page 0 enable
    ER_TFT040_writeCommand(0xF000);
    ER_TFT040_writeData(0x55);
    ER_TFT040_writeCommand(0xF001);
    ER_TFT040_writeData(0xAA);
    ER_TFT040_writeCommand(0xF002);
    ER_TFT040_writeData(0x52);
    ER_TFT040_writeCommand(0xF003);
    ER_TFT040_writeData(0x08);
    ER_TFT040_writeCommand(0xF004);
    ER_TFT040_writeData(0x00);

    // #DISPLAY CONTROL
    ER_TFT040_writeCommand(0xB100);
    ER_TFT040_writeData(0xCC);
    ER_TFT040_writeCommand(0xB101);
    ER_TFT040_writeData(0x00);

    ER_TFT040_writeCommand(0xB500);
    ER_TFT040_writeData(0x50);

    // #SOURCE HOLD TIME
    ER_TFT040_writeCommand(0xB600);
    ER_TFT040_writeData(0x05);

    // Set Gate EQ
    ER_TFT040_writeCommand(0xB700);
    ER_TFT040_writeData(0x70);
    ER_TFT040_writeCommand(0xB701);
    ER_TFT040_writeData(0x70);

    // #Source EQ control (Mode 2)
    ER_TFT040_writeCommand(0xB800);
    ER_TFT040_writeData(0x01);
    ER_TFT040_writeCommand(0xB801);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xB802);
    ER_TFT040_writeData(0x03);
    ER_TFT040_writeCommand(0xB803);
    ER_TFT040_writeData(0x03);

    // #INVERSION MODE
    ER_TFT040_writeCommand(0xBC00);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xBC01);
    ER_TFT040_writeData(0x00);
    ER_TFT040_writeCommand(0xBC02);
    ER_TFT040_writeData(0x00);

    // #Timing control
    ER_TFT040_writeCommand(0xC900);
    ER_TFT040_writeData(0xD0);
    ER_TFT040_writeCommand(0xC901);
    ER_TFT040_writeData(0x02);
    ER_TFT040_writeCommand(0xC902);
    ER_TFT040_writeData(0x50);
    ER_TFT040_writeCommand(0xC903);
    ER_TFT040_writeData(0x50);
    ER_TFT040_writeCommand(0xC904);
    ER_TFT040_writeData(0x50);

    ER_TFT040_writeCommand(0x3500);
    ER_TFT040_writeData(0x00);

    ER_TFT040_writeCommand(0x3A00);
    ER_TFT040_writeData(0x55);  // Data format 16-Bits
    ER_TFT040_writeCommand(0x3600);
    ER_TFT040_writeData(0x00);

    ER_TFT040_writeCommand(0x1100);  // StartUp

    HAL_Delay(120);

    ER_TFT040_clearLCD(0);

    ER_TFT040_writeCommand(0x2900);  // Display On
    HAL_Delay(100);
}

void ER_TFT040_clearLCD(uint16_t color) {
    ER_TFT040_fillRectangle(0, 0, ER_TFT040_SCREEN_WIDTH, ER_TFT040_SCREEN_HEIGHT, color);
}

void ER_TFT040_drawPixel(int16_t x, int16_t y, uint16_t color) {
    ER_TFT040_setCursorToPixel(x, y);

    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    ER_TFT040_setDataPort(color);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void ER_TFT040_drawLine(int16_t xStart, int16_t yStart, int16_t xEnd, int16_t yEnd, uint16_t color) {
    int16_t steep = abs(yEnd - yStart) > abs(xEnd - xStart);

    if (steep) {
        swap(&xStart, &yStart);
        swap(&xEnd, &yEnd);
    }

    if (xStart > xEnd) {
        swap(&xStart, &xEnd);
        swap(&yStart, &yEnd);
    }

    int16_t dx, dy;
    dx = xEnd - xStart;
    dy = abs(yEnd - yStart);

    int16_t err = dx / 2;
    int16_t ystep;

    if (yStart < yEnd) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; xStart <= xEnd; xStart++) {
        if (steep) {
            ER_TFT040_drawPixel(yStart, xStart, color);
        } else {
            ER_TFT040_drawPixel(xStart, yStart, color);
        }
        err -= dy;
        if (err < 0) {
            yStart += ystep;
            err += dx;
        }
    }
}

void ER_TFT040_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    ER_TFT040_drawLine(x, y, x + width, y, color);
    ER_TFT040_drawLine(x + width, y, x + width, y + height, color);
    ER_TFT040_drawLine(x + width, y + height, x, y + height, color);
    ER_TFT040_drawLine(x, y + height, x, y, color);
}

void ER_TFT040_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    ER_TFT040_setCursorToRange(x, x + width - 1, y, y + height - 1);

    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    ER_TFT040_setDataPort(color);

    for (uint16_t h = 0; h < ER_TFT040_SCREEN_WIDTH; h++) {
        for (uint16_t w = 0; w < ER_TFT040_SCREEN_HEIGHT; w++) {
            HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
            HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
        }
    }

    HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void ER_TFT040_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ER_TFT040_drawPixel(x0, y0 + r, color);
    ER_TFT040_drawPixel(x0, y0 - r, color);
    ER_TFT040_drawPixel(x0 + r, y0, color);
    ER_TFT040_drawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ER_TFT040_drawPixel(x0 + x, y0 + y, color);
        ER_TFT040_drawPixel(x0 - x, y0 + y, color);
        ER_TFT040_drawPixel(x0 + x, y0 - y, color);
        ER_TFT040_drawPixel(x0 - x, y0 - y, color);
        ER_TFT040_drawPixel(x0 + y, y0 + x, color);
        ER_TFT040_drawPixel(x0 - y, y0 + x, color);
        ER_TFT040_drawPixel(x0 + y, y0 - x, color);
        ER_TFT040_drawPixel(x0 - y, y0 - x, color);
    }
}

void ER_TFT040_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    ER_TFT040_drawLine(x0, y0 - r, x0, (y0 - r) + (2 * r + 1) - 1, color);

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ER_TFT040_drawLine(x0 + x, y0 - y, x0 + x, y0 - y + 2 * y, color);
        ER_TFT040_drawLine(x0 + y, y0 - x, x0 + y, y0 - x + 2 * x, color);
        ER_TFT040_drawLine(x0 - x, y0 - y, x0 - x, y0 - y + 2 * y, color);
        ER_TFT040_drawLine(x0 - y, y0 - x, x0 - y, y0 - x + 2 * x, color);
    }
}

void ER_TFT040_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint8_t fontSize,
                             uint16_t fontColor, uint16_t bgcolor) {
    uint8_t i, j;
    uint8_t *temp = font;
    uint8_t fontWidth = 8 * fontSize;
    uint8_t fontHeight = 12 * fontSize;

    ER_TFT040_setCursorToRange(x, x + fontWidth - 1, y, y + fontHeight - 1);
    temp += (character - 32) * 12;
    for (j = 0; j < fontHeight; j++) {
        for (i = 0; i < fontWidth; i++) {
            if ((*temp & (1 << (7 - i / fontSize))) != 0) {
                ER_TFT040_writeData(fontColor);
            } else {
                ER_TFT040_writeData(bgcolor);
            }
        }

        if (j % fontSize == fontSize - 1) {
            temp++;
        }
    }
}

void ER_TFT040_drawText(ER_TFT040_textProps *textProps) {
    char *textPointer = textProps->text;
    uint16_t posX = textProps->posX;
    uint16_t posY = textProps->posY;
    uint8_t fontWidth = 8 * textProps->fontSize;

    while (*textPointer != '\0') {
        ER_TFT040_drawCharacter(textProps->font, *textPointer, posX, posY, textProps->fontSize, textProps->fontColor,
                                textProps->backgroundColor);
        posX += fontWidth - 1;
        textPointer++;
    }
}

void ER_TFT040_drawPicture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t picture[]) {
    uint16_t i, w, l;
    uint16_t xEnd = x + width - 1;
    uint16_t yEnd = y + height - 1;

    i = 0;

    ER_TFT040_writeCommand(0x3600);
    ER_TFT040_writeData(0xa0);
    ER_TFT040_setCursorToRange(x, xEnd, y, yEnd);

    for (l = 0; l < height; l++) {
        for (w = 0; w < width; w++) {
            ER_TFT040_writeData(ER_TFT040_CONVERT_DATA(picture[i], picture[i + 1]));
            i += 2;
        }
    }

    ER_TFT040_writeCommand(0x3600);
    ER_TFT040_writeData(0x00);
}