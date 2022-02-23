#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "pivot_utils.h"

int rand_select(int *const a,
                const partition_t rng,
                const size_t order,
                int (*_Nonnull pivot_func)(int *const, const partition_t))
{
    if (rng.hi - rng.lo > 1)
    {
        int pivot = pivot_func(a, rng);

        partition_t p_rng = partition(a, rng, pivot);
        size_t n_l = p_rng.lo - rng.lo;
        size_t n_p = p_rng.hi - p_rng.lo;

        if (n_l > order - 1)
            return rand_select(a, (partition_t){rng.lo, p_rng.lo}, order, pivot_func);
        else if (n_l + n_p > order - 1)
            return pivot;
        else
            return rand_select(a, (partition_t){p_rng.hi, rng.hi}, order - n_l - n_p, pivot_func);
    }
    else
        return a[rng.lo];
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    int a[] = {3, 5, 9, 1, 4, 3, 1, -5};
    const size_t n_a = (size_t)(sizeof(a) / sizeof(*a));

    for (int i = 1; i <= n_a; i++)
    {
        int *a_copy = array_int_copy(a, n_a);
        printf("rand_select: %d\n", rand_select(a_copy, (partition_t){0, n_a}, i, pivot_random));
        free(a_copy);
    }

    partition(a, (partition_t){0, n_a}, 1);
    print_array_int(a, n_a, "\n");

    exit(EXIT_SUCCESS);
}