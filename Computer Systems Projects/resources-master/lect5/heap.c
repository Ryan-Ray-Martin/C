#include <stdio.h>
#include <stdlib.h>



struct heap{
  int vals[1000];
  int lastVal;
};

typedef struct heap Heap;

void printHeap(Heap *heap); 
void insertInHeap(Heap *heap, int newVal){

  heap->vals[heap->lastVal++] = newVal;

  int new_ind = heap->lastVal-1;
  int par_ind = (new_ind - 1)/2;

  while (heap->vals[par_ind] > heap->vals[new_ind]){
    printf("swapping new val %d with parent val %d\n", heap->vals[new_ind], heap->vals[par_ind]); 
    // Swap them
    // logic goes here
    heap->vals[new_ind] = heap->vals[par_ind];
    heap->vals[par_ind] = newVal;
    printHeap(heap); 
    new_ind = par_ind;
    par_ind = (new_ind - 1)/2;
  }

}

int dequeueHeap(Heap *heap){
  int out_val = heap->vals[0];
  heap->lastVal--; 
  
  // Put the last leaf at the root
  heap->vals[0] = heap->vals[heap->lastVal];

  int p = 0; // parent
  int c1 = 1; // child1
  int c2 = 2; // child2

  // If it were a max heap
  int max_ind = (heap->vals[c1] > heap->vals[c2]) ? c1 : c2;
  // What we're using for a min heap
  int min_ind = (heap->vals[c1] < heap->vals[c2]) ? c1 : c2;
  /*
  if (heap->vals[c1] > heap->vals[c2]) {
    max_ind = c1;
  } else {
    max_ind = c2;
  }
  */
  if (heap->vals[min_ind] < heap->vals[p]){
    // Swap
    int tmp = heap->vals[min_ind];
    heap->vals[min_ind] = heap->vals[p];
    heap->vals[p] = tmp;

    p = min_ind;
    c1 = (2 * p) + 1;
    c2 = (2 * p) + 2;

    // TODO: Check going out of bounds of the array/off the bottom of the heap.

  }

  return out_val;
}


void printHeap(Heap *heap){
  int ind = 1;

  // Print root
  //printf("%d\n", heap->vals[0]);

  for (int i=0; i<heap->lastVal; i++) {
    printf("%d-", heap->vals[i]); 
  }
  printf("\n"); 
}


int main(){

  Heap heap;
  heap.lastVal = 0;

  insertInHeap(&heap, 5);
  printHeap(&heap);

  printf("Inserting 19....\n"); 
  insertInHeap(&heap, 19);
  printHeap(&heap);
  printf("Inserting 15....\n"); 
  insertInHeap(&heap, 15);
  printHeap(&heap);
  printf("Inserting 9....\n"); 
  insertInHeap(&heap, 9);
  insertInHeap(&heap, 3);
   
  printf("\n\n"); 
  printHeap(&heap);

  insertInHeap(&heap, 25);
  insertInHeap(&heap, 10);
  insertInHeap(&heap, 11);
  insertInHeap(&heap, 16);

  printHeap(&heap); 
  printf("lowest val: %d\n", dequeueHeap(&heap));

  printHeap(&heap);
  
}
