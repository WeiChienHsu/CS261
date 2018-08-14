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