
#define JPEG_INTERNALS

#include "er_tft040.h"
#include "jinclude.h"
#include "jpeglib.h"
#include "sd_card.h"

struct jpeg_decompress_struct cinfo;
typedef struct RGB {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB_typedef;
struct jpeg_error_mgr jerr;

RGB_typedef *RGB_matrix;

uint16_t RGB16PixelColor;
uint32_t RGB24PixelColor;
static uint8_t *rowBuff;

static uint8_t jpeg_decode(JFILE *file, uint8_t *rowBuff, int posx, int posy, uint16_t *iw, uint16_t *ih) {
    uint32_t line_counter = 0;
    uint32_t i = 0, xc = 0, ratio;
    uint8_t offset = 1;
    JSAMPROW buffer[2] = {0};

    UINT lcdWidth, lcdHeight;

    buffer[0] = rowBuff;
    lcdWidth = 480;
    lcdHeight = 800;

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, file);

    jpeg_read_header(&cinfo, TRUE);
    if (cinfo.image_width > 6000) {
        //	  showMessage("Image width exceeds 6000!!!", 5);
        return 0;
    }

    if (cinfo.image_width > lcdWidth) {
        ratio = cinfo.image_width / lcdWidth;
        cinfo.scale_num = 1;
        if (ratio <= 8) {
            cinfo.scale_denom = 1;
            for (int s = 0x8; s > 0x01; s /= 2) {
                if (ratio & s) {
                    cinfo.scale_denom = s;
                    break;
                }
            }
        } else {
            cinfo.scale_denom = 8;
        }
    }

    cinfo.dct_method = JDCT_IFAST;

    jpeg_start_decompress(&cinfo);
    if (cinfo.output_width > lcdWidth) {
        offset = cinfo.output_width / lcdWidth;
        if (cinfo.output_width % lcdWidth > lcdWidth / 4) offset++;
    }

    if (posx < 0 || posy < 0) {
        posx = (lcdWidth - (cinfo.output_width * (offset - 1) / offset)) / 2;
        posy = (lcdHeight - (cinfo.output_height * (offset - 1) / offset)) / 2;
    }
    *iw = cinfo.image_width;
    *ih = cinfo.image_height;

    ER_TFT040_clearLCD(0x000000);

    if (posx > 0 && cinfo.output_width / offset < lcdWidth) {
        ER_TFT040_drawRectangle(posx - 1, posy - 1, cinfo.output_width / offset + 2, cinfo.output_height / offset + 2,
                                0xFFFFFF);
    }

    while (cinfo.output_scanline < cinfo.output_height && line_counter < lcdHeight - posy) {
        (void)jpeg_read_scanlines(&cinfo, buffer, 1);
        RGB_matrix = (RGB_typedef *)buffer[0];
        for (i = 0, xc = 0; i < cinfo.output_width && xc < (lcdWidth - posx); i += offset, xc++) {
            RGB16PixelColor = (uint16_t)(((RGB_matrix[i].R & 0x00F8) >> 3) | ((RGB_matrix[i].G & 0x00FC) << 3) |
                                         ((RGB_matrix[i].B & 0x00F8) << 8));
            RGB24PixelColor = 0;
            RGB24PixelColor |= RGB_matrix[i].R << 16;
            RGB24PixelColor |= RGB_matrix[i].G << 8;
            RGB24PixelColor |= RGB_matrix[i].B;

            ER_TFT040_drawPixel(xc + posx, line_counter + posy, RGB24PixelColor);
        }
        for (i = 0; i < offset - 1 && cinfo.output_scanline < cinfo.output_height; i++)
            (void)jpeg_read_scanlines(&cinfo, buffer, 1);

        line_counter++;
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return 1;
}

void jpeg_screen_view(char *path, char *fn, int px, int py, uint16_t *iw, uint16_t *ih) {
    FIL file;

    rowBuff = JMALLOC(2048);

    volatile FRESULT result = SDCard_mount("/");

    if (result != FR_OK) {
        free(rowBuff);
        return;
    }

    if (f_open(&file, fn, FA_READ) == FR_OK) {
        jpeg_decode(&file, rowBuff, px, py, iw, ih);
        f_close(&file);
    }

    SDCard_unmount("/");

    free(rowBuff);
}
