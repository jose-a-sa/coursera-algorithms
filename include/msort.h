#ifndef MSORT_H_
#define MSORT_H_

#include <stdlib.h>

static void __msort_merge(void *_Nonnull,
                          const size_t,
                          const size_t,
                          const size_t,
                          const size_t,
                          int (*_Nonnull)(const void *_Nonnull, const void *_Nonnull));
                          
static void __msort_rec(void *_Nonnull,
                        const size_t,
                        const size_t,
                        const size_t,
                        int (*_Nonnull)(const void *_Nonnull, const void *_Nonnull));

void msort(void *_Nonnull,
           const size_t,
           const size_t,
           int (*_Nonnull)(const void *_Nonnull, const void *_Nonnull));

#endif /* MSORT_H_ */