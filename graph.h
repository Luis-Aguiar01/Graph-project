#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include "interface.h"

typedef struct city {
    char name[50];
    int id;
    struct city *next;
} City;

typedef struct graph {
    City **cities;
    int **adj;
} Graph;

typedef struct nodeQueue {
    int id;
    int custo;
} NodeQueue;

typedef struct priorityQueue {
    int size;
    NodeQueue *heap;
} PriorityQueue;

Graph *createNewGraph();
void addNewCity(Graph *graph);
void printCities(Graph *graph);
void printAdjacencyMatrix(Graph *graph);
void startMatrixValues(Graph *graph);
bool addNewRoad(Graph *graph, int city1, int city2, int distance);
int getCitiesCount(Graph *graph);
void chooseCitiesForNewRoad(Graph *graph);
bool removeRoad(Graph *graph, int city1, int city2);
void chooseCitiesForDeleteRoad(Graph *graph);
void showDirectRoadsByCity(Graph *graph);
City *searchCity(Graph *graph, int ID);
void freeMemory(Graph *graph);
bool consultRoadBetweenCities(Graph *graph);
bool checkAvailableCity(Graph *graph, char *cityName);
bool stringCompareIgnoreCase(char *name1, char *name2);
bool areThereRegisteredRoads(Graph *graph);
void startCity(City *city);
int compareQueueNodes(const void *a, const void *b);
PriorityQueue *createPriorityQueue(int numVertices);
void enqueue(PriorityQueue *pq, int id, int custo);
NodeQueue dequeue(PriorityQueue *pq);
void dijkstra(Graph *g, int origem);
void chooseCityForMinPath(Graph *graph);
void printPath(Graph *g, int destino, int *path);
void printResultForDijkstra(Graph *g, int *path, int *distance, int origem);