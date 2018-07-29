# Review Midterm

- [Worksheet 0 ADT Array](#worksheet-0-adt-array)
- [Worksheet 14 Dynamic Array](#worksheet-14-dynamic-array)
- [Worksheet 17 Linked List Stack](#worksheet-17-linked-list-stack)
- [Worksheet 18 Linked List Queue](#worksheet-18-linked-list-queue)
- [Worksheet 20 Dynaic Array Deque and Queue](#worksheet-20-dynaic-array-deque-and-queue)
- [Worksheet 23 Iterator](#worksheet-23-iterator)
- [Worksheet 24 LinkedList Iterator](#worksheet-24-linkedlist-iterator)

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

# Worksheet 17 Linked List Stack
- struct Link *newLink =(struct Link*) malloc(sizeof(struct Link));
- firstLink 本身的 Default Value 是 NULL，return firstLink -> value 就是 HEAD，不額外使用firstLink當作一個DummyNode，把它當作指針。
- 注意 Stack pop 和 push 的實踐。

```c
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Link {
  int value;
  struct Link *next;
};

struct LinkedListStack {
  struct Link *firstLink;
};

void LinkedListStackInit(struct LinkedListStack *s) {
  s -> firstLink = NULL;
}

int LinkedListStackIsEmpty(struct LinkedListStack *s) {
  if(s -> firstLink  == NULL) {
    return 1;
  }
  return 0;
}

void LinkedListStackPop(struct LinkedListStack *s) {
  assert(s -> firstLink != NULL);
  struct Link *temp = s -> firstLink;
  s -> firstLink  = s -> firstLink -> next;
  temp -> next = NULL;
  free(temp);
}

void LinkedListStackFree(struct LinkedListStack *s) {
  while(!LinkedListStackIsEmpty(s)) {
    LinkedListStackPop(s);
  }
}

void LinkedListStackPush(struct LinkedListStack *s, int v) {
  struct Link *newLink =(struct Link*) malloc(sizeof(struct Link));
  newLink -> value = v;
  newLink -> next = s -> firstLink;
  s -> firstLink  = newLink;
}

int LinkedListStackTop(struct LinkedListStack *s) {
  return s -> firstLink  -> value;
}

void LinkedListStackPrint(struct LinkedListStack *s) {
  while(!LinkedListStackIsEmpty(s)) {
    printf("%d \n", LinkedListStackTop(s));
    LinkedListStackPop(s);
  }
}
```

# Worksheet 18 Linked List Queue
- FirstLink 和 LastLink 初始化時，都指向 lnk 一個沒有自帶value的 Link
- AddBack: 改變 LastLink 的 next，並改變 LastLink 指向的 Link
- PopFirst: 改變 FirstLink 指向的點，記得判斷是否直接指向空，要改變 LastLink，free temp pointer

```c
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Link {
  int value;
  struct Link *next;
};

struct LinkedListQueue {
  struct Link *firstLink;
  struct Link *lastLink;
};

void LinkedListQueueInit(struct LinkedListQueue *q) {
  struct Link *lnk = malloc(sizeof(struct Link));
  assert(lnk != 0);
  lnk -> next = 0;
  q -> firstLink = lnk;
  q -> lastLink = lnk;
}

int LinkedListQueueIsEmpty(struct LinkedListQueue *q) {
  if(q -> firstLink == q -> lastLink) {
    return 1;
  }
  return 0;
}

void LinkedListQueueAddBack(struct LinkedListQueue *q, int v) {
  /* Create New List */
  struct Link *newLink = malloc(sizeof(struct Link));
  newLink -> next = 0;
  newLink -> value = v;
  q -> lastLink -> next = newLink;
  q -> lastLink = newLink;
}

void LinkedListQueuePopFirst(struct LinkedListQueue *q) {
  struct Link *temp = q -> firstLink -> next;
  q -> firstLink -> next = temp -> next;
  if(q -> firstLink -> next == 0) {
    q -> lastLink = q -> firstLink;
  }
  free(temp);
}

int LinkedListQueueFront(struct LinkedListQueue *q) {
  assert(!LinkedListQueueIsEmpty(q));
  return q -> firstLink -> next -> value;
}

void LinkedListQueuePrint(struct LinkedListQueue *q) {
  while(!LinkedListQueueIsEmpty(q)) {
    printf("%d \n", LinkedListQueueFront(q));
    LinkedListQueuePopFirst(q);
  }
}
```

# Worksheet 19 Linked List Deque
- Destory LinkedList 的時候，記得要把 frontSentinel 還有 backSentinel 以及 list pointer free.
- 用 addLinkBefore / removeLink 來實現所有 front, back, specific Link 的 add / remove

```c
void linkedListAddFront(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> frontSentinel -> next, value);
}

void linkedListAddBack(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> backSentinel, value);
}
```

```c
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

struct LinkedList;

struct LinkedList* linkedListCreate();
void linkedListDestroy(struct LinkedList* list);
void linkedListPrint(struct LinkedList* list);

// Deque interface

int linkedListIsEmpty(struct LinkedList* list);
void linkedListAddFront(struct LinkedList* list, TYPE value);
void linkedListAddBack(struct LinkedList* list, TYPE value);
TYPE linkedListFront(struct LinkedList* list);
TYPE linkedListBack(struct LinkedList* list);
void linkedListRemoveFront(struct LinkedList* list);
void linkedListRemoveBack(struct LinkedList* list);

// Bag interface

void linkedListAdd(struct LinkedList* list, TYPE value);
int linkedListContains(struct LinkedList* list, TYPE value);
void linkedListRemove(struct LinkedList* list, TYPE value);

```

```c

#include "LinkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};


void init(struct LinkedList* list) {
  list -> frontSentinel = (struct Link*) malloc(sizeof(struct Link));
  list -> backSentinel = (struct Link*) malloc(sizeof(struct Link));
  list -> frontSentinel -> next = list ->backSentinel;
  list -> frontSentinel -> prev = NULL;
  list -> backSentinel -> prev = list -> frontSentinel;
  list -> backSentinel -> next = NULL;
  list -> size = 0;
}

static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value) {
  struct Link* newLink = (struct Link *)malloc(sizeof(struct Link));
  newLink ->value = value;
  newLink -> prev = link -> prev;
  link -> prev -> next = newLink;
  link -> prev = newLink;
  newLink -> next = link;

  list -> size ++;
}

static void removeLink(struct LinkedList* list, struct Link* link) { 
  assert(list != 0);

  link -> prev -> next = link -> next;
  link -> next -> prev = link -> prev;

  link -> prev = NULL;
  link -> next = NULL;
  link -> value = 0;
  free(link);

  list -> size -- ;
}

struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}


int linkedListIsEmpty(struct LinkedList* list) {
  if(list -> frontSentinel == list -> backSentinel) {
    return 1;
  }
  return 0;
}

void linkedListDestroy(struct LinkedList* list) {
  while(!linkedListIsEmpty(list)) {
    linkedListRemoveBack(list);
  }

  free(list -> frontSentinel);
  free(list -> backSentinel);
  free(list);
}

void linkedListPrint(struct LinkedList* list) {
	assert(list -> size != 0);
	struct Link *cur = list -> frontSentinel -> next;
	/* While the current pointer doesn't mean the end */
	while(cur != list -> backSentinel) {
		printf("%d \n", cur -> value);
		cur = cur -> next;
	}
}

void linkedListAddFront(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> frontSentinel -> next, value);
}

void linkedListAddBack(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> backSentinel, value);
}

TYPE linkedListFront(struct LinkedList* list) {
  return list -> frontSentinel -> next -> value;
}

TYPE linkedListBack(struct LinkedList* list) {
  return list -> backSentinel -> prev -> value;
}

void linkedListRemoveFront(struct LinkedList* list) {
  removeLink(list, list -> frontSentinel -> next);
}

void linkedListRemoveBack(struct LinkedList* list) {
  removeLink(list, list -> backSentinel -> prev);
}


void linkedListAdd(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> backSentinel, value);
}

int linkedListContains(struct LinkedList* list, TYPE value) {
  assert(list -> size != 0);
  struct Link *cur = list -> frontSentinel -> next;
  while(cur != list -> backSentinel) {
    if(cur -> value == value) {
      return 1;
    }
    cur = cur -> next;
  }
  return 0;
}

void linkedListRemove(struct LinkedList* list, TYPE value) {
  assert(list -> size != 0);
  struct Link *cur = list -> frontSentinel -> next;
  while(cur != list ->backSentinel) {
    if(cur -> value == value) {
      removeLink(list, cur);
      cur = list -> backSentinel;
    } else {
      cur = cur -> next;
    }
   }
}
```

# Worksheet 20 Dynaic Array Deque and Queue
- AddFront begin往前移動 ->begin index = d -> begin - 1 < 0 ? d -> capacity - 1 : d -> begin - 1;
- AddBack -> end index = (d -> begin + d -> size) % d -> capacity
- RemoveFront begin往後移動 -> begin index = d -> begin + 1 >= d -> capacity ? 0 : d -> begin + 1;
- RemoveBack -> end index = (d -> begin + d -> size - 1) % d -> capacity

- 擴增 Dynamic Array 的時候，重新佈置 begin == 0，elements copy 到新 Array 內。

```c
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
```

```c
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
  if(d -> size >= d -> capacity) {
    _dequeSetCapacity(d, 2 * d -> capacity);
  }
  
  int index = (d -> begin + d -> size) % d -> capacity;
  d -> size ++;
  d -> data[index] = value;
}

void dequeRemoveFront(struct deque *d) {
  if(d -> begin + 1 >= d -> capacity) {
    d -> begin = 0;
  } else {
    d -> begin++;
  }
  d -> size--;
}

void dequeRemoveBack(struct deque *d) {
  d -> size --;
}

int dequeFront(struct deque *d) {
  return d -> data[d -> begin];
}

int dequeBack(struct deque *d) {
  return d -> data[d -> begin + d -> size - 1];
}

void dequePrint(struct deque *d) {
  while(d -> size != 0) {
    printf("%d \n", dequeFront(d));
    dequeRemoveFront(d);
  }
}
```

# Worksheet 23 Iterator
- The first initializes the iterator, associating it with the container it will iterate over. 
- The function hasNext returns true if there are more elements, false otherwise. 
- The function next returns the current element.
- The function remove can be used to remove the element last returned by next.



# Worksheet 24 LinkedList Iterator