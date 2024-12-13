#ifndef UINTEGER_H
#define UINTEGER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *digits;
    int sign; // 1 for positive, -1 for negative
} UInteger;

void uinteger_init(UInteger *num);
void uinteger_free(UInteger *num);
void uinteger_resize(UInteger *num, int new_size);
void uinteger_assign(UInteger *dest, const char *src);
void uinteger_add(UInteger *result, const UInteger *a, const UInteger *b);
void uinteger_subtract(UInteger *result, const UInteger *a, const UInteger *b);
int uinteger_compare(const UInteger *a, const UInteger *b);
void uinteger_print(const UInteger *num);

#endif