#ifndef BOLT_BEARING_355_TEMP_FUNCTION_H
#define BOLT_BEARING_355_TEMP_FUNCTION_H

#include <curses.h>
#include <stdlib.h>
#include <math.h>

#define STEEL_NAME 355

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

typedef struct
{
    unsigned int r_un;             // Run
    unsigned int r_bp_a;           // Rbp класс точности А
    unsigned int r_bp_b;           // Rbp класс точности B
} steel_elem;

typedef struct
{
    double class;            // класс прочности болта
    unsigned int r_bun;      // Rbun
    unsigned int r_byn;      // Rbyn
    unsigned int r_bs;       // Rbs
    unsigned int r_bt;       // Rbt
} bolt;

typedef struct
{
    unsigned int d;    // d
    double a_b;        // Ab
    double a_bn;       // Abn
} bolt_area;

/* Массив под входные данные
 * package_info[0] - диаметр болта
 * package_info[1] - количество срезов
 * package_info[2] - толщина (сумма толщин) детали, сминаемой в одну сторону
 * package_info[3] - толщина (сумма толщин) детали, сминаемой в другую сторону
*/
extern int package_info[4];

// Открываем файл
int open_file(WINDOW *name, FILE **fptr, char *name_file, int position);

// Читаем файл c данными по стали
int read_data_file_steel(FILE **fptr, steel info[]);

// Читаем файл c данными по расч. сопротивлению сминаемых элементов
int read_data_file_steel_elem(FILE **fptr_st_el, steel_elem info_st_el[]);

// Читаем файл c данными по болтам
int read_data_file_bolt(FILE **fptr, bolt info[]);

// Читаем файл c данными по площадям болтов
int read_data_file_bolt_ar(FILE **fptr, bolt_area info[]);

// Добавляем запись площадей болтов
void add_record_bolt_ar(bolt_area info[], int number, unsigned int d, double a_b, double a_bn);

// Добавляем запись прочностных характеристик стали
void add_record_steel(steel info[], int number, unsigned int steel_name, double thickness_1, double thickness_2,
                      unsigned int r_yn, unsigned int r_un, unsigned int r_y, unsigned int r_u);

// Добавляем запись прочностных характеристик сминаемых элементов
void add_record_steel_elem(steel_elem info[], int number, unsigned int r_un, unsigned int r_bp_a,
                           unsigned int r_bp_b);

// Добавляем запись прочностных характеристик болтов
void add_record_bolt(bolt info[], int number, double class, unsigned int r_bun, unsigned int r_byn,
                     unsigned int r_bs, unsigned int r_bt);

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

// Читаем из полученных данных Ru - расчетное сопротивление стали по временному сопротивлению
unsigned int design_steel_resistance_r_u(const steel *info, int count);

// Читаем из полученных данных Run - временное сопротивление стали
unsigned int design_steel_resistance_r_un(const steel *info, int count);

// Читаем из полученных данных Rbp - расчетное сопротивление смятию одноболтового соединения
unsigned int design_steel_resistance_r_bp(const steel_elem *info_st_el, int count, unsigned int r_un);

// Читаем из полученных данных Rbs - расчетное сопротивление срезу
unsigned int design_bolt_resistance_r_bs(const bolt *info, int count);

// Читаем из полученных данных Rbt - расчетное сопротивление растяжению
unsigned int design_bolt_resistance_r_bt(const bolt *info, int count);

// Читаем из полученных данных Ab - площадь сечения болта брутто
double bolt_a_b(const bolt_area *info, int count);

// Читаем из полученных данных Abn - площадь сечения болта нетто
double bolt_a_bn(const bolt_area *info, int count);

// Ввод толщин соединяемых деталей
void enter_thick_info(WINDOW *a, int color_pair, int num_arr, char *arr, char ch,
                      const char *text_1, const char *text_2);

// Ввод силы по оси X
unsigned int enter_force_x(WINDOW *sub1, WINDOW *a, int color_pair);

// Ввод силы по оси Y
unsigned int enter_force_y(WINDOW *sub1, WINDOW *a, int color_pair);

// Ввод силы по оси Z
unsigned int enter_force_z(WINDOW *sub1, WINDOW *a, WINDOW *b, int color_pair);

// Ввод количества болтов в соединении
unsigned int enter_num_bolts(WINDOW *b, WINDOW *a, int color_pair);

// Рисуем таблицу
void draw_table(WINDOW *sub1, int num);

// Заполняем таблицу характеристиками стали
void data_draw_table_steel(WINDOW *sub1, unsigned int r_u, unsigned int r_bp, unsigned int r_un, int num);

// Заполняем таблицу характеристиками болта
void data_draw_table_bolt(WINDOW *sub1, unsigned int r_bs, unsigned int r_bt, double a_b, double a_bn, int num);

// Расчет на смятие / максимальное усилие на смятие
double calc_bearing_n_bp(unsigned int r_bp);

// Расчет на срез / максимальное усилие на срез
double calc_bearing_n_bs(unsigned int r_bs, double a_b);

// Расчет на растяжение / максимальное усилие на растяжение [кН]
double calc_tens_n_bt(unsigned int r_bt, double a_bn);

// Рисуем систему координат
void draw_coord_sys(WINDOW *b);

// Рисуем силы на системе координат
void draw_force_coord_sys(WINDOW *b, unsigned int force_x, unsigned int force_y, unsigned int force_z);

// Вывод результатов расчета_1
void output_results_1(WINDOW *sub1, double max_sher_result, double max_bear_result, double max_tens_result);

#endif //BOLT_BEARING_355_TEMP_FUNCTION_H
