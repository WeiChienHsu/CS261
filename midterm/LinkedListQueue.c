#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Link {
  int value;
  struct Link *next;
};

struct LinkedListQueue {
  struct Link *firstLink;
  struct Link *lastLink;
};

void LinkedListQueueInit(struct LinkedListQueue *q) {
  struct Link *lnk = malloc(sizeof(struct Link));
  assert(lnk != 0);
  lnk -> next = 0;
  q -> firstLink = lnk;
  q -> lastLink = lnk;
}

int LinkedListQueueIsEmpty(struct LinkedListQueue *q) {
  if(q -> firstLink == q -> lastLink) {
    return 1;
  }
  return 0;
}

void LinkedListQueueAddBack(struct LinkedListQueue *q, int v) {
  /* Create New List */
  struct Link *newLink = malloc(sizeof(struct Link));
  newLink -> next = 0;
  newLink -> value = v;
  q -> lastLink -> next = newLink;
  q -> lastLink = newLink;
}

void LinkedListQueuePopFirst(struct LinkedListQueue *q) {
  struct Link *temp = q -> firstLink -> next;
  q -> firstLink -> next = temp -> next;
  if(q -> firstLink -> next == 0) {
    q -> lastLink = q -> firstLink;
  }
  free(temp);
}

int LinkedListQueueFront(struct LinkedListQueue *q) {
  assert(!LinkedListQueueIsEmpty(q));
  return q -> firstLink -> next -> value;
}

void LinkedListQueuePrint(struct LinkedListQueue *q) {
  while(!LinkedListQueueIsEmpty(q)) {
    printf("%d \n", LinkedListQueueFront(q));
    LinkedListQueuePopFirst(q);
  }
}

int main() {
  struct LinkedListQueue *q;
  LinkedListQueueInit(q);
  LinkedListQueueAddBack(q,10);
  LinkedListQueueAddBack(q,20);
  LinkedListQueueAddBack(q,30);
  LinkedListQueuePrint(q);
  return 0;
}