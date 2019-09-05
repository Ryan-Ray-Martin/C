#include <stdio.h>

// Declaring the size of the array as a
//   global constant
const int ARRAY_SIZE = 10;

int main() {

  // Declaring an array
  int arr[10];
  
  // Since we always need to know the
  // size of an array, it helps to store
  // it as a global and use it. 
  int arr2[ARRAY_SIZE]; 

  // Iterating through the array
  for (int i=0; i<=10; i++) {
    arr[i] = i; 
  }

  for (int i=0; i<10; i++) {
    printf("%d\n", arr[i]);
  }
  
  
  // Playing with char arrays and printing strings
  char sparky[5];

  sparky[0] = 'j';
  sparky[1] = 'b';
  sparky[2] = 'o';
  //  sparky[3] = 'a';
  //  sparky[4] = 'z';
  //sparky[5] = 'f'; // Oops, we went over the end!!
  //  sparky[10] = '\0'; 
  
  // Trying to see if we can write over the char array
  int r = 7; 
  
  // What gets printed? 
  //   printf("Sparky: %s\n", sparky); 
   
  // Printing each char and its address
  for (int i=0; i<5; i++) {
    printf("%p\t%c\n", &sparky[i], sparky[i]); 
    }

  // Where was that extra int we created stored? 
  //  printf("\n%p\n", &r); 

  //  printf("arr: %p\n", &arr); 
  
  // Iterating through the array backwards. 
  /*
  for (int i=9; i>=0; i++) {
    printf("%d\n", arr[i]); 
  }
  */

  return 0;
}
