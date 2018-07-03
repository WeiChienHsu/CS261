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


***


***


***


***