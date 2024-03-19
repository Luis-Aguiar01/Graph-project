#include "graph.h"

Graph *createNewGraph() {
    Graph *newGraph = malloc(sizeof(Graph));

    newGraph->adj = malloc(sizeof(int **));
    *(newGraph->adj) = NULL;

    newGraph->cities = malloc(sizeof(City **));
    *(newGraph->cities) = NULL;
    
    return newGraph;
}

void addNewCity(Graph *graph) {
    clearScreen();

    printf(BLUE"=========================================================\n");
    printf("||                 ADICIONAR CIDADES                   ||\n");
    printf("=========================================================\n"RESET);

    City *newCity = malloc(sizeof(City));
    startCity(newCity);

    printf(GREEN"\nDigite o nome da cidade: ");
    scanf(" %[^\n]"RESET, newCity->name);
    
    if (checkAvailableCity(graph, newCity->name)) {
        City *cities = *(graph->cities);

        if (cities == NULL) {
            *(graph->cities) = newCity;
            newCity->id = 1;
            newCity->next = NULL;
        }
        else {
            
            while (cities->next != NULL) {
                cities = cities->next;
            }

            cities->next = newCity;
            newCity->next = NULL;
            newCity->id = cities->id + 1;
        }

        startMatrixValues(graph);
        
        printf(GOLDEN"\n\n\"%s\" adicionada com sucesso.\n\n"RESET, newCity->name);
    }
    else {
        printf(RED"\n\nErro: Cidade ja adicionada.\n\n"RESET);
    }
    
    aguardarEnter();
}

void startCity(City *city) {
    city->id = -1;
    strcpy(city->name, "");
    city->next = NULL;
}

void chooseCitiesForNewRoad(Graph *graph) {
    clearScreen();
 
    printf(BLUE"=========================================================\n");
    printf("||                 ADICIONAR ESTRADAS                  ||\n");
    printf("=========================================================\n"RESET);

    int cityCount = getCitiesCount(graph);
    
    if (cityCount >= 2) {
        int city1 = 0;
        int city2 = 0;
        int distance = 0;

        printCities(graph);

        printf(GREEN"\nDigite o numero da primeira cidade: ");
        scanf("%d", &city1);

        printf("\nDigite o numero da segunda cidade: ");
        scanf("%d", &city2);

        printf("\nDigite a distancia da estrada(km): ");
        scanf("%d"RESET, &distance);

        city1--;
        city2--;
        
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
                printf(RED"\n\nErro: Numero invalido para a segunda cidade.\n\n"RESET);
            }
        }
        else {
            printf(RED"\n\nErro: Numero invalido para a primeira cidade.\n\n"RESET);
        } 
    }
    else {
        printf(RED"\n\nErro: Nao ha cidades o suficiente para construir estradas.\n\n"RESET);
    }

    aguardarEnter();
}

bool addNewRoad(Graph *graph, int city1, int city2, int distance) {

    bool result = false;

    if (graph->adj[city1][city2] == 0 && graph->adj[city2][city1] == 0) {
        
        graph->adj[city1][city2] = distance;
        graph->adj[city2][city1] = distance;

        City *searchCity1 = searchCity(graph, city1);
        City *searchCity2 = searchCity(graph, city2);
        
        printf(GOLDEN"\n\nEstrada entre \"%s\" e \"%s\" adicionada com sucesso!\n\n"RESET, searchCity1->name, searchCity2->name);
        
        result = true;
    }
    else {
        printf(RED"\n\nErro: Ja existe uma estrada ligando as duas cidades.\n\n"RESET);
    }
    
    return result;
}

void printCities(Graph *graph) {
    
    printf(BLUE"==========================================================\n");
    printf("||                 CIDADES CADASTRADAS                  ||\n");
    printf("==========================================================\n");
    
    City *cities = *(graph->cities);
    
    while (cities != NULL) {
        printf("|| [%d] %-20s \t\t\t\t||\n", cities->id, cities->name);
        cities = cities->next;
    }

    printf("==========================================================\n"RESET);
}

void startMatrixValues(Graph *graph) {
    int cityCount = getCitiesCount(graph);

    if (graph->adj == NULL) {
        graph->adj = malloc(sizeof(int *) * cityCount); 
        
        for (int i = 0; i < cityCount; i++) {
            graph->adj[i] = malloc(sizeof(int) * cityCount);
            
            for (int j = 0; j < cityCount; j++) {
                graph->adj[i][j] = 0;
            }
        }
    }
    else {
        graph->adj = realloc(graph->adj, sizeof(int *) * cityCount);
        
        for (int i = 0; i < cityCount - 1; i++) {
            graph->adj[i] = realloc(graph->adj[i], sizeof(int) * cityCount);
            graph->adj[i][cityCount - 1] = 0;
        }
        
        graph->adj[cityCount - 1] = malloc(sizeof(int) * cityCount); 
        
        for (int i = 0; i < cityCount; i++) {
            graph->adj[cityCount - 1][i] = 0;
        }
    }
}

int getCitiesCount(Graph *graph) {
    City *cities = *(graph->cities);
    int cityCount = 0;

    if (cities != NULL) {
        while (cities->next != NULL) {
            cities = cities->next;
        }
        cityCount = cities->id;
    }
    
    return cityCount;
}

void printAdjacencyMatrix(Graph *graph) {
    clearScreen();

    int citiesCount = getCitiesCount(graph);

    if (citiesCount == 0) {
        printf(RED"\n\nErro: Nao ha nenhuma cidade cadastrada.\n\n"RESET);
        aguardarEnter();
        return;
    }

    City *cities = *(graph->cities);
    int maxWidth = 24;

    if (cities != NULL) {
        
        printf(BLUE"\t\t      ");
       
        while (cities != NULL) {
            int maxWidth = 25;
            int cityNameSize = strlen(cities->name);
            int espacoDireita = (maxWidth - cityNameSize) / 2;
            int espacoEsquerda = maxWidth - cityNameSize - espacoDireita;
            
            printf("%*s%s%*s", espacoDireita, "", cities->name, espacoEsquerda, "");
            cities = cities->next;
        }

        printf("\n");

        cities = *(graph->cities);
        int cityCount = getCitiesCount(graph);

        for (int i = 0; i < cityCount; i++) {
            printf("%-21s|", cities->name);
            
            for (int j = 0; j < cityCount; j++) {
                int numberSize = snprintf(NULL, 0, "%d", graph->adj[i][j]);
                
                int espacoDireita = (maxWidth - numberSize) / 2;
                int espacoEsquerda = maxWidth - numberSize - espacoDireita;

                printf("%*s%d%*s|", espacoDireita, "", graph->adj[i][j], espacoEsquerda, "");
            }
            
            cities = cities->next;
            printf("\n");
        }
    }
    
    aguardarEnter(); 
}

bool removeRoad(Graph *graph, int city1, int city2) {

    bool result = false;

    if (graph->adj[city1][city2] != 0 && graph->adj[city2][city1] != 0) {
        graph->adj[city1][city2] = 0;
        graph->adj[city2][city1] = 0;
        result = true;
        printf(GOLDEN"\n\nEstrada removida com sucesso!\n\n"RESET);
    }
    else {
        printf(RED"\n\nErro: Nao ha estrada entre as duas cidades para ser excluida.\n\n"RESET);
    }

    return result;
}

void chooseCitiesForDeleteRoad(Graph *graph) {
    clearScreen();

    printf(BLUE"=====================================================\n");
    printf("||                DELETAR ESTRADAS                 ||\n");
    printf("=====================================================\n"RESET);
    
    int cityCount = getCitiesCount(graph);
    bool areThereRoads = areThereRegisteredRoads(graph);
    
    if (cityCount >= 2 && areThereRoads) {
        int city1 = 0;
        int city2 = 0;
        
        printCities(graph);

        printf(GREEN"\nDigite o numero da primeira cidade: ");
        scanf("%d", &city1);

        printf("\nDigite o numero da segunda cidade: ");
        scanf("%d"RESET, &city2);

        city1--;
        city2--;
        
        if (city1 >= 0 && city1 < cityCount) {
            if (city2 >= 0 && city2 < cityCount && city2 != city1) {
                removeRoad(graph, city1, city2);
            }
            else {
                printf(RED"\n\nErro: Numero invalido para a segunda cidade.\n\n"RESET);
            }
        }
        else {
            printf(RED"\n\nErro: Numero invalido para a primeira cidade.\n\n"RESET);
        } 
    } 
    else {
        printf(RED"\n\nErro: Nao ha estradas para serem excluidas.\n\n"RESET);
    }

    aguardarEnter();
}

bool areThereRegisteredRoads(Graph *graph) {
    bool result = false;
    int size = getCitiesCount(graph);
    
    for (int i = 0; i < size && result != true; i++) {
        for (int j = 0; j < size; j++) {
            if (graph->adj[i][j] != 0) {
                result = true;
            }
        }
    }

    return result;
}

void showDirectRoadsByCity(Graph *graph) {
    clearScreen();

    printf(BLUE"=========================================================\n");
    printf("||              PROCURAR ESTRADAS DIRETAS              ||\n");
    printf("=========================================================\n"RESET);
    
    int cityCount = getCitiesCount(graph);
    bool areThereRoads = areThereRegisteredRoads(graph);

    if (cityCount >= 2 && areThereRoads) {
        printCities(graph);

        int city = 0;
        int count = 1;

        printf(GREEN"\nEscolha o numero da cidade para ver todas as suas estradas diretas: ");
        scanf("%d"RESET, &city);

        city--;
        City *currentCity = searchCity(graph, city);

        if (city < cityCount && city >= 0) {
            clearScreen();
            
            printf(BLUE"====================================================================\n");
            printf("||                ESTRADAS DIRETAS DE %-22s      ||\n", currentCity->name);
            printf("====================================================================\n");
            
            for (int i = 0; i < cityCount; i++) {
                if (graph->adj[city][i] != 0) {
                    City *currentCity = searchCity(graph, i); 
                    printf("|| [%d] %-22s\t\t | Distancia(km): %-5d   ||\n", count, currentCity->name, graph->adj[city][i]);
                    count++;
                }
            }
            printf("====================================================================\n");
        }
        else {
            printf(RED"\n\nErro: Numero de cidade invalido.\n\n"RESET);
        }
    }
    else {
        printf(RED"\n\nErro: Nao ha cidades ou estradas cadastradas.\n\n"RESET);
    }

    aguardarEnter();
}

City *searchCity(Graph *graph, int ID) {
    City *searchCity = *(graph->cities);
     
    if (searchCity != NULL) {
        while (searchCity != NULL && searchCity->id - 1 != ID) {
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

    free(graph);
}

bool consultRoadBetweenCities(Graph *graph) {
    clearScreen();

    printf(BLUE"=========================================================\n");
    printf("||             CONSULTAR ESTRADAS ENTRE CIDADES        ||\n");
    printf("=========================================================\n"RESET);
    
    int citiesCount = getCitiesCount(graph);
    bool areThereRoads = areThereRegisteredRoads(graph);
    bool result = false;
    
    if (citiesCount >= 2 && areThereRoads) {
        int city1 = 0;
        int city2 = 0;

        printCities(graph);

        printf(GREEN"\nDigite o numero da primeira cidade: ");
        scanf("%d", &city1);

        printf("\nDigite o numero da segunda cidade: ");
        scanf("%d"RESET, &city2);

        city1--;
        city2--;

        if (city1 < citiesCount && city1 >= 0) {
            if (city2 < citiesCount && city2 >= 0) {
                
                City *searchCity1 = searchCity(graph, city1); 
                City *searchCity2 = searchCity(graph, city2);
                
                if (graph->adj[city1][city2] != 0) {
                    printf(GREEN"\n\nExiste uma cidade entre \"%s\" e \"%s\" de %d km.\n\n"RESET, searchCity1->name, searchCity2->name, graph->adj[city1][city2]);
                    result = true;
                }
                else {
                    printf(GREEN"\n\nNao existe uma cidade entre \"%s\" e \"%s\".\n\n"RESET, searchCity1->name, searchCity2->name);
                }
            } 
            else {
                printf(RED"\n\nErro: Valor invalido para a cidade 2.\n\n"RESET);
            }
        }
        else {
            printf(RED"\n\nErro: Valor invalido para a cidade 1.\n\n"RESET);
        }
    }
    else {
        printf(RED"\n\nErro: Nao ha cidades ou estradas cadastradas.\n\n"RESET);
    }
    
    aguardarEnter();

    return result;
}

bool checkAvailableCity(Graph *graph, char *cityName) {
    bool result = true;
    City *cities = *(graph->cities);
    
    while (cities != NULL) {
        if (stringCompareIgnoreCase(cityName, cities->name)) {
            result = false;
        }
        cities = cities->next;
    }

    return result;
}

bool stringCompareIgnoreCase(char *name1, char *name2) {
    bool result = true;

    if (strlen(name1) == strlen(name2)) {
        int size = strlen(name1);
        for (int i = 0; i < size && result != false; i++) {
            if (tolower(name1[i]) != tolower(name2[i])) {
                result = false;
            }
        }
    }
    else {
        result = false;
    }

    return result;
}

int compareQueueNodes(const void *a, const void *b) {
    NodeQueue *node1 = (NodeQueue *)a;
    NodeQueue *node2 = (NodeQueue *)b;
    
    return node1->custo - node2->custo;
}

PriorityQueue *createPriorityQueue(int numVertices) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->heap = (NodeQueue *) malloc(sizeof(NodeQueue) * numVertices);
    return pq;
}

void enqueue(PriorityQueue *pq, int id, int custo) {
    NodeQueue node;
    node.id = id;
    node.custo = custo;
    
    pq->heap[pq->size] = node;
    pq->size++;
    
    qsort(pq->heap, pq->size, sizeof(NodeQueue), compareQueueNodes);
}

NodeQueue dequeue(PriorityQueue *pq) {
    return pq->heap[--pq->size];
}

void chooseCityForMinPath(Graph *graph) {
    clearScreen();

    printf(BLUE"=========================================================\n");
    printf("||             CONSULTAR CAMINHOS MINIMOS              ||\n");
    printf("=========================================================\n"RESET);
    
    int citiesCount = getCitiesCount(graph);
    
    if (citiesCount == 0) {
        printf(RED"\n\nErro: Nao ha cidades cadastradas.\n\n"RESET);
        aguardarEnter();
        return;
    }

    printCities(graph);

    int city = 0;

    printf(GREEN"\nEscolha a cidade para consultar seus caminhos minimos: ");
    scanf("%d"RESET, &city);

    city--;

    if (city >= 0 && city < citiesCount) {
        dijkstra(graph, city);
    }
    else {
        printf(RED"\n\nErro: Valor invalido para a cidade.\n\n"RESET);
        aguardarEnter();
    }
}

void dijkstra(Graph *g, int origem) {
    int cityCount = getCitiesCount(g);
    int distance[cityCount];
    int path[cityCount];
    bool visited[cityCount];
    
    for (int i = 0; i < cityCount; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        path[i] = -1;
    }

    distance[origem] = 0;

    PriorityQueue *pq = createPriorityQueue(cityCount);
    enqueue(pq, origem, 0);

    while (pq->size > 0) {
        NodeQueue node = dequeue(pq);
        int city1 = node.id;

        for (int i = 0; i < cityCount; i++) {
            int city2 = i;
            int weight = g->adj[city1][city2];
            bool result = distance[city1] + weight < distance[city2];

            if (result && !visited[city1] && weight != 0 && distance[city1] != INT_MAX) {
                distance[city2] = distance[city1] + weight;
                path[city2] = city1;
                
                enqueue(pq, city2, distance[city2]);
            }
        }

        visited[city1] = true;
    }

    printResultForDijkstra(g, path, distance, origem);

    aguardarEnter(); 
}

void printResultForDijkstra(Graph *g, int *path, int *distance, int origem) {
    clearScreen();
    
    City *originCity = searchCity(g, origem);

    printf(GREEN"============================================================================\n");
    printf("                       CAMINHOS MINIMOS DE %s                               \n", originCity->name);
    printf("============================================================================\n"RESET);

    int cityCount = getCitiesCount(g);
    
    printf(GREEN"============================================================================\n\n"RESET);
    
    for (int i = 0; i < cityCount; i++) {
        City *city = searchCity(g, i);
        
        printf(GREEN"Caminhos minimos de \"%s\": ", city->name);
        printPath(g, i, path);
        
        if (distance[i] != INT_MAX) {
            printf("(%d) km.", distance[i]);
        }
        else {
            printf(" -> Nao ha caminho para essa cidade.");
        }
        
        printf("\n\n"RESET);
    }

    printf(GREEN"============================================================================\n"RESET);
}

void printPath(Graph *g, int destino, int *path) {
    City *city = searchCity(g, destino);
    
    if (path[destino] == -1) {
        printf("\"%s\" ", city->name);
        return;
    }

    printPath(g, path[destino], path);
    printf("-> \"%s\" ", city->name);
}