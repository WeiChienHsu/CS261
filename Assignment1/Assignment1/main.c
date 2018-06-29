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

void make_32(int* num) {
    *num = 32;
}

int main(){
//    struct student s = {.name = "Kevin", .gpa = 4.0 };
//    s.standing = 1;
//    printf("%d\n", s.standing);
    
//    int i = 20;
//    int* i_ptr = &i;
//    printf("%d\n", i); /* Print 20 */
//    printf("%p\n", i_ptr); /* Print memory Address : 0x7ffeefbff608*/
//    printf("%d\n", *i_ptr); /* Print the deference value from memory Address : 0x7ffeefbff608*/
//
//    *i_ptr = 8;
//    printf("%d\n", i); /* Print 8 */
//    printf("%p\n", i_ptr); /* Print memory Address*/
//    printf("%d\n", *i_ptr); /* Print the deference value from memory Address*/
    
//    int a = 30;
//    printf("%d \n", a);
//    make_32(&a);
//    printf("%d \n", a);
    
    
//    int i = 0;
//    int *n_ptr = (int*)malloc(sizeof(int));
//    n_ptr = &i;
//    printf("%d \n", *n_ptr);
    
    int i, n = 4096;
    int *nums = (int*)malloc(n * sizeof(int));
    int count = 0;
    for(i = 1; i < n; i *= 2) {
        nums[count] = i;
        printf("%d \n", nums[count++]);
    }
    
    
    
    return 0;
}




