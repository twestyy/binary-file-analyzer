#include "file_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

MagicNumber magic_numbers[] = {

    { "Этот файл EXE / DLL / SYS (PE)", {0x4D, 0x5A}, 2 },
    { "Этот файл PE-заголовок",        {0x50, 0x45, 0x00, 0x00}, 4 },

    { "Этот файл ZIP", {0x50, 0x4B, 0x03, 0x04}, 4 },
    { "Этот файл PNG", {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}, 8 },
};

const size_t magic_numbers_count =
    sizeof(magic_numbers) / sizeof(magic_numbers[0]);

int check_type(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return -1;

    unsigned char buffer[16];
    size_t read_bytes = fread(buffer, 1, sizeof(buffer), f);
    fclose(f);

    if (read_bytes == 0) return -2;

    for (size_t i = 0; i < magic_numbers_count; i++) {

        if (magic_numbers[i].length > read_bytes)
            continue;

        int match = 1;

        for (size_t j = 0; j < magic_numbers[i].length; j++) {
            if (buffer[j] != magic_numbers[i].magic[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("%s\n", magic_numbers[i].description);
            return (int)i;
        }
    }

    printf("Тип файла не распознан\n");
    return -3;
}
