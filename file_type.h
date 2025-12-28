#ifndef FILE_TYPE_H
#define FILE_TYPE_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    const char *description;
    unsigned char magic[16];
    size_t length;
} MagicNumber;

extern MagicNumber magic_numbers[];
extern const size_t magic_numbers_count;

int check_type(const char *filename);

#endif
