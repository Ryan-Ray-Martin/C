#include<stdio.h>

void cubeByReference(int *);

int main(){
  int number = 5;

  printf("The original value of the number is %d\n", number);


  cubeByReference(&number);

  printf("The new value of the number is %d\n", number);

  return 0;
}

void cubeByReference(int *nPtr) {
  *nPtr = *nPtr * *nPtr * *nPtr;
}
