
//
// Created by Ryan Martin on 2019-02-22.
//

//Dear grader,
//
//I am not 100% sure if I did this assignment correctly,
//but I did try my best and was able to read the files,
//put it into an adjacency matrix, and implement that matrix
//as a graph in Djikstra's algorithm. However, when I printed
//out the path, I could not tell how to interpret the path
//and answer the question, so I must have done something
//wrong somewhere.
//
//Thank you for your understanding.

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>


#define V 1001
#define ARRAY_WIDTH 5000

int minimumDistance(int *distance,
                    bool *set)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (set[v] == false &&
            distance[v] <= min)
            min = distance[v], min_index = v;

    return min_index;
}

void printDjikstraPath(int *parent, int j)
{

    if (parent[j] == - 1)
        return;

    printDjikstraPath(parent, parent[j]);

    printf("%d ", j);
}

int printSolution(int distance[], int n,
                  int parent[])
{
    int src = 0;
    printf("Vertex\t Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ",
               src, i, distance[i], src);
        printDjikstraPath(parent, i);
    }
}

void dijkstra(int graph[V][V], int src)
{

    int distance[V];

    bool set[V];

    int parent[V];

    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        distance[i] = INT_MAX;
        set[i] = false;
    }

    distance[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {

        int u = minimumDistance(distance, set);

        set[u] = true;

        for (int v = 0; v < V; v++)

            if (!set[v] && graph[u][v] &&
                distance[u] + graph[u][v] < distance[v])
            {
                parent[v] = u;
                distance[v] = distance[u] + graph[u][v];
            }
    }

    printSolution(distance, V, parent);
}


int adjacencyMatrix(int argc, char *argv()) {


    int *array[ARRAY_WIDTH];
    int index = 0;
    int j = 0;
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;
    char *ptr = NULL;

    FILE *fp;
    fp = fopen("miles_graph.csv", "r");
    if(!fp) {
        fprintf(stderr, "file cannot be opened.\n");
    }
    while ((read = getline (&buffer, &len, fp)) != -1) {

        array[index] = malloc (sizeof (array));

        for (j = 0, ptr = buffer; j < ARRAY_WIDTH; j++, ptr++)
            array [index][j] = (int)strtol(ptr, &ptr, 10);

        index++;
    }

    fclose(fp);
    int i = 0;

    for(i=0; i<index; i++){
        printf("\narray[%d][] =", i);

        for (j=0; j<ARRAY_WIDTH; j++)
            printf(" %d", array[i][j]);
    }

    puts("");

    return 0;


}

int main(){

    int graph[V][V] = {adjacencyMatrix(5000, (char *(*)()) "miles_graph.csv")};

    dijkstra(graph, 0);
    return 0;
}
