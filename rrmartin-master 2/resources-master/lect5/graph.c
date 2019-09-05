#include <stdio.h>
#include <stdlib.h>
#include "print-ascii-bintree.h"
/*
typedef struct node Node;

struct node{
  char* data;
  Node* leftChild;
  Node* rightChild;
  Node* parent;
} ;

*/
struct binaryTree{
  char* root;

};

typedef struct binaryTree BinaryTree;


//==============================================



Node* createNode(char* data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->element = data;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  newNode->parent = NULL;

  return newNode;
}

void destroyNode(Node *node){
  if (node == NULL) return;

  destroyNode(node->leftChild);
  destroyNode(node->rightChild);
  destroyNode(node->parent);

  // Destroy node
  free(node);
}

// 1 to add the node as a left child;
// 0 to add the node as a right child.
void addChild(Node *node, Node* child, int leftChild){
  if (leftChild){
    node->leftChild = child;
  }
  else{
    node->rightChild = child;
  }
}

/*
  Root
      ------N1
          |.     |-----n3
              |      |-----n4
                  |             |--n5
                      |             |--n6
                          |
                              |------N2
*/

Node* createTree1(){
  Node *root = createNode("Root");
  Node *n1 = createNode("1");
  Node *n2 = createNode("2");
  Node *n3 = createNode("3");
  Node *n4 = createNode("4");
  Node *n5 = createNode("5");
  Node *n6 = createNode("6");
  Node *n7 = createNode("7");
  Node *n8 = createNode("8");


  addChild(root, n1, 1);
  addChild(root, n2, 0);

  addChild(n1, n3, 1);
  addChild(n1, n4, 0);

  addChild(n4, n5, 1);
  addChild(n4, n6, 0);

  return root;
}

void printNode(Node *node){
  printf("%s\n", node->data);
}


void printTreeDfsPost(Node *root){
  if (root->leftChild != NULL) {
    printTreeDfsPost(root->leftChild);
  }

  if (root->rightChild != NULL){
    printTreeDfsPost(root->rightChild);
  }


  if (root != NULL){
    printNode(root);
  }
}

void printTreeDfsPre_v2(Node *root){
  Node* stack[15];
  int top = 0;

  stack[top++] = root;

  Node* curNode;

  while (top > 0){

    curNode = stack[--top];

    if (curNode != NULL){
      printNode(curNode);
    }

    if (curNode->rightChild != NULL){
      stack[top++] = curNode->rightChild;
    }

    if (curNode->leftChild != NULL){
      stack[top++] = curNode->leftChild;
    }

  }
}

void printTreeBfs(Node *root){
  Node* queue[15];
  int head = 0;
  int tail = 0;

  queue[tail++] = root;

  Node* curNode;

  // TODO: Check to make sure we don't put too many elements in!!
  while (head != tail){

    curNode = queue[head++];

    if (curNode != NULL){
      printNode(curNode);
    }

    if (curNode->rightChild != NULL){
      queue[tail++] = curNode->leftChild;
    }

    if (curNode->leftChild != NULL){
      queue[tail++] = curNode->rightChild;
    }

  }
}





int main(){

  Node* tree1 = createTree1();
  printTreeDfsPost(tree1);
  printf("\n\n");
  printTreeDfsPre_v2(tree1);
  printf("\n\n");
  printTreeBfs(tree1);

  print_ascii_tree(tree1); 
  /*
  Node t;
  t.data = "5";

  //free(t);
  Node *tree = &t;

  free(tree);
  */
  
}
