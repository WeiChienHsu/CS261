/* CS261- Assignment 2  */
/* Name: Wei-Chien Hsu
 * Date: 07/15/2018
 * Application of the Stack - Checking balanced paretheses, braces, and brackets
 * Solution description:
 * char nextChar(char *s) : return the next character or '\0' if at the end of string
 * int isBalanced(char *s) : return 1 if the string is balanced and 0 if it is not balanced.
 *  
 * Algorithm :
 * I used a stack.
 * If met {, [, (, put it into the Stack
 * if met } , look for the peek and if the peek was not { return 0
 * if met ],  look for the peek and if the peek was not [ return 0
 * if met ), look for the peek and if the peek was not ( return 0
 * After we went through the string, check if the Stack is Empty, 
 * if not return 0, or return 1
 * delete the Stack before returning value 
 */

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/

char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* Create a Stack implemented by Dynamic Array */
	/* Need to delete this Stack before return the final value */
	DynArr *stack = newDynArr(10);

	char temp_char = nextChar(s);

	while (temp_char != '\0') {
		/* If met (, {, or [ push it into the stack */
		if(EQ(temp_char, '(') || EQ(temp_char, '[') || EQ(temp_char, '{')) {
			pushDynArr(stack, temp_char);
		}

		/* met ) */
		if(EQ(temp_char, ')')) {
			char peek = topDynArr(stack);

			/* if the peek is not equal ), return 0 */
			if(!EQ(peek, '(')) {
				deleteDynArr(stack);
				return 0;
			}

			popDynArr(stack);
		}

		/* met ] */
		if(EQ(temp_char, ']')) {
			char peek = topDynArr(stack);

			/* if the peek is not equal [, return 0 */
			if(!EQ(peek, '[')) {
				deleteDynArr(stack);
				return 0;
			}

			popDynArr(stack);
		}

		/* met } */
		if(EQ(temp_char, '}')) {
			char peek = topDynArr(stack);

			/* if the peek is not equal {, return 0 */
			if(!EQ(peek, '{')) {
				deleteDynArr(stack);
				return 0;
			}
			
			popDynArr(stack);
		}

		/* Move forward to check next character in the string */
		temp_char = nextChar(s);
	}

	/* If Stack is not Empty, return 0 */
	if(!isEmptyDynArr(stack)) {
		deleteDynArr(stack);
		return 0;
	}

	/* All the characters were checked, retrun 1*/
	deleteDynArr(stack);
	return 1;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

