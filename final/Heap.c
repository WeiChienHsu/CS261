TYPE dyArrayGet(DyArray *heap, int index);
void dyArrayPut(DyArray *heap, int index, int value);
void dyArrayAdd(DyArray *heap, int newValue);
void dyArrayRemoveAt(DyArray *heap, int index);
int dyArraySize(DyArray *heap);


void adjustHeap(struct DyArray *heap, int max, int pos) {
  int leftChild = pos * 2 + 1;
  int rightChild = pos * 2 + 2;

  if(max > rightChild) {
    /* There are two children */
    /* Find the smaller one between two children */
    int smallestChild = findSmallesChild(heap, leftChild, rightChild);
    if(dyArrayGet(smallestChild) < dyArrayGet(pos)) {
      swap(heap, smallestChild, pos);
      adjustHeap(heap, max, smallestChild);
    }
  }
  else if(max > leftChild) {
    /* There is only left child */
    /* Compare with the left child and see if it need to be swap */
    if(dyArrayGet(leftChild) < dyArrayGet(pos)) {
      swap(heap, leftChild, pos);
      adjustHeap(heap, max, leftChild);
    }
  }
  /* There is no child: Do nothing */
}

int findSmallesChild(DyArray * heap, int left, int right) {
  if(dyArrayGet(heap, left) > dyArrayGet(heap, right)) {
    return right;
  }
  else {
    return left;
  }
}

void swap(struct DyArray * heap, int i, int j) {
  int temp = dyArrayGet(heap, i);
  dyArrayPut(heap, i, dyArrayGet(j));
  dyArrayPut(heap, j, temp);
}

void heapAdd(struct DyArray *heap, int newValue) {
  int pos = dyArraySize(heap);
  dyArrayAdd(heap, newValue);
  int parent = (pos - 1) / 2;
  while(pos != 0) {
    if(dyArrayGet(parent) < dyArrayGet(pos)) {
      swap(heap, pos, parent);
      pos = parent;
    } else {
      return;
    }
  }
}

void heapRemoveFirst(struct DyArray *heap) {
  /* Remove the last element and replace that value to the first element */
  int last = dyArraySize(heap) - 1;
  int lastValue = dyArrayGet(last);
  dyArrayRemoveAt(heap, last);
  dyArrayPut(heap, 0, lastValue);
  adjustHeap(heap, last, 0); /* Reheaping */
}

int heapGetMin(struct DyArray* heap) {
  assert(dyArraySize(heap) > 0);
  return dyArrayGet(heap, 0);
}