#ifndef BOLT_BEARING_355_TEMP_FUNCTION_H
#define BOLT_BEARING_355_TEMP_FUNCTION_H

#include <curses.h>
#include <stdlib.h>

typedef struct
{
    unsigned int steel_name;       // марка стали
    double thickness_1;            // толщина листа
    double thickness_2;            // толщина листа
    unsigned int r_yn;             // Ryn
    unsigned int r_un;             // Run
    unsigned int r_y;              // Ry
    unsigned int r_u;              // Ru
} steel;

// Открываем файл
int open_file(WINDOW *name, FILE **fptr, char *name_file);

// Вводим исходные данные
void data_entry_dialog(WINDOW *sub1, WINDOW *a, WINDOW *b);

// Удаляем ранее введенные символы
void delete_char(WINDOW *w, int row, int column, int count_ch);

// Блок болта
void block_bolt(WINDOW *b, int number_slices);

// Блок шайбы
void block_washer(WINDOW *b, int position);

// Блок первой детали
void first_part_block(WINDOW *b, int position);

// Блок второй детали
void second_part_block(WINDOW *b, int position);

#endif //BOLT_BEARING_355_TEMP_FUNCTION_H
