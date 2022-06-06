#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void __msort_merge(void *_Nonnull base,
                          const size_t l,
                          const size_t r,
                          const size_t width,
                          int (*_Nonnull compar)(const void *_Nonnull, const void *_Nonnull))
{
    const size_t nL = (r - l) / 2;
    const size_t nR = (r - l) - nL;

    void *base_l;
    if ((base_l = calloc(nL, width)) == NULL)
    {
        fprintf(stderr, "err: failed to allocate memory for base_l in __msort_merge\n");
        exit(EXIT_FAILURE);
    }
    memcpy(base_l, base + l * width, nL * width);

    void *base_r;
    if ((base_r = calloc(nR, width)) == NULL)
    {
        fprintf(stderr, "err: failed to allocate memory for base_r in __msort_merge\n");
        exit(EXIT_FAILURE);
    }
    memcpy(base_r, base + (l + nL) * width, nR * width);

    int i = 0, j = 0, k = l;
    // compare left and right elements using compar(void*,void*)
    while (i < nL && j < nR)
    {
        if (compar(base_l + i * width, base_r + j * width) < 0)
            memcpy(base + (k++) * width, base_l + (i++) * width, width);
        else
            memcpy(base + (k++) * width, base_r + (j++) * width, width);
    }
    // add left elements
    memcpy(base + k * width, base_l + i * width, (nL - i) * width);
    // shift pointer to account the copy of the remainder of left elements
    k += nL - i;
    // add right elements
    memcpy(base + k * width, base_r + j * width, (nR - j) * width);

    free(base_l);
    free(base_r);
}

static void __msort_rec(void *_Nonnull base,
                        const size_t l,
                        const size_t r,
                        const size_t width,
                        int (*_Nonnull compar)(const void *_Nonnull, const void *_Nonnull))
{
    if (r - l > 1)
    {
        const size_t m = l + (r - l) / 2;

        __msort_rec(base, l, m, width, compar);
        __msort_rec(base, m, r, width, compar);

        __msort_merge(base, l, r, width, compar);
    }
}

void msort(void *_Nonnull base,
             const size_t nel,
             const size_t width,
             int (*_Nonnull compar)(const void *_Nonnull, const void *_Nonnull))
{
    __msort_rec(base, 0, nel, width, compar);
}