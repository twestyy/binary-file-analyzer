#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

// Чтение файла в буфер
// filename - путь к файлу
// data - указатель на буфер (выделяется внутри функции)
// size - размер файла
// Возвращает 0 при успехе, отрицательные числа при ошибках
int readfile(const char *filename, uint8_t **data, size_t *size);

// Проверка, начинается ли файл с сигнатуры MZ
// data - буфер с данными файла
// size - размер буфера
// Возвращает 1 если MZ, -1 если нет или размер < 2
int check_mz(uint8_t *data, size_t size);

#endif // FILE_H
