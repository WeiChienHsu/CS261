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

