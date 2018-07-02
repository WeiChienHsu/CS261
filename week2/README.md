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




