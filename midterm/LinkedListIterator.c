#include "LinkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

struct linkedListIterator{
  struct LinkedList *lst;
  struct Link *currentLink; 
};

void linkedListIteratorInit(struct LinkedList *lst ,struct linkedListIterator *itr) {
  itr -> lst  = lst;
  itr -> currentLink = lst -> frontSentinel;
}

int linkedListIteratorHasNext(struct linkedListIterator* itr) {
  if(itr -> currentLink -> next == itr -> lst ->backSentinel) {
    return 0;
  } else {
    itr -> currentLink = itr -> currentLink -> next;
    return 1;
  }
}

int linkedListIteratorNext(struct linkedListIterator *itr) {
  return itr -> currentLink -> value;
}

void _removeLink (struct LinkedList *list, struct Link * link) {
  assert(list != 0);

  link -> prev -> next = link -> next;
  link -> next -> prev = link -> prev;

  link -> prev = NULL;
  link -> next = NULL;
  link -> value = 0;
  free(link);

  list -> size -- ;
}

void linkedListIteratorRemove(struct linkedListIterator *itr) {
  struct Link *temp = itr -> currentLink;
  itr -> currentLink = itr -> currentLink -> prev;
  _removeLink(itr -> lst, temp);
}


int main() {
  struct LinkedList *list = linkedListCreate();
  linkedListAddBack(list, 10);
  linkedListAddFront(list,20);
  linkedListAddBack(list, 40);
  linkedListAddFront(list, 10);
  linkedListAddBack(list, 10);
  linkedListAddFront(list,20);
  linkedListAddBack(list, 40);
  linkedListAddFront(list, 10);
  struct linkedListIterator* itr = malloc(sizeof(struct linkedListIterator));
  linkedListIteratorInit(list, itr);
  while(linkedListIteratorHasNext(itr)) {
    printf("%d \n", linkedListIteratorNext(itr));
    linkedListIteratorRemove(itr);
  }
  printf("%d \n", linkedListIsEmpty(list));
  return 0;
}