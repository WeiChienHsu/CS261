# Abstract Data Type

## Container Abstractions
These container abstactions are now the funamental heart of the study of data structures.

Ex(bag, stack, queue, set, map, etc).

## Three Levels of Abstraction
- Specification/Interface : Properties and behaviors (what)
- Application: How it's used (why)
- Implementatino: The Various implementations in a particular library (how)

## Stack ADT
### Specification / Interface View - > in h file
- initStack()
- pushStack(val)
- valType topStack()
- popStack()
- bool isEmptyStack()

### Properties
A Stack is a collection that has the property that an item removed is the most recently entered item.

### Implementation
```c
void pushStack(struct Stack *stk, double val) {
  arrayAdd(stk->data, bal);
}
int stackIsEmpty(struct Stack *stk) {
  return(assaySize(stk->data) == 0);
}
```

***

# The Bag ADT

Application : Uaed in applications where you need to maintain an unordered collection of elements, without needing to know how it is organized.

Interface/ Bahavior Specification:
- Add(val)
- book Contains(val)
- Remove(val)

*** 

# Dynamic Arrays

## Arrays
Pro: only core data structure designed to hold a collection of elements / random access: can quickly get to any element -> O(1)

Con: fixed size.
- Maximum number of elements mush be specified when created.
- Often don't know much space needed until you're done.

## Dynamic Arrays (Vectir or ArrayList in Java)

- The Dynamic Array gets around this by encapsualting a partially filled array.
- Hide memory management details behinf a simple API
- Is still randomly accessible, but now it grows as necessary.

Can change its capacity:

### Size
is logical collection size:
- Current number of elements in the dynamic array
- What the programmer thinks of as the size of the collection
- Managed by an internal data value

### Capacity
is pysical array size: # of element it can hold before it must "resize".


## Behavior - Adding an element to 【end】 

Addint an element to end is usually easy -> Just increase the logical size and put new value at the end.

### What happens when size reaches capacity?

Must reallocate new data array - but this detail is hidden from user.

- Allocate new (Larger) array and copy valid data element (Double the size of capacity)
- Free up the old array 


## Behavior - Adding an element to 【middle】
- Adding an element to middle can also force reallocation (If the cuurent size is equal to capacity)

- But will ALWAYS require that elements be moved to make space. We want to maintain a contiguous chunk of data so we always know where the next element goes and can put it there quickly.

- Is therefore O(n) worst case. （Double capacity and copy while n array)

- Make space for new Value: Loop from bottom up while copting data.

```
1 | 2 | 3 | 4 | 5 |  |

** add element 6 behind 4

1. Copy 5 to the next

1 | 2 | 3 | 4 | 5 | 5 | 


2. Copy 4 to the next

1 | 2 | 3 | 4 | 4 | 5 | 

3. When we find the target inedx, Put element 6 in that position

1 | 2 | 3 | 6 | 4 | 5 | 
```

***

## Implmentation Of Dynamic Array

- How to make a general purpose container class?
- We defin TYPE as symbolic proprocessor constant.
- Requires recompiling source for new element types.

### Provide a header fule

```c
#ifndef __DYNARR_H
#define __DYNARR_H

#define TYPE int
#define TYPE_SIZE sizeof(TYPE)

#define LT(a, b) ((a) < (b))
#define EQ(a, b) ((a) == (b))

#include <stdio.h>

struct DynArr {
    TYPE *data; /* Pointer to data array. */
    int size;
    int cap;
};

/* Dynamic Array Function */
void initDynArr(struct DynArr *v, int cap);
void freeDynArr(struct DynArr *v);
int sizeDynArr(struct DynArr *v);
void addDynArr(struct DynArr *v, TYPE e);
TYPE getDynArr(struct DynArr *v, int pos);
void putDynArr(struct DynArr *v, int pos, TYPE val);

#endif /* dynarr_h */

```

### Better Solution - Hide the Struct inside the .c file (Source file)

To use a struct dynArr, the user must declare one. To declare it, the compiler must know its size when compiling that file.(ex, it must be in the header)

If it's in the header, it's 'exposed' to the end user and this can be dangerous and violates 'encapsulation'.

Better Solution: Provide new and delete functions for your data structure. New Returs a pointer to allocated space.

User can always decalare pointers and compiler always knows the size of a pointer! And we can hide the Struct in the .c fule or a library.

### When to use Dynamic Arrays
- Need random access
- Low memory footprint
- Don't know size of array at compile time
- See Examples in Java and C++ STL
- When should not use a dynamic array -> When O(n) resize is NEVER acceptable.

***

# Stack

Stack operations obey the last-in first out principles.

Remove all the items from a stack could access them in reverse order.

Use case: Web browser have Back and Forward buttons that allow the user to move backwards and forwards through a series of web page. Back button returns the browser to the previous web page. This works because browser is maintining a stack containing links to web pages.

## Operations
- Push(newEntry) - O(1) - Place a new element into the collection. The value provided becomes the new topmost item in the collection. No output associated with push operation.

- Pop() - O(1) - Remove the topmost item from the stack

- Top() - O(1) - Return but does not remove, the topmost item from the stack.

- isEmpty() - O(1) - Determines whether the stack is empty


## ADT

Stack is combined with other abstractions, such as a dynamic array. In this situation the data structure allows other operations, such as a search or direct access to elements.

- Java

```java
Stack<Integer> stack = new Stack<>();
stack.push(Integer);
stack.peek() // Return value of Integer
stack.pop(); // Pop Integer out
stack.isEmpty() // Return Rrue or False
```

- C++

```c++
Stack stack = new Stack();
stack.push(int);
stack.pop();
stack.top();
stack.isEmpty();
```

- Python

```python
stack = list[]
stack.append(value) # push
Del stack[-1] # pop
stack[-1] # top
len(stack) == 0 # empty
```

## Stack Implementaion - Web Browser

### Question 1

The user of a web browser can also move to a new page by selecting a hyperlink. In fact, this is probably more common than using either the back or forward buttons. When this happens how should the contents of the back and forward stacks be changed?

There are two different Stack. One is:

- Backward Stack: When you click a new hyperlink, or forward button, browser will store that page into this Stack.

- Forward Stack: When you click a backward button, the current browser will store in this Stack. But when user click another Link, this Stack will be empty.

### Question 2

Web browsers often provide a history feature, which records all web pages accessed in the recent past. How is this different from the back stack? 

Describe how the history should change when each of the three following conditions occurs: 

- (a) when the user moves to a new page by pressing a hyperlink?

Store current Page into Back Stack and Clean the Forward Stack

- (b) when the user restores an old page by pressing the back button?

Store current Page into Forward Stack and Pop out the Stack peek page.

- (c) when the user moves forward by pressing the forward button?

Store current Page into Back Stack and pop out the forward Stack page.


## Stack Implementaion - Buffer Character Input

Operating System uses a Stack in order to corrctly process backsapace keys in lines of input typed at a keyboard. 

```
abcaaa<<<d -> abcd
```

## Stack Implementaion - Activation Record Stack (Call Stack)

Image that b hsa the following recursive definiton:

```c
int b (int p)
  if(p < 15) return 1;
  else return 1 + b(p -1)
```

Each time the function b is invoked a new activation record is created.

```
P = 17 | P = 16 | P = 15 -> top of stack
```


## Building a Stack using a Dynamic Array

Array is a simple way to store a collection of values.

Only push the element in the last space with an constant amortized execution time. (Average O(1))


## Linked List Implementation of Stack

The Alternative implementation approach is to use a linked list with O(1) insert and delete time complexity in the Fist or Last element.

The advantage of the linked list that the collection can grow as large as necessary, and each new addition to the chain of linkes requires only a constant amount of work.

Each Node mantains two data fields, a value and a reference to anotehr link. The last linke in the sequence stores a null value in its link. (Whenever you create a dynamically allocated value you need to think about how and when it will be freed)

Because there are no big block (Not continuous) of memory, it is never necessary to copy an entire block from place to place.

```java
class ListNode {
  int val;
  ListNode next = null; // Default
  public ListNode(int val) {
    this.val = val;
  }
}

ListNode head = new ListNode(0);
ListNode current = head;
current.next = new ListNode(1);
current = current.next;
current.next = new ListNode(2);

return head; // Get 0 -> 1 -> 2 -> null

```

***

## Worksheet 17 Linked List Introduction, List Stack

```c++
struct link {
  TYPE value; 
  struct link * next;
};
```

```c
/* Single Linked List Structure */

struct Link {
  TYPE value;
  struct Link *next;
};

struct LinkedListStack {
  struct Link *firstLink;
}

void LinkedListStackInit(struct LinkedListStack * s) {
  s -> fitstLink = NULL;
}

/*
Note: Free gets rid of all links but keeps the firstLink of the list around, so
the list itself still exists and is initialized.
*/

void LinkedListStackFree(struct linkedListStack *s) {
  /* Check if the Stack is Empty */
  while(! linkedListStackIsEmpty(s)) {
    /* Keep poping elements inside (connected) the Stack */
    linkedListStackPop(s);
  }
}

/*
  ** Linked List is empty

    NULL
    f

    newLink(d) -> NULL
                  f

    newLink(d) -> NULL
    f   

  ** Listed List is no empty

    1  ->  2  ->  NULL
    f

    newLink(d)  ->  1  ->  2  ->  NULL
                    f
    
    newLink(d)  ->  1  ->  2  ->  NULL
    f
*/


void LinkedListStackPush (struct LinkedistStack *s, TYPE d) {
  /* Create a new link */
  struct Link * newLink = (struct Link *) malloc (sizeof(struct Link));

  assert(newLink != NULL);

  /* Assign a value to the new Link */
  newLink -> value = d;

  /* Point the next pointer from new Link to current first Link */
  newLink -> next = s -> firstLink;

  /* Move the first Link to the new created link */
   s -> fitstLink = newLink;
}


TYPE LinkedListStackTop (struct LinkedListStack *s) {
  assert(s -> firstLink != NULL);
  return s -> firstLink -> value;
}

void LinkedListStackPop (struct LinkedListStack *s) {
  assert(s -> firstLink != NULL);

  /* Store the reference of current top Link */
  Struct Link* poppedList = s -> firstLink;

  /* Move the first pointer to the next */
  s -> firstLink = s -> firstLink -> next;
  
  /* Cut the old first List out of current Linked List */
  poppedList -> next = NULL;

  /* Free the memory for both of next pointer and value */
  free(poppedList);
}

int LinkedListStackIsEmpty (struct LinkedListStack *s) {
  if(s -> firstLink == NULL) {
    return 1;
  } else {
    return 0;
  }
}
```

***

## Linked List Queue, pointer to Tail

```c
struct link {
  TYPE value;
  struct link *next;
};

struct listQueue {
  struct link *firstLink;
  struct link *lastLink; 
};

void listQueueInit(struct listQueue *q) {
  struct link *lnk = (struct link*) malloc(sizeof(struct link));
  assert(lnk != NULL); /* lnk is the sentinel */
  lnk -> next = NULL;
  q -> firstLink = q -> lastLink = lnk;
}

void listQueueAddBack(struct listQueue *q, TYPE e) {
  struct link *newLink = (struct link*) malloc(sizeof(struct link));
  assert(newLink != NULL);
  newLink -> value = e;
  newLink -> next = NULL;

  if(lnk -> next == NULL) {
    lnk.next = newList;
    q -> firstLink = newLink;
    q -> lastLink = newLink;
  } else {
    q -> lastLink -> next = newLink;
    q -> lastLink = q -> lastLink.next;
  }
}

TYPE listQueueFront(struct listQueue *q) {
  if(listQueuIsEmpty(q)) {
    return NULL;
  } else {
    return q -> firstLink -> value;
  }
}

TYPE listQueueRemoveFront(struct listQueue *q) {
  if(!listQueueIsEmpty(q)) {
    struct link * temp = (struct link *) malloc(sizeof(struct link));
    temp = q -> firstLink;
    q -> firstLink = q -> firstLink -> next;
    temp -> next = NULL;

    free(temp);
  }
}

int listQueueIsEmpty(struct listQueue *q) {
  if(q -> firstLink == q -> lastLink) {
    return 1;
  } else {
    return 0;
  }
}
```

## Linked List Deque

```java
struct dlink{
  TYPE value;
  struct dlink* next;
  struct dlink* prev;
};

struct linkedList {
  int size;
  struct dlink* frontSentinel;
  struct dlink* backSentinel;
}

void LinkedListLnit(struct linkedList *q) {
  q -> frontSentinel = (struct dlink *) malloc (sizeof(struct dlink));
  assert(q -> frontSentinel != NULL);
  q -> backSentinel = (struct dlink *) malloc (sizeof(struct dlink));
  assert(q -> backSentinel != NULL);
  q -> frontSentinel -> next = q -> backSentinel;
  q -> backSentinel -> next = q -> frontSentinel;
  q -> size = 0;
}

void LinkedLitFree(struct linkedList *q) {
  while(q -> size != 0) {
    linkedListRemoveFront(q);
  }
  free(q -> frontSentinel);
  free(q -> backSentinel);
  q -> frontSentinel = q -> backSentinel = NULL;
}

void _addLink(struct linkedList *q, struct dlink *lnk, TYPE e) {
    assert(q != NULL);
    struct dlink *newLink = malloc(sizeof(struct dlink));
    newLink -> value = e;

    /* Link the new sentinel */
    newLink -> prev = lnk -> prev;
    newLink -> next = lnk;

    /* Link the old sentinel */
    lnk -> prev = newLink;

    if(lnk != q -> backSentinel) {
      q -> frontSentinel -> next = newLink;
    }

    q -> size ++;

    
}

void _removeLink(struct linkedList *q, struct dlink *lnk) {
  assert(q != NULL)
  /* Remove lnk */
  lnk -> prev -> next = lnk -> next;
  lnk -> next -> prev = lnk -> prev;

  /* Unlink lnk */
  lnk -> prev = NULL;
  lnk -> next = NULL;

  /* Free Link */
  free(lnk);

  q -> size --;
}


void LinkedListAddFront (struct linkedList *q, TYPE e) { 
  _addLink(q, q -> frontSentinel->next, e); 
}

void LinkedListAddback (struct linkedList *q, TYPE e) { 
  _addLink(q, q -> backSentinel, e); 
}

void linkedListRemoveFront (struct linkedList *q) { 
  assert(! linkedListIsEmpty(q));
  _removeLink (q, q -> frontSentinal -> next);
}

void LinkedListRemoveBack (struct linkedList *q) { 
  assert(! linkedListIsEmpty(q));
  _removeLink (q, q -> backSentinel -> prev);
}
int LinkedListIsEmpty (struct linkedList *q) { 
  return q->size == 0;
}
```


## Dynamic Array Deque and Queue
```c
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
```


## Constructing a Bag using a Linked List