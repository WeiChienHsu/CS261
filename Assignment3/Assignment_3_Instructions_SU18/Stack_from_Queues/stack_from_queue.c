/* CS261- Assignment 3 Part 3
 * Date: 07/16/2018
 * Name: Wei-Chien Hsu
 * Email:	hsuweic@oregonstate.edu
 * Linked List Stack Implementation using two Queue
 * Use Two Queues (Recorded Queue and Helper Queue):
 * 
 * queueStackPush: When push a new Queue, use one of them to record the order.
 * 
 * queueStackTop: When need to search for the Stack Peek, pop out the elements 
 * from recorded queue and leave the last element stands for the peek. Record it's
 * value and then push into the Helper Queue. In the end, swap back two different 
 * queue. Return the record value.
 * 
 * queueStackPop: When need to pop element from Stack, which mean we need to remove 
 * the last elelment in the recorded queue, so we could pop out all the elements 
 * instead of the last one into peek into Helper Queue, and Remove the only element in 
 * Record Queue. In the end, swap those two Queues.
 * 
 * printStack: Print the front in Record Queue, push it into the Helper Queue and remove 
 * that specific element. In the end swap back those two Queues.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef TYPE
#define TYPE int
#endif

/**************************************************
 All of the initial Queue functions
 ***************************************************/
struct link {
	TYPE value;
	struct link * next;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
	int size;
};

/*
* This function takes a queue and allocates the memory. It then
* creates a sentinel and assigns the first link and last link
* to the sentinel.
*/
void listQueueInit(struct listQueue *q) {
	struct link *sentinel = (struct link *) malloc(sizeof(struct link));
	assert(sentinel != 0);
	sentinel -> next = 0;
	/* assigns the first link and last link to the sentinel */ 
	q -> firstLink = sentinel;
	q -> lastLink = sentinel;
	/* Init the size of listQueue */
	q -> size = 0;
}

/*
 * This function creates a new queue. Parts of the create include 
allocating
 * the memory, initializing all of the values and returning a pointer to 
the newly
 * created queue.
 */
struct listQueue * listQueueCreate()
{
 struct listQueue *newLinkQ = (struct listQueue *) malloc(sizeof(struct listQueue));
 listQueueInit(newLinkQ);
 return newLinkQ; 
}


/*
* This function returns a 1 or 0 based on the statement looking at
* the first link. If the next value is null it is empty, and will return 1
*/
int listQueueIsEmpty(struct listQueue *q) {
	if(q -> size == 0) {
		return 1;
	} else {
		return 0;
	}
}

/*
 * This function adds a new link and value to the back of the queue. It 
takes
 * a list and a type variable, allocates the memory and adjusts the proper 
links
 * to make the connection. No return value.
 */
void listQueueAddBack(struct listQueue *q, TYPE e) {

	struct link *newLink = (struct link *) malloc(sizeof(struct link));
	
	assert(newLink != 0);
	newLink -> value = e;
	newLink -> next = NULL;
	/* Add after the lastLink and move forward the current lastLink pointer */
	q -> lastLink -> next = newLink;
	q -> lastLink = newLink;
	q -> size ++;
}

/*
 * This function takes a list argument and removes the link at the front.
 */
void listQueueRemoveFront(struct listQueue *q) {
	assert(!listQueueIsEmpty(q));
	/* Create a temp link points to the first elelment */
	struct link *tempLink = q -> firstLink;

	q -> firstLink = tempLink -> next;

	if(q -> lastLink == tempLink) {
		q -> lastLink = NULL;
	}

	free(tempLink);
	q -> size --;
}

/*
 * Function returns the value at the front of the list.
 */
TYPE listQueueFront(struct listQueue *q) {
	assert(!listQueueIsEmpty(q));
	return q ->firstLink -> next -> value;
}


/*
* This function is a tester function that iterates through the list
* and prints out the values at each link.
*/
void printList(struct listQueue* l)
{
	assert(l != 0);
	
	struct link * printMe = l->firstLink->next;

	while (printMe!= NULL)
	{
		printf("Value: %d\n", printMe->value);
		printMe = printMe->next;
	}
}

/**************************************************
Stack Implementation
***************************************************/

struct linkedListStack {
	struct listQueue *Q1; /* Record Queue */
	struct listQueue *Q2; /* Helper Queue */
	int structSize;
};

/*
 * This function initializes the values of the created Stack. Initializes 
both 
 * queues and the structSize.
 */
void linkedListStackInit(struct linkedListStack * s)
{
	s -> Q1 = listQueueCreate();
	s -> Q2 = listQueueCreate();
	s -> structSize = 0;
 }

/*
* This function creates the linked list stack. It allocates the memory and 
calls the
* initialization function to initialize all of the values. It then returns 
the stack.
*/
struct linkedListStack * linkedListStackCreate(){
	struct linkedListStack *newStack = malloc(sizeof(struct linkedListStack));
	linkedListStackInit(newStack);
	return newStack;
}

/*
* This function returns 1 if the linked list stack is empty and otherwise 
returns a 0.
*/
int linkedListStackIsEmpty(struct linkedListStack *s) {
	assert(s != NULL);
	if(s -> structSize == 0) {
		return 1;
	} else {
		return 0;
	}
}

/*
* This function swaps Record Queue and Helper Queue.
*/
void swap(struct linkedListStack *s){
    struct listQueue *temp;
		temp = s -> Q1 ;
    s -> Q1 = s -> Q2;
    s -> Q2 = temp;
}

/*
 * This is the linked list acting as a stack push function. It takes 
 * a linked list stack argument and a value and pushes it onto the stack. 
The
 * funciton then also increases the size of the stack by 1. 
 */
void linkedListStackPush(struct linkedListStack *s, TYPE d) {
	assert(s);
	listQueueAddBack(s -> Q1, d); /* push the element into Record Queue */
	s -> structSize ++;
}
/*
 * This funciton pops a value off of the stack. It does this by moving all 
values
 * that are currently on the stack to the other queue. The stack top is 
maintained
 * at the back of the queue list. 
 */
void linkedListStackPop(struct linkedListStack *s) {
	assert(s != NULL);
	
	if (s -> structSize == 0) {
		/* if current stack is empty print the error message */
	  printf("Stack is empty, cannot pop! \n");
  } else {
		/* Pop out elements from Q1 to Q 2 */
		while(!listQueueIsEmpty(s -> Q1)) {
			/* If there is only one element in the Q1 */
			if(s -> Q1 -> firstLink -> next == s -> Q1 -> lastLink) {
					listQueueRemoveFront(s -> Q1); /* Pop out the peek in the stack */
			} else {
				/* Keep poping until there is only one element in the Q1 */
				/* Push the first element in Q1 into Q2 */
				listQueueAddBack(s -> Q2, listQueueFront(s -> Q1));
				listQueueRemoveFront(s -> Q1); 
			}
		}
		swap(s);
		s -> structSize --;
	}
}
/*
 * This function returns the value that is at the back of the queue that 
is 
 * maintaing the values of the stack. 
 */
TYPE linkedListStackTop(struct linkedListStack *s) {
	assert(s != NULL);
	assert(!listQueueIsEmpty(s -> Q1));
	TYPE value; /* Record the only elelment leave in the Q1 */

	while(!listQueueIsEmpty(s -> Q1)) {
		/* If there is only one element in the Q1 */
		if(s -> Q1 -> firstLink -> next == s -> Q1 -> lastLink) {
				value = listQueueFront(s -> Q1);
		} 
		/* Keep poping until there is only one element in the Q1 */
		/* Push the first element in Q1 into Q2 */
		listQueueAddBack(s -> Q2, listQueueFront(s -> Q1));
		listQueueRemoveFront(s -> Q1); 
	}

	swap(s);
	return value;
}

/*
 * This function gores through the stack and removes each link in the 
queue.
 * It then frees the struct itself. 
 */
void linkedListStackFree(struct linkedListStack *s){
	
  assert(s != 0);
	
	while (s->structSize != 0) 
	{
		linkedListStackPop(s);
	}

	free(s->Q1->firstLink);
	free(s->Q2->firstLink);
	free(s->Q1);
	free(s->Q2);

	free(s);
}

/*
 * Main is used to test the stack ADT.
 */
int main(int argc, char* argv[])
{
	struct linkedListStack *stack = linkedListStackCreate();

	//Test Stack
	//Push 4 values onto the stack
	printf("Pushing the value: 1\n");
	linkedListStackPush(stack, 1);
	printf("Pushed.\n\n");

	printf("Pushing the value: 2\n");
	linkedListStackPush(stack, 2);
	printf("Pushed.\n\n");

	printf("Pushing the value: 3\n");
	linkedListStackPush(stack, 3);
	printf("Pushed.\n\n");

	
	printf("Pushing the value: 4\n");
	linkedListStackPush(stack, 4);
	printf("Pushed.\n\n");


	//Print value at the top and then remove it
	printf("Value at the top of stack %d now being popped. \n",linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));  
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	//Try to pop when the stack is empty prints error:
	printf("Trying to pop empty stack:\n");

	linkedListStackPop(stack);

	
	//Push and Pop alternating
	printf("Pushing the value: 10\n");
	linkedListStackPush(stack, 10);
	printf("Pushed.\n\n");

	printf("Pushing the value: 11\n");
	linkedListStackPush(stack, 11);
	printf("Pushed.\n\n");

	printf("One more pop:\n");
	linkedListStackPop(stack);
	printf("Value at the top of stack: %d\n", 
	linkedListStackTop(stack));

	linkedListStackFree(stack);

	return 0;

}


