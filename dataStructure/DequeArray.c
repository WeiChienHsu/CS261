struct deque {
  TYPE* data;
  int capacity;
  int size; 
  int begin;
}

void dequeInit(struct deque *d, int initCapacity) {
  d->size = d->begin = 0;
  d -> capacity = initCapacity;
  asset(initCapacity > 0);
  d -> data = (TYPE *) malloc (initCapacity * sizeof(TYPE));
  asset(data -> data != NULL)
}

void _dequeSetCapacity(struct deque *d, int newCap) {
  /* Create a new underlying array */
  TYEP *newArr = (TYPE*) malloc(sizeof(TYPE)* newCap);
  asset(newData != NULL)

  /* Copy element into it */
  int j = d -> begin;
  for(int i = 0; i < d -> size; i++) {
    newArr[i] = d -> data[j++];
    /* Restart from 0 */
    if(j >= d -> capacity) {
      j = 0;
    }
  }

  /* Delete the old underlying array */
  free(d -> data);

  d -> data = newData;
  d -> capacity = newCap;
  d -> begin = 0;
}

void dequeFree(struct deque *d) {
  free(d -> data);
  d -> size = 0;
  d -> capacity = 0; 
}

int dequeSize(struct deque *d) {
  return d -> size;
}

void dequeAddFront(struct deque *d, TYPE newValue) {
  if (d->size >= d->capacity) _dequeSetCapacity(d, 2*d->capacity);

  if (d -> begin == 0) {
      d -> data[d -> capacity - 1] = newValue;
      d -> begin = d -> capacity - 1;
      d -> size ++;
  } else {
    d -> data[d -> begin - 1] = newValue;
    d -> begin --;
    d -> size ++;
  }
}

void dequeAddBack (struct deque *d, TYPE newValue) {
  if (d->size >= d->capacity) _dequeSetcapacity(d, 2* d->capacity);
  int index = (d -> begin + d -> size) % d -> capacity;
  data[index] = newValue;
  d -> size++;
}

TYPE dequeFront (struct deque *d) {
    return d -> data[d -> begin];
}

TYPE dequeBack (struct deque *d) {
    int index = (d -> begin + d -> size - 1) % d -> capacity;
    return d -> data[index];
}

void dequeRemoveFront (struct deque *d) {
  if(d -> begin == d -> size - 1) {
    d -> begin = 0;
  } else {
    d -> begin ++;
  }
  d -> size --;
}

void dequeRemoveBack (struct deque *d) {
  d -> size --;
}