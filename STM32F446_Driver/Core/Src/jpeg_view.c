
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

uint32_t RGB24PixelColor;

static uint8_t jpeg_decode(JFILE *file, int startX, int startY) {
    RGB_typedef *RGB_matrix;
    uint8_t *rowBuff = malloc(34 * ER_TFT040_SCREEN_WIDTH);
    uint32_t lineCounter = 0;
    uint32_t i = 0;
    JSAMPROW buffer[2] = {0};

    UINT lcdWidth, lcdHeight;

    buffer[0] = rowBuff;
    lcdWidth = ER_TFT040_SCREEN_WIDTH;
    lcdHeight = ER_TFT040_SCREEN_HEIGHT;

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    // Images compressed in progressive mode doesn't work, skipping
    if (cinfo.progressive_mode || cinfo.image_width > lcdWidth) {
        // TODO: show error on the screen before skip
        jpeg_destroy_decompress(&cinfo);

        free(rowBuff);

        return 0;
    }

    jpeg_start_decompress(&cinfo);

    ER_TFT040_startPictureDraw(startX, startY, cinfo.image_width, cinfo.image_height);

    while (cinfo.output_scanline < cinfo.output_height && lineCounter < lcdHeight - startY) {
        jpeg_read_scanlines(&cinfo, buffer, 1);

        RGB_matrix = (RGB_typedef *)buffer[0];

        for (i = 0; i < cinfo.output_width && i < (lcdWidth - startX); i++) {
            RGB24PixelColor = (RGB_matrix[i].R << 16) | (RGB_matrix[i].G << 8) | RGB_matrix[i].B;

            ER_TFT040_sendPicturePixel(RGB24PixelColor);
        }

        lineCounter++;
    }

    ER_TFT040_endPictureDraw();

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    free(rowBuff);

    return 1;
}

void jpeg_screen_view(char *path, char *fn, int px, int py) {
    FIL file;

    FRESULT result = SDCard_mount("/");

    if (result != FR_OK) {
        return;
    }

    if (f_open(&file, fn, FA_READ) == FR_OK) {
        jpeg_decode(&file, px, py);
        f_close(&file);
    }

    SDCard_unmount("/");
}
