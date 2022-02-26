#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "msort.h"
#include "pivot_utils.h"

#define GROUP_SIZE 5

int compareInt(const void *_Nonnull a, const void *_Nonnull b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y;
}

int *find_medians(int *const a, const partition_t rng, size_t group_size)
{
    size_t n = rng.hi - rng.lo;
    size_t n_med = n / group_size + (n % group_size > 0);

    int *c_medians;
    if ((c_medians = (int *)calloc(n_med, sizeof(int))) == NULL)
        error("failed alloc of int pointer in deter_select");

    for (size_t i = 0; i < n_med; i++)
    {
        size_t lo = rng.lo + i * group_size;
        size_t hi = rng.lo + MIN((i + 1) * group_size, n);
        size_t n_sub = hi - lo;

        if (n_sub == 1)
            c_medians[i] = a[lo];
        else if (n_sub == 2)
            c_medians[i] = MIN(a[lo], a[lo + 1]);
        else
        {
            size_t m = n_sub - 1 - n_sub / 2;
            int *sub_a = sub_array_int(a, lo, hi);
            msort(sub_a, n_sub, sizeof(int), compareInt);
            c_medians[i] = sub_a[m];
            free(sub_a);
        }
    }

    return c_medians;
}

int deter_select(int *const a, const partition_t rng, const size_t order)
{
    size_t n = rng.hi - rng.lo;
    if (n > 1)
    {
        size_t n_med = n / GROUP_SIZE + (n % GROUP_SIZE > 0);
        int *c_medians = find_medians(a, rng, GROUP_SIZE);
        int pivot = deter_select(c_medians, (partition_t){0, n_med}, n / 10);
        free(c_medians);

        partition_t p_rng = partition(a, rng, pivot);
        size_t n_l = p_rng.lo - rng.lo;
        size_t n_p = p_rng.hi - p_rng.lo;

        if (n_l > order - 1)
            return deter_select(a, (partition_t){rng.lo, p_rng.lo}, order);
        else if (n_l + n_p > order - 1)
            return pivot;
        else
            return deter_select(a, (partition_t){p_rng.hi, rng.hi}, order - n_l - n_p);
    }
    else
        return a[rng.lo];
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    int a[] = {3, 5, 9, 1, 0, 4, 3, 1, -5, 7};
    const size_t n_a = (size_t)(sizeof(a) / sizeof(*a));

    for (int i = 1; i <= n_a; i++)
    {
        int *a_copy = array_int_copy(a, n_a);
        printf("deter_select: %d\n", deter_select(a_copy, (partition_t){0, n_a}, i));
        free(a_copy);
    }

    exit(EXIT_SUCCESS);
}