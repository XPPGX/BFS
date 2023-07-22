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

#ifndef tTime
#define tTime
#include "../Lib/tTime/tTime.h"
#endif

// #define _DEBUG_
// #define showCost

int main(int argc, char* argv[]){
    char* datasetPath = argv[1];
    int version = atoi(argv[2]);
    int startNode = atoi(argv[3]);
    struct Graph* adjList;
    int* cost;
    int nodeId = 0;

    double startTime = 0;
    double time1 = 0;
    double time2 = 0;

    double timeBuildAdjlist = 0;
    double timeBuildCSR = 0;
    double timeSequentialBFS = 0;
    double timeTotal = 0;

    switch(version){
        case 1: //CSR
            //Time counter start
            startTime = seconds();
            adjList = buildGraph(datasetPath);
            time1 = seconds();
            timeBuildAdjlist = time1 - startTime;

            time1 = seconds();
            struct CSR* csr = createCSR(adjList);
            time2 = seconds();
            timeBuildCSR = time2 - time1;

            #ifdef _DEBUG_
            showCSR(csr);
            #endif
            
            time1 = seconds();
            cost = seqBFS_CSR(csr, startNode);
            time2 = seconds();
            timeSequentialBFS = time2 - time1;

            #ifdef showCost
            if(csr->startAtZero == 0){nodeId = 1;}
            for(; nodeId < csr->csrVSize - 1 ; nodeId++){
                printf("cost[%d] = %d\n", nodeId, cost[nodeId]);
            }
            #endif
            time1 = seconds();
            timeTotal = time1 - startTime;

            printf("[Execution Time] Build Adjlist      = %9f\n", timeBuildAdjlist);
            printf("[Execution Time] Build CSR          = %9f\n", timeBuildCSR);
            printf("[Execution Time] SequentialBFS(CSR) = %9f\n", timeSequentialBFS);
            printf("[Execution Time] TotalTime          = %9f\n", timeTotal);
            break;
        case 2: //Adjlist
            //Time counter start
            startTime = seconds();
            adjList = buildGraph(datasetPath);
            time1 = seconds();
            timeBuildAdjlist = time1 - startTime;

            time1 = seconds();
            cost = seqBFS_Adjlist(adjList, startNode);
            time2 = seconds();
            timeSequentialBFS = time2 - time1;

            #ifdef showCost
            int nodeIdTail = adjList->nodeNum;
            if(adjList->startAtZero == 0){
                nodeId = 1;
                nodeIdTail ++;
            }
            for(; nodeId < nodeIdTail ; nodeId++){
                printf("cost[%d] = %d\n", nodeId, cost[nodeId]);
            }
            #endif
            time1 = seconds();
            timeTotal = time1 - startTime;
            printf("[Execution Time] Build Adjlist      = %9f\n", timeBuildAdjlist);
            printf("[Execution Time] SequentialBFS(Adj) = %9f\n", timeSequentialBFS);
            printf("[Execution Time] TotalTime          = %9f\n", timeTotal);
            break;
    }
}
    