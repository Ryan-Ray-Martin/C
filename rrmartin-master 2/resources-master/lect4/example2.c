#include<stdio.h>
#include<stdlib.h>

struct thing {
  int value;
  int age; 
};
typedef struct thing Thing; 

void doThing(Thing myThing) {
  printf("myThing is at %p with value %d and age %d\n", &myThing, myThing.value, myThing.age);
  myThing.age = 15;
}

Thing createThing() {
  Thing thing;
  thing.age = 4;
  thing.value = 750;
  printf("myNewThing is at %p with value %d and age %d\n", &thing, thing.value, thing.age);
  return thing; 
}

Thing* mallCreateThing() {
  Thing* out = malloc(sizeof(Thing));
  out->age = 42;
  out->value = 6;
  return out; 
}

int* createArray() {
  int array[] = {1, 2, 3};
  return array; 
}



int main() {

  Thing* aThing = mallCreateThing(); 

  
  /*  Thing aThing;
  aThing.value = 6;
  aThing.age = 78;
  */
  //  Thing aThing = createThing(); 
  aThing->value = 6;
  printf("aThing is at %p with value %d and age %d\n", &aThing, aThing->value, aThing->age);

  /*  int size = 999999;
  
  Thing* things[size]; 
  
  for (int i=0; i<size
	 ; i++) {
    things[i] = mallCreateThing(); 
    }*/
  
  free(aThing); 
  /*
  int something = 5; 
  Thing thing2 = createThing();
  
  doThing(aThing);
  printf("aThing is at %p with value %d and age %d\n", &aThing, aThing.value, aThing.age);

  something = 6; 
  printf("soinethging %d", something); 
  */
  return 0; 
}

