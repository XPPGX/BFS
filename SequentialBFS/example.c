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

#define showCost

int main(int argc, char* argv[]){
    char* datasetPath = argv[1];
    int version = atoi(argv[2]);
    int startNode = atoi(argv[3]);
    struct Graph* adjList;
    int* cost;
    int nodeId = 0;
    switch(version){
        case 1: //CSR
            adjList = buildGraph(datasetPath);
            struct CSR* csr = createCSR(adjList);
            cost = seqBFS_CSR(csr, startNode);

            #ifdef showCost
            if(csr->startAtZero == 0){nodeId = 1;}
            for(; nodeId < csr->csrVSize ; nodeId++){
                printf("cost[%d] = %d\n", nodeId, cost[nodeId]);
            }
            #endif

            break;
        case 2: //Adjlist
            adjList = buildGraph(datasetPath);
            cost = seqBFS_Adjlist(adjList, startNode);

            #ifdef showCost
            int nodeIdTail = 0;
            if(adjList->startAtZero == 0){
                nodeId = 1;
                nodeIdTail = adjList->nodeNum + 1;
            }
            for(; nodeId < nodeIdTail ; nodeId++){
                printf("cost[%d] = %d\n", nodeId, cost[nodeId]);
            }
            #endif

            break;
    }
}
    