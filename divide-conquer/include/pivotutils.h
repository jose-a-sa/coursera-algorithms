#ifndef PIVOT_UTILS_H_
#define PIVOT_UTILS_H_

#include <stdlib.h>

typedef struct partition_t
{
    size_t lo;
    size_t hi;
} partition_t;

void swap(int *a, int *b);
partition_t partition(int *const, const partition_t, int);
int pivot_first(int *const, const partition_t);
int pivot_last(int *const, const partition_t);
int pivot_median(int *const, const partition_t);
int pivot_random(int *const, const partition_t);

#endif