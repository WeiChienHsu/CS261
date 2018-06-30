//
//  main.c
//  Assignment1
//
//  Created by weichien on 28/06/2018.
//  Copyright © 2018 WeiChien. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h> 

struct student {
    char* name;
    int standing;
    float gpa;
};

void make_32(int* num) {
    *num = 32;
}

void init_student(struct student* s, char* name, float gpa) {
    s->name = name;
    s->gpa = gpa;
}

int main(){
;
    
    return 0;
}




