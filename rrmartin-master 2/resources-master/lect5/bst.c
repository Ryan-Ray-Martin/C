#include <stdio.h>
#include <stdlib.h>


typedef struct node Node;

struct node{
  int key;
  char* value; 
  Node* leftChild;
  Node* rightChild;
  Node* parent;
};


//================================



Node* CreateNode(int key, char* value){
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->key = key;
  newNode->value = value; 
  
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  newNode->parent = NULL;

  return newNode;
}

void DestroyNode(Node *node){
  if (node == NULL) return;

  DestroyNode(node->leftChild);
  DestroyNode(node->rightChild);
  //  DestroyNode(node->parent);

  // Destroy node
  free(node);
}
void PrintNode(Node *node){
  printf("%s: %d\n", node->value, node->key);
}

void PrintTree(Node *node, int numTabs, char whichChild){
  if (node != NULL){
    for (int i=0; i<numTabs; i++) {
      printf("\t"); 
    }
    printf("%c: %s: %d\n", whichChild, node->value, node->key);
    PrintTree(node->leftChild, numTabs+1, 'L');
    PrintTree(node->rightChild, numTabs+1, 'R');
  }
}

// Finds the min of the binary tree rooted at node.
//
// node: the root of the binary tree. 
Node* FindMin(Node* node) {
  Node* current_node = node;

  while (current_node->leftChild != NULL) {
    current_node = current_node->leftChild;
  }
  return current_node;
}

void ReplaceNodeInParent(Node *node, Node *newNode) {
  if (node->parent != NULL) {
    if (node == node->parent->leftChild) {
      printf("Replacing leftChild of parent. \n"); 
      node->parent->leftChild = newNode;
      if (newNode != NULL) {
        newNode->parent = node->parent;
      }
    } else {
      printf("Replacing right child\n"); 
      node->parent->rightChild = newNode;
      if (newNode != NULL) {
        newNode->parent = node->parent;
      }
    }
  } else {
    printf("Parent is null; not replacing anything\n"); 
  }  
}

void BinaryTreeDelete(Node* node, int key) {
  if (key < node->key) {
    BinaryTreeDelete(node->leftChild, key);
    return; 
  } else  {
    if (key > node->key) {
      BinaryTreeDelete(node->rightChild, key);
      return; 
    }
  }
  // We have found the node with the key value
  if (node->leftChild && node->rightChild) {
    printf("Node to replace has two children.\n"); 
    // There are two children
    Node* successor = FindMin(node->rightChild);
    node->key = successor->key;
    node->value = successor->value;
    BinaryTreeDelete(successor, successor->key);
  } else {
    if (node->leftChild) {
      // The node has only a left child
      // Replace this node with the value of the left child; delete the left child
      ReplaceNodeInParent(node, node->leftChild); 
    } else {
      if (node->rightChild) {
        printf("Node to replace has only right child\n"); 
        // The node has only a right child
        // Replace this node with the value of the right child; delete the right child
        ReplaceNodeInParent(node, node->rightChild); 
      } else {
        printf("deleting node with no chilrden\n"); 
        // node has no children
        // Just delete this node
        ReplaceNodeInParent(node, NULL); 
        DestroyNode(node); // TODO: any other cleanup to do here?
      }
    }
    
  }
}

Node* Insert(Node* root, int key, char* value) {
  printf("Inserting node with value %s\n", value); 
  if (!root) {
    root = CreateNode(key, value);
  } else {
    if (key < root->key) {
      printf("Adding new node to the left\n"); 
      root->leftChild = Insert(root->leftChild, key, value);
      root->leftChild->parent = root; 
    } else {
      // key >= root->key
      printf("Adding new node to the right\n"); 
      root->rightChild = Insert(root->rightChild, key, value);
      root->rightChild->parent = root; 
    }
  }  
  return root;
}    

int main() {
  Node* root = Insert(NULL, 25, "Mustafa");
  Insert(root, 15, "Jane");
  PrintTree(root,0, 'A'); 

   Insert(root, 17, "Jim");
  PrintTree(root,0, 'A'); 
  Insert(root, 100, "Jack");
  PrintTree(root,0, 'A'); 
  Insert(root, 38, "Ben"); 
  PrintTree(root,0, 'A'); 
  Insert(root, 52, "Madison"); 
  PrintTree(root,0, 'A'); 
  Insert(root, 5, "Alec"); 
  PrintTree(root,0, 'A'); 
  Insert(root, 53, "Stella"); 

  
  Insert(root, 58, "Deb");
  Insert(root, 75, "Poppy");
  Insert(root, 24, "Walter");
  Insert(root, 61, "Dude");
  Insert(root, 98, "Alfalfa"); 
  
  PrintTree(root,0, 'A');
  
  
  BinaryTreeDelete(root, 38);

  PrintTree(root, 0, 'A');
  
  BinaryTreeDelete(root, 75);

  PrintTree(root, 0, 'A');
}

