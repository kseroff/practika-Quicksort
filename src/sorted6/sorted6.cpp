#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

int partition(int arr[], int first, int last) {
    int p = arr[last];
    int i = first - 1;

    for (int j = first; j < last; j++) {
        if (arr[j] <= p) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[last];
    arr[last] = temp;

    return i + 1;
}

void sort_arr(int arr[], int first, int last) {
    if (first < last) {
        int p_index = partition(arr, first, last);
        sort_arr(arr, first, p_index - 1);
        sort_arr(arr, p_index + 1, last);
    }
}

void a_rr(int arr[], int size) {
    if (size == 0 || size == 1) {
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

void test_sort(int arr[], int size, const char* testName) {
    printf("\n%s\n", testName);
    print_arr(arr, size, "  Исходный:        ");

    a_rr(arr, size);

    print_arr(arr, size, "  Отсортированный: ");
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
