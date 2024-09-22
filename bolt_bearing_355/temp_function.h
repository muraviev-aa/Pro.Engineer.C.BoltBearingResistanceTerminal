#ifndef BOLT_BEARING_355_TEMP_FUNCTION_H
#define BOLT_BEARING_355_TEMP_FUNCTION_H

#include <curses.h>

// Вводим исходные данные
void data_entry_dialog(WINDOW *sub1, WINDOW *a, WINDOW *b);

// Удаляем ранее введенные символы
void delete_char(WINDOW *w, int row, int column, int count_ch);

// Рисуем эскиз болта
void block_bolt(WINDOW *b, int number_slices);

#endif //BOLT_BEARING_355_TEMP_FUNCTION_H
