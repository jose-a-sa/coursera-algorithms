#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int mod(const int x, const int m)
{
    return (x % m + m) % m;
}

void error(char *const msg)
{
    fprintf(stderr, "ERROR: %s", msg);
    exit(EXIT_FAILURE);
}

void print_array_int(int *const a, const size_t n, char *const eol)
{
    printf("{");

    if (n == 0)
    {
        printf("}%s", eol);
        return;
    }

    int i;
    for (i = 0; i < n - 1; i++)
        printf("%d, ", a[i]);
    printf("%d}%s", a[i], eol);
}

int *sub_array_int(int *const a, const size_t l, const size_t r)
{
    if (l > r)
        error("left pointer is greater than right pointer");

    size_t n = r - l;

    int *copy;
    if ((copy = (int *)calloc(n, sizeof(int))) == NULL)
        error("failed to alloc arrayIntSubCopy");

    memcpy(copy, &a[l], n * sizeof(int));

    return copy;
}

int *array_int_copy(int *const a, const size_t n)
{
    return sub_array_int(a, 0, n);
}

char *padright(char *const x, const char p, const size_t m)
{
    const size_t nx = strlen(x);
    char *z;
    if ((z = (char *)calloc(nx + m + 1, sizeof(char))) == NULL)
        error("failed alloc of char pointer in padright");

    memcpy(z, &x[0], nx * sizeof(char));
    memset(&z[nx], p, m);
    z[nx + m] = '\0';

    return z;
}

char *padleft(char *const x, const char p, const size_t m)
{
    const size_t nx = strlen(x);
    char *z;
    if ((z = (char *)calloc(nx + m + 1, sizeof(char))) == NULL)
        error("failed alloc of char pointer in padleft");

    memset(z, p, m);
    memcpy(&z[m], x, nx * sizeof(char));
    z[nx + m] = '\0';

    return z;
}

char *substring(char *const x, const size_t l, const size_t r)
{
    if (l > r)
        error("left pointer is greater than right pointer");

    const size_t n = r - l;
    char *z;
    if ((z = (char *)calloc(n + 1, sizeof(char))) == NULL)
        error("failed alloc of char pointer in substring");

    memcpy(z, &x[l], n * sizeof(char));
    z[n] = '\0';

    return z;
}
