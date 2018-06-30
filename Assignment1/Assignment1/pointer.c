//
//  pointer.c
//  Assignment1
//
//  Created by weichien on 29/06/2018.
//  Copyright © 2018 WeiChien. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void makeNumber32(int num) {
    num = 32;
}



void makeNumber32_PassByPointer(int *num) {
    *num = 32;
}

struct student {
    char* name;
    int standing;
    float gpa;
};


void setStudent(struct student * s, char* name, int standing, float gpa) {
    (*s).name = name;
    (*s).standing = standing;
    (*s).gpa = gpa;
}

void printStudentInfo(struct student *s) {
    printf("%s \n", s->name);
    printf("%d \n", s->standing);
    printf("%f \n", s->gpa);
}

int pointerPlayGround(){
    int a = 30;
    makeNumber32(a);
    printf("%d \n", a);
    makeNumber32_PassByPointer(&a);
    printf("%d \n", a);
    
    struct student* kevin = malloc(sizeof(struct student));
    
    setStudent(kevin, "Kevin", 2, 3.2);
    
    printStudentInfo(kevin);
    
    free(kevin);
    
    return 0;
}
