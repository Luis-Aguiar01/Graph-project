#include "graph.h"

Graph *createNewGraph() {
    Graph *newGraph = malloc(sizeof(Graph));

    newGraph->adj = malloc(sizeof(int **));
    
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
    
    City *endCity = *(graph->cities);

    while (endCity->next != NULL) {
        endCity = endCity->next;
    }

    int cityCount = endCity->id;

    if (graph->adj == NULL) {
        graph->adj = malloc(sizeof(int *) * cityCount);
        for (int i = 0; i < cityCount; i++) {
            graph->adj[i] = malloc(sizeof(int) * cityCount);
        }
    }
    else {
        graph->adj = realloc(graph->adj, sizeof(int *) * cityCount);
        graph->adj[cityCount - 1] = malloc(sizeof(int) * cityCount);
    }

    void startMatrixValues(graph, cityCount);
}

void printCities(Graph *graph) {
    City *firstCity = *(graph->cities);
    
    printf("=========================================================\n");
    printf("||                 CIDADES CADASTRADAS                 ||\n");
    printf("=========================================================\n");

    while (firstCity != NULL) {
        printf("|| [%d] %-20s                            ||\n", firstCity->id, firstCity->name);
        firstCity = firstCity->next;
    }

    printf("=========================================================\n");
}

void startMatrixValues(Graph* graph, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph->adj[i][j] = 0;
        }
    }
}

void printAdjacencyMatrix(Graph *graph) {

    City *endCity = *(graph->cities);
    
    if (endCity != NULL) {
        
        while (endCity->next != NULL) {
            endCity = endCity->next;
        }

        int cityCount = endCity->id;

        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                printf("%d ", graph->adj[i][j]);
            }
            printf("\n");
        }
    } 
}