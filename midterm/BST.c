#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
  int value;
  struct Node *left;
  struct Node *right;
};

struct BST {
  struct Node* root;
  int size;
};

void initBST(struct BST *tree) {
  tree -> size = 0;
  tree -> root = NULL;
}

/* Search a approcitar position to add the new node and return whole current Tree  */
struct Node * _nodeAddBST(Node *current, int newValue) {

}


void addBST(struct BST *tree, int newValue) {
  tree -> root = _nodeAddBST(tree -> root, newValue);
  tree -> size++;
}

int sizeBST(struct BST *tree) {
  return tree -> size;
}

int containBST(struct BST *tree, int d) {
  struct Node * cur = tree -> root;
  
  while(cur != NULL) {
    if(cur -> value == d) {
      return 1;
    }

    if(cur -> value > d) {
      cur = cur -> left;
    } else {
      cur = cur -> right;
    }
  }
  return 0;
}

/* Findh Left Most child value to replace the removed node */
int _leftMostChild(struct Node *current) {
  while(current -> left != NULL) {
    current = current -> left;
  }
  return current -> value;
}

struct Node * _removeLeftMostChild(struct Node *current) {
  struct Node *temp;
  if(current -> left == NULL) {
    /* Current node is the left Most Node */
    /* Levae the right child of the left most Node */
    temp = current -> right;
    free(current);
    return right;
  }

  /* current Left != NULL */
  current -> left = _removeLeftMostChild(current ->left);
  return current;
}

struct Node * _nodeRemoveBST(struct Node *current, int d) {
  struct Node *temp;
  if(current -> value == d) {
    /* If there is no right child */
    if(current -> right == NULL) {
      /* Remove current node directly */
      temp = current -> left;
      free(current);
      return temp;
    }

    current -> val = _leftMostChild(current -> right);
    current -> right = _removeLeftMostChild(current -> right);
  
  }
  else if(current -> value > d) {
    current -> left = _nodeRemoveBST(current -> left, d);
  } else {
    current -> right = _nodeRemoveBST(current -> right, d);
  }

  return current;
  
}

void removeBST(struct BST *tree, int d) {
  _nodeRemoveBST(tree -> root, d);
  tree -> size --;
}