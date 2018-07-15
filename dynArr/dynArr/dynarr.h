#ifndef __DYNARR_H
#define __DYNARR_H

#define TYPE int
#define TYPE_SIZE sizeof(TYPE)

#define LT(a, b) ((a) < (b))
#define EQ(a, b) ((a) == (b))

#include <stdio.h>

struct DynArr {
    TYPE *data; /* Pointer to data array. */
    int size;
    int cap;
};

/* Dynamic Array Function */
void initDynArr(struct DynArr *v, int cap);
void freeDynArr(struct DynArr *v);
int sizeDynArr(struct DynArr *v);
void addDynArr(struct DynArr *v, TYPE e);
TYPE getDynArr(struct DynArr *v, int pos);
void putDynArr(struct DynArr *v, int pos, TYPE val);

#endif /* dynarr_h */
