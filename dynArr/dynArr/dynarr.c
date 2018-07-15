//
//  dynarr.c
//  dynArr
//
//  Created by weichien on 02/07/2018.
//  Copyright © 2018 WeiChien. All rights reserved.
//

#include "dynarr.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void initDynArr(struct DynArr *v, int cap) {
    v->data = malloc(cap * TYPE_SIZE);
    assert(v->data != 0);
    v->size = 0;
    v->cap = cap;
}

void freeDynArr(struct DynArr *v) {
    if(v->data != 0) {
        free(v->data);
        v->data = 0;
    }
    v->cap = 0;
    v->size = 0;
}
