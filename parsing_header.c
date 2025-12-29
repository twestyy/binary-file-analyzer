#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "file.h"
#include "parsing_header.h"

int parse(const char *filename, uint8_t *data, size_t size) {
    if (check_mz(data, size) != 1) {
        printf("Не MZ файл\n");
        return -1;
    }

    uint32_t pe_offset = *(uint32_t *)(data + 0x3C);
    if (pe_offset == 0 || pe_offset >= size) {
        return -2;
    }

    if (data[pe_offset] != 'P' || data[pe_offset+1] != 'E' || data[pe_offset+2] != 0 || data[pe_offset+3] != 0) {
        return -3;
    }

    uint8_t *fh = data + pe_offset + 4;

    uint16_t machine = fh[0] | (fh[1] << 8);
    uint16_t numberOfSections = fh[2] | (fh[3] << 8);
    uint32_t timeDateStamp = fh[4] | (fh[5] << 8) | (fh[6] << 16) | (fh[7] << 24);
    uint16_t sizeOfOptionalHeader = fh[16] | (fh[17] << 8);
    uint16_t characteristics = fh[18] | (fh[19] << 8);

    uint8_t *oh = fh + 20;  
    uint16_t magic = oh[0] | (oh[1] << 8);

    uint32_t entry_rva = oh[16] | (oh[17] << 8) | (oh[18] << 16) | (oh[19] << 24);

    uint64_t image_base;
    if (magic == 0x10B) {  
        image_base = oh[28] | (oh[29] << 8) | (oh[30] << 16) | (oh[31] << 24);
    } else {  
        image_base =
            (uint64_t)oh[24] |
            ((uint64_t)oh[25] << 8) |
            ((uint64_t)oh[26] << 16) |
            ((uint64_t)oh[27] << 24) |
            ((uint64_t)oh[28] << 32) |
            ((uint64_t)oh[29] << 40) |
            ((uint64_t)oh[30] << 48) |
            ((uint64_t)oh[31] << 56);
    }

    uint32_t section_alignment = oh[32] | (oh[33] << 8) | (oh[34] << 16) | (oh[35] << 24);
    uint32_t file_alignment = oh[36] | (oh[37] << 8) | (oh[38] << 16) | (oh[39] << 24);
    // const char* decode_machine(uint16_t machine);

    printf("Machine: 0x%04X (", machine);
    switch (machine) {
        case 0x014c:
            printf("x86 (Intel 386)");
            break;
        case 0x8664:
            printf("x64 (AMD64)");
            break;
        case 0x01c4:
            printf("ARM");
            break;
        case 0xAA64:
            printf("ARM64");
            break;
        case 0x0200:
            printf("IA-64 (Itanium)");
            break;
        default:
            printf("Unknown architecture");
            break;
    }
    printf(")\n");


    printf("Number of sections: %u\n", numberOfSections);
    // printf("TimeDateStamp: %u\n", timeDateStamp);s
    // printf("Size of Optional Header: %u\n", sizeOfOptionalHeader);
    // printf("Characteristics: 0x%X\n", characteristics);
    // printf("=== OPTIONAL HEADER ===\n");
    printf("Magic: 0x%X ", magic);
    if (magic == 0x10B) printf("(PE32 / x86)\n");
    else if (magic == 0x20B) printf("(PE32+ / x64)\n");
    else printf("(UNKNOWN)\n");
    printf("AddressOfEntryPoint (RVA): 0x%X\n", entry_rva);
    // printf("ImageBase: 0x%llX\n", (unsigned long long)image_base);
    // printf("SectionAlignment: 0x%X\n", section_alignment);
    // printf("FileAlignment: 0x%X\n", file_alignment);

    return 0;
}



