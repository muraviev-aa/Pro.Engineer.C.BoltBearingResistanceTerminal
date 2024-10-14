#include <curses.h>
#include "temp_function.h"
#include <stdio.h>

#define SIZE_STEEL 15           // число строк в файле tabl_B_3.csv
#define SIZE_STEEL_ELEM 15      // число строк в файле tabl_G_6.csv
#define SIZE_BOLT 5             // число строк в файле tabl_G_5.csv
#define SIZE_BOLT_AREA 10       // число строк в файле tabl_G_9.csv
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
    steel_elem *info_st_el = (steel_elem *) malloc(SIZE_STEEL_ELEM * sizeof(steel_elem));
    bolt *info_blt = (bolt *) malloc(SIZE_BOLT * sizeof(bolt));
    bolt_area *info_blt_ar = (bolt_area *) malloc(SIZE_BOLT_AREA * sizeof(bolt_area));
    if (!info_st || !info_blt || !info_st_el || !info_blt_ar)
        printf("Error while allocating memory!\n");
    FILE *fptr_st, *fptr_st_el, *fptr_blt, *fptr_blt_ar;
    char file_name_st[] = "tabl_B_3.csv";
    char file_name_st_el[] = "tabl_G_6.csv";
    char file_name_blt[] = "tabl_G_5.csv";
    char file_name_blt_ar[] = "tabl_G_9.csv";
    int count_st;      // количество строк в файле tabl_B_3.csv
    int count_st_el;   // количество строк в файле tabl_G_6.csv
    int count_blt;     // количество строк в файле tabl_G_5.csv
    int count_blt_ar;  // количество строк в файле tabl_G_9.csv
    unsigned int r_u, r_bs, r_un, r_bp, r_bt;
    double a_b, a_bn, max_sher_result, max_bear_result, max_tens_result;

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
    open_file(sub1, &fptr_st, file_name_st, 7);
    count_st = read_data_file_steel(&fptr_st, info_st);
    fclose(fptr_st);
    /* tabl_G_5.csv - данные по болтам */
    open_file(sub1, &fptr_blt, file_name_blt, 12);
    count_blt = read_data_file_bolt(&fptr_blt, info_blt);
    fclose(fptr_blt);
    /* tabl_G_6.csv - расчетные сопротивления смятию элементов */
    open_file(sub1, &fptr_st_el, file_name_st_el, 17);
    count_st_el = read_data_file_steel_elem(&fptr_st_el, info_st_el);
    fclose(fptr_st_el);
    /* tabl_G_9.csv - площади сечения болтов */
    open_file(sub1, &fptr_blt_ar, file_name_blt_ar, 22);
    count_blt_ar = read_data_file_bolt_ar(&fptr_blt_ar, info_blt_ar);
    fclose(fptr_blt_ar);

    // 1. Вводим исходные данные
    data_entry_dialog(sub1, a, b);

    // 2. Читаем из полученных данных нужную информацию
    r_u = design_steel_resistance_r_u(info_st, count_st);
    r_un = design_steel_resistance_r_un(info_st, count_st);
    r_bp = design_steel_resistance_r_bp(info_st_el, count_st_el, r_un);
    r_bs = design_bolt_resistance_r_bs(info_blt, count_blt);
    r_bt = design_bolt_resistance_r_bt(info_blt, count_blt);
    a_b = bolt_a_b(info_blt_ar, count_blt_ar);
    a_bn = bolt_a_bn(info_blt_ar, count_blt_ar);

    // 3. Рисуем таблицу под данные из файлов для стали
    draw_table(sub1, 9);

    // 4. Рисуем таблицу под данные из файлов для болтов
    draw_table(sub1, 16);

    // 5. Заполняем данными таблицу
    data_draw_table_steel(sub1, r_u, r_bp, r_un, 8);
    data_draw_table_bolt(sub1, r_bs, r_bt, a_b, a_bn, 15);

    // 6. Расчет на смятие
    max_bear_result = calc_bearing_n_bp(r_bp);

    // 7. Расчет на срез
    max_sher_result = calc_bearing_n_bs(r_bs, a_b);

    // 8. Расчет на растяжение
    max_tens_result = calc_tens_n_bt(r_bt, a_bn);

    /* Вывод результатов */
    /* Шапка */
    wmove(sub1, 22, 21);
    wprintw(sub1, "*One bolt*");
    wmove(sub1, 22, 37);
    wprintw(sub1, "*One bolt per group*");
    // Макс. срезающая сила
    wmove(sub1, 23, 0);
    waddch(sub1, ACS_DIAMOND);
    wmove(sub1, 23, 2);
    wprintw(sub1, "Shear force: ");
    wmove(sub1, 23, 17); // один болт
    wprintw(sub1, "%.2f kN (%.2f T)", max_sher_result, max_sher_result / 9.81);
    wmove(sub1, 23, 39); // многоболтовое соединение
    wprintw(sub1, "%.2f kN (%.2f T)", 0.9 * max_sher_result, 0.9 * max_sher_result / 9.81);
    // Макс. сила на срез
    wmove(sub1, 24, 0);
    waddch(sub1, ACS_DIAMOND);
    wmove(sub1, 24, 2);
    wprintw(sub1, "Bear. force:");
    wmove(sub1, 24, 17); // один болт
    wprintw(sub1, "%.2f kN (%.2f T)", max_bear_result, max_bear_result / 9.81);
    wmove(sub1, 24, 39); // многоболтовое соединение
    wprintw(sub1, "%.2f kN (%.2f T)", 0.9 * max_bear_result, 0.9 * max_bear_result / 9.81);
    // Макс. сила на растяжение
    wmove(sub1, 25, 0);
    waddch(sub1, ACS_DIAMOND);
    wmove(sub1, 25, 2);
    wprintw(sub1, "Tens. force: ");
    wmove(sub1, 25, 17); // один болт
    wprintw(sub1, "%.2f kN (%.2f T)", max_tens_result, max_tens_result / 9.81);
    wmove(sub1, 25, 39); // многоболтовое соединение
    wprintw(sub1, "%.2f kN (%.2f T)", max_tens_result, max_tens_result / 9.81);

    // n. Рисуем систему координат
    draw_coord_sys(b);

    wrefresh(sub1);
    wrefresh(a);
    wrefresh(b);
    refresh();

    getch();

    // Освобождаем память
    free(info_st);
    free(info_st_el);
    free(info_blt);
    free(info_blt_ar);

    endwin();
    return 0;
}


