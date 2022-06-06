#ifndef MATRIX_INT_H_
#define MATRIX_INT_H_

#include <stdlib.h>

typedef struct
{
    size_t n1;
    size_t n2;
    int *data;
} matrix_int;

void matrix_int_error(char *const);
void matrix_int_check_dim(const size_t, const size_t);
void matrix_int_check_bounds(const size_t, const size_t, const size_t, char *const);
matrix_int *matrix_int_alloc(const size_t, const size_t);
matrix_int *matrix_int_calloc(const size_t, const size_t);
void matrix_int_set(matrix_int *const, const size_t, const size_t, int);
int matrix_int_get(matrix_int *const, const size_t, const size_t);
matrix_int *matrix_int_submatrix(matrix_int *const, const size_t, const size_t, const size_t, const size_t);
matrix_int *matrix_int_from_array(int *const, const size_t, const size_t);

#endif