#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

FILE * readEdges() {

    FILE *cfPtr;
    char line[5000];

    if ((cfPtr = fopen("edges.csv", "r")) == NULL) {
        printf("File could not be opened\n");
    }else{
        while (!feof(cfPtr)) {
            fscanf(cfPtr, "%s", line);
            printf("%s\n", line);
        }
    }
    fclose(cfPtr);
}

FILE * readNodes() {

    FILE *cfPtr;
    char line[5000];

    if ((cfPtr = fopen("nodes.csv", "r")) == NULL) {
        printf("File could not be opened\n");
    }else{
        while (!feof(cfPtr)) {
            fscanf(cfPtr, "%s", line);
            printf("%s\n", line);
        }
    }
    fclose(cfPtr);
}

struct AdjacencyNode
{
    int destination;
    int weight;
    struct AdjacencyNode* next;
};

struct AdjacencyList
{
    struct AdjacencyNode *head;
};

struct Graph
{
    int Vertex;
    struct AdjacencyList* array;
};


struct AdjacencyNode* AdjacencyListNode(int dest, int weight)
{
    struct AdjacencyNode* newNode =
            (struct AdjacencyNode*) malloc(sizeof(struct AdjacencyNode));
    newNode->destination = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->Vertex = V;

    graph->array = (struct AdjacencyList*) malloc(V * sizeof(struct AdjacencyList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}


void addEdge(struct Graph* graph, int source, int destination, int weight)
{
    struct AdjacencyNode* newNode = AdjacencyListNode(destination, weight);
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;

    newNode = AdjacencyListNode(source, weight);
    newNode->next = graph->array[destination].head;
    graph->array[destination].head = newNode;
}


struct MinimumHeapNode
{
    int  vertex;
    int distance;
};


struct MinimumHeap
{
    int size;
    int capacity;
    int *position;
    struct MinimumHeapNode **array;
};

struct MinimumHeapNode* newMinHeapNode(int vertex, int distance)
{
    struct MinimumHeapNode* minHeapNode =
            (struct MinimumHeapNode*) malloc(sizeof(struct MinimumHeapNode));
    minHeapNode->vertex = vertex;
    minHeapNode->distance = distance;
    return minHeapNode;
}


struct MinimumHeap* createMinHeap(int capacity)
{
    struct MinimumHeap* minHeap =
            (struct MinimumHeap*) malloc(sizeof(struct MinimumHeap));
    minHeap->position = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
            (struct MinimumHeapNode**) malloc(capacity * sizeof(struct MinimumHeapNode*));
    return minHeap;
}


void swapMinHeapNode(struct MinimumHeapNode** a, struct MinimumHeapNode** b)
{
    struct MinimumHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinimumHeap* miniHeap, int index)
{
    int smallest, left, right;
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;

    if (left < miniHeap->size &&
        miniHeap->array[left]->distance < miniHeap->array[smallest]->distance )
        smallest = left;

    if (right < miniHeap->size &&
        miniHeap->array[right]->distance < miniHeap->array[smallest]->distance )
        smallest = right;

    if (smallest != index)
    {

        struct MinimumHeapNode *smallestNode = miniHeap->array[smallest];
        struct MinimumHeapNode *idxNode = miniHeap->array[index];

        miniHeap->position[smallestNode->vertex] = index;
        miniHeap->position[idxNode->vertex] = smallest;


        swapMinHeapNode(&miniHeap->array[smallest], &miniHeap->array[index]);

        minHeapify(miniHeap, smallest);
    }
}


int isEmpty(struct MinimumHeap* minHeap)
{
    return minHeap->size == 0;
}

struct MinimumHeapNode* extractMin(struct MinimumHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;


    struct MinimumHeapNode* root = minHeap->array[0];


    struct MinimumHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;


    minHeap->position[root->vertex] = minHeap->size-1;
    minHeap->position[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}


void decreaseVertexValue(struct MinimumHeap *minHeap, int vertex, int distance)
{

    int i = minHeap->position[vertex];


    minHeap->array[i]->distance = distance;

    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance)
    {
        minHeap->position[minHeap->array[i]->vertex] = (i-1)/2;
        minHeap->position[minHeap->array[(i-1)/2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool isInMinHeap(struct MinimumHeap *minHeap, int vertex)
{
    if (minHeap->position[vertex] < minHeap->size)
        return true;
    return false;
}

void printArray(int *dist, int n)
{
    printf("Vertex   Distance\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void shortestPath(struct Graph *graph, int source)
{
    int Vertex = graph->Vertex;
    int distance[Vertex];
    struct MinimumHeap* miniHeap = createMinHeap(Vertex);

    for (int vertex = 0; vertex < Vertex; ++vertex)
    {
        distance[vertex] = INT_MAX;
        miniHeap->array[vertex] = newMinHeapNode(vertex, distance[vertex]);
        miniHeap->position[vertex] = vertex;
    }

    miniHeap->array[source] = newMinHeapNode(source, distance[source]);
    miniHeap->position[source]   = source;
    distance[source] = 0;
    decreaseVertexValue(miniHeap, source, distance[source]);

    miniHeap->size = Vertex;

    while (!isEmpty(miniHeap))
    {
        struct MinimumHeapNode* minHeapNode = extractMin(miniHeap);
        int u = minHeapNode->vertex;

        struct AdjacencyNode* go = graph->array[u].head;
        while (go != NULL)
        {
            int vertex = go->destination;

            if (isInMinHeap(miniHeap, vertex) && distance[u] != INT_MAX &&
                go->weight + distance[u] < distance[vertex])
            {
                distance[vertex] = distance[u] + go->weight;
                decreaseVertexValue(miniHeap, vertex, distance[vertex]);
            }
            go = go->next;
        }
    }
    printArray(distance, Vertex);
}

int main()
{
    int V = 1001;
    struct Graph* graph = createGraph(V);
    readEdges();
    readNodes();
    shortestPath(graph, 0);
    
    return 0;
}
