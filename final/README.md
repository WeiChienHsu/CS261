# Review Final 

## Binary Search Tree

|       | DynamicArr Bag | LL Bag | Ordered Bag | BST Bag |
|:-----:|:--------------:|:------:|:-----------:|:-------:|
|Add    | O(1) *         | O(1)   | O(n)        | O(logN) |
|Contain| O(n)           | O(n)   | O(logN)     | O(logN) |
|Remove | O(n)           | O(1)   | O(n)        | O(logN) |


```c
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
  int val;
  struct Node *right;
  struct Node *left;
}

struct BSTree {
  struct Node *root;
  int    cnt;
}


void initBSTree(struct BSTree * tree) {
  tree -> root = NULL;
  tree -> cnt = 0;
}

void addBSTree(struct BSTree *tree, int value) {
  tree -> root = _addNode(tree -> root, value);
  tree -> cnt++;
}

struct Node _addNode(struct Node* cur, int value) {
  /* Base Case */
  if(cur == NULL) {
    /* Allocate a new memory space for new Node */
    struct Node * newNode = malloc(sizeof(struct Node));
    newNode -> val = value;
    newNode -> left = newNode -> right = NULL;
    return newNode;
  }
  
  /* Recursive Case */
  if(cur -> val > value) {
    cur -> left = _addNode(cur -> left, value);
  }
  else {
    cur -> right = _addNode(cur -> right, value)
  }
  /* Return the current recursion level*/
  return cur;
}

int containsBSTree(struct BSTree* tree, int value) {
  struct Node current = tree -> root;
  while(current != NULL) {
    if(current -> val == value) {
        return 1;
    }
    else if(current -> val > value) {
      current = current -> left;
    }
    else {
      current = current -> right;
    }
  }
  return 0;
}

void removeBSTree(struct BSTree * tree, int value) {
  tree -> root = _removeNode(tree -> root, value);
  tree -> cnt --;
}
/* 
  Found target value -> No Right Child : Direct remove and connect Left child
                     -> Has Right Child: Replace by right child's leftMost child
  Did not find target -> Recursivly find the target on left or right child
*/

struct Node _removeNode(struct Node * current, int value) {
  /* Found the target */
  if(current -> val == value) {
    /* No right child */
    if(current -> right == NULL) {
      /* Remove and free the current node */
      struct Node *temp = current -> left;
      free(current);
      /* Return the current -> left node */
      return temp;
    }
    /* Replace the current Node with its right child's LeftMost child value */
    current -> val = _leftMostChild(current -> right);
    /* Remove current value's right child's LeftMost child */
    current -> right = _removeLeftMostChild(current -> right);

  }
  else if(current -> val > value) {
    current -> left = _removeNode(current -> left, value);
  } else {
    current -> right = _removeNode(current -> right, value);
  }

  return current;
}

int _leftMostChild(struct Node *current) {
  while(current -> left != NULL) {
    current = current -> left;
  }
  return current -> val;
}

struct Node _removeListMostChild(struct Node *current) {
  /* Check if the current node the LeftMost one */
  if(current -> left == NULL) {
    struct Node * temp = current -> right;
    free(current);
    return temp;

  }
  /* Keep finding the Left Most Child */
  current -> left = _removeLeftMostChild(current -> left);
  return current;
}

int sizeBSTree(struct BSTree * tree){
  return tree -> cnt;
}
```

***

## AVL Tree (Height-Balanced BST)

When Unbalanced, performs a 'rotation' to balance the tree.


### Left Rotation

0. Current node is the unbalanced node.
1. New Top node is the current node's right child
2. Current node's new right child is the new top nodes left child
3. New top's left child is the current node
4. Set height of current node
5. Set height of new top node
6. Return new top node


### Right Rotation

0. Current node is the unbalanced node.
1. New Top node is the current node's left child
2. Current node's new left child is the new top nodes right child
3. New top's right child is the current node
4. Set height of current node
5. Set height of new top node
6. Return new top node


### Double Rotation

When an insertion is made on the left or right side of a node that is itself a heavy right or left child. (Heavy Right with left child / Heavy Left with right child)

1. First Rotate the heavy right or left child to the right or left.
2. Rotate the top node to the left.

```
If LEFT child is tallest (by more than 1):
  If LEFT child is heavy on the RIGHT side:  // Double Rotation needed
    Rotate the LEFT child to the LEFT
  Rotate unbalanced top node to the RIGHT

Else If RIGHT child is tallest (by more than 1):
  IF RIGHT child is heavy on the LEFT side:
    Rotate the RIGHT child to the RIGHT
  Rotate unbalanced top node to the LEFT

```

```c
struct AVLnode {
  int value;
  struct AVLnode *left;
  struct AVLnode *right;
  int height;
};

int _h(struct AVLnode *current) {
  if(current == NULL) return -1;
  return current -> height;
}

void _setHeight(struct AVLnode *current) {
  int l_height = h(current -> left);
  int r_height = h(current -> right);

  if(l_height < r_height) {
    current -> height = r_height + 1;
  } else {
    current -> height = l_height + 1;
  }
}

struct AVLnode *_rotateLeft(struct AVLnode *current) {
  struct AVLnode* newRoot = current -> right;
  current -> right = newRoot -> left;
  newRoot -> left = current;
  _setHeight(current);
  _setHeight(newRoot);
  return newRoot;
}

int _bf(struct AVLnode *current) {
  /* Return the difference between  */
  return h(current -> right) - h(current -> left);
}

struct AVLnode *_rotateRight(struct AVLnode *current) {
  struct AVLnode* newRoot = current -> left;
  current -> left = newRoot -> right;
  newRoot -> right = current;
  _setHeight(current);
  _setHeight(newRoot);
  return newRoot;
}

struct AVLnode* _balance(struct AVLnode *current) {
  int difference = bf(current);

  /* Left Child is Tallest : Rotate Right */
  if(difference < -1) {
    /* Check if the Left Child's right is heavy */
    if(bf(current -> left) > 0)
      /* Double Rotate LEFT */
      current -> left = _rotateLeft(current -> left);
    return _rotateRight(current);
  }
  /* Right Child is Tallest */
  else if(difference > 1) {

  }

  _setHeight(current);
  return current;
}

struct AVLnode* _AVLnodeAdd(struct AVLnode* current, int newValue) {
  if(current == NULL) {
    struct AVLnode * newNode = (struct AVLnode *) malloc(sizeof(struct AVLnode));
    assert(newNode != NULL);
    newNode -> value = newValue;
    newNode -> left = newNode -> right = 0;
    return newNode;
  }
  else if (current -> value > newValue) {
    current -> left = _AVLnodeAdd(current -> left, newValue);
  } else {
    current -> right = _AVLnodeAdd(current -> right, newValue);
  }
  return _balance(current);
}

int _leftMost(struct AVLnode *current) {
  if(current -> left != NULL) {
    current = current -> left;
  }
  return current;
}

struct AVLnode *_removeLeftMost(struct AVLnode * current) {
  struct AVLnode *temp;
  if(current -> left != NULL) {
    current -> left = _removeLeftMost(current -> left);
    return _balance(current);
  }

  /* There is no Left Child */
  temp = current -> right;
  free(current);
  return temp;
}

/* Find the target and replace by it's right child's LeftMost */
struct AVLnode *_removeNode(struct AVLnode *current, int val) {
  if(current -> value == val) {
    /* There is a right child*/
    if(current -> right != NULL) {
      current -> value = _leftMost(current -> right);
      current -> right = _removeLeftMost(current -> right);
      return _balance(current);
    }
    else {
      /* There is no right child */
      struct AVLnode *temp = current -> left;
      free(current);
      return temp;
    }

  }

  else if(current -> value > val) {
    current -> left = _removeLeftMost(current -> left, val);
  } else {
    current -> right = _removeLeftMost(current -> right, val);
  }

  return _balance(current);
}

void removeAVLTree(struct AVLTree *tree, int val) {
  if(containsAVLTree(tree, val)) {
    tree -> root = _removeNode(tree -> root, val);
    tree -> cnt --;
  }
}
```

***

## Heap

- adjustHeap(heap, max, smallestChild);

|      | Sorted Vector | Sorted List | Heap   |
|:----:|:-------------:|:-----------:|:------:|
| Add  | O(logn)       | O(n)        | O(logn)|
|getMin| O(1) - get(0) | O(1)        |O(1)    |
|removeMin| O(n)       | O(1)        | O(logn)|


```c
TYPE dyArrayGet(DyArray *heap, int index);
void dyArrayPut(DyArray *heap, int index, int value);
void dyArrayAdd(DyArray *heap, int newValue);
void dyArrayRemoveAt(DyArray *heap, int index);
int dyArraySize(DyArray *heap);


void adjustHeap(struct DyArray *heap, int max, int pos) {
  int leftChild = pos * 2 + 1;
  int rightChild = pos * 2 + 2;

  if(max > rightChild) {
    /* There are two children */
    /* Find the smaller one between two children */
    int smallestChild = findSmallesChild(heap, leftChild, rightChild);
    if(dyArrayGet(smallestChild) < dyArrayGet(pos)) {
      swap(heap, smallestChild, pos);
      adjustHeap(heap, max, smallestChild);
    }
  }
  else if(max > leftChild) {
    /* There is only left child */
    /* Compare with the left child and see if it need to be swap */
    if(dyArrayGet(leftChild) < dyArrayGet(pos)) {
      swap(heap, leftChild, pos);
      adjustHeap(heap, max, leftChild);
    }
  }
  /* There is no child: Do nothing */
}

int findSmallesChild(DyArray * heap, int left, int right) {
  if(dyArrayGet(heap, left) > dyArrayGet(heap, right)) {
    return right;
  }
  else {
    return left;
  }
}

void swap(struct DyArray * heap, int i, int j) {
  int temp = dyArrayGet(heap, i);
  dyArrayPut(heap, i, dyArrayGet(j));
  dyArrayPut(heap, j, temp);
}

void heapAdd(struct DyArray *heap, int newValue) {
  int pos = dyArraySize(heap);
  dyArrayAdd(heap, newValue);
  int parent = (pos - 1) / 2;
  while(pos != 0) {
    if(dyArrayGet(parent) < dyArrayGet(pos)) {
      swap(heap, pos, parent);
      pos = parent;
    } else {
      return;
    }
  }
}

void heapRemoveFirst(struct DyArray *heap) {
  /* Remove the last element and replace that value to the first element */
  int last = dyArraySize(heap) - 1;
  int lastValue = dyArrayGet(last);
  dyArrayRemoveAt(heap, last);
  dyArrayPut(heap, 0, lastValue);
  adjustHeap(heap, last, 0); /* Reheaping */
}

int heapGetMin(struct DyArray* heap) {
  assert(dyArraySize(heap) > 0);
  return dyArrayGet(heap, 0);
}
```

***

## HashTabke

### Open Address - Probing

```c
struct openHashTable {
  TYPE **table; /* Points to pointer stored in the array */
  int tableSize;
  int count;
}

void initOpenHashTable(struct openHashTable *ht, int size) {
  ht -> table = (TYPE **) malloc(size * sizeof(TYPE *));
  ht -> tableSize = size;
  ht -> count = 0;
  /*  Fill in the array */
  for(int i = 0; i < size; i++) {
    ht ->table[i] = 0; /* Points to the 0 means there is no stored value */
  }
}

void openHashTableSize(struct openHashTable *ht) {
  return ht -> tableSize;
}

void openHashTableAdd(struct openHashTable *ht, TYPE *newValue) {
  if((ht -> count / (double) ht -> tableSize) > 0.75) {
    _resizeOpenHashTable(ht);
  }
  ht -> count ++;

  int index = HASH(newValue) * ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  while(index >= 0) {
    /* If index exceed */
    if(index == ht -> tableSize) {
      index = 0;
    }
    /* Meet empty space */
    if(ht -> table[index] == 0) {
      ht -> table[index] = newValue;
      index = -1;
    }
    else {
      index ++;
    }
  } 
}

int openHashTableContains(struct openHashTable *ht, TYPE* newValue) {
  int index = HASH(newValue) % ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  while(ht -> table[index] != 0) {
    if(index == ht ->tableSize) {
      index = 0;
    }
    if(compare(ht -> table[index], newValue) == 0) {
      return 1;
    } else {
      index ++;
    }
  }

  return 0;
}

void _resizeOpenHashTable(struct openHashTable *ht) {
  int originalSize = ht -> tableSize;
  TYPE **temp = ht -> table;
  initOpenHashTable(ht, originalSize * 2);
  for(int i = 0; i < originalSize; i++) {
    if(temp[i] != 0) {
      openHashTableAdd(ht, temp[i]);
    } 
  }
  free(temp);
}
```


### Chaining (or Buckets)

***
