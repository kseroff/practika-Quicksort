#define _CRT_SECURE_NO_WARNINGS
#include "sort.h"
#include "metrics.h"
#include <stdio.h>
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

void three_way_partition(int arr[], int first, int last, int* lt, int* gt) {
    if (first >= last) {
        *lt = first;
        *gt = last;
        return;
    }

    int mid = first + (last - first) / 2;
    if (arr[first] > arr[mid]) swap(&arr[first], &arr[mid]);
    if (arr[first] > arr[last]) swap(&arr[first], &arr[last]);
    if (arr[mid] > arr[last]) swap(&arr[mid], &arr[last]);
    swap(&arr[mid], &arr[last]);

    int pivot = arr[last];
    int i = first;
    int lt_ptr = first;
    int gt_ptr = last;

    while (i <= gt_ptr) {
        comparisons++;
        if (arr[i] < pivot) {
            swap(&arr[i], &arr[lt_ptr]);
            lt_ptr++;
            i++;
        }
        else if (arr[i] > pivot) {
            swap(&arr[i], &arr[gt_ptr]);
            gt_ptr--;
        }
        else {
            i++;
        }
    }

    *lt = lt_ptr;
    *gt = gt_ptr;
}

void sort_arr(int arr[], int first, int last) {
    recursive_calls++;
    if (first < last) {
        int lt, gt;
        three_way_partition(arr, first, last, &lt, &gt);

        int left_size = lt - first;
        int right_size = last - gt;

        if (left_size < right_size) {
            sort_arr(arr, first, lt - 1);
            sort_arr(arr, gt + 1, last);
        }
        else {
            sort_arr(arr, gt + 1, last);
            sort_arr(arr, first, lt - 1);
        }
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