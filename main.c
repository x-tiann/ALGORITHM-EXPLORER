#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "datastructures.h"
#include "sorting.h"

static void print_array(const int arr[], int size) {
    putchar('[');
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    putchar(']');
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer> [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    if (size > MAX_SIZE) {
        fprintf(stderr, "Error: at most %d integers are supported.\n", MAX_SIZE);
        return EXIT_FAILURE;
    }

    int values[MAX_SIZE];
    for (int i = 0; i < size; i++) {
        char *end = NULL;
        errno = 0;
        long value = strtol(argv[i + 1], &end, 10);
        if (errno == ERANGE || end == argv[i + 1] || *end != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Error: '%s' is not a valid integer.\n", argv[i + 1]);
            return EXIT_FAILURE;
        }
        values[i] = (int)value;
    }

    ExecutionMetrics metrics = {0};
    run_merge_sort(values, size, &metrics);

    printf("OPERATIONS: %lld\n", metrics.operations);
    printf("TIME_MS: %.3f\n", metrics.execution_time_ms);
    printf("SORTED: ");
    print_array(values, size);
    putchar('\n');

    printf("STEPS: [");
    for (int step = 0; step < metrics.step_count; step++) {
        if (step > 0) {
            printf(", ");
        }
        print_array(metrics.steps[step], metrics.step_sizes[step]);
    }
    printf("]\n");

    return EXIT_SUCCESS;
}
