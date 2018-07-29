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

struct dynArrIterator {
  struct DynArr *da;
  int currentIndex;
};



void dynArrIteratorInit(struct DynArr *da, struct dynArrIterator *itr) {
  itr -> da = da;
  itr -> currentIndex = 0;
}

int dynArrIteratorHasNext(struct dynArrIterator *itr) {
  return (itr -> currentIndex < itr -> da -> size);
}

int dynArrIteratorNext(struct dynArrIterator *itr) {
  return (itr -> da -> data[itr -> currentIndex ++]);
}

void dynArrIteratorRemove(struct dynArrIterator *itr) {
  removeAtDynArr(itr -> da, itr -> currentIndex);
  itr -> currentIndex --;
}

int main() {
  struct DynArr *arr;
  struct dynArrIterator *itr = (struct dynArrIterator *) malloc(sizeof(struct dynArrIterator));

  initDynArr(arr, 10);
  pushDynArr(arr, 12);
  pushDynArr(arr, 30);
  pushDynArr(arr, 40);

  dynArrIteratorInit(arr, itr);

  while(dynArrIteratorHasNext(itr)){
    printf("%d \n", dynArrIteratorNext(itr));
  }

 
  return 0;
}