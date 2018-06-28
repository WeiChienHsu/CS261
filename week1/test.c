#include<stdio.h>

void foo(int x) {
  printf("Foo got %d\n", x);
}

int main(int argc, char** argv) {
  foo(2);
}