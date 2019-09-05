#include <stdio.h>

void printArray(int*, int);

void printArray2(int[], int);

int ARRAY_SIZE = 15; 

int main() {


  char *somevar = "Once upon a time"; 

  char color1[] = "blue";
  char *colorPtr = "blue";  // creates a variable of type char pointer
  char color2[] = {'b', 'l', 'u', 'e', '\0'};


  printf("color: %s\n", colorPtr);

  int array[ARRAY_SIZE];

  for (int i=0; i<ARRAY_SIZE; i++) {
    array[i] = i; 
  }

  printArray(array, ARRAY_SIZE); 

  printf("\n\n");

  printArray2(array, ARRAY_SIZE);

  return 0; 
}

void printArray(int *a, int len) {
  for (int i=0; i<len; i++) {
    printf("%d\n", a[i]); 
  }
}




void printArray2(int a[], int len) {
  for (int i=0; i<len; i++) {
    printf("%d\n", a[i]); 
  }
}
