
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "a3.h"
#include <string.h>


// YOUR CODE GOES HERE


void big(Name *name){
  if (name->middle)
  {
    printf("%s %s  %s\n", name->first, name->middle,  name->last);
  }
 
  printf("%s %s\n", name->first,  name->last);
   
}

void last(Name *name)
{
  printf("%s, %s\n", name->last, name->first);
}

void reg(Name *name)
{
  printf("%s %s\n", name->first, name->last);
}
   

void mid(Name *name)
{
  if (name->middle)
    {
      printf("%s %c. %s\n", name->first, *name->middle, name->last);
    }
    printf("%s %s\n", name->first, name->last);
}

void small(Name *name)
{
  printf("%s\n", name->first);
}

void formatName(Name *name, char format){
  switch(format)
    {
    case 'B':
    case 'b':
      big(name);
      break;
    case 'L':
    case 'l':
      last(name);
      break;
    case 'R':
    case 'r':
      reg(name);
      break;
    case 'M':
    case 'm':
      mid(name);
      break;
    case 'S':
    case 's':
      small(name);
      break;
    }
}

void fillName(Name *name, char format, char *dest){
  switch(format)
    {
    case 'B':
    case 'b':
      if(name->middle){
	strcat(dest, (const char*) name->first);
	strcat(dest, " ");
	strcat(dest, (const char*) name->middle);
	strcat(dest, " ");
	strcat(dest, (const char*) name->last);
	strcat(dest, " ");
      }else{
	strcat(dest, (const char*) name->first);
	strcat(dest, " ");
	strcat(dest, (const char*) name->last);
	strcat(dest, " ");
      }
      break;
    case 'L':
    case 'l':
        strcat(dest, (const char*) name->last);
	strcat(dest, " ");
	strcat(dest, (const char*) name->first);
	strcat(dest, " ");
      break;
    case 'R':
    case 'r':
        strcat(dest, (const char*) name->first);
	strcat(dest, " ");
	strcat(dest, (const char*) name->last);
	strcat(dest, " ");
      break;
    case 'M':
    case 'm':
      if(name->middle){
	strcat(dest, (const char*) name->first);
	strcat(dest, " ");
	strcat(dest, (const char*) name->middle);
	strcat(dest, " ");
	strcat(dest, (const char*) name->last);
	strcat(dest, " ");
      }else{
	strcat(dest, (const char*) name->first);
	strcat(dest, " ");
	strcat(dest, (const char*) name->last);
	strcat(dest, " ");
      }
      break;
    case 'S':
    case 's':
       strcat(dest, (const char*) name->first);
       strcat(dest, " ");
      break;
    }
}

//void sortNames(char arr[], int n){
// char temp[100];
//  int j, i;
//  for (int j=0; j<n-1; j++){
//   for (int i=j+1; i<n; i++){
//    if (strcmp(arr[j], arr[i]) > 0){
//	strcpy(temp, arr[j]);
//	strcpy(arr[j], arr[i]);
//	strcpy(arr[i], temp);
//      }
//    }
//  }
//}

//void listByName(Name *n1, Name *n2, Name *n3, char format){
//  char arr[100] = {0};
//  printf("%s\n", arr);
//  int n = sizeof(arr)/sizeof(arr[0]);

//  sortNames(arr, n);
//  printf("Names in sorted order are: ");
//  for (int i=0; i<n; i++)
//    printf("\n String %d is %d", i + 1, arr[i]);
//}

//void listByAge(Name* names[], int numNames, char format){
//  int i, key, j;
//  for (i = 1; i<n; i++){
//    key = names[i];
//    j = i-1;
//    while (j>=0 && names[i] < key){
//      names[j+1] = names[j];
//      j= j-1;
//    }
//    names[j+1] =(const int*) key;
//  }
//}

//int ages(){
//  int i;
//  int size = 4;
//  int arr[size];
//  for (i=1; i<size+1; i++){
//    arr[i] = name->age;
//  }
//  return arr[i];
//}
  

    
