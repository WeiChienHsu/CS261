#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "DynArr.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

int _binarySearch(TYPE *data, int size, TYPE testValue) {
  int low = 0;
  int high = size;
  int mid;
  while(low < high) {
    mid = low + (high - low) / 2;
    if(data[mid] < testValue) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}

int dyArrayBinarySearch(struct DynArr *da, TYPE testValue) {
  return _binarySearch(da -> data, da -> size, testValue);
}

void orderedArrayAddAt(struct DynArr *da, TYPE newElement) {
  int index = _binarySearch(da -> data, da -> size, newElement);
  putDynArr(da, index, newElement);
}

int orderedArrayContains(struct DynArr *da, TYPE testElement) {
  int index = _binarySearch(da -> data, da -> size, testElement);
  if(index < da -> size && (testElement == da -> data[index])) {
    return 1;
  }
  return 0;
}

void orderedArrayRemove(struct DynArr *da, TYPE testElement) {
  int index = _binarySearch(da -> data, da -> size, testElement);
  if(index < da -> size && (testElement == da -> data[index])) {
    removeAtDynArr(da, index);
  }
}

void orderedArrayPrint(struct DynArr *da) {
  for(int i = 0; i < da -> size; i++) {
    printf(" %d \n", getDynArr(da, i));
  }
  printf(" \n");
}

int main() {
  struct DynArr *arr = newDynArr(10);
  addDynArr(arr, 10);
  addDynArr(arr, 20);
  addDynArr(arr, 30);
  addDynArr(arr, 40);
  addDynArr(arr, 50);
  addDynArr(arr, 60);
  orderedArrayPrint(arr);
  orderedArrayAddAt(arr,25);
  orderedArrayAddAt(arr,32);
  orderedArrayRemove(arr,20);
  orderedArrayRemove(arr,40);
  orderedArrayRemove(arr,10);
  orderedArrayPrint(arr);



  return 0;
}