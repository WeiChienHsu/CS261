## Array Iterators

```c
void dynArrayRemoveAt (struct dynArray * dy, int index);

struct dynArrayIterator { 
  struct dynArray * da; 
  int currentIndex;
};

void dynArrayIteratorInit (struct dynArray *da, struct dynArrayIterator *itr) {
  /* Initialize the iterator array */
  itr -> da = da;
  /* Assign index to iterator */
  itr -> currentIndex = 0;
}

int dynArrayIteratorHasNext (struct dynArrayIterator *itr) {
  if(itr -> currentIndex != itr -> da -> size) {
    itr -> currentIndex++;
    return 1;
  }
  return 0;
}

TYPE dynArrayIteratorNext (struct dynArrayIterator *itr) {
  return itr -> da -> data[itr -> currentIndex];
}

void dynArrayIteratorRemove (struct dynArrayIterator *itr) {
  dynArrayRemoveAt(itr -> da, itr -> currentIndex);
  itr -> currentIndex--;
}
```

## Linked List Iterator

```c
struct linkedListIterator { 
  struct linkedList * lst; 
  struct dLink * currentLink;
}

void linkedListIteratorInit (struct linkedList *lst, struct linkedListIterator * itr) { 
  itr->lst = lst;
  itr->currentLink = lst->frontSentinel;
}

void _removeLink (struct linkedList *lst, struct dLink * lnk); 

int linkedListIteratorHasNext (struct linkedListIterator *itr) {
  if(itr -> currentLink != itr -> lst -> backSentinel) {
    return 1;
  }
  return 0;
}

TYPE linkedListIteratorNext (struct linkedListIterator *itr) {
  TYPE temp = itr -> currentLink -> value;
  itr -> currentLink = itr -> currentLink -> next;
  return temp;
}
/* think about the next one carefully. Draw a picture. What should itr->currentLink be pointing to after the remove operation? */
void linkedListIteratorRemove (struct linkedListIterator *itr) {
  struct dLink *temp = itr ->currentLink;
  itr -> currentLink = itr -> currentLink -> next;
  _remove(itr -> lst, temp);
}
```

****
# Sorted Arrays and Binary Search

As we did with remove, we will divide this into two steps. The add method will find the correct location at which to insert a value, then call another method that will insert an element at a given location:

```c
int dyArrayBinarySearch (struct dyArray * da, TYPE testValue) { 
  return _binarySearch (da->data, da->size, testValue); 
}

int bunarySearch(TYPE *data, int size, TYPE testValue) {
  int start = 0;
  int end = size - 1;

  while(start < end) {
    int mid = start + (end - start) / 2;
    if(data[mid] == testValue) {
      return mid;
    } else if(data[mid] > testValue) {
      end = mid;
    } else {
      start = mid;
    }
  }
  return -1; /* Not found the element */
}

void orderedArrayAdd (struct dyArray *da, TYPE newElement) { 
  int index = binarySearch(da->data, da->size, newElement); 
  dyArrayAddAt (da, index, newElement);
}

int orderArrayContains(struct dyArray *da, TYPE testElement) {
  if(bunarySearch(da, testElement) == -1) {
    return 0;
  } else {
    return 1;
  }
}

void orderedArrayRemove(struct dyArray *da, TYPE testElement) {
  int index = bunarySearch(da, testElement);
  assert(index != -1);

  for(int i = index, i < da -> size - 1; i++) {
    da -> data[i] = da -> data[i + 1];
  }
  da -> data[size - 1] = 0;
}


void dyArrayAddAt(struct dyArray *da, int index, TYPE newElement){
  assert(index >= 0 && index <= da -> size);
  if(da -> size >= da -> capacity) {
    _dyArrayDoubleCapacity(da);
  }
  for(int i = da -> size; i > index; i--) {
    da -> data[i] = da -> data[i - 1];
  }
  da -> data[index] = newElement;
}


```


***
# Binary Search Trees

A binary search tree is a binary tree that has the following additional property: for each node, the values in all descendants to the left of the node are less than or equal to the value of the node, and the values in all descendants to the right are greater than or equal.

```
         6
       /   \
      4     8
     / \      \
    4   5      9
   /            \
  2              10
 /  \
1    3  
```

### Notice that an in-order traversal of a BST will list the elements in sorted order. 

```java
void inOrder(tree root) {
  if(root == null) return;
  inOrder(root.left);
  print(root.value);
  inOrder(root.right);
}
```

## a BST can be used to produce a fast Bag implementation. O(logn) time for searching.

Travers to the left or right depends on the value and could remove the rest of other side in the Tree.

## Insertion in BST

Use a private internal function that takes a Node and a value, and returns the new tree in which the Node has been inserted.

```
Node add (Node start, E newValue)
 if start is null then return a new Node with newValue
 otherwise if newValue is less than the value at start then
    set the left child to be the value returned by add(leftChild, newValue)
 otherwise set the right child to be add(rightChild, newValue)
 return the current node
```

## Removal in BST

The difficulty is that removing a node leaves a “hole”. 

### What value should be used in place of the removed element? 

```
leftmost child of the right node
```

This is because it is this value that is the smallest element in the right subtree. The leftmost child of a node is the value found by running through left child Nodes as far as possible.


```
 if start.value is the value we seek
    decrease the value of dataSize
    if right child is null
        return left child
    otherwise
        replace value of node with leftmost child of right child
        set right child to be removeLeftmost(right child)
 otherwise if testValue is smaller than start.value
    set left child to remove (left child, testValue)
 otherwise
    set right child to remove (right child, testValue)
 return current node
```


```
         6
       /   \
      4     8
     / \   /  \
    4   5 7    9
   /            \
  2              10
 /  \
1    3  
```

For example, we remove 6:

```
        [ ]
       /   \
      4     8
     / \   /  \
    4   5 7    9
   /            \
  2              10
 /  \
1    3  
```

LeftMost element in the right chuld tree is 7

```
         7
       /   \
      4     8
     / \      \
    4   5      9
   /            \
  2              10
 /  \
1    3  
```

For example, we continuouly remove 8:

Since 7 is smaller then 8, move to it's right child 8

Remove 8 and replace by the leftMost in it's right child which is 9

```
         7
       /   \
      4     9
     / \      \
    4   5      10
   /           
  2              
 /  \
1    3  
```

## Implementation of Binary Search Tree

```c
struct Node {
  TYPE value;
  struct Node *left;
  struct Node *right;
};

struct BinarySearchTree {
  struct Node *root;
  int size;
};

void initBST(struct BinarySearchTree *tree) { 
  tree->size = 0; 
  tree->root = 0: 
}

void addBST(struct BinarySearchTree *tree, TYPE newValue) {
    tree->root = _nodeAddBST(tree->root, newValue); tree->size++; 
}

int sizeBST (struct BinarySearchTree *tree) {
   return tree->size; 
}

/************************************************************
 * _nodeAddBST(struct Node *current, TYPE newValue)
 * If the Tree is empty, directly add the new Node into root's left child.
 * If the root value is smaller than new Value:
 *   we must add this new Node in root's right child,
 *   so, connect current -> right with another _nodeAddBST function recursivly.
 * Oppositely,
 *   connect current -> left with it's left child with another _nodeAddBST function recursivly.
 ************************************************************/

struct Node * _nodeAddBST (struct Node *current, TYPE newValue) {
  struct Node *currentNode;

  /* If the current root is NULL, directly add the new node in root's left child */
  if(current == 0) {
    currentNode = (struct Node*) malloc(sizeof(struct Node));
    assert(currentNode != 0);

    currentNode -> value = newValue;
    currentNode -> left = 0;
    currentNode -> right = 0;

    return currentNode;
  }

  if(newValue > current -> value) {
    /* newValue is larget than root value, go right */
    current -> right = _nodeAddBST(current -> right, newValue);
  } else {
    /* new value is smaller or equal to root value, go left */
    current -> left = _nodeAddBST(current -> left, newValue);
  }

  return current;
}


/************************************************************
 * containsBST(struct Node *current, TYPE d)
 * Binary-Search like searching method.
 * Go through the different direction depends on the value.
 ************************************************************/

int containsBST (struct BinarySearchTree *tree, TYPE d) {
  struct Node *cur = tree -> root;

  while(cur != 0) {
    if(cur -> value == d) {
      return 1;
    } else if(cur -> value > d) {
      /* Current value is too large, search left child */
      cur = cur -> left;
    } else {
      /* Current value is too small, search right child */
      cur = cur -> right;
    }
  }

  return 0;
}

/************************************************************
 * _leftMostChild(struct Node *current)
 * Find the left most child by keeping searching the left side child until meet 0.
 ************************************************************/

TYPE _leftMostChild (struct Node * current) {
  /* Keep searching the current left child */
  while(current -> left != 0) {
    current = current -> left;
  }
  return current -> value;
}

/************************************************************
 * _remvoeLeftmostChild(struct Node *current)
 * Need to find the left most child by using "_leftMostChuld" function.
 * There will be two situations:
 *  1. Current node has already been the leftMost one which means without left child.
        -> Remove itself and move the current root left.
 *  2. There is a left child, and we used left child as arugement to remvoe it's left most child.
 ************************************************************/

struct node * _removeLeftmostChild (struct Node *current) {
  struct Node *temp;
  if(current -> left == 0) {
    /* If current has already been the leftMost (No left child) */
    /* Revmoe itself */
    temp = current -> right;
    free(current);
    return temp;
  } 
  /* If current node has a left child, go left and find it's left most */
  current -> left = _removeLeftmostChild(current -> left);
  reutnr current;
}

/************************************************************
 * _nodeRemoveBST(struct Node *current, TYPE d)
 * We need to find the target first. (By recusively calling the _NodeRemoveBST)
 * When we found the target node:
 * 1. Find if there is a left Most Node in it's right child
 * 2. If there is no right child, remove the target and return it's left child.
 * 3. If there is a right child of this target node, get it's right child's left
 *    Most node value, assign that value to the removed node and revmoe that 
 *    left most child by calling (_removeLeftmostChild(current -> right)).
 ************************************************************/

struct Node * _nodeRemoveBST (struct Node * current, TYPE d) {
  struct Node *node;
  if(current -> val == d) {
    /* Find the leftMost in right Tree and replace the Value */
    if(current -> right == 0) {
      /* If there is no right tree */
      node = current -> left;
      free(current);
      return node;
    }

    /* Get the Value of LeftMost node in right child and assign the the removed node */
    current -> val = _leftMostChild(current -> right);
    /* Get rid of the right LeftMost Node */
    current -> right = _removeLeftmostChild(current -> right);
  }
  else if (current -> val > d) {
    current -> left = _nodeRemoveBST(current -> left, d);
  }
  else {
    current -> right = _nodeRemoveBST(current -> right, d);
  }

  return current;
}

void removeBST (struct BinarySearchTree *tree, TYPE d) {
 if (containsBST(tree, d) {
 tree->root = _nodeRemoveBST(tree->root, d);
 tree->size--;
 }
}
```

***

# Chapter 10 Efficient Collections 