#include "sd_card.h"

FATFS fs;  // file system
FIL fil;   // File
FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;      // File read/write count

/**** capacity related *****/
FATFS *pfs;
DWORD fre_clust;

FRESULT SDCard_mount(const TCHAR *path) {
    fresult = f_mount(&fs, path, 1);

    return fresult;
}

FRESULT SDCard_unmount(const TCHAR *path) {
    fresult = f_mount(NULL, path, 1);

    return fresult;
}

FRESULT SDCard_checkCapacity(SDCard_capacity *capacity) {
    FRESULT fresult = f_getfree("", &fre_clust, &pfs);

    if (fresult != FR_OK) {
        return fresult;
    }

    uint32_t total_capacity = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    uint32_t free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
    uint32_t used_space = total_capacity - free_space;

    capacity->total = total_capacity;
    capacity->free = free_space;
    capacity->used = used_space;

    return fresult;
}

/* Only supports removing files from home directory */
FRESULT SDCard_removeFiles(void) {
    DIR dir;
    char *path = malloc(20 * sizeof(char));
    sprintf(path, "%s", "/");

    fresult = f_opendir(&dir, path); /* Open the directory */

    if (fresult == FR_OK) {
        while (1) {
            fresult = f_readdir(&dir, &fno);                  /* Read a directory item */
            if (fresult != FR_OK || fno.fname[0] == 0) break; /* Break on error or end of dir */

            if (fno.fattrib & AM_DIR) { /* It is a directory */
                if (!(strcmp("SYSTEM~1", fno.fname))) continue;
                fresult = f_unlink(fno.fname);
                if (fresult == FR_DENIED) continue;
            } else { /* It is a file. */
                fresult = f_unlink(fno.fname);
            }
        }

        f_closedir(&dir);
    }

    free(path);

    return fresult;
}

FRESULT SDCard_writeFile(char *name, char *data) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);
    if (fresult != FR_OK) {
        char *buf = malloc(100 * sizeof(char));
        sprintf(buf, "ERROR!!! *%s* does not exists\n\n", name);
        free(buf);
        return fresult;
    } else {
        /* Create a file with read write access and open it */
        fresult = f_open(&fil, name, FA_OPEN_EXISTING | FA_WRITE);

        if (fresult != FR_OK) {
            char *buf = malloc(100 * sizeof(char));
            sprintf(buf, "ERROR!!! No. %d in opening file *%s*\n\n", fresult, name);
            free(buf);
            return fresult;
        } else {
            fresult = f_write(&fil, data, strlen(data), &bw);

            if (fresult != FR_OK) {
                char *buf = malloc(100 * sizeof(char));
                sprintf(buf, "ERROR!!! No. %d while writing to the FILE *%s*\n\n", fresult, name);
                free(buf);
            }

            /* Close file */
            fresult = f_close(&fil);
            if (fresult != FR_OK) {
                char *buf = malloc(100 * sizeof(char));
                sprintf(buf, "ERROR!!! No. %d in closing file *%s* after writing it\n\n", fresult, name);
                free(buf);
            } else {
                char *buf = malloc(100 * sizeof(char));
                sprintf(buf, "File *%s* is WRITTEN and CLOSED successfully\n", name);
                free(buf);
            }
        }

        return fresult;
    }
}

FRESULT SDCard_readFile(char *name) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);
    if (fresult != FR_OK) {
        char *buf = malloc(100 * sizeof(char));
        sprintf(buf, "ERRROR!!! *%s* does not exists\n\n", name);
        free(buf);
        return fresult;
    } else {
        /* Open file to read */
        fresult = f_open(&fil, name, FA_READ);

        if (fresult != FR_OK) {
            char *buf = malloc(100 * sizeof(char));
            sprintf(buf, "ERROR!!! No. %d in opening file *%s*\n\n", fresult, name);
            free(buf);
            return fresult;
        }

        /* Read data from the file
         * see the function details for the arguments */

        char *buffer = malloc(sizeof(f_size(&fil)));
        fresult = f_read(&fil, buffer, f_size(&fil), &br);

        if (fresult != FR_OK) {
            char *buf = malloc(100 * sizeof(char));
            free(buffer);
            sprintf(buf, "ERROR!!! No. %d in reading file *%s*\n\n", fresult, name);
            free(buf);
        } else {
            free(buffer);

            /* Close file */
            fresult = f_close(&fil);
            if (fresult != FR_OK) {
                char *buf = malloc(100 * sizeof(char));
                sprintf(buf, "ERROR!!! No. %d in closing file *%s*\n\n", fresult, name);
                free(buf);
            } else {
                char *buf = malloc(100 * sizeof(char));
                sprintf(buf, "File *%s* CLOSED successfully\n", name);
                free(buf);
            }
        }

        return fresult;
    }
}

FRESULT SDCard_createFile(char *name) {
    fresult = f_stat(name, &fno);

    if (fresult == FR_OK) {
        char *buf = malloc(100 * sizeof(char));
        sprintf(buf, "ERROR!!! *%s* already exists!!!!\n use Update_File \n\n", name);
        free(buf);
        return fresult;
    } else {
        fresult = f_open(&fil, name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);

        if (fresult != FR_OK) {
            char *buf = malloc(100 * sizeof(char));
            sprintf(buf, "ERROR!!! No. %d in creating file *%s*\n\n", fresult, name);
            free(buf);
            return fresult;
        } else {
            char *buf = malloc(100 * sizeof(char));
            sprintf(buf, "*%s* created successfully\n Now use Write_File to write data\n", name);
            free(buf);
        }

        fresult = f_close(&fil);

        if (fresult != FR_OK) {
            char *buf = malloc(100 * sizeof(char));
            sprintf(buf, "ERROR No. %d in closing file *%s*\n\n", fresult, name);
            free(buf);
        } else {
            char *buf = malloc(100 * sizeof(char));
            sprintf(buf, "File *%s* CLOSED successfully\n", name);
            free(buf);
        }
    }

    return fresult;
}

FRESULT SDCard_updateFile(char *name, char *data) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);

    if (fresult != FR_OK) {
        char *buf = malloc(100 * sizeof(char));
        sprintf(buf, "ERROR!!! *%s* does not exists\n\n", name);
        free(buf);
        return fresult;
    } else {
        /* Create a file with read write access and open it */
        fresult = f_open(&fil, name, FA_OPEN_APPEND | FA_WRITE);

        if (fresult != FR_OK) {
            return fresult;
        }

        /* Writing text */
        fresult = f_write(&fil, data, strlen(data), &bw);

        /* Close file */
        fresult = f_close(&fil);
    }

    return fresult;
}

FRESULT SDCard_removeFile(char *name) {
    /**** check whether the file exists or not ****/
    fresult = f_stat(name, &fno);

    if (fresult != FR_OK) {
        return fresult;
    } else {
        fresult = f_unlink(name);
    }

    return fresult;
}

FRESULT SDCard_createDirectory(char *name) {
    fresult = f_mkdir(name);

    return fresult;
}