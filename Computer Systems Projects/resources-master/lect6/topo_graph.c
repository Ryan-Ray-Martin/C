#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_NODES 17

// ==============================================
// Structs and prototypes.

typedef struct listItem ListItem;

typedef struct node Node; 

struct node{
  char* data; 
  ListItem* neighbor; 
  int nodeId; // Helper field assigned by graph. Used in topo. 
}; 

struct graph{
  Node* nodes[MAX_NUM_NODES]; 
  int numNodes; 
};

typedef struct graph Graph;

struct listItem{
  Node* origNode;
  ListItem* nextListItem; 
};

//==============================================

ListItem* createListItem(){
  ListItem* item = (ListItem*)malloc(sizeof(ListItem));
  item->origNode = NULL;
  item->nextListItem = NULL;
  return item; 
}

void destroyListItem(ListItem *item) {
  if (item == NULL) return; 
  destroyListItem(item->nextListItem);
  item->nextListItem = NULL; 
  item->origNode = NULL; 
  free(item); 
}


Node* createNode(char* data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data; 
	
  newNode->neighbor = NULL; 
  newNode->nodeId = -1; 
  return newNode; 
}

void destroyNode(Node *node){
  if (node == NULL) return; 
  destroyListItem(node->neighbor);
  free(node);
}

Graph* createGraph(){
  Graph* out = (Graph*)malloc(sizeof(Graph));
  int i; 

  for (i = 0; i<MAX_NUM_NODES; i++){
    out->nodes[i] = NULL; 
  }
  out->numNodes = 0; 

  return out; 
}

void destroyGraph(Graph* graph) {
  for (int i=0; i<graph->numNodes; i++) {
    destroyNode(graph->nodes[i]); 
  }
  free(graph); 
}

//==================================


void addNode(Graph* graph, Node* node){
  node->nodeId = graph->numNodes;
  graph->nodes[graph->numNodes++] = node; 
}

void addEdge(Node* u, Node* v){
  ListItem* listItem = createListItem();

  listItem->origNode = v;
  listItem->nextListItem = u->neighbor;

  u->neighbor = listItem; 
}

// Creates the graph used in Lecture 6 (Spr 2019)
Graph* createGraph_topo() {
  Graph* graph = createGraph(); 

  // Create nodes
  Node* nA = createNode("A"); 
  Node* nB = createNode("B"); 	
  Node* nC = createNode("C"); 
  Node* nD = createNode("D"); 
  Node* nE = createNode("E"); 
  Node* nF = createNode("F"); 
  Node* nG = createNode("G"); 

  addNode(graph, nA); 
  addNode(graph, nB); 
  addNode(graph, nC); 
  addNode(graph, nD); 
  addNode(graph, nE); 
  addNode(graph, nF); 
  addNode(graph, nG); 

  // Create edges
  addEdge(nA, nB);
  addEdge(nB, nC); 
  addEdge(nB, nD); 
  addEdge(nA, nC);
  addEdge(nC, nE); 
  addEdge(nC, nF); 
  addEdge(nF, nE);
  addEdge(nE, nD); 
  addEdge(nG, nA);
  addEdge(nG, nF); 

  return graph; 
}

// Helper function: returns 1 if an edge exists between n1->n2
// Returns 0 otherwise
int edgeExists(Node* n1, Node* n2) {
  ListItem* li = n1->neighbor; 
  while (li != NULL) {
    if (li->origNode == n2) {
      return 1;
    }
    li = li->nextListItem;
  }
  return 0; 
}

// Calculates the in-degree of every node in the graph. 
// Stores it in the provided array. 
void calculateInDegree(Graph* graph, int counts[]) {
  // Go through every node
  for (int i=0; i<graph->numNodes; i++) {
    for (int j=0; j<graph->numNodes; j++) {
      if (i == j)
        continue; 
      if (edgeExists(graph->nodes[j], graph->nodes[i])) {
        counts[i]++; 
      }
    }
  }
  // Print out for sanity
  for (int i=0; i<graph->numNodes; i++) {
    printf("Node %s\tCount: %d\n", graph->nodes[i]->data, counts[i]); 
  }
}

// Returns the index of the first element that is zero 
// in the array degreeCounts. 
// degreeCounts: an array of ints that represent the in-degree of nodes in a graph
// numNodes: the number of nodes, also the length of the array.
// returns: the first element of the array that is zero. 
// returns -1 if no element has value 0. 
int findZeroNode(int degreeCounts[], int numNodes) {
  for (int i=0; i<numNodes; i++) {
    if (degreeCounts[i] == 0) {
      return i;
    }
  }
  return -1; 
}


int main(){
  Graph* graph = createGraph_topo(); 
  int in_degrees[MAX_NUM_NODES] = {0}; 
  calculateInDegree(graph, in_degrees); 

  int zeroNodeInd = findZeroNode(in_degrees, MAX_NUM_NODES);

  if (zeroNodeInd == -1) {
    printf("No zero nodes, so can't do topo sort!!\n"); 
    destroyGraph(graph); 
    return 0; 
  }
	
  zeroNodeInd = findZeroNode(in_degrees, graph->numNodes); 

  while (zeroNodeInd != -1) {
    //printf("zeroNodeInd: %d\n", zeroNodeInd); 
    Node* zeroNode = graph->nodes[zeroNodeInd];

    printf("%s-", zeroNode->data); 
    // Update the items. 
    ListItem* neighbor = zeroNode->neighbor; 

    while (neighbor != NULL) {
      in_degrees[neighbor->origNode->nodeId]--; 
      neighbor = neighbor->nextListItem; 
    }

    // Using -1 as a sentinel value to indicate node is already out. 
    in_degrees[zeroNodeInd] = -1;
    zeroNodeInd = findZeroNode(in_degrees, graph->numNodes); 
  }

  printf("\n"); 
  destroyGraph(graph); 
}
