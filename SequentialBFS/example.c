#ifndef COMMON
#define COMMON
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//content

#ifndef SEQUENTIAL_BFS
#define SEQUENTIAL_BFS
#include "SequentialBFS.h"
#endif


int main(int argc, char* argv[]){
    char* datasetPath = argv[1];
    int version = atoi(argv[2]);
    int startNode = atoi(argv[3]);
    struct Graph* adjList;
    switch(version){
        case 1: //CSR
            adjList = buildGraph(datasetPath);
            struct CSR* csr = createCSR(adjList);
            seqBFS_CSR(csr, startNode);
            break;
        case 2: //Adjlist
            adjList = buildGraph(datasetPath);
            seqBFS_Adjlist(adjList, startNode);
            break;
    }
}
    