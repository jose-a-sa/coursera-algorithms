#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct
{
    int *array;
    size_t count;
} array_inv_count;

size_t array_inversions_merge(array_inv_count *t, const size_t l, const size_t r)
{
    int *a = t->array;
    size_t c = t->count;
    size_t c0 = 0;

    const size_t nL = (r - l) / 2;
    const size_t nR = (r - l) - nL;
    int *L = sub_array_int(a, l, l + nL);
    int *R = sub_array_int(a, l + nL, r);

    int i = 0;
    int j = 0;
    int k = l;
    // check L and R while both have elements
    while (i < nL && j < nR)
    {
        if (L[i] < R[j])
            a[k++] = L[i++];
        else
        {
            c += nL - i;
            c0 += nL - i;
            a[k++] = R[j++];
        }
    }
    // add L elements
    while (i < nL)
        a[k++] = L[i++];
    // add R elements
    while (j < nR)
        a[k++] = R[j++];

    free(L);
    free(R);

    t->count = c;

    return c0;
}

size_t array_inversions_rec(array_inv_count *t, const size_t l, const size_t r)
{
    size_t inv_l = 0, inv_r = 0, inv_merge = 0;

    if (r - l > 1)
    {
        const size_t m = l + (r - l) / 2;

        inv_l = array_inversions_rec(t, l, m);
        inv_r = array_inversions_rec(t, m, r);
        
        inv_merge = array_inversions_merge(t, l, r);
    }

    return inv_l + inv_r + inv_merge;
}

size_t array_inversions(int *const a, const size_t n)
{
    array_inv_count *t;
    if ((t = (array_inv_count *)malloc(sizeof(array_inv_count))) == NULL)
        error("failed to alloc a array_inv_count* at array_inversions");
    t->array = array_int_copy(a, n);
    t->count = 0;

    size_t c;
    c = array_inversions_rec(t, 0, n);
    printf("Num of inv return: %zu\n", c);

    return t->count;
}

int main(int argc, const char *argv[])
{
    const size_t n = 100000;
    int *exer_array;
    if ((exer_array = (int *)calloc(n, sizeof(int))) == NULL)
        error("failed to calloc the array");

    FILE *f1;
    if ((f1 = fopen("../data/array_inv_exer.txt", "r")) == NULL)
        error("failed to read the file");

    int *ptr_i = exer_array;
    while (EOF != fscanf(f1, "%d", ptr_i))
        ptr_i = ptr_i + 1;
    fclose(f1);

    printf("Num of inv struct: %zu\n", array_inversions(exer_array, n));

    exit(EXIT_SUCCESS);
}