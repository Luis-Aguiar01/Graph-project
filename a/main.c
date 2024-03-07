#include "graph.h"

int main(void) {
    Graph *myGraph = createNewGraph();
    
    printAdjacencyMatrix(myGraph);
    addNewCity(myGraph);
    printAdjacencyMatrix(myGraph);
    addNewCity(myGraph);
    printAdjacencyMatrix(myGraph);
    addNewCity(myGraph);
    printAdjacencyMatrix(myGraph);
    printCities(myGraph);   
}