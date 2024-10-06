#include "temp_function.h"
#include <stdlib.h>

int open_file(WINDOW *name, FILE **fptr, char *name_file, int position)
{
    if ((*fptr = fopen(name_file, "r")) == NULL)
    {
        perror("Error opening file");
        wbkgd(name, COLOR_PAIR(9));
        wmove(name, position, 15);
        wprintw(name, "!!!      ATTENTION     !!!");
        wmove(name, position + 1, 15);
        wprintw(name, "!!!    %s    !!!", name_file);
        wmove(name, position + 2, 15);
        wprintw(name, "!!! ERROR OPENING FILE !!!"); // файл с данными не найден
        wrefresh(name);
        return 1;
    }
    return 0;
}

// Читаем файл c данными по стали
int read_data_file_steel(FILE **fptr, steel info[])
{
    unsigned int steel_name, r_yn, r_un, r_y, r_u;
    double thickness_1, thickness_2;
    int count = 0;
    while (fscanf(*fptr, "%d;%lf;%lf;%d;%d;%d;%d", &steel_name, &thickness_1, &thickness_2,
                  &r_yn, &r_un, &r_y, &r_u) > 0)
    {
        add_record_steel(info, count, steel_name, thickness_1, thickness_2, r_yn, r_un, r_y, r_u);
        count++;
    }
    return count;
}

// Читаем файл c данными по расч. сопротивлению сминаемых элементов
int read_data_file_steel_elem(FILE **fptr_st_el, steel_elem info_st_el[])
{
    unsigned int r_un, r_bp_a, r_bp_b;
    int count = 0;
    while (fscanf(*fptr_st_el, "%d;%d;%d", &r_un, &r_bp_a, &r_bp_b) > 0)
    {
        add_record_steel_elem(info_st_el, count, r_un, r_bp_a, r_bp_b);
        count++;
    }
    return count;
}

// Читаем файл c данными по болтам
int read_data_file_bolt(FILE **fptr, bolt info[])
{
    double class;
    unsigned int r_bun, r_byn, r_bs, r_bt;
    int count = 0;
    while (fscanf(*fptr, "%lf;%d;%d;%d;%d", &class, &r_bun, &r_byn,
                  &r_bs, &r_bt) > 0)
    {
        add_record_bolt(info, count, class, r_bun, r_byn, r_bs, r_bt);
        count++;
    }
    return count;
}

// Добавляем запись прочностных характеристик стали
void add_record_steel(steel info[], int number, unsigned int steel_name, double thickness_1, double thickness_2,
                      unsigned int r_yn, unsigned int r_un, unsigned int r_y, unsigned int r_u)
{
    info[number].steel_name = steel_name;
    info[number].thickness_1 = thickness_1;
    info[number].thickness_2 = thickness_2;
    info[number].r_yn = r_yn;
    info[number].r_un = r_un;
    info[number].r_y = r_y;
    info[number].r_u = r_u;
}

// Добавляем запись прочностных характеристик сминаемых элементов
void add_record_steel_elem(steel_elem info[], int number, unsigned int r_un, unsigned int r_bp_a, unsigned int r_bp_b)
{
    info[number].r_un = r_un;
    info[number].r_bp_a = r_bp_a;
    info[number].r_bp_b = r_bp_b;
}

// Добавляем запись прочностных характеристик болтов
void add_record_bolt(bolt info[], int number, double class, unsigned int r_bun, unsigned int r_byn,
                     unsigned int r_bs, unsigned int r_bt)
{
    info[number].class = class;
    info[number].r_bun = r_bun;
    info[number].r_byn = r_byn;
    info[number].r_bs = r_bs;
    info[number].r_bt = r_bt;
}

void data_entry_dialog(WINDOW *sub1, WINDOW *a, WINDOW *b)
{
    int number_slices;
    char info_bolt_diam[3];
    char info_number_slices[2];
    char info_thick_first_part[3];
    char info_thick_second_part[3];
    char ch;
    /* Пункты входных данных */
    wmove(sub1, 1, 7);
    waddstr(sub1, "Initial data:");
    for (int i = 2; i <= 6; i++)
    {
        wmove(sub1, i, 1);
        waddch(sub1, ACS_LANTERN);
    }
    wrefresh(sub1);

    /* Ввод диаметра болта */
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(3));
        wmove(a, 0, 2);
        waddstr(a, "1.Enter bolt diameter (mm): ");
        wgetnstr(a, info_bolt_diam, 2);
        package_info[0] = atoi(info_bolt_diam);
        wmove(a, 1, 4);
        wprintw(a, "Bolt diameter is %d mm. If the information is correct then press 'y', "
                   "if incorrect press 'n' ", package_info[0]);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода диаметра болта
    wmove(sub1, 2, 3);
    wprintw(sub1, "bolt diameter is %d mm", package_info[0]);
    wmove(sub1, 2, 1);
    waddch(sub1, ACS_DIAMOND);
    wmove(sub1, 3, 3);
    wprintw(sub1, "strength class  is 8.8", package_info[0]);
    wmove(sub1, 3, 1);
    waddch(sub1, ACS_DIAMOND);
    wrefresh(sub1);

    /* Ввод количества расчетных срезов одного болта */
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(4));
        wmove(a, 0, 2);
        waddstr(a, "2.Enter number of slices: ");
        wgetnstr(a, info_number_slices, 1);
        number_slices = atoi(info_number_slices);
        wmove(a, 1, 4);
        wprintw(a, "Number of slices is %d mm. If the information is correct then press 'y', "
                   "if incorrect press 'n' ", number_slices);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод количества расчетных срезов одного болта
    wmove(sub1, 4, 3);
    wprintw(sub1, "number of slices  is %d", number_slices);
    wmove(sub1, 4, 1);
    waddch(sub1, ACS_DIAMOND);
    // Рисуем эскиз болта
    block_bolt(b, number_slices);
    // Рисуем шайбы
    block_washer(b, 5);
    block_washer(b, 15);
    wrefresh(sub1);

    if (number_slices == 1) // если один расчетный срез
    {
        char thick_first_1[47] = "3.Enter the thickness of the first part (mm): ";
        char thick_first_2[108] = "Thickness of the first part is %d mm. If the information "
                                  "is correct then press 'y', if incorrect press 'n' ";
        char thick_first_3[23] = "first part    is %d mm";
        char thick_second_1[48] = "4.Enter the thickness of the second part (mm): ";
        char thick_second_2[109] = "Thickness of the second part is %d mm. If the information "
                                   "is correct then press 'y', if incorrect press 'n' ";

        /* Ввод толщины первой сминаемой в одном направлении детали */
        enter_thick_info(a, 5, 2, info_thick_first_part, ch,
                         thick_first_1, thick_first_2);

        // Вывод результата ввода толщины первого элемента сминаемого в одном направлении
        wmove(sub1, 5, 3);
        wprintw(sub1, thick_first_3, package_info[2]);
        wmove(sub1, 5, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 5, 27);
        waddch(sub1, ACS_LARROW);
        wrefresh(sub1);

        /* Ввод толщины второй сминаемой в другом направлении детали */
        enter_thick_info(a, 6, 3, info_thick_second_part, ch,
                         thick_second_1, thick_second_2);

        // Вывод результата ввода толщины второго элемента сминаемого в другом направлении
        wmove(sub1, 6, 3);
        wprintw(sub1, "second part   is %d mm", package_info[3]);
        wmove(sub1, 6, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 6, 27);
        waddch(sub1, ACS_RARROW);
        wrefresh(sub1);
    } else
    {
        char thick_first_1[69] = "3.Enter the total thickness of parts bearing in one direction (mm): ";
        char thick_first_2[113] = "Total thickness of parts bearing is %d mm. If the information "
                                  "is correct then press 'y', if incorrect press 'n' ";
        char thick_second_1[79] = "4.Enter the total thickness of the parts bearing in the other direction (mm): ";
        char thick_second_2[113] = "Total thickness of parts bearing is %d mm. If the information "
                                   "is correct then press 'y', if incorrect press 'n' ";

        /* Ввод суммы первых сминаемых в одном направлении деталей */
        enter_thick_info(a, 5, 2, info_thick_first_part, ch,
                         thick_first_1, thick_first_2);

        // Вывод результата ввода суммарной толщины
        wmove(sub1, 5, 3);
        wprintw(sub1, "total thickness  %d mm", package_info[2]);
        wmove(sub1, 5, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 5, 27);
        waddch(sub1, ACS_LARROW); // стрелка влево
        wrefresh(sub1);

        /* Ввод суммы вторых сминаемых в другом направлении деталей */
        enter_thick_info(a, 6, 3, info_thick_first_part, ch,
                         thick_second_1, thick_second_2);

        // Вывод результата ввода суммарной толщины
        wmove(sub1, 6, 3);
        wprintw(sub1, "total thickness  %d mm", package_info[3]);
        wmove(sub1, 6, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 6, 27);
        waddch(sub1, ACS_RARROW); // стрелка вправо
        wrefresh(sub1);
    }
}

// Ввод толщин соединяемых деталей
void
enter_thick_info(WINDOW *a, int color_pair, int num_arr, char *arr, char ch, const char *text_1, const char *text_2)
{
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(color_pair));
        wmove(a, 0, 2);
        waddstr(a, text_1);
        wgetnstr(a, arr, 2);
        package_info[num_arr] = atoi(arr);
        wmove(a, 1, 4);
        wprintw(a, text_2, package_info[num_arr]);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
}

/* Блок болта */
void block_bolt(WINDOW *b, int number_slices)
{
    // головка болта
    for (int j = 25; j <= 33; j++)
    {
        wmove(b, 4, j);
        waddch(b, ACS_BLOCK);
    }
    // тело болта
    for (int i = 5; i <= 15; i++)
    {
        wmove(b, i, 29);
        waddch(b, ACS_LANTERN);
    }
    // 1-я гайка
    for (int j = 25; j <= 33; j++)
    {
        wmove(b, 16, j);
        waddch(b, ACS_BLOCK);
    }
    // 2-я гайка
    for (int j = 25; j <= 33; j++)
    {
        wmove(b, 18, j);
        waddch(b, ACS_BLOCK);
    }
    // промежутки
    wmove(b, 17, 29);
    waddch(b, ACS_LANTERN);
    wmove(b, 19, 29);
    waddch(b, ACS_LANTERN);

    if (number_slices == 1)
    {
        first_part_block(b, 7);
        second_part_block(b, 11);
    } else
    {
        first_part_block(b, 6);
        second_part_block(b, 9);
        first_part_block(b, 13);
    }
    wrefresh(b);
}

/* Блок шайбы */
void block_washer(WINDOW *b, int position)
{
    for (int i = 24; i <= 28; i++)
    {
        wmove(b, position, i);
        waddch(b, ACS_HLINE);
    }
    for (int i = 30; i <= 34; i++)
    {
        wmove(b, position, i);
        waddch(b, ACS_HLINE);
    }
    wrefresh(b);
}

/* Блок первой детали */
void first_part_block(WINDOW *b, int position)
{
    for (int i = position; i <= position + 1; i++)
    {
        for (int j = 19; j <= 27; j++)
        {
            wmove(b, i, j);
            waddch(b, ACS_BOARD);
        }
    }
    for (int i = position; i <= position + 1; i++)
    {
        for (int j = 31; j <= 33; j++)
        {
            wmove(b, i, j);
            waddch(b, ACS_BOARD);
        }
    }
    for (int i = position; i <= position + 1; i++)
    {
        wmove(b, i, 17);
        waddch(b, ACS_LARROW); // стрелка влево
    }
}

/*  Блок второй детали  */
void second_part_block(WINDOW *b, int position)
{
    for (int i = position; i <= position + 2; i++)
    {
        for (int j = 25; j <= 27; j++)
        {
            wmove(b, i, j);
            waddch(b, ACS_CKBOARD);
        }
    }
    for (int i = position; i <= position + 2; i++)
    {
        for (int j = 31; j <= 40; j++)
        {
            wmove(b, i, j);
            waddch(b, ACS_CKBOARD);
        }
    }
    for (int i = position; i <= position + 2; i++)
    {
        wmove(b, i, 42);
        waddch(b, ACS_RARROW); // стрелка вправо
    }
}

/* Удаляем ранее введенные символы */
void delete_char(WINDOW *w, int row, int column, int count_ch)
{
    for (int i = 0; i < count_ch; i++)
    {
        wmove(w, row, column++);
        waddrawch(w, ' ');
        wrefresh(w);
    }
}

// Читаем из полученных данных Ru - расчетное сопротивление стали по временному сопротивлению
unsigned int design_steel_resistance_r_u(const steel *info, int count)
{
    unsigned int first_r_u = 0;
    unsigned int second_r_u = 0;
    unsigned int r_u;

    for (int i = 0; i < count; i++)
    {
        if (info[i].steel_name == 355 && package_info[2] >= (int) info[i].thickness_1
            && package_info[2] <= (int) info[i].thickness_2)
            first_r_u = info[i].r_u;
        if (info[i].steel_name == 355 && package_info[3] >= (int) info[i].thickness_1
            && package_info[3] <= (int) info[i].thickness_2)
            second_r_u = info[i].r_u;
    }
    r_u = (first_r_u < second_r_u) ? first_r_u : second_r_u;
    return r_u;
}

// Читаем из полученных данных Run - временное сопротивление стали
unsigned int design_steel_resistance_r_un(const steel *info, int count)
{
    unsigned int first_r_un = 0;
    unsigned int second_r_un = 0;
    unsigned int r_un;

    for (int i = 0; i < count; i++)
    {
        if (info[i].steel_name == 355 && package_info[2] >= (int) info[i].thickness_1
            && package_info[2] <= (int) info[i].thickness_2)
            first_r_un = info[i].r_un;
        if (info[i].steel_name == 355 && package_info[3] >= (int) info[i].thickness_1
            && package_info[3] <= (int) info[i].thickness_2)
            second_r_un = info[i].r_un;
    }
    r_un = (first_r_un < second_r_un) ? first_r_un : second_r_un;
    return r_un;
}

// Читаем из полученных данных Rbp - расчетное сопротивление смятию одноболтового соединения
unsigned int design_steel_resistance_r_bp(const steel_elem *info_st_el, int count, unsigned int r_un)
{
    unsigned int r_bp;
    for (int i = 0; i < count; i++)
    {
        if (info_st_el[i].r_un == r_un)
            r_bp = info_st_el[i].r_bp_b;
    }
    return r_bp;
}

// Читаем из полученных данных Rbs - расчетное сопротивление срезу
unsigned int design_bolt_resistance_r_bs(const bolt *info, int count)
{
    unsigned int r_bs;

    for (int i = 0; i < count; i++)
    {
        if (info[i].class == 8.8)
            r_bs = info[i].r_bs;
    }
    return r_bs;
}

// Читаем из полученных данных Rbt - расчетное сопротивление растяжению
unsigned int design_bolt_resistance_r_bt(const bolt *info, int count)
{
    unsigned int r_bt;

    for (int i = 0; i < count; i++)
    {
        if (info[i].class == 8.8)
            r_bt = info[i].r_bt;
    }
    return r_bt;
}

// Рисуем таблицу
void draw_table(WINDOW *sub1, int num)
{
    // 1-я горизонтальная линия
    wmove(sub1, num, 1);
    waddch(sub1, ACS_ULCORNER); // верхний левый угол
    wmove(sub1, num, 56);
    waddch(sub1, ACS_URCORNER); // верхний правый угол
    wmove(sub1, num, 14);
    waddch(sub1, ACS_TTEE);     // начало 1-ой разделит. линии
    wmove(sub1, num, 28);
    waddch(sub1, ACS_TTEE);     // начало 2-ой разделит. линии
    wmove(sub1, num, 42);
    waddch(sub1, ACS_TTEE);     // начало 3-ей разделит. линии
    for (int i = 2; i < 14; i++)
    {
        wmove(sub1, num, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 15; i < 28; i++)
    {
        wmove(sub1, num, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 29; i < 42; i++)
    {
        wmove(sub1, num, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 43; i < 56; i++)
    {
        wmove(sub1, num, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }

    // 2-я горизонтальная линия
    wmove(sub1, num + 2, 1);
    waddch(sub1, ACS_LTEE); // левый разделитель
    wmove(sub1, num + 2, 56);
    waddch(sub1, ACS_RTEE); // правый разделитель
    wmove(sub1, num + 2, 14);
    waddch(sub1, ACS_PLUS); // первый крест
    wmove(sub1, num + 2, 28);
    waddch(sub1, ACS_PLUS); // второй крест
    wmove(sub1, num + 2, 42);
    waddch(sub1, ACS_PLUS); // третий крест
    for (int i = 2; i < 14; i++)
    {
        wmove(sub1, num + 2, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 15; i < 28; i++)
    {
        wmove(sub1, num + 2, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 29; i < 42; i++)
    {
        wmove(sub1, num + 2, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 43; i < 56; i++)
    {
        wmove(sub1, num + 2, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }

    // 3-я горизонтальная линия
    wmove(sub1, num + 4, 1);
    waddch(sub1, ACS_LLCORNER); // левый разделитель
    wmove(sub1, num + 4, 56);
    waddch(sub1, ACS_LRCORNER); // правый разделитель
    wmove(sub1, num + 4, 14);
    waddch(sub1, ACS_BTEE); // первый крест
    wmove(sub1, num + 4, 28);
    waddch(sub1, ACS_BTEE); // второй крест
    wmove(sub1, num + 4, 42);
    waddch(sub1, ACS_BTEE); // третий крест
    for (int i = 2; i < 14; i++)
    {
        wmove(sub1, num + 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 15; i < 28; i++)
    {
        wmove(sub1, num + 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 29; i < 42; i++)
    {
        wmove(sub1, num + 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
    for (int i = 43; i < 56; i++)
    {
        wmove(sub1, num + 4, i);
        waddch(sub1, ACS_HLINE); // горизонтальная линия
    }
}

// Заполняем таблицу характеристиками стали
void data_draw_table_steel(WINDOW *sub1, unsigned int r_u, unsigned int r_bp, unsigned int r_un, int num)
{
    /* Название таблицы */
    wmove(sub1, num, 6);
    wprintw(sub1, "Table 1 - Strength characteristics of steel");
    /* Заполнение 1 столбца */
    wmove(sub1, num + 2, 3);
    wprintw(sub1, "Data  name");
    wmove(sub1, num + 4, 6);
    wprintw(sub1, "C355");
    /* Заполнение Ru */
    wmove(sub1, num + 2, 20);
    wprintw(sub1, "Ru");
    wmove(sub1, num + 4, 17);
    wprintw(sub1, "%u N/mm^2", r_u);
    /* Заполнение Rbp */
    wmove(sub1, num + 2, 34);
    wprintw(sub1, "Rbp");
    wmove(sub1, num + 4, 31);
    wprintw(sub1, "%u N/mm^2", r_bp);
    /* Заполнение Run */
    wmove(sub1, num + 2, 48);
    wprintw(sub1, "Run");
    wmove(sub1, num + 4, 45);
    wprintw(sub1, "%u N/mm^2", r_un);
}

// Заполняем таблицу характеристиками болта
void data_draw_table_bolt(WINDOW *sub1, unsigned int r_bs, unsigned int r_bt, int num)
{
    wmove(sub1, 15, 13);
    wprintw(sub1, "Table 2 - Bolt characteristics");
    /* Заполнение 1 столбца */
    wmove(sub1, num + 2, 6);
    wprintw(sub1, "Ab");
    //wmove(sub1, num + 4, 6);
    //wprintw(sub1, "C355");
    /* Заполнение Ru */
    wmove(sub1, num + 2, 20);
    wprintw(sub1, "Abn");
    //wmove(sub1, num + 4, 17);
    //wprintw(sub1, "%u N/mm^2", r_u);
    /* Заполнение Rbp */
    wmove(sub1, num + 2, 34);
    wprintw(sub1, "Rbs");
    wmove(sub1, num + 4, 31);
    wprintw(sub1, "%u N/mm^2", r_bs);
    /* Заполнение Run */
    wmove(sub1, num + 2, 48);
    wprintw(sub1, "Rbt");
    wmove(sub1, num + 4, 45);
    wprintw(sub1, "%u N/mm^2", r_bt);
}