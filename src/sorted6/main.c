#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "array_io.h"
#include "metrics.h"


void menu() {
    system("cls");
    printf("\n");
    printf("     БЫСТРАЯ СОРТИРОВКА (QuickSort)\n");
    printf("\n");
    printf("  1. Создать массив вручную\n");
    printf("  2. Сгенерировать случайный массив\n");
    printf("  3. Создать массив из одинаковых чисел\n");
    printf("  4. Загрузить массив из файла\n");
    printf("  5. Сохранить массив в файл\n");
    printf("  6. Вывести текущий массив\n");
    printf("  7. Отсортировать текущий массив\n");
    printf("  8. Выйти из программы\n");
    printf("\n");
    printf("Ваш выбор: ");
}

int read_menu_choice() {
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) == 0) {
        printf("Ошибка: пустой ввод\n");
        return -1;
    }
    if (!is_number(input)) {
        printf("Ошибка: введите число от 1 до 8\n");
        return -1;
    }
    int choice = atoi(input);
    if (choice < 1 || choice > 8) {
        printf("Ошибка: введите число от 1 до 8\n");
        return -1;
    }
    return choice;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;

    do {
        menu();
        choice = read_menu_choice();

        if (choice == -1) {
            printf("\nНажмите Enter для продолжения...");
            clear_input();
            continue;
        }

        switch (choice) {
        case 1:
            create_manual_array();
            break;
        case 2:
            generate_random_array();
            break;
        case 3:
            create_identical_array();
            break;
        case 4:
            load_from_file();
            break;
        case 5:
            save_to_file();
            break;
        case 6:
            if (current_size == 0) {
                printf("\nМассив пуст!\n");
            }
            else {
                printf("\nТекущий массив: ");
                print_arr(current_array, current_size, "");
            }
            break;
        case 7:
            sort_current_array();
            break;
        case 8:
            printf("\nВыход из программы...\n");
            break;
        default:
            printf("\nОшибка: неверный выбор.\n");
        }

        if (choice != 8) {
            printf("\nНажмите Enter для продолжения...");
            clear_input();
        }
    } while (choice != 8);

    return 0;
}