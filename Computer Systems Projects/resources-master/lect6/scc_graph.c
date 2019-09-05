#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_NODES 17

// ==============================================
// Structs and prototypes.

typedef struct listItem ListItem;

void destroyListItem(ListItem*); 

typedef struct node Node; 

struct node{
  char* data; 
  ListItem* neighbor; 
  int nodeId; // Helper field assigned by graph. Used in topo.
  int startTime; // Helpers for doing Strongly Connected Components.
  int finishTime;
  int visited;
  int component; 
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


Node* createNode(char* data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data; 
	
  newNode->neighbor = NULL; 
  newNode->nodeId = -1;
  newNode->visited = 0;
  newNode->component = -1; 
  return newNode; 
}

void destroyNode(Node *node){
  if (node == NULL) return; 
  destroyListItem(node->neighbor);
  free(node);
}

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
Graph* createGraph_scc() {
  Graph* graph = createGraph(); 

  // Create nodes
  Node* nA = createNode("A"); 
  Node* nB = createNode("B"); 	
  Node* nC = createNode("C"); 
  Node* nD = createNode("D"); 
  Node* nE = createNode("E"); 
  Node* nF = createNode("F"); 
  Node* nG = createNode("G"); 
  Node* nH = createNode("H");
  
  addNode(graph, nA); 
  addNode(graph, nB); 
  addNode(graph, nC); 
  addNode(graph, nD); 
  addNode(graph, nE); 
  addNode(graph, nF); 
  addNode(graph, nG); 
  addNode(graph, nH);
  
  // Create edges
  addEdge(nA, nB);
  addEdge(nB, nC); 
  addEdge(nB, nE);
  addEdge(nB, nD); 
  addEdge(nC, nA);
  addEdge(nD, nA); 
  addEdge(nD, nF);
  addEdge(nE, nF); 
  addEdge(nG, nE);
  addEdge(nF, nG);
  addEdge(nD, nH);
  addEdge(nH, nF); 

  return graph; 
}

Graph* createTranspose(Graph* g) {
  // Create new graph
  Graph* transG = createGraph();
    printf("adding node duplicates\n"); 
  // Add all the same nodes to the graph
  for (int i=0; i<g->numNodes; i++) {
    // Make a copy
    Node* newNode = createNode(g->nodes[i]->data); 
    addNode(transG, newNode);
    newNode->finishTime = g->nodes[i]->finishTime; 
  }

  // Add edges in the reverse direction
  for (int i=0; i<g->numNodes; i++) {
    ListItem* neighbor = g->nodes[i]->neighbor;
    while (neighbor != NULL) {
      addEdge(transG->nodes[neighbor->origNode->nodeId], transG->nodes[i]);
      neighbor = neighbor->nextListItem; 
    }
  }
  return transG; 
}

// returns finish time for this node
int calculateFinishTime(Node* root, int startTime) { 
  Node* stack[MAX_NUM_NODES];
  int top = 0;

  root->visited = 1;
  root->startTime = startTime;
  
  // Put all the neighbors on the stack
  ListItem* neighbors = root->neighbor;
  while (neighbors != NULL) {
    if (neighbors->origNode->visited == 0) {
      stack[top++] = neighbors->origNode;
      neighbors->origNode->visited = 1; // so it doesn't get put on the stack twice
    }
    neighbors = neighbors->nextListItem;
  }
  
  int time = startTime; 
  // pop off each neighbor, and calc FinishTime for the neighbor
  while (top > 0){
    Node* curNode;
    curNode = stack[--top];
  
    time = calculateFinishTime(curNode, ++time);
    }
  root->finishTime = ++time; 
  return time; 
}

// graph is the transpose graph
void findComponents(Graph* graph, int componentId) {
  // Find the node with the latest finishing time.
  Node* first = NULL;
  int lastTime = -1;
  
  for (int i=0; i<graph->numNodes; i++) {
    if (graph->nodes[i]->finishTime > lastTime) {
      first = graph->nodes[i];
      lastTime = first->finishTime; 
    }
  }

  if (lastTime == -1 || first == NULL) {
    return; 
  }
  
  // Do a depth-first search from there.
  Node* stack[MAX_NUM_NODES];
  int top = 0;

  stack[top++] = first;

  
  while(top > 0) {
    // Pop node off
    Node* curNode = stack[--top];
    
    // Assign componentId and fix finishTime
    curNode->component = componentId;
    curNode->finishTime = -1;
    curNode->visited = 1;
    
    // Put neighbors on
    ListItem* neighbors = curNode->neighbor;
    while (neighbors != NULL) {
      if (neighbors->origNode->visited == 0) {
        stack[top++] = neighbors->origNode;
        neighbors->origNode->visited = 1; // so it doesn't get put on the stack twice
      }
      neighbors = neighbors->nextListItem;
    }    
    printf("Component %d: Node %s\n", componentId, curNode->data); 
  }
  findComponents(graph, componentId+1); 
}

void printGraph(Graph* graph){
  int i;

  for (i=0; i<graph->numNodes; i++){

    Node* node = graph->nodes[i];
    printf("Node: %s. ==== ", node->data);
    ListItem* neighbor = node->neighbor; 
        
    while (neighbor != NULL){
      printf("Node: %s. ==== ", neighbor->origNode->data); 
      neighbor = neighbor->nextListItem;
    }
    printf("\n");
  }
}


int main(){
  Graph* graph = createGraph_scc();

  printGraph(graph); 
  
  int finishTime = calculateFinishTime(graph->nodes[0], 1);

  for (int i=0; i<graph->numNodes; i++) {
    printf("Node %s\tStartTime: %d\tFinishTime: %d\n", graph->nodes[i]->data,
           graph->nodes[i]->startTime, graph->nodes[i]->finishTime); 
  }
  
  printf("Creating transposeG\n"); 
  Graph* transposeG = createTranspose(graph); 
  printGraph(transposeG); 
  printf("transposeG has %d nodes\n", transposeG->numNodes); 

  findComponents(transposeG, 1);

  printf("\n"); 
  destroyGraph(graph);
  destroyGraph(transposeG); 
}
