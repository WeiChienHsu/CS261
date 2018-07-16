/* CS261- Assignment 3 Part 2  */
/* Name: Wei-Chien Hsu
 * Date: 07/16/2018
 * Solution description:
 * Circularly Linked List Deque Implementation
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	/* allocates the list's sentinel */
	list -> sentinel = malloc(sizeof(struct Link));
	assert(list -> sentinel != 0);
	
	/* Point to itself */
	list -> sentinel -> next = list -> sentinel;
	list -> sentinel -> prev = list -> sentinel;

	list -> size = 0; 
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = (struct Link *) malloc(sizeof(struct Link));
	assert(newLink != 0);

	newLink -> value = value;
	/* NULL next and prev pointers */
	newLink -> next = NULL;
	newLink -> prev = NULL;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
	struct Link *newLink = createLink(value);

	/* link <-> newLink <-> link.next */

	newLink -> prev = link;
	newLink -> next = link -> next;
	link -> next -> prev = newLink;
	link -> next = newLink;

	list -> size ++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list != 0);

	/* link.prev <-> link.next */
	link -> prev -> next = link -> next;
	link -> next -> prev = link -> prev;
	/* Free the link in order to disconnect with original list */
	link -> prev = NULL;
	link -> next = NULL;
	free(link);

	list -> size --;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while(!circularListIsEmpty(list)) {
		circularListRemoveFront(list);
	}

	free(list -> sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	/* O <-> s <-> newList <-> O */
	addLinkAfter(list, list -> sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	/* O <-> newList <-> s <-> O */
	addLinkAfter(list, list -> sentinel -> prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	return list -> sentinel -> next -> value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	return list -> sentinel -> prev -> value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	removeLink(list, list -> sentinel -> next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	removeLink(list, list -> sentinel -> prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if(list -> size == 0) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list != 0);
	struct Link *cur = list -> sentinel -> next;
	/* While current pointer doesn't meet sentinel (the end of list) */
	while(cur != list -> sentinel) {
		printf("%f\n", cur -> value);
		cur = cur -> next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list -> size != 0);

	/* use a two temp pointers to record from sentinel */

	struct Link *temp_cur = list -> sentinel -> next;
	list -> sentinel -> next = list -> sentinel -> prev;
	list -> sentinel -> prev = temp_cur;

	struct Link *temp_prev;
	/* Traverse from the new sentinel.next list */

	while(temp_cur != list -> sentinel) {
		temp_prev = temp_cur -> next;
		temp_cur -> next = temp_cur -> prev;
		temp_cur -> prev = temp_prev;
		temp_cur = temp_prev;
	}
}
