#ifndef MSORT_H_
#define MSORT_H_

#include <stdlib.h>

void msort(void *_Nonnull,
           const size_t,
           const size_t,
           int (*_Nonnull)(const void *_Nonnull, const void *_Nonnull));

#endif /* MSORT_H_ */