#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Link {
  int value;
  struct Link *next;
};

struct LinkedListStack {
  struct Link *firstLink;
};

void LinkedListStackInit(struct LinkedListStack *s) {
  s -> firstLink = NULL;
}

int LinkedListStackIsEmpty(struct LinkedListStack *s) {
  if(s -> firstLink  == NULL) {
    return 1;
  }
  return 0;
}

void LinkedListStackPop(struct LinkedListStack *s) {
  assert(s -> firstLink != NULL);
  struct Link *temp = s -> firstLink;
  s -> firstLink  = s -> firstLink -> next;
  temp -> next = NULL;
  free(temp);
}

void LinkedListStackFree(struct LinkedListStack *s) {
  while(!LinkedListStackIsEmpty(s)) {
    LinkedListStackPop(s);
  }
}

void LinkedListStackPush(struct LinkedListStack *s, int v) {
  struct Link *newLink =(struct Link*) malloc(sizeof(struct Link));
  newLink -> value = v;
  newLink -> next = s -> firstLink;
  s -> firstLink  = newLink;
}

int LinkedListStackTop(struct LinkedListStack *s) {
  return s -> firstLink  -> value;
}

void LinkedListStackPrint(struct LinkedListStack *s) {
  while(!LinkedListStackIsEmpty(s)) {
    printf("%d \n", LinkedListStackTop(s));
    LinkedListStackPop(s);
  }
}

int main() {
  struct LinkedListStack *s;
  LinkedListStackInit(s);
  LinkedListStackPush(s, 10);
  LinkedListStackPop(s);
  LinkedListStackPush(s, 20);
  LinkedListStackPush(s, 30);
  LinkedListStackPrint(s);
  return 0;
}