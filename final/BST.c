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
