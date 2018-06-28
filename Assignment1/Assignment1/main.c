//
//  main.c
//  Assignment1
//
//  Created by weichien on 28/06/2018.
//  Copyright © 2018 WeiChien. All rights reserved.
//

#include <stdio.h>

struct student {
    char* name;
    int standing;
    float gpa;
};

int main(){
//    struct student s = {.name = "Kevin", .gpa = 4.0 };
//    s.standing = 1;
//    printf("%d\n", s.standing);
    
    int i = 20;
    int* i_ptr = &i;
    printf("%d\n", i); /* Print 20 */
    printf("%p\n", i_ptr); /* Print memory Address : 0x7ffeefbff608*/
    printf("%d\n", *i_ptr); /* Print the deference value from memory Address : 0x7ffeefbff608*/
    
    *i_ptr = 8;
    printf("%d\n", i); /* Print 8 */
    printf("%p\n", i_ptr); /* Print memory Address*/
    printf("%d\n", *i_ptr); /* Print the deference value from memory Address*/
    
    
    return 0;
}




