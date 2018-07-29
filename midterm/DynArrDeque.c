#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct deque {
  int *data;
  int capacity;
  int size;
  int begin;
};

void dequeInit(struct deque *d, int initCapacity) {
  d -> size = 0;
  d -> capacity = initCapacity;
  d -> data = (int *) malloc(initCapacity * sizeof(int));
  d -> begin = 0;
  assert(d -> data != 0);
}

int dequeSize(struct deque *d) {
  return d -> size;
}

void _dequeSetCapacity(struct deque *d, int newCapacity) {
  int *newDeque = (int *) malloc(sizeof(int) * newCapacity);
  int j = d -> begin;
  for(int i = 0; i < d -> size; i++) {
    newDeque[i] = d -> data[j];
    j++;
    if(j >= d -> capacity) {
      j = 0;
    }
  }

  free(d -> data);
  d -> data = newDeque;
  d -> begin = 0;
  d -> capacity = newCapacity;
}

void dequeAddFront(struct deque *d, int value) {
  if(d -> size >= d -> capacity) {
    _dequeSetCapacity(d, 2 * d -> capacity);
  }

  if(d -> begin == 0) {
    d -> begin = d -> capacity - 1;
  } else {
    d -> begin --;
  }

  d -> data[d -> begin] = value;
  d -> size ++;
}


void dequeAddBack(struct deque *d, int value) {

}

void dequeRemoveFront(struct deque *q) {

}

void dequeRemoveBack(struct deque *q) {

}

int dequeFront(struct deque *q) {

}

int dequeBack(struct deque *q) {
  
}