#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "file.h"
#include "parsing_header.h"

int main() {
    uint8_t *data;
    size_t size;

    if (readfile("test.exe", &data, &size) != 0){
          printf("Ошибка при чтении файла\n");
        return 1;
    
    }

       

    parse("test.exe", data, size); // передаем указатель и размер без &

    free(data);
    return 0;
}
