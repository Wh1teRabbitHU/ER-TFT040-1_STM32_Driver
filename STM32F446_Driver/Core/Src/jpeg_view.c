
#define JPEG_INTERNALS

#include "er_tft040.h"
#include "jinclude.h"
#include "jpeglib.h"
#include "sd_card.h"

struct jpeg_decompress_struct cinfo;
typedef struct rgb_t {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} rgb_t;

struct jpeg_error_mgr jerr;

static uint8_t jpeg_decode(JFILE *file, int startX, int startY) {
    rgb_t *rgbData;
    uint8_t *rowBuff = malloc(34 * ER_TFT040_SCREEN_WIDTH);
    uint32_t pixelColor;
    uint32_t rowIndex = 0;
    uint32_t i = 0;
    JSAMPROW buffer[2] = {0};

    buffer[0] = rowBuff;

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    // Images compressed in progressive mode doesn't work, skipping
    if (cinfo.progressive_mode || cinfo.image_width > ER_TFT040_SCREEN_WIDTH) {
        // TODO: show error on the screen before skip
        jpeg_destroy_decompress(&cinfo);

        free(rowBuff);

        return 0;
    }

    jpeg_start_decompress(&cinfo);

    ER_TFT040_startPictureDraw(startX, startY, cinfo.image_width, cinfo.image_height);

    while (cinfo.output_scanline < cinfo.output_height && rowIndex < (ER_TFT040_SCREEN_HEIGHT - startY)) {
        jpeg_read_scanlines(&cinfo, buffer, 1);

        rgbData = (rgb_t *)buffer[0];

        for (i = 0; i < cinfo.output_width && i < (ER_TFT040_SCREEN_WIDTH - startX); i++) {
            pixelColor = (rgbData[i].R << 16) | (rgbData[i].G << 8) | rgbData[i].B;

            ER_TFT040_sendPicturePixel(pixelColor);
        }

        rowIndex++;
    }

    ER_TFT040_endPictureDraw();

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    free(rowBuff);

    return 1;
}

uint8_t jpeg_display(char *path, char *fn, int px, int py) {
    FIL file;
    FRESULT result;

    result = SDCard_mount("/");

    if (result != FR_OK) {
        // TODO: Log error message to screen
        return 0;
    }

    result = f_open(&file, fn, FA_READ);

    if (result != FR_OK) {
        // TODO: Log error message to screen
        return 0;
    }

    jpeg_decode(&file, px, py);
    f_close(&file);

    SDCard_unmount("/");

    return 1;
}
