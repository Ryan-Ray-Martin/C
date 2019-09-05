#include<stdio.h>
#include<stdlib.h>

typedef struct node Node; 

struct node {
  char* data;
  Node *next;
  Node *prev; 
};

int counter = 0; 

void myMalloc(long size) {
  malloc(size);
  counter++; 
}

void myFree(void *data) {
  free(data);
  counter--; 
}

Node* createNode() {
  Node* out = (Node*)malloc(sizeof(Node));

  out->next = NULL;
  out->prev = NULL;
  out->data = ""; 
  
  return out; 
}

void destroyNode(Node *node) {
  //  node->data = "";
  //  node->prev = NULL;
  //  node->next = NULL; 
    
  free(node); 
}

void printNode(Node *node) {
  printf("%p %s\n", node, node->data); 
}



int main() {
  Node *node = createNode();

  printNode(node);

  node->data = "Don't Panic";

  printNode(node); 

  destroyNode(node); 
  
  printNode(node);

  printf("%s\n", node->data); 
}













