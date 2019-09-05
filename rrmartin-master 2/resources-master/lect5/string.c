#include<stdio.h>
#include<string.h>

#define MAX_STR_LENGTH 100

int main() {

  /*
  // Multiple ways to declare strings
  char *string1 = "blue";
  char string3[] = "green";
  char string4[] = {'r', 'e', 'd', '\0'};
  char string15[MAX_STR_LENGTH];
  char *string2; 
  
  printf("string1: %s\n", string1);
  printf("string3: %s\n", string3);
  printf("string4: %s\n", string4);



  // Part 2 & 3
  //  string1[0] = 'A'; 
  string3[0] = 'A';
  string4[0] = 'A';
  
  printf("string1: %s\n", string1);
  printf("string3: %s\n", string3);
  printf("string4: %s\n", string4);

  
  // Part 4
  

  char *string2;
  string2 = string1;
  printf("string2: %s\n", string2);

  string2 = string3;
  printf("string2: %s\n", string2);
  
  string2 = string4;
  printf("string2: %s\n", string2);
*/  
  // Part 5

  char string5[3] = "purple"; //{'p', 'u', 'r', '\0'}
  char string6[10] = {'p', 'u', '\0', 'p', 'l', 'e', '\0'};
  printf("string5: %s\n", string5);
  printf("string6: %s\n", string6);

  printf("length string5: %d\n", strlen(string5));
  printf("length string6: %d\n", strlen(string6));
         

}
