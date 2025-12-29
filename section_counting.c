#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "section_counting.h"


#define IMAGE_SCN_CNT_CODE               0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA   0x00000040
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA 0x00000080

#define IMAGE_SCN_MEM_EXECUTE            0x20000000
#define IMAGE_SCN_MEM_READ               0x40000000
#define IMAGE_SCN_MEM_WRITE              0x80000000




#pragma pack(push, 1)
typedef struct {
    uint8_t  Name[8];
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
} IMAGE_SECTION_HEADER;
#pragma pack(pop)



int analyze_sections(uint8_t *data,size_t size){
    uint32_t pe_offset = *(uint32_t *)(data + 0x3C);
    uint16_t num_sections = *(uint16_t*)(data + pe_offset + 6);
    uint16_t opt_header_size = *(uint16_t*)(data + pe_offset + 20);



    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(data + pe_offset + 24 + opt_header_size);


    for(int i = 0; i < num_sections;i++){
         char name[9] = {0};
        memcpy(name, sections[i].Name, 8);

        printf("Section: %s\n", name);

        uint32_t c = sections[i].Characteristics;

        if (c & IMAGE_SCN_CNT_CODE)
            printf("  Type: CODE\n");

        if (c & IMAGE_SCN_CNT_INITIALIZED_DATA)
            printf("  Type: INIT DATA\n");

        if (c & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
            printf("  Type: BSS\n");

        if ((c & IMAGE_SCN_MEM_EXECUTE) && (c & IMAGE_SCN_MEM_WRITE))
            printf("  ⚠ RXW section (suspicious)\n");

        printf("  Flags: %08X\n\n", c);
    }

}


