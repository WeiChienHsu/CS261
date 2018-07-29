#include <assert.h>
#include <stdlib.h>
#include "DynArr.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


void initDynArr(DynArr *v, int capacity) {
  v -> data = malloc(sizeof(TYPE) * capacity);
  assert(v -> data != NULL);
  v -> capacity = capacity;
  v -> size = 0;
}

DynArr *newDynArr(int cap) {
  assert(cap > 0);
  DynArr *arr = (DynArr *)malloc(sizeof(DynArr));
  initDynArr(arr, cap);
  return arr;
}

void freeDynArr(DynArr *v){
  if(v -> data != 0) {
    free(v -> data);
    v -> data = 0;
  }
  v -> capacity = 0;
  v -> size = 0;
}

void deleteDynArr(DynArr *v) {
  freeDynArr(v); /* Free the data stored in memeory */
  free(v);  /* Free the pointer points to DynArr */
}

void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	TYPE *temp = malloc(sizeof(TYPE) * newCap); /* Create a new array to hold copied elements */
	assert(temp != 0);

	/* Copy the original elements from data array in to temp one */
	for(int i = 0; i < v -> size; i++) {
		temp[i] = v -> data[i];
	}

	/* free the old array with the elelment which has been copied */
	free(v -> data);
	
	v -> data = temp;	/* Assign a new array for current DynArr */
	v -> capacity = newCap; /* Upgtade the capacity */
}

void addDynArr(DynArr *v, TYPE val) {
  if(v -> size >= v -> capacity) {
    _dynArrSetCapacity(v, 2 * v -> capacity);
  }

  v -> data[v -> size] = val;
  v -> size ++;
}


TYPE getDynArr(DynArr *v, int pos) {
  assert(v -> data != 0);
  return v -> data[pos];
}

void putDynArr(DynArr *v, int pos, TYPE val) {
  assert(v -> data != 0);
  assert(pos < v -> size);
  assert(pos > 0);
  if(v -> size >= v -> capacity) {
    _dynArrSetCapacity(v, 2 * v -> capacity);
  }
  for(int i = v -> size; i > pos; i--) {
    v -> data[i] = v -> data[i - 1];
  }

  v -> data[pos] = val;
  v -> size ++;
}


void swapDynArr(DynArr *v, int i, int  j) {
  assert(v -> data != 0);
  assert(i < v -> size);
  assert(j < v -> size);
  TYPE temp = v -> data[i];
  v -> data[i] = v -> data[j];
  v -> data[j] = temp;
}

void removeAtDynArr(DynArr *v, int idx) {
  assert(idx < v -> size);
  assert(idx >= 0);
  for(int i = idx; i < v -> size - 1; i++) {
    v -> data[i] = v -> data[i + 1];
  }
  v -> size--;
  v -> data[v -> size] = 0;
}




int isEmptyDynArr(DynArr *v) {
  if(v -> size == 0) {
    return 1;
  }
  return 0;
}

void pushDynArr(DynArr *v, TYPE val) {
  addDynArr(v, val);
}

TYPE topDynArr(DynArr *v) {
  return getDynArr(v, v -> size - 1);
}

void popDynArr(DynArr *v) { 
  removeAtDynArr(v, v -> size - 1);
}

int containsDynArr(DynArr *v, TYPE val) {
  for(int i = 0; i < v -> size; i++) {
    if(v -> data[i] == val) {
      return 1;
    }
  }
  return 0;
}

void removeDynArr(DynArr *v, TYPE val) {
  removeAtDynArr(v, getDynArr(v, val));
}

// int main() {
//   return 0;
// }