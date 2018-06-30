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

  /* Temp pointer */
  int k = 0; 
  
  int leftStart = low, leftEnd = mid;
  int rightStart = mid + 1, rightEnd = high; 

  /* Merge two seperate one by comparing their first element and move the current pointer */

  while(leftStart <= leftEnd &&  rightStart <= rightEnd) {

    if(data[leftStart] <= data[rightStart]) {

      /* Put left one into the temp array */
      temp[k++] = data[leftStart++];
    }
    else {

      /* Put Right one into the temp array */
      temp[k++] = data[rightStart++];
    }
  }

  /* When one of the subarray is pointed to the end */

  while(leftStart <= leftEnd) {
    temp[k++] = data[leftStart++];
  }

  while(rightStart < rightEnd) {
    temp[k++] = data[rightStart++];
  }

  /* copy merged values back */
  for(i = 0; i < k; i++) {
    data[low + i] = temp[i];
  }
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

***

## Algorithmic Analysis of Merge Sort

Recall that the analysis of recursive algorithms involves defining the execution time as a recurrence relation. Merge sort is breaking an array of size n into two smaller arrays, and then sorting the smaller arrays. So the equation is roughly

```
T(N) = 2 * T(N / 2) + c1*n + c2
```

You will remember that the solution to this relation is approximately n log n. Another
way to think about this is the recursive calls on merge sort will be approximately O(log n)
levels deep, and at each level it will be doing approximately O(n) operations. 

Merge sort does have one annoying feature, which is that it uses extra memory. It is possible to discover algorithms that, while not asymptotically faster than merge sort, do not have this disadvantage. 

***

## Quick Sort

Quick sort, on the other hand, spends more time on the task of breaking apart. Quick sort selects one element, which is called the pivot. It then divides the array into two sections with the following property:

Every element in the first half is smaller than or equal to the pivot value, while every element in the second half is larger than or equal to the pivot. Notice that this property does not guarantee sorting. Each of the smaller arrays must then be sorted (by recursively calling quick sort). But once sorted, this property makes putting the two sections back together much easier. No merge is necessary, since we know that elements in the first part of the array must all occur before the elements in the second part of the array.

Because the two sections do not have to be moved after the recursive call, the sorting can be performed in-place. That is, there is no need for any additional array as there is when using the merge sort algorithm. As with the merge sort algorithm, it is convenient to have the main function simply invoke an interior function that uses explicit limits for the upper and lower index of the area to be sorted.

### Unsatble Algorithm

There is, however, a danger in this process. In merge sort it was easy to guarantee that the two halves
were roughly equal size, yielding a fast O(n log n) process. In quick sort this is much more difficult to guarantee. If we are unlucky then in the worst case one partition contains no values, and the other is just one element smaller. This leads to poor O(n2) performance.

### Partitioning

The process of dividing a portion of an array into two sections is termed partitioning. 

The limits of the partition are described by a pair of values: low and high. 

The first represents the lowest index in the section of interest, and the second the highest index. In addition there is a third element that is selected, termed the pivot. 

The first step is to swap the element at the pivot location and the first position. This moves the pivot value out of way of the partition step. The variable i is set to the next position, and the variable j to high.

The heart of the partition algorithm is a while loop. The invariant that is going to be preserved is that 【 all the elements with index values smaller than i are themselves smaller than or equal to the pivot, while all the elements with index values larger than j are themselves larger than the pivot. 】 

At each step of the loop the value at the i position is compared to the pivot. If it is smaller or equal, the invariant is preserved, and the i position can be advanced.

Otherwise, the location of the j position is compared to the pivot. If it is larger then the invariant is also preserved, and the j position is decremented. 

If neither of these two conditions is true the values at the i and j positions can be swapped, since they are bothout of order. Swapping restores our invariant condition.

```
-> while i < j -> i is pivot + 1, j is high
-> if the value at i is larger than the pivot value, swap value at i with j
-> Now the value at j must be larget than pivot value, and we could decrease j
-> Then, still check the current value at i before swapping, if the value is
-> small or equal than pivot value, increase i to the next value
-> In the end, out of the while loop. Swap i and pivot.
```

The loop proceeds until the values of i and j meet and pass each other. When this happens we know that all the elements with index values less than i are less than or equal to the pivot. This will be the first section. All those elements with index values larger than or equal to i are larger than or equal to the pivot. This will be the second section. The pivot is swapped back to the top of the first section, and the location of the pivot is returned.

### Quick Sort In C language

```c
void quickSort (double storage [ ], int n){ 
  quickSortInternal (storage, 0, n-1); 
}

void quickSortInternal (double storage [ ], int low, int high) {
 if (low >= high) return; /* base case */
 int pivot = low + (high - low) / 2; /* one of many techniques */
 
 pivot = partition(storage, low, high, pivot);
 
 quickSortInternal (storage, low, pivot - 1); // first recursive call
 quickSortInternal (storage, pivot + 1, high); // second recursive call
}

int partition(double stroage[ ], int low, int high, int pivot){
  double pivotValue = storage[pivot];
  swap(pivot, low, storage[]);
  int i = low + 1, j = high;

  while(i < j) {
    if (stroage[i] > pivotValue) {
      swap(i, j, storage[]);
      j--;
    } else {
      i++;
    }
  }

  swap(pivot, low, storage[]);
  return pivot;
}

void swap(int i, int j, double arr[]) {
  double temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}
```
***

### Worst case, best case, and average case
Quicksort also has different worst-, best-, and average-case complexities:
- Worst case: O(n ^ 2).
- Best case: O(n log n).
- Average case: O(n log n).
- Quicksort is still widely used because the worst case is very rare and the ignored constant factors make it typically faster than other O(n log n) sorts.

### Different execution time

The execution time of quicksort depends upon selecting a good pivot value. Many heuristics have been proposed for this task. These include:

- Selecting the middle element, as we have done
-  Selecting the first element. This avoids the initial swap, but leads to O(n2) performance in the common case where the input is already sorted
- Selecting a value at random
- Selecting the median of three randomly chosen values

***

## Example of Big Oh Analysis

```java
sum = 0;
for(int i = 0; i < n; i++) {
  sum += array[i];
}
return sum;
```

- The instruction sum = 0 executes in some constant time c1 independent of n.
- Each iteration of the loop executes in some constant time c2 and this happens n times.
- The return statement executes in some constant time c3 independent of n.
- So runtime is c1 + c2 n + c3.

-  c1, c2, and c3 depend on the particular computer running this function, so we ignore them to figure out run-time complexity.

- Thus, we say this sum function grows on the order of n, or, in other words that it is O(n).
- This is also known as a linear-time function.


***

## Nest loop - time complexity

So, for example, when an O(n) loop is nested within another O(n) loop, the total complexity is O(n^2). 

Similarly:

- O(√n) loop inside O(n) loop (and vice versa) → O(n√n).
- O(log n) loop inside O(n) loop (and vice versa) → O(n log n).
- O(√n) loop inside O(√n) loop → O(n).
- O(log n) loop inside O(log n) loop → O(log2 n).
- O(n) loop inside O(n) loop inside O(n) loop → O(n^3).

***

# C Review 

## Printing to stdout: printf()
printf() is the C way of printing stuff to stdout; there are no
streams in C.

printf() uses a format string as a template for the output.

- Format specifiers, designated by %, act as placeholders into which additional printf() arguments are inserted.

- The i’th printf() argument goes to the i’th format specifier.
- In general, the character after the % indicates the type of the
argument to be printed

1. %d – int, as a signed decimal number
2. %f – double, in fixed-point notation (e.g. 3.1415…) float arguments are cast as double
3. %c – char, as a character
4. %s – a null-terminated string

```c
#include <stdio.h>

/* Prototype the function */
void foo(int);

int main(int argc, const char * argv[]) {
    foo(4);
    return 0;
}

void foo(int num) {
    printf("%d\n", num);
}
```


## C has no reference types, unlike C++! 

That means functions are all pass-by-value.

- In other words, a copy of each argument is passed to the
function as a parameter.
- Passing big structures can be a problem with small stack sizes.
- More under “pointers” below.

## C is procedural, not object oriented like C++.

- Operate on data by passing it as arguments to functions.
- No classes or class methods.
- Structured data represented with struct.

### In C++
```
Student s = new Student("Kevin");
s.yell();
```

### In C
```c
struct student {
    char* name;
    int standing;
    float gpa;
};

int main(){
    struct student s = {.name = "Kevin", .gpa = 4.0 };
    s.standing = 1;
    printf("%d\n", s.standing);
    return 0;
}
```

## Pointers

A pointer is a variable whose value is a memory address.

A few important things here:

* acts as both a pointer variable designator (int*) and as the dereference operator (*i_ptr).
* The dereference operator gives you 【the value at an address.】
* zs& is the “address-of” operator.


```c
int i = 20;
int* i_ptr = &i;
printf("%d\n", i); /* Print 20 */
printf("%p\n", i_ptr); /* Print memory Address : 0x7ffeefbff608*/
printf("%d\n", *i_ptr); /* Print the deference value from memory Address : 0x7ffeefbff608*/

*i_ptr = 8;
printf("%d\n", i); /* Print 8 */
printf("%p\n", i_ptr); /* Print memory Address*/
printf("%d\n", *i_ptr); /* Print the deference value from memory Address*/
```

C, unlike C++, has no pass-by-reference, but we can achieve the
same thing with pointers:

```c
void make_32(int* num) { /* Pass the pointer */
    *num = 32; /* Deference and assign the value */
}

int main() {
  int a = 30;
  printf("%d \n", a); /* print 30 */
  make_32(&a); /* Pass the 'address' into the function (Not passed by reference) */
  printf("%d \n", a); /* print 32 */
}
```

***

# Program memory - Call Stack vs The Heap

A running C program (or a program in any language, for that matter) has two separate areas of memory in which it can store data, the call stack and the heap.

-  The call stack​ is a small, limited-size chunk of memory from the larger blob of system memory. Among other things, the values of variable declared in a program’s functions are stored on the call stack.

- The call stack is small: usually at most 8kb. The heap​ comprises essentially all the rest of system memory.

-  A program must specifically request to allocate memory from out of the heap. the heap is huge compared to the call stack.


# Allocating memory on the heap

我們在使用 Pointer to Struct 的時候，記得要 init 這個 pinter 指向的位置，因為在一開始定義一個pointer的時候，他只有在記憶體裡面圈出一塊屬於 Pointer 的位置

```c
struct student* kevin = malloc(sizeof(struct student));

setStudent(kevin, "Kevin", 2, 3.2);

printStudentInfo(kevin);

free(kevin);
```

### malloc()
The call stack is small (e.g. only 2048 4-byte integers fit on an 8kb stack). We need to be able to work with more memory.

We’ll need to start allocating from the heap.

```c
void* mem_block = malloc(NUMBER_OF_BYTES);
```

###  A few things to note:
- Must #include <stdlib.h>
- malloc() allocates a contiguous block of memory.
- This is useful for allocating arrays.
- malloc() returns a pointer of type void*.
- This can be cast to any type.
- We need to know how many bytes we need to allocate.

### sizeof()

We use sizeof() to help figure out how many bytes to
allocate, e.g.:

```c
printf("sizeof(int): %d \n", sizeof(int)); /* 4 */
```

### Generally use sizeof() in conjunction with malloc()
- allocate single intger

```c
int k = 13;
int* i_ptr = (int*)malloc(sizeof(int));

*i_ptr = k;
printf("*i_ptr: %d", *i_ptr); // Prints 13
```

- allocate arrays:

```c
int i, n = 4096;
int* nums = (int*)malloc(n * sizeof(int));
  int index = 0;
  for (i = 2; i < n; i*=2) {
  nums[index++] = i;
} 
```
***

## malloc() and struct

```c
struct student *s = malloc(sizeof(struct student));
(*s).name = "Luck";
(*s).gpa = 3.0;
s->name = "Nick";
s->gpa = 5.0;
```

Something to notice: students[i] is a dereferenced memory
address (a pointer).

We see here that (students + 13) is the same thing as
&students[13].


This can allow you to factor your code nicely, something like this:

```c
int n = 5, i;
struct student* students = malloc(n * sizeof(struct student));

for (i = 0; i < n; i++) {
    init_student(students + i, "Dick", 2 + i);
}

for(i = 0; i < n; i++) {
    printf("%s : %f \n",students[i].name, students[i].gpa);
}
```

***

## Freeing malloc()’ed memory

- Need to have this on the header
```c
#include <stdlib.h> 
```

We MUST​ free all of the memory we allocate using malloc(), otherwise our program will have memory leaks.

To free memory, we use free().

A good rule of thumb is this: For every call to malloc() you should have a call to free().

To use free(), just pass the pointer that was returned by malloc(), no matter whether that pointer represents a single item, an array, a struct, or whatever, e.g

```c
int* i = malloc(sizeof(int));

free(i);

int* nums = malloc(1000000 * sizeof(int));

free(nums);

struct student* s = malloc(sizeof(struct student));

free(s);

struct student* students = malloc(1000 * sizeof(struct student));

free(students);
```


## Avoid Memory Leak (valgrind)

valgrind is a great tool for helping debug memory issues.

To run a program with valgrind, you need to compile it with debug flags using the -g option:

```
gcc --std=c99 -g prog.c -o prog
```

- The just pass your program to valgrind:

```
valgrind ./prog [args to prog]
```

valgrind will run your program and detect memory leaks. If you have any leaks, it will let you know that some memory was "lost"

To dig deeper into where the memory was lost, use valgrind--leak-check=full:

```
valgrind --leak-check=full ./prog [args]
```

This will give you a report with the line numbers of the malloc() calls for the memory that was lost.

***

# C strings

In C, strings are just arrays of characters, but there are some things to be aware of.

- This doesn’t do what you might expect:
```c
char* str = "foo";
```

- That actually allocates static, read-only memory, so that you couldn’t later do this:

```c
str[2] = 'x'; // You can’t do this.
```

- If you initialize a string that way, you really should use const:
```
const char* str = "foo";
```

- Otherwise, you can allocate a string just like any other array:

```c
int n = 64;
char* str = malloc(n * sizeof(char));
```

- Then, you have lots of functions available to help you get data into that string, e.g.:
```c
#include <string.h>
strncpy(str, src_str, n); 
// Copy up to n chars.
```
```c
#include <stdio.h>
snprintf(str, n, "%s %d", some_str, some_int);
// Use a format string to initialize.
```


## Segmentation faults and debugging with gdb

A segmentation fault (segfault) is a memory access violation

- i.e. when a program tries to access a memory location in a way
that’s not allowed.

- Working with pointers, arrays, and memory allocation, you will have segfaults.

- Common causes are trying to dereference a NULL pointer or an uninitialized pointer.

```c
struct student* s;
s->name = "Luke Skywalker"; // Woops! Didn’t
// allocate s.
```


***

# Compilation Process

### Pre-processor
Remove Comments
Replace pre-processor directive
Conditional compilation

### Compiler
Transfer Soucre code to Assembly code.

### Assembler
Assembler generates object code(.o) from the assembly code. Object code is in binary and can't be viewed with a text reader.

### Linker
The Linker pulls together your object code with libraries that you're using in your program.



