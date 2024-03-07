#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct city {
    char name[50];
    int id;
    struct city *next;
} City;

typedef struct graph {
    City **cities;
    int roads;
    int **adj;
} Graph;

Graph *createNewGraph();
void addNewCity(Graph *graph);
void printCities(Graph *graph);
void printAdjacencyMatrix(Graph *graph);
void startMatrixValues(Graph* graph, int size);