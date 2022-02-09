#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix_int.h"
#include "msort.h"


int cmpfunc(const void *_Nonnull a, const void *_Nonnull b)
{
    int x = *(int*)a;
    int y = *(int*)b;
    return (y - x);
}

int main(int argc, const char *argv[])
{
    int a[] = {1, 2 ,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    matrix_int * m = matrix_int_from_array(a, 4, 4);
    matrix_int * s = matrix_int_submatrix(m, 0, 4, 0, 2);
    
    for(int i  = 0; i < 4; i++)
    {
        for(int j  = 0; j < 2; j++)
            printf("%3d ", matrix_int_get(s, i, j));
        printf("\n");
    }
    
    msort(a, 16, sizeof(int), cmpfunc);

    print_array_int(a, 16, "\n");

    exit(EXIT_SUCCESS);
}