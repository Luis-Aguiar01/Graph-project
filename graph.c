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

    printf(GREEN"Digite o nome da cidade: ");
    scanf(" %[^\n]"RESET, newCity->name);

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
    
    int cityCount = getCitiesCount(graph);

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

    startMatrixValues(graph, cityCount);
}

void chooseCitiesForNewRoad(Graph *graph) {
    clearScreen();
    
    int city1 = 0;
    int city2 = 0;
    int distance = 0;

    printCities(graph);

    printf(GREEN"Digite o numero da primeira cidade: ");
    scanf("%d", &city1);

    printf("Digite o numero da segunda cidade: ");
    scanf("%d", &city2);

    printf("Digite a distancia da estrada: ");
    scanf("%d"RESET, &distance);

    city1--;
    city2--;
    
    int cityCount = getCitiesCount(graph);
    
    if (city1 >= 0 && city1 < cityCount) {
        if (city2 >= 0 && city2 < cityCount && city2 != city1) {
            if (distance > 0) {
                addNewRoad(graph, city1, city2, distance);
            }
            else {
                printf(RED"\n\nErro: A distancia entre as duas cidades nao pode ser zero ou negativa.\n\n"RESET);
            }
        }
        else {
            printf(RED"\n\nErro: Número inválido para a segunda cidade.\n\n"RESET);
        }
    }
    else {
        printf(RED"\n\nErro: Número inválido para a primeira cidade.\n\n"RESET);
    } 

    aguardarEnter();
}

bool addNewRoad(Graph *graph, int city1, int city2, int distance) {

    bool result = false;

    if (graph->adj[city1][city2] == 0 && graph->adj[city2][city1] == 0) {
        graph->adj[city1][city2] = distance;
        graph->adj[city2][city1] = distance;
        result = true;
        printf(GREEN"\n\nEstrada adicionada com sucesso!\n\n"RESET);
    }
    else {
        printf(RED"\n\nErro: Ja existe uma estrada ligando as duas cidades.\n\n"RESET);
    }
    
    return result;
}

void printCities(Graph *graph) {
    
    City *firstCity = *(graph->cities);
    
    printf(BLUE"=========================================================\n");
    printf("||                 CIDADES CADASTRADAS                 ||\n");
    printf("=========================================================\n");

    while (firstCity != NULL) {
        printf("|| [%d] %-20s                            ||\n", firstCity->id, firstCity->name);
        firstCity = firstCity->next;
    }

    printf("=========================================================\n"RESET);
}

void startMatrixValues(Graph *graph, int size) {
    for (int i = 0; i < size; i++) {
        graph->adj[size - 1][i] = 0;
        graph->adj[i][size - 1] = 0;
    }
}

int getCitiesCount(Graph *graph) {
    City *endCity = *(graph->cities);

    while (endCity->next != NULL) {
        endCity = endCity->next;
    }

    int cityCount = endCity->id;

    return cityCount;
}

void printAdjacencyMatrix(Graph *graph) {
    clearScreen();

    City *endCity = *(graph->cities);
    
    if (endCity != NULL) {
        
        printf(BLUE"                       ");
       
        while (endCity!= NULL) {
            int largura = 22;
            int tamanho = largura - strlen(endCity->name);
            printf("%*s%s%*s", tamanho / 2, "", endCity->name, tamanho / 2, "");
            endCity = endCity->next;
        }

        printf("\n");

        endCity = *(graph->cities);
        int cityCount = getCitiesCount(graph);

        for (int i = 0; i < cityCount; i++) {
            printf("%-22s|", endCity->name);
            for (int j = 0; j < cityCount; j++) {
                int largura = 22;
                int tamanho = returnNumLenght(graph->adj[i][j]);
                int result = (largura - tamanho) / 2;
                printf("%*s%d%*s|", result, "", graph->adj[i][j], result, "");
            }
            endCity = endCity->next;
            printf("\n");
        }
        printf(RESET);
    } 
}

int returnNumLenght(int num) {

    int result = 0;

    if (num <= 9) {
        result = 1;
    }

    while (num != 0) {
        result++;
        num /= 10;
    }

    return result;
}

bool removeRoad(Graph *graph, int city1, int city2) {

    bool result = false;

    if (graph->adj[city1][city2] != 0 && graph->adj[city2][city1] != 0) {
        graph->adj[city1][city2] = 0;
        graph->adj[city2][city1] = 0;
        result = true;
        printf(GREEN"\n\nEstrada removida com sucesso!\n\n"RESET);
    }
    else {
        printf(RED"\n\nErro: Nao há estrada entre as duas cidades para ser excluida.\n\n"RESET);
    }

    return result;
}

void chooseCitiesForDeleteRoad(Graph *graph) {
    int city1 = 0;
    int city2 = 0;
    
    printCities(graph);

    printf(GREEN"Digite o numero da primeira cidade: ");
    scanf("%d", &city1);

    printf("Digite o numero da segunda cidade: ");
    scanf("%d"RESET, &city2);

    city1--;
    city2--;
    
    int cityCount = getCitiesCount(graph);
    
    if (city1 >= 0 && city1 < cityCount) {
        if (city2 >= 0 && city2 < cityCount && city2 != city1) {
            removeRoad(graph, city1, city2);
        }
        else {
            printf(RED"\n\nErro: Número inválido para a segunda cidade.\n\n"RESET);
        }
    }
    else {
        printf(RED"\n\nErro: Número inválido para a primeira cidade.\n\n"RESET);
    } 

    aguardarEnter();
}

void showDirectRoadsByCity(Graph *graph) {
    clearScreen();

    printf(BLUE"================================================\n");
    printf("||           PROCURAR ESTRADAS DIRETAS        ||\n");
    printf("================================================\n"RESET);
    
    printCities(graph);

    int city = 0;
    int cityCount = getCitiesCount(graph);
    int count = 1;

    printf(GREEN"\nEscolha o numero da cidade para ver todas as suas estradas diretas: ");
    scanf("%d"RESET, &city);

    city--;

    if (city < cityCount && city >= 0) {
       
        printf("====================================================\n");
        printf("||        ESTRADAS DIRETAS DE %-22s               ||\n");
        printf("====================================================\n");
        
        for (int i = city; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                if (graph->adj[i][j] != 0) {
                    City *currentCity = searchCity(graph, j); 
                    printf("|| [%d] %-22s | Distancia: %d km       ||\n", count, currentCity->name, graph->adj[i][j]);
                    count++;
                }
            }
        }
    }
    else {
        printf(RED"\n\nErro: Numero de cidade invalido.\n\n"RESET);
    }

    aguardarEnter();
}

City *searchCity(Graph *graph, int ID) {
    City *searchCity = *(graph->cities);

    if (searchCity != NULL) {
        while (searchCity != NULL && searchCity->id != ID) {
            searchCity = searchCity->next;
        }
    }

    return searchCity;
}

void freeMemory(Graph *graph) {

    City *cities = *(graph->cities);
    int citiesCount = getCitiesCount(graph);

    if (cities != NULL) {

        City *nextCity = NULL;

        while (cities != NULL) {
            nextCity = cities->next;
            free(cities);
            cities = nextCity;
        }

        graph->cities = NULL;
    }

    if (citiesCount > 0) {

        for (int i = 0; i < citiesCount; i++) { 
            free(graph->adj[i]);
        }

        free(graph->adj);

        graph->adj = NULL;
    }
}

bool consultRoadBetweenCities(Graph *graph) {
    bool result = false;

    



    return result;
}