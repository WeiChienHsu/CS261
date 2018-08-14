struct AVLnode {
 TYPE value;
 struct AVLnode *left;
 struct AVLnode *right;
 int height;
};

int _h(struct AVLnode * current){
  if (current == 0) return -1; 
  return current->height;
}

void _setHeight (struct AVLnode * current) {
 int lch = h(current->left);
 int rch = h(current->right);

 if (lch < rch) {
   /* Right height is higher, count the right + 1 */
   current->height = 1 + rch;
 } else {
   current->height = 1 + lch;
 }
}

struct AVLnode * _AVLnodeAdd (struct AVLnode* current, TYPE newValue) {
 struct AVLnode * newnode;
 /* Find a correct place to insert */
 if (current == 0) {
    newnode = (struct AVLnode *) malloc(sizeof(struct AVLnode));
    assert(newnode != 0);
    newnode->value = newValue;
    newnode->left = newnode->right = 0;
    return newnode;
 } else if (LT(newValue, current->value)) {
    current->left = AVLnodeAdd(current->left, newValue);
 } else {
    current->right = AVLnodeAdd(current->right, newValue);
 }
  return balance(current); /* <- NEW the call on balance */
}

int _bf (struct AVLnode * current){ 
  /* count the different of height between two children */
  return h(current->right) - h(current->left); 
}

struct AVLnode * _balance (struct AVLnode * current) {
 /* Check if the current node is unbalanced */
 int cbf = bf(current);
 
 if (cbf < -1) {
   /* Left Child is Tallest */
    if (bf(current->left) > 0)
      /* Double Rotation */
      /* Left Side have heavy Right Side : Rotate left child LEFT */
      current->left = rotateLeft(current->left);
    /* Single Rotation: rotate Right */
    return rotateRight(current); 

 } else if (cbf > 1) {
   /* Right Child is Tallest */
    if (bf(current->right) < 0)
      /* Double Rotation */
      /* Right Child have heavy Left Side : Rotate right child RIGHT*/
      current->right = rotateRight(current->right);
    /* Single Rotation: rotate Left */
    return rotateLeft(current);
 }

  setHeight(current); /* Update the height */
  return current;
 }

 struct AVLnode *_rotateRight(struct AVLnode * current) {
   struct AVLnode * newRoot = current->left;
   current -> left = newRoot -> right;
   newRoot -> right = current;
   setHeight(current);
   setHeight(newRoot);
   return newRoot;
}

struct AVLnode *_rotateLeft(struct AVLnode * current) {
   struct AVLnode * newRoot = current -> right;
   current -> right = newRoot -> left;
   newtop -> left = current;
   setHeight(current);
   setHeight(newRoot);
   return newRoot;
}


void removeAVLTree(struct AVLTree *tree, TYPE val) {
 if (containsAVLTree(tree, val)) {
    tree->root = _removeNode(tree->root, val);
    tree->cnt--;
 }
}

TYPE _leftMost(struct AVLNode *cur) {
 while(cur->left != 0) {
 cur = cur->left;
 }
 return cur->val;
}

struct AVLNode *_removeLeftmost(struct AVLNode *cur) {
  struct AVLNode *temp;
    if(cur->left != 0) {
      cur->left = _removeLeftmost(cur->left);
      return _balance(cur);
    }
  /* There is no left child */
  temp = cur->rght;
  free(cur);
  return temp;
}

struct AVLNode *_removeNode(struct AVLNode *cur, TYPE val) {
  struct AVLNode *temp;
  if(EQ(val, cur->val)) {
    if(cur->rght != 0) {
      /* If there is a right child */
      /* Find the value of leftMost node to replace the current value 
      and remove the left Most node in right child */
      cur->val =  _leftMost(cur->rght);
      cur->rght =_removeLeftmost(cur->rght);
      return _balance(cur);
    } else {
      /* If there is not right child, return current left and remove current node */
        temp = cur->left;
        free(cur);
        return temp;
    } 
  } 
  /* Haven't found the value */
  else if(LT(val, cur->val)){
    cur->left  = _removeNode(cur->left, val);
  }
  else {
     cur->rght = _removeNode(cur->rght, val);
  }

  return _balance(cur);   
}