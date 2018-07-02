/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 * 1) The function int foo(int *a, int *b, int c) should perform the following computations :
 * - Swap the addresses of the integers pointed to by a and b 
 * (not the values of the integers pointed to by a and b).
 * - Decrement the value of c.
 * - Return the value of c.
 * 
 * 2) In the main function, declare three integers x, y, and z, and assign them random integer 
 * values in the interval [0, 10]. Print the values of the integers x, y, and z. 
 * 
 * Call foo(..) appropriately passing x, y, and z as arguments. 
 * Print out the values of integers x, y, and z after calling the function foo(..). 
 * Also, print the value returned by foo(..).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    int *temp = a;
    a = b;
    b = temp;

    /*Decrement the value of integer variable c*/
    c--;
    /*Return c*/
    return c;
}

int main(){
    /* Use current time as seet for random generator */
    srand(time(0));

    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;

    /*Print the values of x, y and z*/
    printf("Value of x : %d \n", x);
    printf("Value of y : %d \n", y);
    printf("Value of z : %d \n", z);    
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    foo(&x, &y, z);
    printf("-- Call foo() -- \n");   
    
    /*Print the values of x, y and z*/
    printf("Value of x : %d \n", x);
    printf("Value of y : %d \n", y);
    printf("Value of z : %d \n", z);    
    
    /*Print the value returned by foo*/
    printf("Value return by foo : %d \n", foo(&x, &y, z));
    
    return 0;
}

/* a) Is the return value different than the value of integer z? Why or why not?
 * Yes. The return value will be different. Since in the foo function, we decrement 
 * the value of integer variable c and directly call the return syntax to get the 
 * value of c stored in the call stack when the funciton is called.
 * 
 * b) Are the values of integers x and y different before and after calling 
 * the function foo(..)? Why or why not?
 * No. When we called the funciton foo, the sawp of addresses stored in the pointer, were
 * just changed in the function scale not since we didn't pass the pointer by reference which 
 * is not allowed in the C programming */
    
    


