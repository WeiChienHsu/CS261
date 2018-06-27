# Learning Topic

## Abstract​ ​data​ ​types​ ​(ADTs)​ ​vs.​ ​data​ ​structures. 

ADTs​ ​are​ ​data​ ​types​ ​modeled​ ​from​ ​the​ ​point​ ​of​ ​view​ ​of​ ​the​ ​user. For​ ​example,​ ​a​ ​hash​ ​table​ ​can​ ​be​ ​implemented​ ​with​ ​either​ ​a list​ ​or​ ​an​ ​array.​ ​​ ​The​ ​user​ ​of​ ​the​ ​hash​ ​table​ ​doesn’t​ ​need​ ​to know​ ​(or​ ​care​ ​about)​ ​how​ ​it’s​ ​implemented,​ ​only​ ​how​ ​it behaves. 
Data​ ​structures​ ​are​ ​concrete​ ​representations​ ​of​ ​data,​ ​i.e.​ ​a​ ​data type​ ​from​ ​the​ ​point​ ​of​ ​view​ ​of​ ​the​ ​implementor. 

## Learning Outcomes

1. describe the properties, interfaces, and behaviors of basic abstract data types, such as collection, bag, indexed collection, sorted collection, stack, and queue.

2. read an algorithm or program code segment that contains iterative constructs and analyze the asymptotic time complexity of the algorithm or code segment.

3. state the asymptotic time complexity of the fundamental operations associated with a variety of data structures, such as vector, linked list, tree, and heap.

4. recall the space utilization of common data structures in terms of the long-term storage needed to maintain the structure, as well as the short-term memory requirements of fundamental operations, such as sorting. 

5. design and implement general-purpose, reusable data structures that implement one or more abstractions.

6. compare and contrast the operation of common data structures (such as linear structures, priority queues, tree structures, hash tables, maps, and graphs) in terms of time complexity, space utilization, and the abstract data types they implement .

***
## Algorithm vs Function

A function is a set of instructions written in a particular programming language. 

A function will often embody an algorithm, but the essence of the algorithm transcends the function, transcends even the programming language. 

The way to find square roots, and the details of the algorithm will remain the same no matter what programming language is used to write the code.


## Properties of Algorithm

### Input preconditions. 

The most common form of algorithm is a transformation that takes
a set of input values and performs some manipulations to yield a set of output values.
(For example, taking a positive number as input, and returning a square root).

The simplest of these is the idea of types, and a function type signature.

Some requirements cannot be captured by type signatures. A common example is a range
restriction. For instance, the square root program we discussed earlier only works for
positive numbers. Typically programs will check the range of their input at run-time, and
issue an error or exception if the input is not correct.


### Precise specification of each instruction. 
Each step of an algorithm must be well
defined. There should be no ambiguity about the actions to be carried out at any point. 

Using a pseudo-code form allows us to emphasize the important properties of the algorithm, and downplay incidental details that, while they may be necessary for a working program, do nothing to assist in the understanding of the procedure.

### Correctness. 
An algorithm is expected to solve a problem. 

### Termination, time to execute. 
It must be clear that for any input values the algorithm is guaranteed to terminate after a finite number of steps.


### Description of the result or effect. 
Finally, it must be clear exactly what the algorithm is intended to accomplish. Most often this can be expressed as the production of a result value having certain properties. 

The most obvious is the result type, defined as part of a function signature. But this only specifies the type
of the result, and not the relationship to the inputs. So equally important is some sort ofdocumentation, frequently written as a comment. In the min function given earlier it is noted that the result is not only an integer, but it also represents the smaller of the two input values.

***

## Recursive Algorithms

Recursion is a very common technique used for both algorithms and the functions that result from implementing algorithms. The basic idea of recursion is to “reduce” a complex problem by “simplifying” it in some way, then invoking the algorithm on the simpler problem. 

This is performed repeated until one or more special cases, termed 【base cases】, are encountered. Arguments that do not correspond to base cases are called 【recursive cases】, or sometimes inductive cases.


***

## Question

What is the activation record stack? What values are stored on the activation record stack? How does this stack simplify the execution of recursive functions?

```java
void printInteger(int n) {
  if(n > 9)
    printInteger(n / 10);
  printDigit(n % 10);
}
```
Previous values of n are left pending, stacked up so that they can be restored after the function returns. This is called the activation record stack. 

```
n = 4 Callend the fucntion idside second called function
n = 49 Called the functino inside first function
n = 499 First Called the function, value of n is equal 499 in that stack
```
***

# Correctness (Debugging, Testing and Proving)

## Hints on Debugging

- Test small sections of a program in isolation. 
- When you see an error produced for a given input, try to find the simplest input that consistently reproduces the same error.
- Think about what occurs before the point the error is noticed. An incorrect result is simply the symptom, and you must look earlier to find the cause.
- Use breakpoints or print statements to view the state of the computation in the middle.
- Don’t assume that just because one input is handled correctly that your program is correct.
- Use assertions and invariants to reason logically about your program.

## Assertions and Invariants

An assertion is simply a comment that explains what you know to be true when execution reaches a specific point in the program. Assertions can include information you know from a specific statement, as well as information you know from tracing a flow of control.

Assertions become most useful when they are combined with loops. An assertion inside a loop is often termed an invariant, since it must describe a condition that does not vary during the course of executing the loop.

The assertion statement, on the other hand, takes as argument an expression, and typically will halt execution and print an error message if the statement is not true. Because assertion statements are executed at run time, and halt execution if they are not satisfied, they should be used sparingly, but can be useful during debugging.

```java
double sqrt(double val) {
  assert (val >= 0); /* Halt execution if value is not legal */
}
```

## Testing and Boundary Cases

### Unit Testing

Test individual functions before you have a working application. This is termed unit testing.

A special purpose main method used in testing is termed a test harness. The test harness will feed one or more values into the function under test, and check the result.

Never content yourself with just one test case. A single test case cannot exercise all the possible ways a function can be used. As you develop test cases, think about the input data. If there are limits to the data, try to exercise values that are just at the edge of the limits.

```c
int main ( ) {
 double test1 [ ] = {1.0, 2.0, 3.0}; /* smallest first */
 double test2 [ ] = {3.0, 2.0, 1.0}; /* smallest last */
 double test3 [ ] = {2.0, 1.0, 3.0}; /* smallest middle */
 double test4 [ ] = {3.0, 1.0, 1.0, 2.0}; /* repeated smallest */
 double test5 [ ] = { }; /* no elements */
 double t1, t2, t3, t4, t5;
 t1 = min(test1, 3);
 t2 = min(test2, 3);
 t3 = min(test3, 3);
 t4 = min(test4, 4);
 printf(“test cases 1, 2, 3, and 4: %g %g %g %g \n”, t1, t2, t3, t4);
 t5 = min(test5, 0); /* should generate assertion error */
  printf(“test case 5: %g \n”, t5);
 return 0;
}
```

### Integration Testing

Once you are convinced that individual functions are working correctly, the next step is to combine calls on functions into more complex programs.

### Regression testing

Once you fix these you should go back and re-execute the earlier test harness to ensure that the changes have not inadvertently introduced any new errors. 

### Black box testing

Testing considers only the structure of the input and output values, and ignores the
algorithm used to produce the result. 

### White box testing
Consider the structure of the function, for example to ensure that every if statement is exercised both with a value that makes it true and a value that makes it false. Goals for white box testing should include that every
statement is executed, and that every condition is evaluated both true and false. 

***


***

# Big O notation 

[big-O notation(Stack Overflow)](https://stackoverflow.com/questions/2307283/what-does-olog-n-mean-exactly)


## O(1) - Constant

```
Best Case: Given the page that a
business's name is on and the 
business name, find the phone number.
```

Prints hello once and it doesn't depend on n, so it will always run in constant time, so it is O(1).

```java
print "hello";
```

Even prints hello 3 times, however it does not depend on an input size. Even as n grows, this algorithm will always only print hello 3 times. That being said 3, is a constant, so this algorithm is also O(1).

```java
print "hello";
print "hello";
print "hello";
```

## O(log(n)) - Logarithmic

```
Given a person's name, find the 
phone number by picking a random 
point about halfway through the 
part of the book you haven't searched 
yet, then checking to see whether 
the person's name is at that point. 

Then repeat the process about halfway 
through the part of the book where 
the person's name lies. (This is a 
binary search for a person's name.)
```

an algorithm that runs in log_2(n). Notice the post operation of the for loop multiples the current value of i by 2, so i goes from 1 to 2 to 4 to 8 to 16 to 32。

``` java
for(int i = 1; i <= n; i = i * 2)
  print "hello";
```

## O(n) - Linear Time

```
O(n): Find all people whose phone 
numbers contain the digit "5".

O(n): Given a phone number, find 
the person or business with 
that number.
```

This algorithm is simple, which prints hello n times.

```java
for(int i = 0; i < n; i++)
  print "hello";
```

This algorithm shows a variation, where it will print hello n/2 times. n/2 = 1/2 * n. We ignore the 1/2 constant and see that this algorithm is O(n).

```java
for(int i = 0; i < n; i = i + 2)
  print "hello";
```

## nlog(n) 

```
There was a mix-up at the 
printer's office, and our phone 
book had all its pages inserted 
in a random order. Fix the ordering 
so that it's correct by looking 
at the first name on each page and 
then putting that page in the 
appropriate spot in a new, empty 
phone book.
```

Think of this as a combination of O(log(n)) and O(n). The nesting of the for loops help us obtain the O(n*log(n))

```java
for(int i = 0; i < n; i++)
  for(int j = 1; j < n; j = j * 2)
    print "hello";
```


## O(n^2) - n squared 
```
A mistake occurred at the office, and
every entry in each of the phone books
has an extra "0" at the end of the 
phone number. Take some white-out 
and remove each zero.
```

O(n^2) is obtained easily by nesting standard for loops.

```java
for(int i = 0; i < n; i++)
  for(int j = 0; j < n; j++)
    print "hello";
```

## O(n^3) - n cubed


```java
for(int i = 0; i < n; i++)
  for(int j = 0; j < n; j++)
    for(int k = 0; k < n; k++)
      print "hello";
```

```java
for(int i = 0; i < n; i++)
  for(int j = 0; j < n + 5; j = j + 2)
    for(int k = 0; k < n; k = k + 3)
      print "hello";
```

***
## Discussion 

- O(log(n)): Since it cut the line to the half.

```java
for(int i = n; i > 0; i = i / 2) {
  print(i);
}
```
```
if n = 10, output will be:

10, 5, 2, 1, 0
```

- O(sqrt(n)): Since j < squrt(n).

```java
for(int j = 0; j * j < n; j++)
```


***


| Function | Common Name |
|:--------:|:-----------:|
| N!       | Factorial   |
| 2^n      | Exponential |
| N^d      | Polynomial  |
| N^3      | Cubic       |
| N^2 square| Quadratic   |
| N sqrt n |             |
| N log n  |             |
| N        | Linear      |
| sqrt(n) square root| Root-in     |
| Log n    | Logarithmic |
| 1        | Constant    |
