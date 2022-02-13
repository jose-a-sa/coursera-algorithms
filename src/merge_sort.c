#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "msort.h"

void merge(int *array, const size_t l, const size_t r)
{
    const size_t nL = (r - l) / 2;
    const size_t nR = (r - l) - nL;
    int *L = sub_array_int(array, l, l + nL);
    int *R = sub_array_int(array, l + nL, r);

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

        merge(array, l, r);
    }
}

int *mergeSort(int * const array, const size_t n)
{
    int *copy = array_int_copy(array, n);

    mergeSortRecursive(copy, 0, n);

    return copy;
}

int cmpfunc(const void *_Nonnull a, const void *_Nonnull b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y;
}

int main(int argc, const char *argv[])
{
    int a[] = {4, 5, 9, 1, 4, -1, -5};
    const size_t n_a = (size_t)(sizeof(a) / sizeof(*a));

    printf("%30s: ", "array a");
    print_array_int(a, n_a, "\n");

    printf("%30s: ", "sorted a (infile mergeSort)");
    print_array_int(mergeSort(a, n_a), n_a, "\n");

    int b[] = {4, 5, 9, 1, 4, -1, -5};
    const size_t n_b = (size_t)(sizeof(b) / sizeof(*b));

    printf("%30s: ", "array b");
    print_array_int(a, n_a, "\n");

    msort(b, n_b, sizeof(int), cmpfunc);

    printf("%30s: ", "sorted b (infile mergeSort)");
    print_array_int(b, n_b, "\n");

    exit(EXIT_SUCCESS);
}
