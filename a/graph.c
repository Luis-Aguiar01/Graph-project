#include "graph.h"

Graph *createNewGraph() {
    Graph *newGraph = malloc(sizeof(Graph));

    newGraph->adj = NULL;
    newGraph->cities = malloc(sizeof(City **));
    *(newGraph->cities) = NULL;
    newGraph->roads = 0;

    return newGraph;
}

void addNewCity(Graph *graph) {
    City *newCity = malloc(sizeof(City));

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", newCity->name);

    City *firstCity = *(graph->cities);

    if (firstCity == NULL) {
        *(graph->cities) = newCity;
        newCity->id = 1;
        newCity->next = NULL;
    }
    else {
        
        while (firstCity->next != NULL) {
            firstCity = firstCity->next;
        }

        firstCity->next = newCity;
        newCity->next = NULL;
        newCity->id = firstCity->id + 1;
    }
}

void printCities(Graph *graph) {
    City *firstCity = *(graph->cities);
    
    while (firstCity != NULL) {
        printf("Nome: %s\n", firstCity->name);
        printf("ID: %d\n", firstCity->id);
        printf("\n");
        firstCity = firstCity->next;
    }
}