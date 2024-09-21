#include <curses.h>
#include "temp_function.h"
#include <stdio.h>

#define USER 100
#define USER1 101
#define USER2 102
#define USER3 103

int main(void)
{
    WINDOW *sub1, *a;
    int maxx, maxy;

    initscr();

    start_color();
    if (!can_change_color())
        addstr("This probably won't work...\n");
    init_color(USER, 760, 960, 70);          // создаем салатовый цвет
    init_color(USER1, 1000, 1000, 0);        // создаем ядовито желтый цвет
    init_color(USER2, 0, 890, 420);          // создаем зеленый цвет
    init_color(USER3, 840, 970, 690);        // создаем  салатово-желтый цвет

    // Создание цветовых пар
    init_pair(1, COLOR_BLUE, COLOR_WHITE);   // окно sub1 - базовый белый
    init_pair(2, COLOR_WHITE, COLOR_BLUE);   // окно a - базовый синий
    init_pair(3, COLOR_BLACK, USER);         // базовый салатовый
    init_pair(4, COLOR_BLACK, USER1);        // базовый ядовито желтый цвет
    init_pair(5, COLOR_BLACK, USER2);        // базовый зеленый цвет
    init_pair(6, COLOR_BLACK, USER3);        // базовый  салатово-желтый цвет
    slk_color(0);

    // Базовое окно терминала
    bkgd(COLOR_PAIR(1));
    refresh();

    // Определяем размеры и положение доп. окон
    getmaxyx(stdscr, maxy, maxx);

    // Создаем доп. окна
    sub1 = subwin(stdscr, maxy - 4, maxx - 2, 3, 1); // окно таблицы
    a = subwin(stdscr, LINES - 28, COLS - 2, 1, 1);  // диалоговое окно

    if (sub1 == NULL || a == NULL)
    {
        endwin();
        puts("Unable to create subwindow");
        return (1);
    }
    wbkgd(a, COLOR_PAIR(2));

    /* здесь будет основной код */
    // 1. Вводим исходные данные
    data_entry_dialog(sub1, a);

    wrefresh(sub1);
    wrefresh(a);
    refresh();

    getch();
    endwin();
    return 0;
}
