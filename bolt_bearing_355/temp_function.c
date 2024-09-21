#include "temp_function.h"
#include <stdlib.h>

void data_entry_dialog(WINDOW *sub1, WINDOW *a)
{
    int bolt_diam;
    int number_slices;
    int thick_first_part;
    int thick_second_part;
    char info_bolt_diam[3];
    char info_number_slices[2];
    char info_thick_first_part[3];
    char info_thick_second_part[3];
    char ch;
    /* Пункты входных данных */
    wmove(sub1, 1, 7);
    waddstr(sub1, "Initial data");
    wmove(sub1, 2, 1);
    waddch(sub1, ACS_LANTERN);
    wmove(sub1, 3, 1);
    waddch(sub1, ACS_LANTERN);
    wmove(sub1, 4, 1);
    waddch(sub1, ACS_LANTERN);
    wmove(sub1, 5, 1);
    waddch(sub1, ACS_LANTERN);
    wmove(sub1, 6, 1);
    waddch(sub1, ACS_LANTERN);
    wrefresh(sub1);

    /* Ввод диаметра болта */
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(3));
        wmove(a, 0, 2);
        waddstr(a, "1.Enter bolt diameter (mm): ");
        wgetnstr(a, info_bolt_diam, 2);
        bolt_diam = atoi(info_bolt_diam);
        wmove(a, 1, 4);
        wprintw(a, "Bolt diameter is %d mm. If the information is correct then press 'y', "
                   "if incorrect press 'n' ", bolt_diam);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода диаметра болта
    wmove(sub1, 2, 3);
    wprintw(sub1, "bolt diameter is %d mm", bolt_diam);
    wmove(sub1, 2, 1);
    waddch(sub1, ACS_DIAMOND);
    wmove(sub1, 3, 3);
    wprintw(sub1, "strength class  is 8.8", bolt_diam);
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
            thick_first_part = atoi(info_thick_first_part);
            wmove(a, 1, 4);
            wprintw(a, "Thickness of the first part is %d mm. If the information is correct then press 'y', "
                       "if incorrect press 'n' ", thick_first_part);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода толщины первого элемента
        wmove(sub1, 5, 3);
        wprintw(sub1, "first part    is %d mm", thick_first_part);
        wmove(sub1, 5, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 5, 27);
        waddch(sub1, ACS_RARROW); // стрелка вправо
        wrefresh(sub1);

        /* Ввод толщины второй сминаемой в одном направлении детали */
        do
        {
            wclear(a);
            wbkgd(a, COLOR_PAIR(6));
            wmove(a, 0, 2);
            waddstr(a, "4.Enter the thickness of the second part (mm): ");
            wgetnstr(a, info_thick_second_part, 2);
            thick_second_part = atoi(info_thick_second_part);
            wmove(a, 1, 4);
            wprintw(a, "Thickness of the second part is %d mm. If the information is correct then press 'y', "
                       "if incorrect press 'n' ", thick_second_part);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода толщины второго элемента
        wmove(sub1, 6, 3);
        wprintw(sub1, "second part   is %d mm", thick_second_part);
        wmove(sub1, 6, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 6, 27);
        waddch(sub1, ACS_LARROW); // стрелка влево
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
            thick_first_part = atoi(info_thick_first_part);
            wmove(a, 1, 4);
            wprintw(a, "Total thickness of parts bearing is %d mm. If the information "
                       "is correct then press 'y', if incorrect press 'n' ", thick_first_part);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода суммарной толщины
        wmove(sub1, 5, 3);
        wprintw(sub1, "total thickness  %d mm", thick_first_part);
        wmove(sub1, 5, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 5, 27);
        waddch(sub1, ACS_RARROW); // стрелка вправо
        wrefresh(sub1);

        /* Ввод суммы вторых сминаемых в другом направлении деталей */
        do
        {
            wclear(a);
            wbkgd(a, COLOR_PAIR(6));
            wmove(a, 0, 2);
            waddstr(a, "4.Enter the total thickness of the parts bearing in the other direction (mm): ");
            wgetnstr(a, info_thick_second_part, 2);
            thick_second_part = atoi(info_thick_second_part);
            wmove(a, 1, 4);
            wprintw(a, "Total thickness of parts bearing is %d mm. If the information is correct then press 'y', "
                       "if incorrect press 'n' ", thick_second_part);
            ch = (char) wgetch(a);
            if (ch == 'n')
                delete_char(a, 1, 1, 95);
        } while (ch != 'y');
        // Вывод результата ввода суммарной толщины
        wmove(sub1, 6, 3);
        wprintw(sub1, "total thickness  %d mm", thick_second_part);
        wmove(sub1, 6, 1);
        waddch(sub1, ACS_DIAMOND);
        wmove(sub1, 6, 27);
        waddch(sub1, ACS_LARROW); // стрелка влево
        wrefresh(sub1);
    }
}

void delete_char(WINDOW *w, int row, int column, int count_ch)
{
    for (int i = 0; i < count_ch; i++)
    {
        wmove(w, row, column++);
        waddrawch(w, ' ');
        wrefresh(w);
    }
}