
#include<stdio.h>

int cubeByValue(int);

void cubeByReference(int*);

int main(){

  int number = 5;

  printf("The original value of the number is %d\n", number);
  //  number = cubeByValue(number);
  cubeByReference(&number); 
  printf("The new value of hte number is %d\n", number);

  return 0;
}

void cubeByValue(int n) {
  //  return n*n*n;
  n = n*n*n;   
}

void cubeByReference(int *nPtr) {
  *nPtr = *nPtr * *nPtr * *nPtr;
}
