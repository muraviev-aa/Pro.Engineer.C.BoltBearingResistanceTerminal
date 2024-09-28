#include "temp_function.h"
#include <stdlib.h>

int open_file(WINDOW *name, FILE **fptr, char *name_file)
{
    if ((*fptr = fopen(name_file, "r")) == NULL)
    {
        perror("Error opening file");
        wbkgd(name, COLOR_PAIR(9));
        wmove(name, 10, 15);
        wprintw(name, "!!!      ATTENTION     !!!");
        wmove(name, 11, 15);
        wprintw(name, "!!! ERROR OPENING FILE !!!"); // файл с данными не найден
        wrefresh(name);
        return 1;
    }
    return 0;
}

int read_data_file(FILE **fptr, steel info[])
{
    unsigned int steel_name, r_yn, r_un, r_y, r_u;
    double thickness_1, thickness_2;
    int count = 0;
    while (fscanf(*fptr, "%d;%lf;%lf;%d;%d;%d;%d", &steel_name, &thickness_1, &thickness_2,
                  &r_yn, &r_un, &r_y, &r_u) > 0)
    {
        add_record(info, count, steel_name, thickness_1, thickness_2, r_yn, r_un, r_y, r_u);
        count++;
    }
    return count;
}

void add_record(steel info[], int number, unsigned int steel_name, double thickness_1, double thickness_2,
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
    waddstr(sub1, "Initial data");
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
        /* Ввод толщины первой сминаемой в одном направлении детали */
        do
        {
            wclear(a);
            wbkgd(a, COLOR_PAIR(5));
            wmove(a, 0, 2);
            waddstr(a, "3.Enter the thickness of the first part (mm): ");
            wgetnstr(a, info_thick_first_part, 2);
            package_info[2] = atoi(info_thick_first_part);
            wmove(a, 1, 4);
            wprintw(a, "Thickness of the first part is %d mm. If the information is correct then press 'y', "
                       "if incorrect press 'n' ", package_info[2]);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода толщины первого элемента
        wmove(sub1, 5, 3);
        wprintw(sub1, "first part    is %d mm", package_info[2]);
        wmove(sub1, 5, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 5, 27);
        waddch(sub1, ACS_LARROW); // стрелка влево
        wrefresh(sub1);

        /* Ввод толщины второй сминаемой в одном направлении детали */
        do
        {
            wclear(a);
            wbkgd(a, COLOR_PAIR(6));
            wmove(a, 0, 2);
            waddstr(a, "4.Enter the thickness of the second part (mm): ");
            wgetnstr(a, info_thick_second_part, 2);
            package_info[3] = atoi(info_thick_second_part);
            wmove(a, 1, 4);
            wprintw(a, "Thickness of the second part is %d mm. If the information is correct then press 'y', "
                       "if incorrect press 'n' ", package_info[3]);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода толщины второго элемента
        wmove(sub1, 6, 3);
        wprintw(sub1, "second part   is %d mm", package_info[3]);
        wmove(sub1, 6, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 6, 27);
        waddch(sub1, ACS_RARROW); // стрелка вправо
        wrefresh(sub1);
    } else
    {
        /* Ввод суммы первых сминаемых в одном направлении деталей */
        do
        {
            wclear(a);
            wbkgd(a, COLOR_PAIR(5));
            wmove(a, 0, 2);
            waddstr(a, "3.Enter the total thickness of parts bearing in one direction (mm): ");
            wgetnstr(a, info_thick_first_part, 2);
            package_info[2] = atoi(info_thick_first_part);
            wmove(a, 1, 4);
            wprintw(a, "Total thickness of parts bearing is %d mm. If the information "
                       "is correct then press 'y', if incorrect press 'n' ", package_info[2]);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода суммарной толщины
        wmove(sub1, 5, 3);
        wprintw(sub1, "total thickness  %d mm", package_info[2]);
        wmove(sub1, 5, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 5, 27);
        waddch(sub1, ACS_LARROW); // стрелка влево
        wrefresh(sub1);

        /* Ввод суммы вторых сминаемых в другом направлении деталей */
        do
        {
            wclear(a);
            wbkgd(a, COLOR_PAIR(6));
            wmove(a, 0, 2);
            waddstr(a, "4.Enter the total thickness of the parts bearing in the other direction (mm): ");
            wgetnstr(a, info_thick_second_part, 2);
            package_info[3] = atoi(info_thick_second_part);
            wmove(a, 1, 4);
            wprintw(a, "Total thickness of parts bearing is %d mm. If the information is correct then press 'y', "
                       "if incorrect press 'n' ", package_info[3]);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
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

// Читаем из полученных данных расчетное сопротивление стали
int design_steel_resistance(WINDOW *sub1, const steel *info, int count)
{
    int first_r_u = 0;
    int second_r_u = 0;
    int r_u;

    for (int i = 0; i < count; i++)
    {
        if (info[i].steel_name == 355 && package_info[2] >= (int) info[i].thickness_1
            && package_info[2] <= (int) info[i].thickness_2)
        {
            first_r_u = info[i].r_u;
            wmove(sub1, 8, 15);
            wprintw(sub1, "first = %d N/mm^2", first_r_u);
        }
        if (info[i].steel_name == 355 && package_info[3] >= (int) info[i].thickness_1
            && package_info[3] <= (int) info[i].thickness_2)
        {
            second_r_u = info[i].r_u;
            wmove(sub1, 9, 15);
            wprintw(sub1, "second = %d N/mm^2", second_r_u);
        }
    }
    r_u = (first_r_u < second_r_u) ? first_r_u : second_r_u;
    wmove(sub1, 10, 15);
    wprintw(sub1, "Ru = %d N/mm^2", r_u);
    return r_u;
}