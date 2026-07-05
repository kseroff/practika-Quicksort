#define _CRT_SECURE_NO_WARNINGS
#include "array_io.h"
#include "sort.h"
#include "metrics.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>


int current_array[MAX_SIZE];
int current_size = 0;

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

void print_arr(int arr[], int size, const char* message) {
    printf("%s", message);

    int print_count = (size > 1000) ? 1000 : size;

    for (int i = 0; i < print_count; i++) {
        printf("%d ", arr[i]);
    }

    if (size > 1000) {
        printf("... (показано 1000 из %d)\n", size);
    }
    else {
        printf("\n");
    }
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
    if (n > 100) {
        printf("\n ВНИМАНИЕ: Вы собираетесь вручную ввести %d чисел!\n", n);
        printf("Рекомендуется использовать:\n");
        printf("  - Пункт 2 (Сгенерировать случайный массив)\n");
        printf("  - Пункт 3 (Загрузить массив из файла)\n");
        printf("\nВы уверены, что хотите продолжить? (1 - да, 0 - нет): ");
        int confirm;
        if (scanf("%d", &confirm) != 1 || confirm != 1) {
            clear_input();
            return;
        }
        clear_input();
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

void create_identical_array() {
    int n, value;

    if (!read_int("\nВведите размер массива (до 50000): ", &n)) {
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

    if (!read_int("Введите число для заполнения массива: ", &value)) {
        return;
    }

    for (int i = 0; i < n; i++) {
        current_array[i] = value;
    }
    current_size = n;

    printf("\n Создан массив из %d одинаковых чисел (%d)\n", n, value);
}

void load_from_file() {
    char filename[256];
    printf("\nВведите имя файла для загрузки (с расширением): ");
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

    int count = 0;
    int temp;
    char c;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
        fscanf(file, "%c", &c);
        if (c == ',') {
        }
    }

    if (count > 50000) {
        printf("Файл содержит %d чисел, будет загружено только 50000 чисел.!\n", count);
        printf("Остальные %d чисел будут проигнорированы.\n", count - 50000);
    }
    rewind(file);

    current_size = 0;
    int num;


    while (current_size < MAX_SIZE) {

        if (fscanf(file, "%d", &num) == 1) {
            current_array[current_size] = num;
            current_size++;
        }
        else {
            if (feof(file)) break;
            fgetc(file);
        }
    }
    fclose(file);

    if (current_size == 0) {
        printf("Ошибка: файл пуст или не содержит чисел\n");
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

    char* ext = strrchr(filename, '.');
    if (ext == NULL || (strcmp(ext, ".csv") != 0 && strcmp(ext, ".CSV") != 0)) {
        strcat(filename, ".csv");
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать файл '%s'\n", filename);
        return;
    }

    for (int i = 0; i < current_size; i++) {
        fprintf(file, "%d", current_array[i]);
        if (i < current_size - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    fclose(file);

    printf("\nМассив сохранён в CSV файл: %s\n", filename);
    printf("Количество элементов: %d\n", current_size);
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