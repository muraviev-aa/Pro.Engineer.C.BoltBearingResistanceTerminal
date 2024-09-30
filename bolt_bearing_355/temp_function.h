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

/* Массив под входные данные
 * package_info[0] - диаметр болта
 * package_info[1] - количество срезов
 * package_info[2] - толщина (сумма толщин) детали, сминаемой в одну сторону
 * package_info[3] - толщина (сумма толщин) детали, сминаемой в другую сторону
*/
extern int package_info[4];

// Открываем файл
int open_file(WINDOW *name, FILE **fptr, char *name_file);

// Читаем файл
int read_data_file(FILE **fptr, steel info[]);

// Добавляем запись
void add_record(steel info[], int number, unsigned int steel_name, double thickness_1, double thickness_2,
                unsigned int r_yn, unsigned int r_un, unsigned int r_y, unsigned int r_u);

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

// Читаем из полученных данных расчетное сопротивление стали
int design_steel_resistance(WINDOW *sub1, const steel *info, int count);

// Ввод толщин соединяемых деталей
void enter_thick_info(WINDOW *a, int color_pair, int num_arr, char *arr, char ch,
                      const char *text_1, const char *text_2);

// Рисуем таблицу
void draw_table(WINDOW *sub1);

#endif //BOLT_BEARING_355_TEMP_FUNCTION_H
