#include "pivot_utils.h"

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

partition_t partition(int *const a, const partition_t rng, int pivot)
{
    size_t l = rng.lo;
    size_t r = rng.hi - 1;
    size_t i = l;

    while (i <= r)
    {
        if (a[i] < pivot)
            swap(&a[i++], &a[l++]);
        else if (a[i] > pivot)
            swap(&a[i], &a[r--]);
        else
            i++;
    }

    return (partition_t){l, r + 1};
}

int pivot_first(int *const a, const partition_t rng)
{
    return a[rng.lo];
}

int pivot_last(int *const a, const partition_t rng)
{
    return a[rng.hi - 1];
}

int pivot_median(int *const a, const partition_t rng)
{
    size_t m = rng.lo + (rng.hi - rng.lo) / 2 - ((rng.hi - rng.lo + 1) % 2);
    int a_l = a[rng.lo];
    int a_m = a[m];
    int a_r = a[rng.hi - 1];

    if ((a_r <= a_m && a_m <= a_l) || (a_l <= a_m && a_m <= a_r))
        return a_m;
    else if ((a_m <= a_r && a_r <= a_l) || (a_l <= a_r && a_r <= a_m))
        return a_r;
    else
        return a_l;
}

int pivot_random(int *const a, const partition_t rng)
{
    size_t i = arc4random() % (rng.hi - rng.lo) + rng.lo;
    return a[i];
}
