#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>

#define LEN(a) (size_t)(sizeof(a) / sizeof(a[0]))
#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define FRAC(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); ((1.0L * _a)/(1.0L * _b)); })

void error(char *const);
int mod(const int, const int);

void print_array_int(int *const, const size_t, char *const);
int *sub_array_int(int *const, const size_t, const size_t);
int *array_int_copy(int *const, const size_t);
char *substring(char *const, const size_t, const size_t);
char *padleft(char *const, const char, const size_t);
char *padright(char *const, const char, const size_t);

#endif /* UTILS_H_ */