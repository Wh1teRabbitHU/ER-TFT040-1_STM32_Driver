#include "er_tft040.h"
#include "main.h"

/**
 * LCD_cs 	DISPLAY_CSX_Pin 	chip select when low
 * RS		DISPLAY_DC_Pin		high :data  low:command
 * wrb		DISPLAY_WR_Pin		write
 * rdb		DISPLAY_RD_Pin		read
 * RES		DISPLAY_RESET_Pin	reset
 */

unsigned char HSDLCD = 1;
unsigned char CPTLCD = 2;

// #define LCD  1	  // HSDLCD	 IPS
#define LCD 2 // CPTLCD  TN

static void write_data(uint16_t data)
{
	uint16_t setData = data & ER_TFT040_DATA_MASK;

	GPIOB->BRR = ER_TFT040_DATA_MASK;
	GPIOB->BSRR = setData;
}

void Write_Command(uint16_t command)
{
	HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
	HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
	HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 0);

	write_data(command);

	HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
	HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
	HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void Write_Data_int(uint16_t data)
{
	HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 0);
	HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
	HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

	write_data(data);

	HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
	HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
	HAL_GPIO_WritePin(DISPLAY_CSX_GPIO_Port, DISPLAY_CSX_Pin, 1);
}

void LCD_clear(unsigned int i)
{
	unsigned int l = 480, w;
	LCD_SetPos_Vertical(0, 479, 0, 799);
	while (l--)
	{
		for (w = 0; w < 800; w++)
		{
			Write_Data_int(i);
		}
	}
}

void LCD_FULL(unsigned int i)
{
	unsigned int w, u;
	LCD_SetPos_Vertical(0, 479, 0, 799);

	for (w = 0; w < 480; w++)
	{
		Write_Data_int(~i);
	}

	for (w = 0; w < 798; w++)
	{
		Write_Data_int(~i);

		for (u = 0; u < 478; u++)
			Write_Data_int(i);

		Write_Data_int(~i);
	}

	for (w = 0; w < 480; w++)
	{
		Write_Data_int(~i);
	}
}

void show_pic(unsigned char p[]) // 200*120
{
	unsigned int i, w, l, x1, x2, y1, y2, xa, xb, ya, yb;
	unsigned char k, m;
	Write_Command(0x3600);
	Write_Data_int(0xa0);

	xa = 0;
	xb = 199;
	ya = 0;
	yb = 119;
	i = 0;
	for (m = 0; m < 4; m++)
	{
		for (k = 0; k < 4; k++)
		{
			x1 = xa;
			x2 = xb;
			y1 = ya;
			y2 = yb;
			LCD_SetPos_Horizontal(x1, x2, y1, y2);
			for (l = 0; l < 120; l++)
			{
				for (w = 0; w < 200; w++)
				{
					Write_Data_int(ER_TFT040_CONVERT_DATA(p[i], p[i + 1]));
					i += 2;
				}
			}
			xa += 200;
			xb += 200;
			i = 0;
		}
		xa = 0;
		xb = 199;
		ya += 120;
		yb += 120;
	}

	Write_Command(0x3600);
	Write_Data_int(0x00);
}

void DispRGBGray(void)
{

	unsigned int COL = 800;
	unsigned char i, j, k, dbl, dbh;
	Write_Command(0x3600);
	Write_Data_int(0xa0);
	LCD_SetPos_Horizontal(0, 799, 0, 479);

	// balck -> red
	for (k = 0; k < 80; k++)
	{
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < 25; j++)
			{
				dbh = i << 3;
				dbl = 0;
				Write_Data_int(ER_TFT040_CONVERT_DATA(dbh, dbl));
			}
		}
	}

	// red -> black
	for (k = 0; k < 80; k++)
	{

		for (i = 31; i > 0; i--)
		{
			for (j = 0; j < 25; j++)
			{
				dbh = i << 3;
				dbl = 0;
				Write_Data_int(ER_TFT040_CONVERT_DATA(dbh, dbl));
			}
		}

		dbh = 0x00;
		dbl = 0x00;
		for (i = 0; i < 25; i++)
			Write_Data_int(0x0);
	}

	// black -> green
	for (k = 0; k < 80; k++)
	{

		for (i = 0; i < 64; i += 2)
		{
			for (j = 0; j < 25; j++)
			{
				dbh = i >> 3;
				dbl = i << 5;
				Write_Data_int(ER_TFT040_CONVERT_DATA(dbh, dbl));
			}
		}
	}

	// green -> black
	for (k = 0; k < 80; k++)
	{
		for (i = 63; i != 1; i -= 2)
		{
			for (j = 0; j < 25; j++)
			{
				dbh = i >> 3;
				dbl = i << 5;
				Write_Data_int(ER_TFT040_CONVERT_DATA(dbh, dbl));
			}
		}
		dbh = 0x00;
		dbl = 0x00;
		for (i = 0; i < 25; i++)
			Write_Data_int(0x0);
	}

	// balck -> blue
	for (k = 0; k < 80; k++)
	{
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < 25; j++)
			{
				dbh = 0;
				dbl = i;
				Write_Data_int(ER_TFT040_CONVERT_DATA(dbh, dbl));
			}
		}
	}

	// blue -> black
	for (k = 0; k < 80; k++)
	{

		for (i = 31; i > 0; i--)
		{
			for (j = 0; j < 25; j++)
			{
				dbh = 0;
				dbl = i;
				Write_Data_int(ER_TFT040_CONVERT_DATA(dbh, dbl));
			}
		}
		dbh = 0x00;
		dbl = 0x00;
		for (i = 0; i < 25; i++)
			Write_Data_int(0x0);
	}

	Write_Command(0x3600);
	Write_Data_int(0x00);
}

void LCD_SetPos_Vertical(unsigned int xs, unsigned int xe, unsigned int ys, unsigned int ye)
{
	if (LCD == HSDLCD)
	{
		ys += 4;
		ye += 4;
	}
	if (LCD == CPTLCD)
		;
	Write_Command(0x2A00);
	Write_Data_int(xs >> 8);
	Write_Command(0x2A01);
	Write_Data_int(xs & 0x00ff);
	Write_Command(0x2A02);
	Write_Data_int(xe >> 8);
	Write_Command(0x2A03);
	Write_Data_int(xe & 0x00ff);
	Write_Command(0x2B00);
	Write_Data_int(ys >> 8);
	Write_Command(0x2B01);
	Write_Data_int(ys & 0x00ff);
	Write_Command(0x2B02);
	Write_Data_int(ye >> 8);
	Write_Command(0x2B03);
	Write_Data_int(ye & 0x00ff);

	Write_Command(0x2C00);
}

void LCD_SetPos_Horizontal(unsigned int xs, unsigned int xe, unsigned int ys, unsigned int ye)
{
	if (LCD == HSDLCD)
	{
		xs += 50;
		xe += 50;
	}
	if (LCD == CPTLCD)
		;
	Write_Command(0x2A00);
	Write_Data_int(xs >> 8);
	Write_Command(0x2A01);
	Write_Data_int(xs & 0x00ff);
	Write_Command(0x2A02);
	Write_Data_int(xe >> 8);
	Write_Command(0x2A03);
	Write_Data_int(xe & 0x00ff);
	Write_Command(0x2B00);
	Write_Data_int(ys >> 8);
	Write_Command(0x2B01);
	Write_Data_int(ys & 0x00ff);
	Write_Command(0x2B02);
	Write_Data_int(ye >> 8);
	Write_Command(0x2B03);
	Write_Data_int(ye & 0x00ff);

	Write_Command(0x2C00);
}

void nt35510_Initial(void)
{

	HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 0);
	HAL_Delay(800);
	HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
	HAL_Delay(800);

	// 35510h
	Write_Command(0xF000);
	Write_Data_int(0x55);
	Write_Command(0xF001);
	Write_Data_int(0xAA);
	Write_Command(0xF002);
	Write_Data_int(0x52);
	Write_Command(0xF003);
	Write_Data_int(0x08);
	Write_Command(0xF004);
	Write_Data_int(0x01);

	// #AVDD Set AVDD 5.2V
	Write_Command(0xB000);
	Write_Data_int(0x0D);
	Write_Command(0xB001);
	Write_Data_int(0x0D);
	Write_Command(0xB002);
	Write_Data_int(0x0D);

	// #AVDD ratio
	Write_Command(0xB600);
	Write_Data_int(0x34);
	Write_Command(0xB601);
	Write_Data_int(0x34);
	Write_Command(0xB602);
	Write_Data_int(0x34);

	// #AVEE  -5.2V
	Write_Command(0xB100);
	Write_Data_int(0x0D);
	Write_Command(0xB101);
	Write_Data_int(0x0D);
	Write_Command(0xB102);
	Write_Data_int(0x0D);

	// #AVEE ratio
	Write_Command(0xB700);
	Write_Data_int(0x34);
	Write_Command(0xB701);
	Write_Data_int(0x34);
	Write_Command(0xB702);
	Write_Data_int(0x34);

	// #VCL  -2.5V
	Write_Command(0xB200);
	Write_Data_int(0x00);
	Write_Command(0xB201);
	Write_Data_int(0x00);
	Write_Command(0xB202);
	Write_Data_int(0x00);

	// #VCL ratio
	Write_Command(0xB800);
	Write_Data_int(0x24);
	Write_Command(0xB801);
	Write_Data_int(0x24);
	Write_Command(0xB802);
	Write_Data_int(0x24);

	// #VGH  15V
	Write_Command(0xBF00);
	Write_Data_int(0x01);
	Write_Command(0xB300);
	Write_Data_int(0x0F);
	Write_Command(0xB301);
	Write_Data_int(0x0F);
	Write_Command(0xB302);
	Write_Data_int(0x0F);

	// #VGH  ratio
	Write_Command(0xB900);
	Write_Data_int(0x34);
	Write_Command(0xB901);
	Write_Data_int(0x34);
	Write_Command(0xB902);
	Write_Data_int(0x34);

	// #VGL_REG  -10V
	Write_Command(0xB500);
	Write_Data_int(0x08);
	Write_Command(0xB500);
	Write_Data_int(0x08);
	Write_Command(0xB501);
	Write_Data_int(0x08);
	Write_Command(0xC200);
	Write_Data_int(0x03);

	// #VGLX  ratio
	Write_Command(0xBA00);
	Write_Data_int(0x24);
	Write_Command(0xBA01);
	Write_Data_int(0x24);
	Write_Command(0xBA02);
	Write_Data_int(0x24);

	// #VGMP/VGSP 4.5V/0V
	Write_Command(0xBC00);
	Write_Data_int(0x00);
	Write_Command(0xBC01);
	Write_Data_int(0x78);
	Write_Command(0xBC02);
	Write_Data_int(0x00);

	// #VGMN/VGSN -4.5V/0V
	Write_Command(0xBD00);
	Write_Data_int(0x00);
	Write_Command(0xBD01);
	Write_Data_int(0x78);
	Write_Command(0xBD02);
	Write_Data_int(0x00);

	// #VCOM  -1.325V
	Write_Command(0xBE00);
	Write_Data_int(0x00);
	Write_Command(0xBE01);
	Write_Data_int(0x89); // 69

	// Gamma Setting
	Write_Command(0xD100);
	Write_Data_int(0x00);
	Write_Command(0xD101);
	Write_Data_int(0x2D);
	Write_Command(0xD102);
	Write_Data_int(0x00);
	Write_Command(0xD103);
	Write_Data_int(0x2E);
	Write_Command(0xD104);
	Write_Data_int(0x00);
	Write_Command(0xD105);
	Write_Data_int(0x32);
	Write_Command(0xD106);
	Write_Data_int(0x00);
	Write_Command(0xD107);
	Write_Data_int(0x44);
	Write_Command(0xD108);
	Write_Data_int(0x00);
	Write_Command(0xD109);
	Write_Data_int(0x53);
	Write_Command(0xD10A);
	Write_Data_int(0x00);
	Write_Command(0xD10B);
	Write_Data_int(0x88);
	Write_Command(0xD10C);
	Write_Data_int(0x00);
	Write_Command(0xD10D);
	Write_Data_int(0xB6);
	Write_Command(0xD10E);
	Write_Data_int(0x00);
	Write_Command(0xD10F);
	Write_Data_int(0xF3); //
	Write_Command(0xD110);
	Write_Data_int(0x01);
	Write_Command(0xD111);
	Write_Data_int(0x22);
	Write_Command(0xD112);
	Write_Data_int(0x01);
	Write_Command(0xD113);
	Write_Data_int(0x64);
	Write_Command(0xD114);
	Write_Data_int(0x01);
	Write_Command(0xD115);
	Write_Data_int(0x92);
	Write_Command(0xD116);
	Write_Data_int(0x01);
	Write_Command(0xD117);
	Write_Data_int(0xD4);
	Write_Command(0xD118);
	Write_Data_int(0x02);
	Write_Command(0xD119);
	Write_Data_int(0x07);
	Write_Command(0xD11A);
	Write_Data_int(0x02);
	Write_Command(0xD11B);
	Write_Data_int(0x08);
	Write_Command(0xD11C);
	Write_Data_int(0x02);
	Write_Command(0xD11D);
	Write_Data_int(0x34);
	Write_Command(0xD11E);
	Write_Data_int(0x02);
	Write_Command(0xD11F);
	Write_Data_int(0x5F); //
	Write_Command(0xD120);
	Write_Data_int(0x02);
	Write_Command(0xD121);
	Write_Data_int(0x78);
	Write_Command(0xD122);
	Write_Data_int(0x02);
	Write_Command(0xD123);
	Write_Data_int(0x94);
	Write_Command(0xD124);
	Write_Data_int(0x02);
	Write_Command(0xD125);
	Write_Data_int(0xA6);
	Write_Command(0xD126);
	Write_Data_int(0x02);
	Write_Command(0xD127);
	Write_Data_int(0xBB);
	Write_Command(0xD128);
	Write_Data_int(0x02);
	Write_Command(0xD129);
	Write_Data_int(0xCA);
	Write_Command(0xD12A);
	Write_Data_int(0x02);
	Write_Command(0xD12B);
	Write_Data_int(0xDB);
	Write_Command(0xD12C);
	Write_Data_int(0x02);
	Write_Command(0xD12D);
	Write_Data_int(0xE8);
	Write_Command(0xD12E);
	Write_Data_int(0x02);
	Write_Command(0xD12F);
	Write_Data_int(0xF9); //
	Write_Command(0xD130);
	Write_Data_int(0x03);
	Write_Command(0xD131);
	Write_Data_int(0x1F);
	Write_Command(0xD132);
	Write_Data_int(0x03);
	Write_Command(0xD133);
	Write_Data_int(0x7F);

	Write_Command(0xD200);
	Write_Data_int(0x00);
	Write_Command(0xD201);
	Write_Data_int(0x2D);
	Write_Command(0xD202);
	Write_Data_int(0x00);
	Write_Command(0xD203);
	Write_Data_int(0x2E);
	Write_Command(0xD204);
	Write_Data_int(0x00);
	Write_Command(0xD205);
	Write_Data_int(0x32);
	Write_Command(0xD206);
	Write_Data_int(0x00);
	Write_Command(0xD207);
	Write_Data_int(0x44);
	Write_Command(0xD208);
	Write_Data_int(0x00);
	Write_Command(0xD209);
	Write_Data_int(0x53);
	Write_Command(0xD20A);
	Write_Data_int(0x00);
	Write_Command(0xD20B);
	Write_Data_int(0x88);
	Write_Command(0xD20C);
	Write_Data_int(0x00);
	Write_Command(0xD20D);
	Write_Data_int(0xB6);
	Write_Command(0xD20E);
	Write_Data_int(0x00);
	Write_Command(0xD20F);
	Write_Data_int(0xF3); //
	Write_Command(0xD210);
	Write_Data_int(0x01);
	Write_Command(0xD211);
	Write_Data_int(0x22);
	Write_Command(0xD212);
	Write_Data_int(0x01);
	Write_Command(0xD213);
	Write_Data_int(0x64);
	Write_Command(0xD214);
	Write_Data_int(0x01);
	Write_Command(0xD215);
	Write_Data_int(0x92);
	Write_Command(0xD216);
	Write_Data_int(0x01);
	Write_Command(0xD217);
	Write_Data_int(0xD4);
	Write_Command(0xD218);
	Write_Data_int(0x02);
	Write_Command(0xD219);
	Write_Data_int(0x07);
	Write_Command(0xD21A);
	Write_Data_int(0x02);
	Write_Command(0xD21B);
	Write_Data_int(0x08);
	Write_Command(0xD21C);
	Write_Data_int(0x02);
	Write_Command(0xD21D);
	Write_Data_int(0x34);
	Write_Command(0xD21E);
	Write_Data_int(0x02);
	Write_Command(0xD21F);
	Write_Data_int(0x5F); //
	Write_Command(0xD220);
	Write_Data_int(0x02);
	Write_Command(0xD221);
	Write_Data_int(0x78);
	Write_Command(0xD222);
	Write_Data_int(0x02);
	Write_Command(0xD223);
	Write_Data_int(0x94);
	Write_Command(0xD224);
	Write_Data_int(0x02);
	Write_Command(0xD225);
	Write_Data_int(0xA6);
	Write_Command(0xD226);
	Write_Data_int(0x02);
	Write_Command(0xD227);
	Write_Data_int(0xBB);
	Write_Command(0xD228);
	Write_Data_int(0x02);
	Write_Command(0xD229);
	Write_Data_int(0xCA);
	Write_Command(0xD22A);
	Write_Data_int(0x02);
	Write_Command(0xD22B);
	Write_Data_int(0xDB);
	Write_Command(0xD22C);
	Write_Data_int(0x02);
	Write_Command(0xD22D);
	Write_Data_int(0xE8);
	Write_Command(0xD22E);
	Write_Data_int(0x02);
	Write_Command(0xD22F);
	Write_Data_int(0xF9); //
	Write_Command(0xD230);
	Write_Data_int(0x03);
	Write_Command(0xD231);
	Write_Data_int(0x1F);
	Write_Command(0xD232);
	Write_Data_int(0x03);
	Write_Command(0xD233);
	Write_Data_int(0x7F);

	Write_Command(0xD300);
	Write_Data_int(0x00);
	Write_Command(0xD301);
	Write_Data_int(0x2D);
	Write_Command(0xD302);
	Write_Data_int(0x00);
	Write_Command(0xD303);
	Write_Data_int(0x2E);
	Write_Command(0xD304);
	Write_Data_int(0x00);
	Write_Command(0xD305);
	Write_Data_int(0x32);
	Write_Command(0xD306);
	Write_Data_int(0x00);
	Write_Command(0xD307);
	Write_Data_int(0x44);
	Write_Command(0xD308);
	Write_Data_int(0x00);
	Write_Command(0xD309);
	Write_Data_int(0x53);
	Write_Command(0xD30A);
	Write_Data_int(0x00);
	Write_Command(0xD30B);
	Write_Data_int(0x88);
	Write_Command(0xD30C);
	Write_Data_int(0x00);
	Write_Command(0xD30D);
	Write_Data_int(0xB6);
	Write_Command(0xD30E);
	Write_Data_int(0x00);
	Write_Command(0xD30F);
	Write_Data_int(0xF3); //
	Write_Command(0xD310);
	Write_Data_int(0x01);
	Write_Command(0xD311);
	Write_Data_int(0x22);
	Write_Command(0xD312);
	Write_Data_int(0x01);
	Write_Command(0xD313);
	Write_Data_int(0x64);
	Write_Command(0xD314);
	Write_Data_int(0x01);
	Write_Command(0xD315);
	Write_Data_int(0x92);
	Write_Command(0xD316);
	Write_Data_int(0x01);
	Write_Command(0xD317);
	Write_Data_int(0xD4);
	Write_Command(0xD318);
	Write_Data_int(0x02);
	Write_Command(0xD319);
	Write_Data_int(0x07);
	Write_Command(0xD31A);
	Write_Data_int(0x02);
	Write_Command(0xD31B);
	Write_Data_int(0x08);
	Write_Command(0xD31C);
	Write_Data_int(0x02);
	Write_Command(0xD31D);
	Write_Data_int(0x34);
	Write_Command(0xD31E);
	Write_Data_int(0x02);
	Write_Command(0xD31F);
	Write_Data_int(0x5F); //
	Write_Command(0xD320);
	Write_Data_int(0x02);
	Write_Command(0xD321);
	Write_Data_int(0x78);
	Write_Command(0xD322);
	Write_Data_int(0x02);
	Write_Command(0xD323);
	Write_Data_int(0x94);
	Write_Command(0xD324);
	Write_Data_int(0x02);
	Write_Command(0xD325);
	Write_Data_int(0xA6);
	Write_Command(0xD326);
	Write_Data_int(0x02);
	Write_Command(0xD327);
	Write_Data_int(0xBB);
	Write_Command(0xD328);
	Write_Data_int(0x02);
	Write_Command(0xD329);
	Write_Data_int(0xCA);
	Write_Command(0xD32A);
	Write_Data_int(0x02);
	Write_Command(0xD32B);
	Write_Data_int(0xDB);
	Write_Command(0xD32C);
	Write_Data_int(0x02);
	Write_Command(0xD32D);
	Write_Data_int(0xE8);
	Write_Command(0xD32E);
	Write_Data_int(0x02);
	Write_Command(0xD32F);
	Write_Data_int(0xF9); //
	Write_Command(0xD330);
	Write_Data_int(0x03);
	Write_Command(0xD331);
	Write_Data_int(0x1F);
	Write_Command(0xD332);
	Write_Data_int(0x03);
	Write_Command(0xD333);
	Write_Data_int(0x7F);

	Write_Command(0xD400);
	Write_Data_int(0x00);
	Write_Command(0xD401);
	Write_Data_int(0x2D);
	Write_Command(0xD402);
	Write_Data_int(0x00);
	Write_Command(0xD403);
	Write_Data_int(0x2E);
	Write_Command(0xD404);
	Write_Data_int(0x00);
	Write_Command(0xD405);
	Write_Data_int(0x32);
	Write_Command(0xD406);
	Write_Data_int(0x00);
	Write_Command(0xD407);
	Write_Data_int(0x44);
	Write_Command(0xD408);
	Write_Data_int(0x00);
	Write_Command(0xD409);
	Write_Data_int(0x53);
	Write_Command(0xD40A);
	Write_Data_int(0x00);
	Write_Command(0xD40B);
	Write_Data_int(0x88);
	Write_Command(0xD40C);
	Write_Data_int(0x00);
	Write_Command(0xD40D);
	Write_Data_int(0xB6);
	Write_Command(0xD40E);
	Write_Data_int(0x00);
	Write_Command(0xD40F);
	Write_Data_int(0xF3); //
	Write_Command(0xD410);
	Write_Data_int(0x01);
	Write_Command(0xD411);
	Write_Data_int(0x22);
	Write_Command(0xD412);
	Write_Data_int(0x01);
	Write_Command(0xD413);
	Write_Data_int(0x64);
	Write_Command(0xD414);
	Write_Data_int(0x01);
	Write_Command(0xD415);
	Write_Data_int(0x92);
	Write_Command(0xD416);
	Write_Data_int(0x01);
	Write_Command(0xD417);
	Write_Data_int(0xD4);
	Write_Command(0xD418);
	Write_Data_int(0x02);
	Write_Command(0xD419);
	Write_Data_int(0x07);
	Write_Command(0xD41A);
	Write_Data_int(0x02);
	Write_Command(0xD41B);
	Write_Data_int(0x08);
	Write_Command(0xD41C);
	Write_Data_int(0x02);
	Write_Command(0xD41D);
	Write_Data_int(0x34);
	Write_Command(0xD41E);
	Write_Data_int(0x02);
	Write_Command(0xD41F);
	Write_Data_int(0x5F); //
	Write_Command(0xD420);
	Write_Data_int(0x02);
	Write_Command(0xD421);
	Write_Data_int(0x78);
	Write_Command(0xD422);
	Write_Data_int(0x02);
	Write_Command(0xD423);
	Write_Data_int(0x94);
	Write_Command(0xD424);
	Write_Data_int(0x02);
	Write_Command(0xD425);
	Write_Data_int(0xA6);
	Write_Command(0xD426);
	Write_Data_int(0x02);
	Write_Command(0xD427);
	Write_Data_int(0xBB);
	Write_Command(0xD428);
	Write_Data_int(0x02);
	Write_Command(0xD429);
	Write_Data_int(0xCA);
	Write_Command(0xD42A);
	Write_Data_int(0x02);
	Write_Command(0xD42B);
	Write_Data_int(0xDB);
	Write_Command(0xD42C);
	Write_Data_int(0x02);
	Write_Command(0xD42D);
	Write_Data_int(0xE8);
	Write_Command(0xD42E);
	Write_Data_int(0x02);
	Write_Command(0xD42F);
	Write_Data_int(0xF9); //
	Write_Command(0xD430);
	Write_Data_int(0x03);
	Write_Command(0xD431);
	Write_Data_int(0x1F);
	Write_Command(0xD432);
	Write_Data_int(0x03);
	Write_Command(0xD433);
	Write_Data_int(0x7F);

	Write_Command(0xD500);
	Write_Data_int(0x00);
	Write_Command(0xD501);
	Write_Data_int(0x2D);
	Write_Command(0xD502);
	Write_Data_int(0x00);
	Write_Command(0xD503);
	Write_Data_int(0x2E);
	Write_Command(0xD504);
	Write_Data_int(0x00);
	Write_Command(0xD505);
	Write_Data_int(0x32);
	Write_Command(0xD506);
	Write_Data_int(0x00);
	Write_Command(0xD507);
	Write_Data_int(0x44);
	Write_Command(0xD508);
	Write_Data_int(0x00);
	Write_Command(0xD509);
	Write_Data_int(0x53);
	Write_Command(0xD50A);
	Write_Data_int(0x00);
	Write_Command(0xD50B);
	Write_Data_int(0x88);
	Write_Command(0xD50C);
	Write_Data_int(0x00);
	Write_Command(0xD50D);
	Write_Data_int(0xB6);
	Write_Command(0xD50E);
	Write_Data_int(0x00);
	Write_Command(0xD50F);
	Write_Data_int(0xF3); //
	Write_Command(0xD510);
	Write_Data_int(0x01);
	Write_Command(0xD511);
	Write_Data_int(0x22);
	Write_Command(0xD512);
	Write_Data_int(0x01);
	Write_Command(0xD513);
	Write_Data_int(0x64);
	Write_Command(0xD514);
	Write_Data_int(0x01);
	Write_Command(0xD515);
	Write_Data_int(0x92);
	Write_Command(0xD516);
	Write_Data_int(0x01);
	Write_Command(0xD517);
	Write_Data_int(0xD4);
	Write_Command(0xD518);
	Write_Data_int(0x02);
	Write_Command(0xD519);
	Write_Data_int(0x07);
	Write_Command(0xD51A);
	Write_Data_int(0x02);
	Write_Command(0xD51B);
	Write_Data_int(0x08);
	Write_Command(0xD51C);
	Write_Data_int(0x02);
	Write_Command(0xD51D);
	Write_Data_int(0x34);
	Write_Command(0xD51E);
	Write_Data_int(0x02);
	Write_Command(0xD51F);
	Write_Data_int(0x5F); //
	Write_Command(0xD520);
	Write_Data_int(0x02);
	Write_Command(0xD521);
	Write_Data_int(0x78);
	Write_Command(0xD522);
	Write_Data_int(0x02);
	Write_Command(0xD523);
	Write_Data_int(0x94);
	Write_Command(0xD524);
	Write_Data_int(0x02);
	Write_Command(0xD525);
	Write_Data_int(0xA6);
	Write_Command(0xD526);
	Write_Data_int(0x02);
	Write_Command(0xD527);
	Write_Data_int(0xBB);
	Write_Command(0xD528);
	Write_Data_int(0x02);
	Write_Command(0xD529);
	Write_Data_int(0xCA);
	Write_Command(0xD52A);
	Write_Data_int(0x02);
	Write_Command(0xD52B);
	Write_Data_int(0xDB);
	Write_Command(0xD52C);
	Write_Data_int(0x02);
	Write_Command(0xD52D);
	Write_Data_int(0xE8);
	Write_Command(0xD52E);
	Write_Data_int(0x02);
	Write_Command(0xD52F);
	Write_Data_int(0xF9); //
	Write_Command(0xD530);
	Write_Data_int(0x03);
	Write_Command(0xD531);
	Write_Data_int(0x1F);
	Write_Command(0xD532);
	Write_Data_int(0x03);
	Write_Command(0xD533);
	Write_Data_int(0x7F);

	Write_Command(0xD600);
	Write_Data_int(0x00);
	Write_Command(0xD601);
	Write_Data_int(0x2D);
	Write_Command(0xD602);
	Write_Data_int(0x00);
	Write_Command(0xD603);
	Write_Data_int(0x2E);
	Write_Command(0xD604);
	Write_Data_int(0x00);
	Write_Command(0xD605);
	Write_Data_int(0x32);
	Write_Command(0xD606);
	Write_Data_int(0x00);
	Write_Command(0xD607);
	Write_Data_int(0x44);
	Write_Command(0xD608);
	Write_Data_int(0x00);
	Write_Command(0xD609);
	Write_Data_int(0x53);
	Write_Command(0xD60A);
	Write_Data_int(0x00);
	Write_Command(0xD60B);
	Write_Data_int(0x88);
	Write_Command(0xD60C);
	Write_Data_int(0x00);
	Write_Command(0xD60D);
	Write_Data_int(0xB6);
	Write_Command(0xD60E);
	Write_Data_int(0x00);
	Write_Command(0xD60F);
	Write_Data_int(0xF3); //
	Write_Command(0xD610);
	Write_Data_int(0x01);
	Write_Command(0xD611);
	Write_Data_int(0x22);
	Write_Command(0xD612);
	Write_Data_int(0x01);
	Write_Command(0xD613);
	Write_Data_int(0x64);
	Write_Command(0xD614);
	Write_Data_int(0x01);
	Write_Command(0xD615);
	Write_Data_int(0x92);
	Write_Command(0xD616);
	Write_Data_int(0x01);
	Write_Command(0xD617);
	Write_Data_int(0xD4);
	Write_Command(0xD618);
	Write_Data_int(0x02);
	Write_Command(0xD619);
	Write_Data_int(0x07);
	Write_Command(0xD61A);
	Write_Data_int(0x02);
	Write_Command(0xD61B);
	Write_Data_int(0x08);
	Write_Command(0xD61C);
	Write_Data_int(0x02);
	Write_Command(0xD61D);
	Write_Data_int(0x34);
	Write_Command(0xD61E);
	Write_Data_int(0x02);
	Write_Command(0xD61F);
	Write_Data_int(0x5F); //
	Write_Command(0xD620);
	Write_Data_int(0x02);
	Write_Command(0xD621);
	Write_Data_int(0x78);
	Write_Command(0xD622);
	Write_Data_int(0x02);
	Write_Command(0xD623);
	Write_Data_int(0x94);
	Write_Command(0xD624);
	Write_Data_int(0x02);
	Write_Command(0xD625);
	Write_Data_int(0xA6);
	Write_Command(0xD626);
	Write_Data_int(0x02);
	Write_Command(0xD627);
	Write_Data_int(0xBB);
	Write_Command(0xD628);
	Write_Data_int(0x02);
	Write_Command(0xD629);
	Write_Data_int(0xCA);
	Write_Command(0xD62A);
	Write_Data_int(0x02);
	Write_Command(0xD62B);
	Write_Data_int(0xDB);
	Write_Command(0xD62C);
	Write_Data_int(0x02);
	Write_Command(0xD62D);
	Write_Data_int(0xE8);
	Write_Command(0xD62E);
	Write_Data_int(0x02);
	Write_Command(0xD62F);
	Write_Data_int(0xF9); //
	Write_Command(0xD630);
	Write_Data_int(0x03);
	Write_Command(0xD631);
	Write_Data_int(0x1F);
	Write_Command(0xD632);
	Write_Data_int(0x03);
	Write_Command(0xD633);
	Write_Data_int(0x7F);

	// #LV2 Page 0 enable
	Write_Command(0xF000);
	Write_Data_int(0x55);
	Write_Command(0xF001);
	Write_Data_int(0xAA);
	Write_Command(0xF002);
	Write_Data_int(0x52);
	Write_Command(0xF003);
	Write_Data_int(0x08);
	Write_Command(0xF004);
	Write_Data_int(0x00);

	// #DISPLAY CONTROL
	Write_Command(0xB100);
	Write_Data_int(0xCC);
	Write_Command(0xB101);
	Write_Data_int(0x00);

	if (LCD == HSDLCD)
	{
		Write_Command(0xB500);
		Write_Data_int(0x6b);
	}
	if (LCD == CPTLCD)
	{
		Write_Command(0xB500);
		Write_Data_int(0x50);
	}

	// #SOURCE HOLD TIME
	Write_Command(0xB600);
	Write_Data_int(0x05);

	// Set Gate EQ
	Write_Command(0xB700);
	Write_Data_int(0x70);
	Write_Command(0xB701);
	Write_Data_int(0x70);

	// #Source EQ control (Mode 2)
	Write_Command(0xB800);
	Write_Data_int(0x01);
	Write_Command(0xB801);
	Write_Data_int(0x03);
	Write_Command(0xB802);
	Write_Data_int(0x03);
	Write_Command(0xB803);
	Write_Data_int(0x03);

	// #INVERSION MODE
	Write_Command(0xBC00);
	Write_Data_int(0x02);
	Write_Command(0xBC01);
	Write_Data_int(0x00);
	Write_Command(0xBC02);
	Write_Data_int(0x00);

	// #Timing control
	Write_Command(0xC900);
	Write_Data_int(0xD0);
	Write_Command(0xC901);
	Write_Data_int(0x02);
	Write_Command(0xC902);
	Write_Data_int(0x50);
	Write_Command(0xC903);
	Write_Data_int(0x50);
	Write_Command(0xC904);
	Write_Data_int(0x50);

	Write_Command(0x3500);
	Write_Data_int(0x00);

	Write_Command(0x3A00);
	Write_Data_int(0x55); // Data format 16-Bits
	Write_Command(0x3600);
	Write_Data_int(0x00);

	Write_Command(0x1100); // StartUp

	HAL_Delay(120);

	Write_Command(0x2900); // Display On
	HAL_Delay(100);
}