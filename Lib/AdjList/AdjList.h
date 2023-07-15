#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

//content
#ifndef VVECTOR
#define VVECTOR
#include "../vVector/vVector.h"
#endif

#ifndef FILEREADER
#define FILEREADER
#include "../FileReader/FileReader.h"
#endif

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
