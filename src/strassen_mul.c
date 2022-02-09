#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix_int.h"

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
        

    exit(EXIT_SUCCESS);
}