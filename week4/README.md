# Iterators


****
# Sorted Arrays and Binary Search


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


int containsBST (struct BinarySearchTree *tree, TYPE d) {

}

void removeBST (struct BinarySearchTree *tree, TYPE d) {
 if (containsBST(tree, d) {
 tree->root = _nodeRemoveBST(tree->root, d);
 tree->size--;
 }
}


TYPE _leftMostChild (struct Node * current) {

}

struct node * _removeLeftmostChild (struct Node *current) {

}

struct Node * _nodeRemoveBST (struct Node * current, TYPE d) {

}

```

***

# Chapter 10 Efficient Collections 