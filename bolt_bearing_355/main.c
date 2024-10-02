#include <curses.h>
#include "temp_function.h"
#include <stdio.h>

#define SIZE_STEEL 15      // число строк в файле tabl_B_3.csv
#define SIZE_BOLT 5        // число строк в файле tabl_G_5.csv
#define USER 100
#define USER1 101
#define USER2 102
#define USER3 103

// Массив под входные данные
int package_info[4];

int main(void)
{
    WINDOW *sub1, *a, *b;
    int maxx, maxy, halfx, halfy;
    steel *info_st = (steel *) malloc(SIZE_STEEL * sizeof(steel));
    bolt *info_blt = (bolt *) malloc(SIZE_BOLT * sizeof (bolt));
    if (!info_st || !info_blt)
        printf("Error while allocating memory!\n");
    FILE *fptr_st;
    FILE *fptr_blt;
    char file_name_st[] = "tabl_B_3.csv";
    char file_name_blt[] = "tabl_G_5.csv";
    int count_st;    // количество строк в файле tabl_B_3.csv
    int count_blt;   // количество строк в файле tabl_G_5.csv
    int r_u;
    int r_bs;

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
    init_pair(7, COLOR_WHITE, COLOR_BLUE);   // окно b - базовый синий
    slk_color(0);

    // Базовое окно терминала
    bkgd(COLOR_PAIR(1));
    refresh();

    // Определяем размеры и положение доп. окон
    getmaxyx(stdscr, maxy, maxx);
    halfx = maxx >> 1;
    halfy = maxy >> 1;

    // Создаем доп. окна
    sub1 = subwin(stdscr, maxy - 4, maxx - 2, 3, 1);     // окно введенных и полученных данных
    a = subwin(stdscr, LINES - 28, COLS - 2, 1, 1);      // диалоговое окно
    b = subwin(stdscr, halfy + 10, halfx - 1, 4, halfx); // окно для эскиза

    if (sub1 == NULL || a == NULL || b == NULL)
    {
        endwin();
        puts("Unable to create subwindow");
        return (1);
    }
    wbkgd(a, COLOR_PAIR(2));
    wbkgd(b, COLOR_PAIR(7));

    // Работа с файлами
    /* tabl_B_3.csv - данные по стали */
    open_file(sub1, &fptr_st, file_name_st, 10);
    count_st = read_data_file_steel(&fptr_st, info_st);
    fclose(fptr_st);
    /* tabl_G_5.csv - данные по болтам */
    open_file(sub1, &fptr_blt, file_name_blt, 15);
    count_blt = read_data_file_bolt(&fptr_blt, info_blt);
    fclose(fptr_blt);


    // 1. Вводим исходные данные
    data_entry_dialog(sub1, a, b);

    // 2. Читаем из полученных данных Ru и Rbs
    r_u = design_steel_resistance(sub1, info_st, count_st);
    // r_bs

    // 3. Рисуем таблицу под данные из файлов
    draw_table(sub1);

    // 4. Заполняем данными таблицу
    data_draw_table(sub1, r_u);


    wrefresh(sub1);
    wrefresh(a);
    wrefresh(b);
    refresh();

    getch();
    endwin();
    return 0;
}
