/* CS261- Assignment 1 - Q. 0*/
/* Name: Wei-Chien Hsu
 * Date: 07/01/2018
 * Solution description:
 * 
 * 1. In the main() function, declare an integer, x. Then assign it to a random integer value in 
 * the interval [0, 10]. Then print the value and address (using the address of operator) of x.
 *
 * 2. In fooA(int * iptr) function, print the value of the integer pointed to by iptr and the 
 * address pointed to by iptr. Change the value of the integer pointed to by iptr as instructed 
 * in the skeleton code. Print the address of iptr itself at the end.
 * 
 * 3. In the main() function, following the call to fooA(..), print the value of x. Answer the 
 * following question in a comment right after printing the value of x. 
 * ** Is the value of x 
 * ** different than the value that was printed at first? Why or why not?
 * 
 * 
 * 4. In fooB(int * jptr) function, print the value of the integer pointed to by jptr and the 
 * address pointed to by jptr. Then change the address stored in the pointer variable jptr 
 * as instructed in the skeleton code. Print the address of jptr itself at the end.
 * 
 * 5. In the main function, following the call to fooB(..), print the value and address of x. 
 * Answer the following question in a comment right after printing the value and address of x:
 * 
 * ** Are the value and address of x different than the value and address that were printed 
 * ** before the call to fooB(..)? Why or why not?
 */

 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){

     /*Print the value and address of the integer pointed to by iptr*/
    printf("Value of the integer pointed to by iptr* : %d. (In fooA func) \n", *iptr);
    printf("Address of the integer pointed to by iptr* : %p.  (In fooA func) \n", iptr);   

     /*Increment the value of the integer pointed to by iptr by 5*/
     *iptr += 5;     
     /*Print the address of iptr itself*/
     printf("Address of iptr itseld %p.  (In fooA func) \n", &iptr);

}


void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
    printf("Value of the integer pointed to by jptr* : %d.  (In fooB func) \n", *jptr);
    printf("Address of the integer pointed to by jptr* : %p.  (In fooB func) \n", jptr);     
               
     /*Decrement jptr by 1*/
     *jptr -= 1;
      
     /*Print the address of jptr itself*/
     printf("Address of jptr itseld %p.  (In fooB func) \n", &jptr);
}


int main(){
    /* Use current time as seet for random generator */
    srand(time(0));

    /*Declare an integer x and initialize it randomly to a value in [0,10] */
    int x = rand() % 11;
    
    /*Print the value and address of x*/
    printf("Value of the integer of x : %d. (In main func) \n", x);
    printf("Address of the integer of x : %p. (In main func)  \n", &x);   

    /*Call fooA() with the address of x*/
    fooA(&x);  

    /*  Is the value of x different than the value that was printed at first? Why or why not? */
    /* Yes. The value of x was changed when we called the fooA function. Since we passed the address
        of integer x into the functino and used a pointer to point to its address and then deferenced 
        the address to modify content inside that memory stored, thus the acutal value in that specified
        address was changed and when we call that address out by print the value of integer x, we got the
        different x */

    /*Print the value of x*/
    printf("Value of the integer of x : %d. (In main func)  \n", x);
    
    /*Call fooB() with the address of x*/
    fooB(&x);  
    
    /*Print the value and address of x*/
    printf("Value of the integer of x : %d. (In main func)  \n", x);
    printf("Address of the integer of x : %p. (In main func)  \n", &x);   

    /* Are the value and address of x different than the value and address that were 
    printed before the call to fooB(..)? Why or why not? */

    /* Value changed from 11 to 10 since we passed the address of x into the function and modify the value
       by deferencing the pointer but the actual address didn't change. Reason why the address kept the same
       is because we didn't create a new space in memeory to store any new interger or value */
    
    
    return 0;
}




