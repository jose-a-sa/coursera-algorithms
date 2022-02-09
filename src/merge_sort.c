#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void merge(int *array, const size_t l, const size_t m, const size_t r)
{
    const size_t nL = m - l;
    const size_t nR = r - m;
    int *L = sub_array_int(array, l, m);
    int *R = sub_array_int(array, m, r);

    int i = 0;
    int j = 0;
    int k = l;
    // check L and R while both have elements
    while (i < nL && j < nR)
        array[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
    // add L elements
    while (i < nL)
        array[k++] = L[i++];
    // add R elements
    while (j < nR)
        array[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSortRecursive(int *array, const size_t l, const size_t r)
{
    if (r - l > 1)
    {
        const size_t m = l + (r - l) / 2;

        mergeSortRecursive(array, l, m);
        mergeSortRecursive(array, m, r);

        merge(array, l, m, r);
    }
}

int *mergeSort(int * const array, const size_t n)
{
    int *copy = array_int_copy(array, n);

    mergeSortRecursive(copy, 0, n);

    return copy;
}

int main(int argc, const char *argv[])
{
    int array[] = {4, 5, 9, 1, 4, -1, -5};
    const size_t n = (size_t)(sizeof(array) / sizeof(*array));

    printf("%6s: ", "array");
    print_array_int(array, n, "\n");
    printf("%6s: %zu\n", "n", n);

    printf("%6s: ", "array");
    print_array_int(mergeSort(array, n), n, "\n");

    exit(EXIT_SUCCESS);
}
