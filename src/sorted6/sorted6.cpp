#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>

long long comparisons = 0;
long long swaps = 0;
long long recursive_calls = 0;

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

    if (arr == NULL || size < 2) {
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
    printf("\n МЕТРИКИ СОРТИРОВКИ \n");
    printf("Размер массива:       %d\n", size);
    printf("Сравнений:            %lld\n", comparisons);
    printf("Обменов:              %lld\n", swaps);
    printf("Рекурсивных вызовов:  %lld\n", recursive_calls);
    printf("Время выполнения:     %.6f сек\n", time_seconds);
    printf("\n");
}

void test_sort(int arr[], int size, const char* testName) {
    printf("\n%s\n", testName);
    print_arr(arr, size, "  Исходный:        ");

    clock_t start = clock();
    quick_sort(arr, size);
    clock_t end = clock();
    double time_seconds = (double)(end - start) / CLOCKS_PER_SEC;

    print_arr(arr, size, "  Отсортированный: ");

    print_metrics(size, time_seconds);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int arr1[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    test_sort(arr1, size1, "Массив с одинаковыми значениями");

    int arr2[] = { -5, 3, -8, 1, -2, 7, -4, 6, -1, 10 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    test_sort(arr2, size2, "Массив с отрицательными числами");

    int arr3[] = { 42 };
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    test_sort(arr3, size3, "Массив из одного элемента");

    int arr4[] = { 64, 34, 25, 12, 22, 11, 90 };
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    test_sort(arr4, size4, "Обычный массив");

    int arr5[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    test_sort(arr5, size5, "Уже отсортированный массив");

    int arr6[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int size6 = sizeof(arr6) / sizeof(arr6[0]);
    test_sort(arr6, size6, "Массив в обратном порядке");

    return 0;
}