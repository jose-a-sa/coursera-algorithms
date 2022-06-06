#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

size_t pivot_first(int *const a, const size_t lo, const size_t hi)
{
    return lo;
}

size_t pivot_last(int *const a, const size_t lo, const size_t hi)
{
    swap(&a[lo], &a[hi - 1]);
    return lo;
}

size_t pivot_median(int *const a, const size_t lo, const size_t hi)
{
    size_t m = lo + (hi - lo) / 2 - ((hi - lo + 1) % 2);

    if ((a[hi - 1] <= a[m] && a[m] <= a[lo]) || (a[lo] <= a[m] && a[m] <= a[hi - 1]))
        swap(&a[lo], &a[m]);
    else if ((a[hi - 1] <= a[lo] && a[m] <= a[hi - 1]) || (a[hi - 1] <= a[m] && a[lo] <= a[hi - 1]))
        swap(&a[lo], &a[hi - 1]);

    return lo;
}

size_t quick_sort_partition(int *const a,
                            const size_t lo,
                            const size_t hi,
                            size_t (*_Nonnull pivot_func)(int *const, const size_t, const size_t),
                            size_t *const cnt)
{
    (*cnt) = (*cnt) + hi - lo - 1;

    size_t pi = pivot_func(a, lo, hi);
    int pivot = a[pi];

    size_t i = lo + 1;
    for (size_t j = lo + 1; j < hi; j++)
    {
        if (a[j] < pivot)
            swap(&a[j], &a[i++]);
    }
    swap(&a[pi], &a[i - 1]);

    return i - 1;
}

size_t quick_sort(int *const a,
                  const size_t lo,
                  const size_t hi,
                  size_t (*_Nonnull pivot_func)(int *const, const size_t, const size_t),
                  size_t *const cnt)
{
    if (hi - lo > 1)
    {
        int pi = quick_sort_partition(a, lo, hi, pivot_func, cnt);

        quick_sort(a, lo, pi, pivot_func, cnt);
        quick_sort(a, pi + 1, hi, pivot_func, cnt);
    }
}

int main(int argc, const char *argv[])
{
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
    quick_sort(array_int_copy(exer_array, n), 0, n, pivot_first, &cnt);
    printf("Number of inversions (pivot_first): %zu\n", cnt);

    cnt = 0;
    quick_sort(array_int_copy(exer_array, n), 0, n, pivot_last, &cnt);
    printf("Number of inversions (pivot_last): %zu\n", cnt);

    cnt = 0;
    quick_sort(array_int_copy(exer_array, n), 0, n, pivot_median, &cnt);
    printf("Number of inversions (pivot_median): %zu\n", cnt);

    exit(EXIT_SUCCESS);
}