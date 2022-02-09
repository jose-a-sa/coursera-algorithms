#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_int.h"

void matrix_int_error(char *const msg)
{
    fprintf(stderr, "ERROR <matrix_int>:  %s\n", msg);
    exit(EXIT_FAILURE);
}

void matrix_int_check_dim(const size_t n, const size_t d)
{
    char msg[45];
    sprintf(msg, "matrix dimension %zu must be positive integer", d);
    
    if (n <= 0)
        matrix_int_error(msg);
}

void matrix_int_check_bounds(const size_t n, const size_t i, const size_t d, char* const var)
{
    char msg[50];
    sprintf(msg, "matrix position %s in dimension %zu out of bounds", var, d);
    
    if (i < 0 || i >= n)
        matrix_int_error(msg);
}

matrix_int *matrix_int_alloc(const size_t n1, const size_t n2)
{
    matrix_int_check_dim(n1, 1);
    matrix_int_check_dim(n2, 2);

    matrix_int *m;
    if ((m = (matrix_int *)malloc(sizeof(matrix_int))) == NULL)
        matrix_int_error("failed to allocate space for matrix struct");

    int *data;
    if ((data = (int *)malloc(n1 * n2 * sizeof(int))) == NULL)
        matrix_int_error("failed to allocate space for matrix data");

    m->data = data;
    m->n1 = n1;
    m->n2 = n2;

    return m;
}

matrix_int *matrix_int_calloc(const size_t n1, const size_t n2)
{
    matrix_int *m = matrix_int_alloc(n1, n2);

    memset(m->data, 0, n1 * n2 * sizeof(int));

    for (int i = 0; i < n1 * n2; i++)
        m->data[i] = 0;

    return m;
}

void matrix_int_set(matrix_int * const m, const size_t i, const size_t j, int x)
{
    int *const data = m->data;
    const size_t n1 = m->n1;
    const size_t n2 = m->n2;

    matrix_int_check_bounds(n1, i, 1, "i");
    matrix_int_check_bounds(n2, j, 2, "j");

    *(int *)(data + (i * n2 + j)) = x;
}

int matrix_int_get(matrix_int * const m, const size_t i, const size_t j)
{
    int *const data = m->data;
    const size_t n1 = m->n1;
    const size_t n2 = m->n2;

    matrix_int_check_bounds(n1, i, 1, "i");
    matrix_int_check_bounds(n2, j, 2, "j");

    return *(int *)(data + (i * n2 + j));
}

matrix_int *matrix_int_submatrix(matrix_int * const m, const size_t iL, const size_t iR, const size_t jL, const size_t jR)
{
    int *const data = m->data;
    const size_t n1 = m->n1;
    const size_t n2 = m->n2;

    matrix_int_check_bounds(n1, iL, 1, "iL");
    matrix_int_check_bounds(n1, iR-1, 1, "iR");
    matrix_int_check_bounds(n2, jL, 2, "jL");
    matrix_int_check_bounds(n2, jR-1, 2, "jR");

    const size_t N1 = iR - iL;
    const size_t N2 = jR - jL;
    if (N1 <= 0)
        matrix_int_error("submatrix dimension 1 must be a positive number, iL < iR");
    if (N2 <= 0)
        matrix_int_error("submatrix dimension 2 must be a positive number,  jL < jR");

    matrix_int *subM = (matrix_int *)matrix_int_calloc(N1, N2);
    int *const subData = subM->data;

    for (size_t i = 0; i < N1; i++)
        for (size_t j = 0; j < N2; j++)
            *(int *)(subData + i * N2 + j) = *(int *)(data + (i + iL) * n2 + (j + jL));

    return subM;
}

matrix_int *matrix_int_from_array(int * const a, const size_t n1, const size_t n2)
{
    matrix_int_check_dim(n1, 1);
    matrix_int_check_dim(n2, 2);

    matrix_int * const m = (matrix_int *) matrix_int_calloc(n1, n2);
    int *const data = m->data;

    for(int i =0; i < n1*n2; i++)
        * (int *) (data + i) = * (int *) (a + i);

    return m;
}