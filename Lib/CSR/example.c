#include "CSR.h"

int main(int argc, char* argv[]){
    char* datasetPath = argv[1];
    struct Graph* adjList = buildGraph(datasetPath);
    struct CSR* csr = createCSR(adjList);
    //showCSR(csr);
    // showAdjList(adjList);
}