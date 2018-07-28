
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


void init(struct LinkedList* list) {
  list -> frontSentinel = (struct Link*) malloc(sizeof(struct Link));
  list -> backSentinel = (struct Link*) malloc(sizeof(struct Link));
  list -> frontSentinel -> next = list ->backSentinel;
  list -> frontSentinel -> prev = NULL;
  list -> backSentinel -> prev = list -> frontSentinel;
  list -> backSentinel -> next = NULL;
  list -> size = 0;
}

static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value) {
  struct Link* newLink = (struct Link *)malloc(sizeof(struct Link));
  newLink ->value = value;
  newLink -> prev = link -> prev;
  link -> prev -> next = newLink;
  link -> prev = newLink;
  newLink -> next = link;

  list -> size ++;
}

static void removeLink(struct LinkedList* list, struct Link* link) { 
  assert(list != 0);

  link -> prev -> next = link -> next;
  link -> next -> prev = link -> prev;

  link -> prev = NULL;
  link -> next = NULL;
  link -> value = 0;
  free(link);

  list -> size -- ;
}

struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}


int linkedListIsEmpty(struct LinkedList* list) {
  if(list -> frontSentinel == list -> backSentinel) {
    return 1;
  }
  return 0;
}

void linkedListDestroy(struct LinkedList* list) {
  while(!linkedListIsEmpty(list)) {
    linkedListRemoveBack(list);
  }

  free(list -> frontSentinel);
  free(list -> backSentinel);
  free(list);
}

void linkedListPrint(struct LinkedList* list) {
	assert(list -> size != 0);
	struct Link *cur = list -> frontSentinel -> next;
	/* While the current pointer doesn't mean the end */
	while(cur != list -> backSentinel) {
		printf("%d \n", cur -> value);
		cur = cur -> next;
	}
}

void linkedListAddFront(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> frontSentinel -> next, value);
}

void linkedListAddBack(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> backSentinel, value);
}

TYPE linkedListFront(struct LinkedList* list) {
  return list -> frontSentinel -> next -> value;
}

TYPE linkedListBack(struct LinkedList* list) {
  return list -> backSentinel -> prev -> value;
}

void linkedListRemoveFront(struct LinkedList* list) {
  removeLink(list, list -> frontSentinel -> next);
}

void linkedListRemoveBack(struct LinkedList* list) {
  removeLink(list, list -> backSentinel -> prev);
}


void linkedListAdd(struct LinkedList* list, TYPE value) {
  addLinkBefore(list, list -> backSentinel, value);
}

int linkedListContains(struct LinkedList* list, TYPE value) {
  assert(list -> size != 0);
  struct Link *cur = list -> frontSentinel -> next;
  while(cur != list -> backSentinel) {
    if(cur -> value == value) {
      return 1;
    }
    cur = cur -> next;
  }
  return 0;
}

void linkedListRemove(struct LinkedList* list, TYPE value) {
  assert(list -> size != 0);
  struct Link *cur = list -> frontSentinel -> next;
  while(cur != list ->backSentinel) {
    if(cur -> value == value) {
      removeLink(list, cur);
      cur = list -> backSentinel;
    } else {
      cur = cur -> next;
    }
   }
}


int main() {
  struct LinkedList *list = linkedListCreate();
  linkedListAddBack(list, 10);
  linkedListAddFront(list,20);
  linkedListAddBack(list, 40);
  linkedListAddFront(list, 10);
  printf(" %d \n", linkedListFront(list));
  linkedListPrint(list);
  return 0;
}