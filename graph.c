#include "graph.h"

Graph *createNewGraph() {
    Graph *newGraph = malloc(sizeof(Graph));

    newGraph->adj = malloc(sizeof(int **));
    *(newGraph->adj) = NULL;

    newGraph->cities = malloc(sizeof(City **));
    *(newGraph->cities) = NULL;
    
    newGraph->roads = 0;

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
                printf(RED"\n\nErro: Número inválido para a segunda cidade.\n\n"RESET);
            }
        }
        else {
            printf(RED"\n\nErro: Número inválido para a primeira cidade.\n\n"RESET);
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

void startMatrixValues(Graph *graph, int size) {
    for (int i = 0; i < size; i++) {
        graph->adj[size - 1][i] = 0;  
        graph->adj[i][size - 1] = 0;  
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

    City *cities = *(graph->cities);
    
    if (cities != NULL) {
        int largura = 22;
        
        printf(BLUE"                       ");
       
        while (cities!= NULL) {
            int size = largura - strlen(cities->name);
            printf("%*s%s%*s", size / 2, "", cities->name, size / 2, "");
            cities = cities->next;
        }

        printf("\n");

        cities = *(graph->cities);
        int cityCount = getCitiesCount(graph);

        for (int i = 0; i < cityCount; i++) {
            printf("%-22s|", cities->name);
            
            for (int j = 0; j < cityCount; j++) {
                int tamanho = returnNumLenght(graph->adj[i][j]);
                int result = (largura - tamanho) / 2;
                if (tamanho % 2 == 0) {
                    printf("%*s%d%*s|", ++result, "", graph->adj[i][j], --result, "");
                }
                else {
                   printf("%*s%d%*s |", result, "", graph->adj[i][j], result, ""); 
                }       
            }
            
            cities = cities->next;
            printf("\n");
        }
    }
    
    aguardarEnter(); 
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
        printf(GOLDEN"\n\nEstrada removida com sucesso!\n\n"RESET);
    }
    else {
        printf(RED"\n\nErro: Nao há estrada entre as duas cidades para ser excluida.\n\n"RESET);
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
                printf(RED"\n\nErro: Número inválido para a segunda cidade.\n\n"RESET);
            }
        }
        else {
            printf(RED"\n\nErro: Número inválido para a primeira cidade.\n\n"RESET);
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
                    printf(GREEN"\n\nExiste uma cidade entre \"%s\" e \"%s\" de %d km.\n\n"RESET, searchCity1->name, searchCity2, graph->adj[city1][city2]);
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

    printCities(graph);

    int city = 0;
    int citiesCount = getCitiesCount(graph);

    printf(GREEN"\nEscolha a cidade para consultar seus caminhos minimos: "RESET);
    scanf("%d", &city);

    city--;

    if (city >= 0 && city < citiesCount) {
        dijkstra(graph, city);
    }
}

void dijkstra(Graph *g, int origem) {
    int numVertices = getCitiesCount(g);
    int dist[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        dist[i] = __INT_MAX__;
    }

    dist[origem] = 0;

    PriorityQueue *pq = createPriorityQueue(numVertices);
    enqueue(pq, origem, 0);

    while (pq->size > 0) {
        NodeQueue node = dequeue(pq);
        int u = node.id;

        for (int i = 0; i < numVertices; i++) {
            int v = i;
            int weight = g->adj[u][i];
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                enqueue(pq, v, dist[v]);
            }
        }
    }

    printResultForDijkstra(g, numVertices, dist, origem);
}

void printResultForDijkstra(Graph *graph, int numVertices, int *dist, int origem) {
    clearScreen();
    
    City *originCity = searchCity(graph, origem);

    printf(BLUE"=========================================================\n");
    printf("||             CAMINHOS MINIMOS DE %s                  ||\n", originCity->name);
    printf("=========================================================\n");

    printf("=========================================================\n");
    
    for (int i = 0; i < numVertices; i++) {
        City *city = searchCity(graph, i);
        printf("|| Distancia minima de \"%s\" ate \"%s\": %d km ||\n", originCity->name, city, dist[i]);
    }

    printf("=========================================================\n"RESET);
    aguardarEnter();
}