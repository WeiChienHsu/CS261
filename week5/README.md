# Priority Queue and Heaps

A priority Queue maintains values in order of importance. Key feature is that you want to be able to quickly find the most important item, the value with highest priority.

Normally priority is defined by the user, who provides a comparision function that can be applied to any two elements.

## Priority Queue Implementation Techniques

The first is to examine how any variety of ordered bag (Such as SortedBag, SkipList or AVLTree) can be used to implement the priority queue.

The second approach introduces a new type of binary tree, term the heap. Provide a very memory efficient representaion for a priority Queue.

The Third technique, skew heap, used an interesting variation on the heap technique.


## Building a Priority Queue using an Ordered Bag

Included sorted dynamic array, the skip list, and the AVL tree. In each of these containers the smallest element is always the first value.

## Building a Priority Queue using a Heap - O(log(n)) insertion

A heap is a binary tree that also maintains the property that the value stored at every node is less than or equal to the values stored at either of its child nodes. This is termed the heap order property. 

The classic heap structure (known just as the heap) adds the additional requirement that the binary tree is complete.

That is, the tree if full except for the bottom row, which is filled from left to right. The following is an example of such a heap:

```
           2
         /   \
        3     5
      /  \   / \
     9   10 7   8
    /\   / \
   12 14 11 13   

2 3 4 9 10 7 8 12 14 11 13
```

In particular, the smallest element is always at the root. Although we will continue to think of the heap as a tree, we will make use of the fact that a complete binary tree can be very efficiently represented as an array.

To root of the tree will be stored as the first element in the array. The children of node i are found at positions 2i+1 and 2i+2, the parent at (i-1)/2. You should examine the tree above, and verify that the transformation given will always lead you to the children of any node. To reverse the process, to move from a node back to the parent, simply subtract 1 and divide by 2. You should also verify that this process works as you would expect.


### Insertion in the Heap (to implement the Priority Queue)

To insert a new value into a heap the value is first added to the end. Adding an element to the end preserves the complete binary tree property, but not the heap ordering. To fix the ordering, the new value is percolated up into position.

It is compared to its parent node. If smaller, the node and the parent are exchanged. This continues until the root is reached, or the new value finds its correct position. Because this process follows a path in a complete binary tree, it is O(log n).

- Insert 4

```
            2
         /     \
        3        5
      /  \      / \
     9   10    7   8
    /\   / \   /
   12 14 11 13 4  

Switch 4 and 7


            2
         /     \
        3        5
      /  \      / \
     9   10    4   8
    /\   / \   /
   12 14 11 13 7  

Switch 4 and 5

            2
         /     \
        3        4
      /  \      / \
     9   10    5   8
    /\   / \   /
   12 14 11 13 7  

```

### Removal in the Heap (to implement the Priority Queue)

When the root node is removed it leaves a “hole.” Filling this hole with the last element in the heap restores the complete binary tree property, but not the heap order property. To restore the heap order the new value must percolate down into position.

To percolate down a node is compared to its children. If there are no children, the process halts. Otherwise, the value of the node is compared to the value of the smallest child. If the node is larger, it is swapped with the smallest child, and the process continues with the child. Again, the process is traversing a path from root to leaf in a complete binary tree. It is therefore O(log n).


```
Pop out 2

            2
         /     \
        3        4
      /  \      / \
     9   10    5   8
    /\   / \   /
   12 14 11 13 7  


          Empty
         /     \
        3        4
      /  \      / \
     9   10    5   8
    /\   / \   /
   12 14 11 13 7


   The last element 7 comes up

            7
         /     \
        3        4
      /  \      / \
     9   10    5   8
    /\   / \   
   12 14 11 13 


  7 Compare with two child, swith with the smallest one

            3
         /     \
        7        4
      /  \      / \
     9   10    5   8
    /\   / \   
   12 14 11 13 

  7 keep comparing with it's children but now there is no smaller value

```

# Sorting

## Quicksort. 

For random data, this algorithm tends to partition the dataset into two similarly sized pieces, placing one item in its final position, and the smaller items on one side and larger items on the other side. This means that in terms of locality, once we have a piece that fits in memory, locality is exploited until this piece is fully sorted. Thus, apart from the log(N) complexity of the algorithm, this method exploits locality quite reasonably.

## Heapsort. 

This method uses a heap that may be traversed randomly depending on the characteristics of the data. This is not really local, as the heap is touched all-over when the items find their place in the heap and other ithems are pulled up, leading to a poor locality if the heap does not fit in memory.

## Merge Sort. 

This is used when several runs (pieces of the data) are already sorted. The locality of the method comes from the fact that each run is traversed sequentially, thus, locality is exploited reasonably. Also, the heap used to sort is R Log(R) size for R being the number of runs to be sorted, which keeps locality reasonably well if the heap fits in memory.