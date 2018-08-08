#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkListStack.c"

int main() {
  struct LinkedListStack *stack;
  LinkedListStackInit(stack);


  LinkedListStackFree(stack);
  return 0;
}