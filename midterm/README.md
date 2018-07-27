# Review Midterm

- [Worksheet 0 ADT Array](#worksheet-0-adt-array)
- [Worksheet 14 Dynamic Array](#worksheet-14-dynamic-array)

# Worksheet 0 ADT Array

- Remove 的時候，記得更新 struct arrayBagStack 內的 count.
- 記得 ADT 的 Functions 是怎麼寫的，要傳入 struct arrayBagStack的 pointer

```h
# ifndef ArrayBagStack
# define ArrayBagStack
# define MAX_SIZE 100

# define TYPE int
# define EQ(a, b) (a == b)

struct arrayBagStack {
  TYPE data [MAX_SIZE];
  int count;
};

/* Interface for Bag */
void initBag (struct arrayBagStack * b);
void addBag (struct arrayBagStack * b, TYPE v);
int containsBag (struct arrayBagStack * b, TYPE v);
void removeBag (struct arrayBagStack * b, TYPE v);
int sizeBag (struct arrayBagStack * b);
/* Interface for Stack */
void pushStack (struct arrayBagStack * b, TYPE v);
int topStack (struct arrayBagStack * b);
void popStack (struct arrayBagStack * b);
int isEmptyStack (struct arrayBagStack * b);
# endif
```

```c
# include "ArrayBagStack.h"
# include <stdio.h>


void initBag(struct arrayBagStack *b) {
  b -> count = 0;
}

void addBag(struct arrayBagStack *b, TYPE v) {
  b -> data[b -> count] = v;
  b -> count ++;
}

int containsBag (struct arrayBagStack * b, TYPE v) {
  // assert(b != NULL);
  for(int i = 0; i < b -> count; i++) {
    if(b -> data[i] == v) {
      return 1;
      printf("Found %d \n", v);
    }
  }
  return 0;
}

void removeBag (struct arrayBagStack * b, TYPE v) {
  // assert(b != NULL);
  if(containsBag(b, v) == 1) {
      for(int i = 0; i < b -> count; i++) {
        if(EQ(b -> data[i], v)) {
          for(int j = i; j < b ->count; j++) {
            b -> data[j] = b -> data[j + 1];
          }
        }
        printf("Removed  %d \n", v);
        b -> count--;
        break;  
      }
  }
  printf("Not Contained. \n");

}


int sizeBag (struct arrayBagStack * b) {
  return b -> count;
}

/* Interface for Stack */
void pushStack (struct arrayBagStack * b, TYPE v) {
  // assert(b != NULL);
  addBag(b, v);
}

int topStack (struct arrayBagStack * b) {
  return b -> data[b -> count - 1];
}
void popStack (struct arrayBagStack * b){
  removeBag(b, topStack(b));
}

int isEmptyStack (struct arrayBagStack * b){
  if(b -> count == 0) {
    return 1;
  }
  return 0;
}

int main() {
  struct arrayBagStack *stack;
  initBag(stack);
  printf("%d \n", containsBag(stack, 10));
  pushStack(stack,30);
  printf("%d \n", topStack(stack));
  pushStack(stack,40);
  pushStack(stack,50);
  popStack(stack);
  popStack(stack);
  isEmptyStack(stack);
  return 0;
}
```

***

# Worksheet 14 Dynamic Array
- 記得初始化是使用 malloc(sizeof(TYPE * capacity));
- put 操作記得檢查 Capacity，並且移動position以後的elements


```c
#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY_INCLUDED 1

#ifndef __TYPE
#define __TYPE
# define TYPE      char
# define TYPE_SIZE sizeof(int)
# endif

# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif

typedef struct DynArr DynArr;

/* Dynamic Array Functions */
void initDynArr(DynArr *v, int capacity);	
DynArr *newDynArr(int cap);

void freeDynArr(DynArr *v);
void deleteDynArr(DynArr *v);

int sizeDynArr(DynArr *v);

void addDynArr(DynArr *v, TYPE val);
TYPE getDynArr(DynArr *v, int pos);
void putDynArr(DynArr *v, int pos, TYPE val);
void swapDynArr(DynArr *v, int i, int  j);
void removeAtDynArr(DynArr *v, int idx);

/* Stack interface. */
int isEmptyDynArr(DynArr *v);
void pushDynArr(DynArr *v, TYPE val);
TYPE topDynArr(DynArr *v);
void popDynArr(DynArr *v);

/* Bag Interface */	
/* Note addDynArr is already declared above*/
int containsDynArr(DynArr *v, TYPE val);
void removeDynArr(DynArr *v, TYPE val);

#endif
```

```c
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

```