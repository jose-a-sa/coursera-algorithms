#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

char *strip_left_zeros(char *const x)
{
    const size_t nx = strlen(x);
    size_t zeros = 0;

    for (char *i = x; *i != '\0'; i++)
    {
        if (*i == '0')
            zeros++;
        else
            break;
    }

    if (nx <= zeros)
        return "0";

    return substring(x, zeros, nx);
}

char *karatsuba_add(char *const x, char *const y, const int sign)
{
    const int s = (sign < 0) ? -1 : 1;
    const size_t nx = strlen(x);
    const size_t ny = strlen(y);
    const size_t n = MAX(nx, ny) + 1;

    char *z0, *z;
    if ((z0 = (char *)calloc(n + 1, sizeof(char))) == NULL)
        error("failed alloc of char pointer in karatsuba_add");
    z0[n] = '\0';

    int sum, cx, cy;
    int carry = 0;
    for (int i = 0; i < n; i++)
    {
        cx = (i < nx) ? (int)(x[nx - 1 - i] - '0') : 0;
        cy = (i < ny) ? (int)(y[ny - 1 - i] - '0') : 0;
        sum = cx + s * (cy + carry);
        z0[n - 1 - i] = (char)(mod(sum, 10) + '0');
        carry = sum < 0 || sum >= 10;
    }

    if (carry && sign < 0)
        error("x < y when subtracting (sign<0) gives incorrect result\n");

    z = strip_left_zeros(z0);
    free(z0);

    return z;
}

char *karatsuba_mul(char *const x0, char *const y0)
{
    const size_t nx = strlen(x0);
    const size_t ny = strlen(y0);
    const size_t n = MAX(nx, ny);

    char *x, *y;
    x = padleft(x0, '0', n - nx);
    y = padleft(y0, '0', n - ny);

    if (n == 0) return "0";

    if (n == 1)
    {
        int res = (x[0] - '0') * (y[0] - '0');
        if (res == 0) return "0";

        char *z0, *z;
        if ((z0 = (char *)calloc(3, sizeof(char))) == NULL)
            error("failed alloc of char pointer in karatsuba_mul");
        z0[2] = '\0';

        sprintf(z0, "%02d", res);
        z = strip_left_zeros(z0);
        free(z0);

        return z;
    }

    const size_t m = n / 2;
    char *a = substring(x, 0, m);
    char *b = substring(x, m, n);
    char *c = substring(y, 0, m);
    char *d = substring(y, m, n);

    char *ac = karatsuba_mul(a, c);
    char *bd = karatsuba_mul(b, d);
    char *aPbcPd = karatsuba_mul(karatsuba_add(a, b, 1), karatsuba_add(c, d, 1));
    char *adPbc = karatsuba_add(aPbcPd, karatsuba_add(ac, bd, 1), -1);
    char *res = karatsuba_add(bd, karatsuba_add(padright(adPbc, '0', n - m), padright(ac, '0', 2 * (n - m)), 1), 1); 

    free(x);
    free(y);
    free(a);
    free(b);
    free(c);
    free(d);

    return res;
}

int main(int argc, const char *argv[])
{
    char *x = "3141592653589793238462643383279502884197169399375105820974944592";
    char *y = "2718281828459045235360287471352662497757247093699959574966967627";

    printf("  x: %s\n", x);
    printf("  y: %s\n", y);
    printf("x*y: %s\n", karatsuba_mul(x, y));

    exit(EXIT_SUCCESS);
}
