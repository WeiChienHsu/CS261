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
## Program Proof - Selection Sort as an example

Definition : Find the index of the largest element in an array. Swap the largest value into the final location in the array. Then do the same with the next largest element. Then the next largest, and so on until you reach the smallest element. At that point the array will be sorted.


The first asserts what must be true before the loop starts, and the last must be what we want to be true
after the loop finishes, which is normally the outcome we desire.

```java
double storage [ ];
 ...
int indexLargest = 0;
int position = n – 1;
// 1. indexLargest is the index of the largest element in the range 0 .. 0

for (int i = 1; i <= position; i++) {

  // 2. indexLargest is the index of the largest element in the range 0 .. (i-1)
 if (storage[i] > storage[indexLargest])
 indexLargest = i;

 // 3. indexLargest is the index of the largest element in the range 0 .. i
}

// 4. indexLargest is index of largest element in the range 0 .. (storage.length-1)
```


Finding the largest value is a task that must be performed repeatedly. It is first performed
to find the largest element in the array, and then the next largest, and then the one before
that, and so on. So again a loop seems to be called for. Since we are looking for the
largest value to fill a given position, let us name this loop variable position. The loop that
is filling this variable looks as follows:

```java
for (position = n – 1; position > 0; position--) {
 // find the largest element in 0 .. position
 int indexLargest = 0;
 ...
 // then swap into place
 swap(storage, indexLargest, position);
 // Noew indexLargest have the largest number in the memory
}
```
***

## Exponential and Logarithm Function

The exponential is the function you get by repeated multiplication. 

In computer science we almost always use powers of two, and so the exponential sequence is 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, and so on. 

The logarithm is the inverse of the exponential. It is the number that a base (generally 2) must be raised to in order to find a value. 

If we want the log (base 2) of 1000, for example, we know that it must be between 9 and 10. This is because 29 is 512, and 210 is 1024. Since 1000 is between these two values, the log of 1000 must be between 9 and 10. The log is a very slow growing function. The log of one million is less than 20, and the log of one billion is less than 30.

```
The log, base 2, of a value n is
approximately equal to the number of times that
n can be split in half. The word approximately is
used because the log function yields a fractional
value, and the exact figure can be as much as
one larger than the integer ceiling of the log. But
integer differences are normally ignored when
discussing asymptotic bounds
```

***

# Big O notation 


What a big-oh characterization of an algorithm does is to abstract away unimportant distinctions caused by factors such as different machines or different compilers. Instead, it goes to the heart of the key differences between algorithms. 

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


***

## Recursive Function

The analysis of recursive functions is slightly more complicated than the analysis of algorithms with loops. A useful technique is to describe the execution time using a recurrence relation. 

|Recyrrebce relactions|Time Complexity |
|:-------------------:|:--------------:|
|T(n) = T(n - 1) + c  | O(N) |
|T(n) = T(n / 2) + c  | O(logN) |
|T(n) = 2 * T(n / 2) + cn + c | O(nlogN)|
|T(n) = 2 * T(n - 1) + c| O(2^n) | 


## Proof of Binary Search Time Complexity
Through O(1) time, to change the problem scale of n into a scale of n/2.

```
T(n) = T(n/2) + O(1)
= T(n/4) + O(1) + O(1)
= T(n/8) + 3 * O(1)
= T(n/16) + 4 * O(1)
.
.
.
= T(1) + logn * O(1)

T(n) = O(logn)
```

Through O(n) time, to change the problem scale of n into a scale of n/2.

```
T(n) = T(n/2) + O(n)
= T(n/4) + O(n/2) + O(n)
= T(n/8) + O(n/4) + O(n/2) + O(n)
.
.
.
= T(1) + O(n + n/2 + n/4 + ...+ 2 + 1)
= O(2n - 1)
= O(n)
```

***

## Divide and Conquer

The general idea of dividing a problem into two roughly equal problems of the same form is known as the “divide and conquer” heuristic. We have earlier shown that the number of time a collection of size n can be repeatedly split in half is log n. Since log n is a very small value, this leads to many efficient algorithms. 


## Merge Sort O(nlogn)

### Merge Algorithm O(n)

For merge sort the key insight is that two already sorted arrays can be very rapidly merged together to form a new collection. All that is necessary is to walk down each of the original lists in order, selecting the smallest element in turn.

When you reach the end of one of the arrays (you cannot, in general, predict which list
will end first), you must copy the remainder of the elements from the other.
Based on this description you should now be able to complete the implementation of the
merge method. This you will do in worksheet 12. Let n represent the length of the result.
At each step of the loop one new value is being added to the result. Hence the merge
algorithm is O(n).

### Sort Algorithm (D&C) O(logn)

The key is to think recursively.

Imagine sorting as a three-step process. In the first step an unordered array of length n is broken into two unordered arrays each containing approximately half the elements of the original. (Approximately, because if the size of the original is odd, one of the two will have one more element than the other). Next, each of these smaller lists is sorted by means of a recursive call. Finally, the two sorted lists are merged back to form the original.

Notice a key feature here that is characteristic of all recursive algorithms. We have solved a problem by assuming the ability to solve a “smaller” problem of the same form. The meaning of “smaller” will vary from task to task. Here, “smaller” means a smaller length array. The algorithm demonstrates how to sort an array of length n, assuming you know how to sort an array (actually, two arrays) of length n/2. 


## Implementation of Merge Sort

The only actions are to separate the array into two parts, recursively sort them, and merge the results.

However, the merge operation cannot be performed in place. Therefore the merge sort algorithm requires a second temporary array, the same size as the original. The merge operation copies values into this array, then copies the array back into the original location.

### Merge Sort In C language
```c
void mergeSort (double data [ ], int n) {
 double * temp = (double *) malloc (n * sizeof(double));
 assert (temp != 0); /* make sure allocation worked */
 mergeSortInternal (data, 0, n-1, temp);
 free (temp);
}

void mergeSortInternal (double data [ ], int low, int high, double temp [ ]) {
 int i, mid;
 if (low >= high) return; /* base case */
 mid = (low + high) / 2;
 
 mergeSortInternal(data, low, mid, temp); /* first recursive call */
 mergeSortInternal(data, mid+1, high, temp); /* second recursive call */
 
 merge(data, low, mid, high, temp); /* merge into temp */
 
 for (i = low; i <= high; i++) /* copy merged values back */
 data[i] = temp[i];
}

void merge(double data [ ], int low, int mid, int high, double temp [ ]) {
  // Need to do merge in C
}

```

### Merge Sort in Java

```java
  public static int[] mergeSort(int[] arr) {
        if(arr == null) return arr;
        int[] helper = new int[arr.length];
        doSort(arr, helper, 0, arr.length -1);
        return arr;
    }

    private static void doSort(int[] arr, int[] helper, int start, int end) {
        // End the recursion
        if(start >= end) return;

        int mid = start + (end - start) / 2;
        // Sort left side
        doSort(arr, helper, start, mid);
        // Sort right side
        doSort(arr, helper, mid + 1, end);

        merge(arr, helper, start, mid, end);
    }

    private static void merge(int[] arr, int[] helper, int aStart, int aEnd, int bEnd) {
        // Copy arr from aStart to bEnd
        for (int i = aStart; i <= bEnd; i++ ) {
            helper[i] = arr[i];
        }

        int aCur = aStart;
        int bCur = aEnd + 1;

        for(int i = aStart; i <= bEnd; i++ ) {
            if (aCur > aEnd){
                // use out a
                arr[i] = helper[bCur++];
            } else if (bCur > bEnd){
                // use out b
                arr[i] = helper[aCur++];
            } else if (helper[aCur] <= helper[bCur]) {
                // a < b
                arr[i] = helper[aCur++];
            } else {
                arr[i] = helper[bCur++];
            }

        }
    }
```