//  Assignment1
//  Write a C program to find the area of a triangle with
//  all its three sides given as a,b and c.
//  Created by WeiChien Hsu on 29/06/2018.

#include <stdio.h>
#include <math.h>

double countArea(float side1, float side2, float side3) {
    double const S = (side1 + side2 + side3) / 2.0;
    double const A = sqrt((S * (S - side1) * (S - side2) * (S - side3))) ;
    return A;
}

int main() {
    double side1 = 5;
    double side2 = 12;
    double side3 = 13;
    double area = countArea(side1, side2, side3);
    printf("We got a Triangle with 3 Sides : a = %f, b = %f, c = %f. \n", side1, side2, side3);
    printf("Count the Area of Triangle: %f \n", area);
    return 0;
}
