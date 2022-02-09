#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct
{
    int *array;
    size_t count;
} array_inv_count;

void array_inversions_merge(array_inv_count *t, const size_t l, const size_t m, const size_t r)
{
    int *a = t->array;
    size_t c = t->count;

    const size_t nL = m - l;
    const size_t nR = r - m;
    int *L = sub_array_int(a, l, m);
    int *R = sub_array_int(a, m, r);

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
}

void array_inversions_rec(array_inv_count *t, const size_t l, const size_t r)
{
    if (r - l > 1)
    {
        const size_t m = l + (r - l) / 2;

        array_inversions_rec(t, l, m);
        array_inversions_rec(t, m, r);

        array_inversions_merge(t, l, m, r);
    }
}

size_t array_inversions(int *const a, const size_t n)
{
    array_inv_count *t;
    if ((t = (array_inv_count *)malloc(sizeof(array_inv_count))) == NULL)
        error("failed to alloc a array_inv_count* at array_inversions");
    t->array = array_int_copy(a, n);
    t->count = 0;

    array_inversions_rec(t, 0, n);

    return t->count;
}

int main(int argc, const char *argv[])
{
    int a[] = {6, 5 ,4, 3, 2, 1};
    const size_t n = (size_t) sizeof(a)/sizeof(int);
    printf("Number of inversion: %zu\n", array_inversions(a, n)) ;

    exit(EXIT_SUCCESS);
}