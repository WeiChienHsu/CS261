/* CS261- Assignment 3 Part 1  */
/* Name: Wei-Chien Hsu
 * Date: 07/16/2018
 * Solution description:
 * Linked Lust Deque and Bag Implementation.
 */


#include "linkedList.h"
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

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	/* allocates frontSentinel */
	list -> frontSentinel = malloc(sizeof(struct Link));
	assert(list -> frontSentinel != 0);

	/* allocates backSentinel */
	list -> backSentinel = malloc(sizeof(struct Link));
	assert(list -> backSentinel != 0);

	/* NULL <-> front <-> back <-> NULL */
	list -> frontSentinel -> next = list -> backSentinel;
	list -> frontSentinel -> prev = NULL;

	list -> backSentinel -> prev = list -> frontSentinel;
	list -> backSentinel -> next = NULL;

	/* init size to 0 */
	list -> size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	/* O <-> X <-> O */
	/* O <-> newLink <-> X <-> O */
	/* Add new new Link and assign a newLink.next and newLink.prev */
	/* Change the link.prev.next and link.prev*/

	struct Link *newLink = (struct Link *) malloc(sizeof(struct Link));
	assert(newLink != 0);
	newLink -> value = value;

	newLink -> next = link;
	newLink -> prev = link -> prev;
	link -> prev -> next = newLink;
	link -> prev = newLink;

	/* Update the size of list */
	list -> size ++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != 0);

	/* Connect link prev with link next */
	link -> prev -> next = link -> next;
	link -> next -> prev = link -> prev;

	/* Disconnect link wiht current list and free the link */
	link -> prev = NULL;
	link -> next = NULL;
	link -> value = 0;
	free(link);

	list -> size --;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	/* front <-> new <-> *O <-> O */
	addLinkBefore(list, list -> frontSentinel -> next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	/* O <-> O <-> new <-> *back */
	addLinkBefore(list, list -> backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != 0);
	return list ->frontSentinel -> next -> value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != 0);
	return list -> backSentinel -> prev -> value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	/* Check if there is element could be revmoed */
	assert(!linkedListIsEmpty(list));
	/* front <-> *O <-> O */
	removeLink(list, list -> frontSentinel -> next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	/* Check if there is element could be revmoed */
	assert(!linkedListIsEmpty(list));
	/* O <-> *O <-> back */
	removeLink(list, list -> backSentinel -> prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list -> size == 0) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list -> size != 0);
	struct Link *cur = list -> frontSentinel -> next;
	/* While the current pointer doesn't mean the end */
	while(cur != list -> backSentinel) {
		printf("%d", cur -> value);
		cur = cur -> next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list -> backSentinel, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list -> size != 0);
	struct Link *cur = list -> frontSentinel -> next;
	/* While the current pointer doesn't mean the end */
	while(cur != list -> backSentinel) {
		if(cur -> value == value) {
			return 1;
		}
		cur = cur -> next;
	}
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list -> size != 0);
	struct Link *cur = list -> frontSentinel -> next;
	
	/* While the current pointer doesn't mean the end */
	while(cur != list -> backSentinel) {
		if(cur -> value == value) {
			removeLink(list, cur);
			cur = list -> backSentinel; /* Mark current pointer to the end */
		} else {
			cur = cur -> next; /* Move forward the current pointer */
		}
	}
}
