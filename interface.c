#include "interface.h"

void menuOptions() {
    clearScreen();
    printf(BLUE"=========================================\n");
    printf("||            MENU DE OPCOES           ||\n");
    printf("=========================================\n");
    printf("|| [1] Adicionar nova cidade           ||\n");
    printf("|| [2] Adicionar nova estrada          ||\n");
    printf("|| [3] Remover estrada                 ||\n");
    printf("|| [4] Mostrar estradas diretas        ||\n");
    printf("|| [5] Consultar estrada entre cidades ||\n");
    printf("|| [0] Sair                            ||\n");
    printf("=========================================\n"RESET);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void aguardarEnter() {
    printf(GREEN"PRESSIONE ENTER PARA CONTINUAR: "RESET);
    getchar();
    getchar();
}