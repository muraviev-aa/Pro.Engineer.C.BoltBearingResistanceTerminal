#include "temp_function.h"
#include <stdlib.h>

void data_entry_dialog(WINDOW *sub1, WINDOW *a)
{
    int bolt_diam;
    int thick_first_part;
    int thick_second_part;
    char info_bolt_diam[3];
    char info_thick_first_part[3];
    char info_thick_second_part[3];
    char ch;
    wmove(sub1, 1, 1);
    waddch(sub1, ACS_LANTERN);
    wmove(sub1, 2, 1);
    waddch(sub1, ACS_LANTERN);
    wmove(sub1, 3, 1);
    waddch(sub1, ACS_LANTERN);
    wrefresh(sub1);
    // Ввод диаметра болта
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(3));
        wmove(a, 0, 2);
        waddstr(a, "1.Enter bolt diameter (mm): ");
        wgetnstr(a, info_bolt_diam, 2);
        bolt_diam = atoi(info_bolt_diam);
        wmove(a, 1, 4);
        wprintw(a,
                "Bolt diameter is %d mm. If the information is correct then press 'y', if incorrect press 'n' ",
                bolt_diam);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода диаметра болта
    wmove(sub1, 1, 3);
    wprintw(sub1, "Data: bolt diameter is %d mm", bolt_diam);
    wmove(sub1, 1, 1);
    waddch(sub1, ACS_DIAMOND);
    wrefresh(sub1);
    // Ввод толщины первой сминаемой в одном направлении детали
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(4));
        wmove(a, 0, 2);
        waddstr(a, "2.Enter the thickness of the first part (mm): ");
        wgetnstr(a, info_thick_first_part, 2);
        thick_first_part = atoi(info_thick_first_part);
        wmove(a, 1, 4);
        wprintw(a,
                "Thickness of the first part is %d mm. If the information is correct then press 'y', if incorrect press 'n' ",
                thick_first_part);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода толщины первого элемента
    wmove(sub1, 2, 9);
    wprintw(sub1, "first part is %d mm", thick_first_part);
    wmove(sub1, 2, 1);
    waddch(sub1, ACS_DIAMOND);
    wrefresh(sub1);
    // Ввод толщины второй сминаемой в одном направлении детали
    do
    {
        wclear(a);
        wbkgd(a, COLOR_PAIR(5));
        wmove(a, 0, 2);
        waddstr(a, "2.Enter the thickness of the second part (mm): ");
        wgetnstr(a, info_thick_second_part, 2);
        thick_second_part = atoi(info_thick_second_part);
        wmove(a, 1, 4);
        wprintw(a,
                "Thickness of the second part is %d mm. If the information is correct then press 'y', if incorrect press 'n' ",
                thick_second_part);
        ch = (char) wgetch(a);
        if (ch == 'n')
            delete_char(a, 1, 1, 95);
    } while (ch != 'y');
    // Вывод результата ввода толщины второго элемента
    wmove(sub1, 3, 9);
    wprintw(sub1, "second part is %d mm", thick_second_part);
    wmove(sub1, 3, 1);
    waddch(sub1, ACS_DIAMOND);
    wrefresh(sub1);
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