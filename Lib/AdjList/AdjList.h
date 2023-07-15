#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#include "../vVector/vVector.h"

#ifndef AdjList
#define AdjList

struct adjList{
    struct vVector* neighbors;
};

struct Graph{
    int nodeNum;
    int edgeNum;
    bool startAtZero;
    struct adjList* vertices;
};

struct Graph* buildGraph(char* _datasetPath);
void showAdjList(struct Graph* _graph);
#endif