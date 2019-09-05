#include <stdio.h>

void checkN(int);

void check2(); 

int n = 1;

int NUM_CARDS = 5; 


int main() {
  int x = 2;

  checkN(x);

  check2(n, x); 
  
  printf("The value of n in main is: %d\n", n);
}

void checkN(int n) {
  check2(); 
  printf("The value of n in checkN is: %d\n", n);
}

void check2() {
  n = 3;
}
