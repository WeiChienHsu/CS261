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
 int cbf = bf(current);
 
 if (cbf < -1) {
    if (bf(current->left) > 0) // double rotation
      current->left = rotateLeft(current->left);
    return rotateRight(current); // single rotation

 } else if (cbf > 1) {
    if (bf(current->right) < 0)
      current->right = rotateRight(current->right);
    return rotateLeft(current);
 }

 /* Current Balance factor == -1 0 1, no need to rotation */   
  setHeight(current); /* Update the height */
  return current;
 }