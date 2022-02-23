#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

typedef struct partition_t
{
    size_t lo;
    size_t hi;
} partition_t;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void pivot_first(int *const a, const partition_t rng)
{
    return;
}

void pivot_last(int *const a, const partition_t rng)
{
    swap(&a[rng.lo], &a[rng.hi - 1]);
}

void pivot_median(int *const a, const partition_t rng)
{
    size_t m = rng.lo + (rng.hi - rng.lo) / 2 - ((rng.hi - rng.lo + 1) % 2);
    int a_l = a[rng.lo];
    int a_m = a[m];
    int a_r = a[rng.hi - 1];

    if ((a_r <= a_m && a_m <= a_l) || (a_l <= a_m && a_m <= a_r))
        swap(&a[rng.lo], &a[m]);
    else if ((a_m <= a_r && a_r <= a_l) || (a_l <= a_r && a_r <= a_m))
        swap(&a[rng.lo], &a[rng.hi - 1]);
}

void pivot_random(int *const a, const partition_t rng)
{
    size_t i = rand() % (rng.hi - rng.lo) + rng.lo;
    swap(&a[rng.lo], &a[i]);
}

size_t quick_sort_partition(int *const a,
                            const partition_t rng,
                            void (*_Nonnull pivot_func)(int *const, const partition_t),
                            size_t *const cnt)
{
    (*cnt) = (*cnt) + rng.hi - rng.lo - 1;

    pivot_func(a, rng);
    int pivot = a[rng.lo];

    size_t i = rng.lo + 1;
    for (size_t j = rng.lo + 1; j < rng.hi; j++)
    {
        if (a[j] < pivot)
            swap(&a[j], &a[i++]);
    }
    swap(&a[rng.lo], &a[i - 1]);

    return i - 1;
}

void quick_sort(int *const a,
                const partition_t rng,
                void (*_Nonnull pivot_func)(int *const, const partition_t),
                size_t *const cnt)
{
    if (rng.hi - rng.lo > 1)
    {
        int pi = quick_sort_partition(a, rng, pivot_func, cnt);

        quick_sort(a, (partition_t){rng.lo, pi}, pivot_func, cnt);
        quick_sort(a, (partition_t){pi + 1, rng.hi}, pivot_func, cnt);
    }
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    const size_t n = 10000;
    int *exer_array;
    if ((exer_array = (int *)calloc(n, sizeof(int))) == NULL)
        error("failed to calloc the array");

    FILE *f1;
    if ((f1 = fopen("../data/array_inv_exer2.txt", "r")) == NULL)
        error("failed to read the file");

    int *ptr_i = exer_array;
    while (EOF != fscanf(f1, "%d", ptr_i))
        ptr_i = ptr_i + 1;
    fclose(f1);

    size_t cnt;

    cnt = 0;
    quick_sort(array_int_copy(exer_array, n), (partition_t){0, n}, pivot_first, &cnt);
    printf("Number of inversions (pivot_first): %zu\n", cnt);

    cnt = 0;
    quick_sort(array_int_copy(exer_array, n), (partition_t){0, n}, pivot_last, &cnt);
    printf("Number of inversions (pivot_last): %zu\n", cnt);

    cnt = 0;
    quick_sort(array_int_copy(exer_array, n), (partition_t){0, n}, pivot_median, &cnt);
    printf("Number of inversions (pivot_median): %zu\n", cnt);

    exit(EXIT_SUCCESS);
}