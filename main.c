#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "parsing_header.h"
#include "section_counting.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file> [options]\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int flag_sections = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-sections") == 0) {
            flag_sections = 1;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    uint8_t *data = NULL;
    size_t size = 0;

    if (readfile(filename, &data, &size) != 0) {
        printf("Ошибка при чтении файла %s\n", filename);
        return 1;
    }

    parse(filename, data, size);

    if (flag_sections) {
        analyze_sections(data, size);
    }

    free(data);
    return 0;
}
