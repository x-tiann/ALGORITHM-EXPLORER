#include <stdio.h>
#include <time.h>
#include "sorting.h"
#include "datastructures.h"

// Merge two sub-arrays while tracking operations and recording steps
void merge(int arr[], int left, int mid, int right, ExecutionMetrics* metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        metrics->operations++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        metrics->operations++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
        metrics->operations++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
        metrics->operations++;
    }

    // Capture the array transformation snapshot for step-by-step logging
    record_step(metrics, arr, right + 1);
}

// Recursive divide-and-conquer function tracking recursion depth
void merge_sort_recursive(int arr[], int left, int right, ExecutionMetrics* metrics) {
    metrics->current_depth++;
    if (metrics->current_depth > metrics->max_recursion_depth) {
        metrics->max_recursion_depth = metrics->current_depth;
    }

    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(arr, left, mid, metrics);
        merge_sort_recursive(arr, mid + 1, right, metrics);
        merge(arr, left, mid, right, metrics);
    }

    metrics->current_depth--;
}

// Wrapper function to time the sorting process
void run_merge_sort(int arr[], int size, ExecutionMetrics* metrics) {
    clock_t start = clock();
    merge_sort_recursive(arr, 0, size - 1, metrics);
    clock_t end = clock();
    metrics->execution_time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}