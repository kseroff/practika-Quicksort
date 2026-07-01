#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 1000

long long comparisons = 0;
long long swaps = 0;
long long recursive_calls = 0;
int current_array[MAX_SIZE];
int current_size = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swaps++;
}

int partition(int arr[], int first, int last) {
    int mid = first + (last - first) / 2;

    comparisons++;
    if (arr[first] > arr[mid]) {
        swap(&arr[first], &arr[mid]);
    }
    comparisons++;
    if (arr[first] > arr[last]) {
        swap(&arr[first], &arr[last]);
    }
    comparisons++;
    if (arr[mid] > arr[last]) {
        swap(&arr[mid], &arr[last]);
    }
    swap(&arr[mid], &arr[last]);

    int pivot = arr[last];
    int i = first - 1;

    for (int j = first; j < last; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[last]);

    return i + 1;
}

void sort_arr(int arr[], int first, int last) {
    recursive_calls++;
    if (first < last) {
        int p_index = partition(arr, first, last);
        sort_arr(arr, first, p_index - 1);
        sort_arr(arr, p_index + 1, last);
    }
}

void quick_sort(int arr[], int size) {
    comparisons = 0;
    swaps = 0;
    recursive_calls = 0;

    if (arr == NULL  || size < 2) {
        return;
    }
    sort_arr(arr, 0, size - 1);
}

void print_arr(int arr[], int size, const char* message) {
    printf("%s", message);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_metrics(int size, double time_seconds) {
    printf("\n");
    printf("           МЕТРИКИ СОРТИРОВКИ\n");
    printf("\n");
    printf("  Размер массива:       %d\n", size);
    printf("  Сравнений:            %lld\n", comparisons);
    printf("  Обменов:              %lld\n", swaps);
    printf("  Рекурсивных вызовов:  %lld\n", recursive_calls);
    printf("  Время выполнения:     %.6f сек\n", time_seconds);
    printf("\n");
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int is_number(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    int i = 0;
    if (str[0] == '-') {
        i = 1;
    }
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int read_int(const char* prompt, int* value) {
    char input[100];
    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Ошибка: пустой ввод\n");
        return 0;
    }

    char* endptr;
    long val = strtol(input, &endptr, 10);

    if (*endptr != '\0') {
        printf("Ошибка: введите целое число\n");
        return 0;
    }

    if (val == LONG_MIN || val == LONG_MAX) {
        printf("Ошибка: число вне допустимого диапазона\n");
        return 0;
    }

    if (val < INT_MIN || val > INT_MAX) {
        printf("Ошибка: число слишком большое для int\n");
        return 0;
    }

    *value = (int)val;
    return 1;
}

void menu() {
    system("cls");
    printf("\n");
    printf("     БЫСТРАЯ СОРТИРОВКА (QuickSort)\n");
    printf("\n");
    printf("  1. Создать массив вручную\n");
    printf("  2. Сгенерировать случайный массив\n");
    printf("  3. Загрузить массив из файла\n");
    printf("  4. Отсортировать текущий массив\n");
    printf("  5. Вывести текущий массив\n");
    printf("  6. Сохранить массив в файл\n");
    printf("  7. Выйти из программы\n");
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
        printf("Ошибка: введите число от 1 до 7\n");
        return -1;
    }
    int choice = atoi(input);
    if (choice < 1 || choice > 7) {
        printf("Ошибка: введите число от 1 до 7\n");
        return -1;
    }
    return choice;
}

void create_manual_array() {
    int n;
    if (!read_int("\nВведите размер массива: ", &n)) {
        return;
    }
    if (n <= 0) {
        printf("Ошибка: размер должен быть больше 0\n");
        return;
    }
    if (n > MAX_SIZE) {
        printf("Ошибка: размер не может превышать %d\n", MAX_SIZE);
        return;
    }

    printf("Введите %d элементов через пробел: ", n);
    int count = 0;
    while (count < n) {
        int val;
        if (scanf("%d", &val) == 1) {
            current_array[count] = val;
            count++;
        }
        else {
            printf("Ошибка: введите целое число\n");
            clear_input();
            return;
        }
    }
    clear_input();
    current_size = n;
    printf("\nМассив успешно создан!\n");
}

void generate_random_array() {
    int n, min_val, max_val;

    if (!read_int("\nВведите размер массива: ", &n)) {
        return;
    }
    if (n <= 0) {
        printf("Ошибка: размер должен быть больше 0\n");
        return;
    }
    if (n > MAX_SIZE) {
        printf("Ошибка: размер не может превышать %d\n", MAX_SIZE);
        return;
    }

    if (!read_int("Введите минимальное значение: ", &min_val)) {
        return;
    }
    if (!read_int("Введите максимальное значение: ", &max_val)) {
        return;
    }
    if (min_val >= max_val) {
        printf("Ошибка: минимум должен быть меньше максимума\n");
        return;
    }

    current_size = n;
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        current_array[i] = min_val + rand() % (max_val - min_val + 1);
    }

    printf("\nСлучайный массив успешно создан!\n");
}

void load_from_file() {
    char filename[256];
    printf("\nВведите имя файла для загрузки: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Ошибка: пустой ввод\n");
        return;
    }
    filename[strcspn(filename, "\n")] = 0;

    if (strlen(filename) == 0) {
        printf("Ошибка: имя файла не может быть пустым\n");
        return;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: файл '%s' не найден или не удалось открыть\n", filename);
        return;
    }

    current_size = 0;
    int num;
    int result;
    while (current_size < MAX_SIZE) {
        result = fscanf(file, "%d", &num);
        if (result == EOF) {
            break;
        }
        if (result != 1) {
            fclose(file);
            printf("Ошибка: файл содержит некорректные данные (не число)\n");
            current_size = 0;
            return;
        }
        current_array[current_size] = num;
        current_size++;
    }
    fclose(file);

    if (current_size == 0) {
        printf("Ошибка: файл пуст\n");
    }
    else {
        printf("\nЗагружено %d элементов из файла %s\n", current_size, filename);
    }
}

void save_to_file() {
    if (current_size == 0) {
        printf("\nМассив пуст! Нечего сохранять.\n");
        return;
    }

    char filename[256];
    printf("\nВведите имя файла для сохранения: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Ошибка: пустой ввод\n");
        return;
    }
    filename[strcspn(filename, "\n")] = 0;

    if (strlen(filename) == 0) {
        printf("Ошибка: имя файла не может быть пустым\n");
        return;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать файл '%s'\n", filename);
        return;
    }

    for (int i = 0; i < current_size; i++) {
        fprintf(file, "%d%c", current_array[i], (i == current_size - 1) ? '\n' : ' ');
    }

    fprintf(file, "\n");
    fclose(file);

    printf("\nМассив сохранён в файл %s\n", filename);
}

void sort_current_array() {
    if (current_size == 0) {
        printf("\nМассив пуст! Сначала создайте или загрузите массив.\n");
        return;
    }

    printf("\nИсходный массив: ");
    print_arr(current_array, current_size, "");

    clock_t start = clock();
    quick_sort(current_array, current_size);
    clock_t end = clock();
    double time_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Отсортированный массив: ");
    print_arr(current_array, current_size, "");

    print_metrics(current_size, time_seconds);
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
            load_from_file();
            break;
        case 4:
            sort_current_array();
            break;
        case 5:
            if (current_size == 0) {
                printf("\nМассив пуст!\n");
            }
            else {
                printf("\nТекущий массив: ");
                print_arr(current_array, current_size, "");
            }
            break;
        case 6:
            save_to_file();
            break;
        case 7:
            printf("\nВыход из программы...\n");
            break;
        default:
            printf("\nОшибка: неверный выбор.\n");
        }

        if (choice != 7) {
            printf("\nНажмите Enter для продолжения...");
            clear_input();
        }
    } while (choice != 7);

    return 0;
}