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
    int startNode = atoi(argv[2]);
    struct Graph* graph = buildGraph(datasetPath);
    //showAdjList(graph);
    seqBFS(graph, startNode);
    
}