#include<stdio.h> 

int main() {

  int int1, int2, int3, int4, sum;
  
  // Original code (input and sum):
  /*
  printf("Enter the first integer: \n"); // prompt
  scanf("%d", &int1);                  // read an int
  printf("Enter the second integer:\n");
  scanf("%d", &int2);
  sum = int1 + int2;
  printf("Sum of %d and %d  is %d if you really wanted to know. \n", int1, int2, sum);
  */

  

  char my_char = 'A';

  double my_double = 3.14159;

  double another_double = 1.54;

  // Printing out the addresses of
  // where these variables are living
  printf("int1: %p\n", &int1);
  printf("int2: %p\n", &int2);
  printf("int3: %p\n", &int3);
  printf("int4;%p\n", &int4);
  
  printf("sum: %p\n", &sum);
  printf("my_char: %p\n", &my_char);
  printf("my_double: %p\n", &my_double);
  printf("another_double: %p\n", &another_double);

  
  // Printing out the char as either a char or int. 
    printf("testChar %c\n", my_char);
    printf("testInt %d\n\n",  my_char );

    printf("crazy letter is %c\n", 4000);
    
  // Printing a double
  printf("Double: %f\n", my_double);

  /*
  // Printing a double as an int
  printf("Int: %d\n", my_double);
  printf("Int (aDoub): %d\n", another_double); 

   */
  return 0; // Program finished successfully
}
