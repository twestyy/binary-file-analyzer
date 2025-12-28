#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int readfile(const char *filename, uint8_t **data, size_t *size) {
    FILE *f = fopen(filename, "rb");
    if (!f) return -1;

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return -2;
    }

    long file_size = ftell(f);
    if (file_size < 0) {
        fclose(f);
        return -3;
    }

    rewind(f);

    uint8_t *buffer = (uint8_t *)malloc(file_size);
    if (!buffer) {
        fclose(f);
        return -4;
    }

    if (fread(buffer, 1, file_size, f) != (size_t)file_size) {
        free(buffer);
        fclose(f);
        return -5;
    }

    fclose(f);
    *data = buffer;
    *size = (size_t)file_size;
    return 0;
}

int check_mz(uint8_t *data, size_t size) {
    if (size < 2) return -1;
    if (data[0] != 'M' || data[1] != 'Z') return -1;
    return 1;
}

