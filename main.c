#include "graph.h"

int main(void) {
    
    Graph *graph = createNewGraph();
    int choice = 1;

    while (choice != 0) {
        menuOptions();
        printf(GREEN"Digite a sua escolha: ");
        scanf("%d"RESET, &choice);

        switch(choice) {
            case 1:
                addNewCity(graph);
                break;
            case 2:
                chooseCitiesForNewRoad(graph);
                break;
            case 3:
                chooseCitiesForDeleteRoad(graph);
                break;
            case 4:
                showDirectRoadsByCity(graph);
                break;
            case 5:
                consultRoadBetweenCities(graph);
                break;
            case 0:
                printf(GOLDEN"\n\nEncerrando...\n\n"RESET);
                freeMemory(graph);
                break;
            default:
                printf(RED"\n\nErro: Opcao invalida.\n\n"RESET);
                break;
        }
    }
}