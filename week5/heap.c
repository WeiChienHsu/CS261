TYPE dyArrayGet(DyArray *heap, int index);
void dyArrayPut(DyArray *heap, int index, int value);
void dyArrayAdd(DyArray *heap, int newValue);
void dyArrayRemoveAt(DyArray *heap, int index);
int dyArraySize(DyArray *heap);


/**************************************************************
 * adjustHeap
 * Adjust the minHeap by checking if input position is smaller 
 * than its children.
 * There are three situations of Child:
 * 1. Have two children 
 * 2. Only have one child
 * 3. no Child
 * If value of parent larger than its child, swap their value and 
 * reheap the current child with its children recursively until 
 * this Heap maintained balanced. 
 **************************************************************/

void adjustHeap(struct dyArray * heap, int max, int pos) {
  int leftChild = 2 * pos + 1;
  int rightChild = 2 * pos + 2;

  /* Right Child < max -> Have two children */
  if(rightChild < max) {
    /* Get index of smallest child */
    int smallerChild = indexSmallest(heap, leftChild, rightChild);
    if(dyArrayGet(heap, pos) > dyArrayGet(heap, smallerChild)) {
      swap(heap, pos, smallerChild);
      adjustHeap(heap, max, smallerChild);
    }
  }
  /* Only have one child */
  else if(leftChild < max) {
    if(dyArrayGet(heap, pos) > dyArrayGet(heap, leftChild)) {
      swap(heap, pos, leftChild);
      adjustHeap(heap, max, leftChild);
    }
  } 
} 

void swap(struct dyArray * arr, int i, int j) {
  TYPE temp = dyArrayGet(arr, i);
  dyArrayPut(arr, i, dyArrayGet(arr, j));
  dyArrayPut(arr, j, temp);
}

int indexSmallest(struct dyArray* arr, int i, int j) {
  /* return index of smallest element */
  if(LT(dyArrayGet(arr, i), dyArrayGet(arr, j))){
    return i;
  }
  return j;
}

/**************************************************************
 *  heapAdd
 *  Add a new value in the last element of exist array.
 *  Comparing the value with its parents and reheap this element
 *  to the correct position to maintain the balance of the Heap.
 **************************************************************/

void heapAdd(struct dyArray *heap, TYPE newValue) {
  dyArrayAdd(heap, newValue); /* Add a new Node in the end */

  /* Adjust the new node with its parent until the root maintained the min element */
  int pos = dyArraySize(heap);
  int parent;

  while(pos != 0) {
    parent = (pos - 1) / 2;
    if(dyArrayGet(heap, pos) < dyArrayGet(heap, parent)) {
      swap(heap, pos, parent);
      pos = parent;
    } else {
      return;
    }
  }
}

void heapRemoveFirst(struct dyArray *heap) {
  /* Replace the root value by the value of last element */
  int last = dyArraySize(heap) - 1;
  assert(dyArraySize(heap) > 0);

  dyArrayPut(heap, 0, dyArrayGet(heap, last));
  dyArrayRemoveAt(heap, last); /* Remove the last element */
  adjustHeap(heap, last, 0);  /* Reheaping */
}


TYPE heapGetFirst(struct dyArray *heap) {
  assert(dyArraySize(heap) > 0);
  return dyArrayGet(heap, 0);
}
