#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"

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
void startMatrixValues(Graph *graph, int size);
bool addNewRoad(Graph *graph, int city1, int city2, int distance);
int getCitiesCount(Graph *graph);
void chooseCitiesForNewRoad(Graph *graph);
int returnNumLenght(int num);
bool removeRoad(Graph *graph, int city1, int city2);
void chooseCitiesForDeleteRoad(Graph *graph);
int returnNumLenght(int num);
void showDirectRoadsByCity(Graph *graph);
City *searchCity(Graph *graph, int ID);
void freeMemory(Graph *graph);