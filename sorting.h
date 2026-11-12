#ifndef SORTING_H
#define SORTING_H

#include "datastructures.h"

void merge(int arr[], int left, int mid, int right, ExecutionMetrics* metrics);
void merge_sort_recursive(int arr[], int left, int right, ExecutionMetrics* metrics);
void run_merge_sort(int arr[], int size, ExecutionMetrics* metrics);

#endif

