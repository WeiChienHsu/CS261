# include "ArrayBagStack.h"
# include <stdio.h>


void initBag(struct arrayBagStack *b) {
  b -> count = 0;
}

void addBag(struct arrayBagStack *b, TYPE v) {
  b -> data[b -> count] = v;
  b -> count ++;
}

int containsBag (struct arrayBagStack * b, TYPE v) {
  // assert(b != NULL);
  for(int i = 0; i < b -> count; i++) {
    if(b -> data[i] == v) {
      return 1;
      printf("Found %d \n", v);
    }
  }
  return 0;
}


void removeBag (struct arrayBagStack * b, TYPE v) {
  // assert(b != NULL);
  if(containsBag(b, v) == 1) {
      for(int i = 0; i < b -> count; i++) {
        if(EQ(b -> data[i], v)) {
          for(int j = i; j < b ->count; j++) {
            b -> data[j] = b -> data[j + 1];
          }
        }
        printf("Removed  %d \n", v);
        b -> count--;
        break;  
      }
  }
  printf("Not Contained. \n");

}


int sizeBag (struct arrayBagStack * b) {
  return b -> count;
}

/* Interface for Stack */
void pushStack (struct arrayBagStack * b, TYPE v) {
  // assert(b != NULL);
  addBag(b, v);
}

int topStack (struct arrayBagStack * b) {
  return b -> data[b -> count - 1];
}
void popStack (struct arrayBagStack * b){
  removeBag(b, topStack(b));
}

int isEmptyStack (struct arrayBagStack * b){
  if(b -> count == 0) {
    return 1;
  }
  return 0;
}

int main() {
  struct arrayBagStack *stack;
  initBag(stack);
  printf("%d \n", containsBag(stack, 10));
  pushStack(stack,30);
  printf("%d \n", topStack(stack));
  pushStack(stack,40);
  pushStack(stack,50);
  popStack(stack);
  popStack(stack);
  isEmptyStack(stack);
  return 0;
}