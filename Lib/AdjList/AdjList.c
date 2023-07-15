#include "AdjList.h"
#include "../FileReader/FileReader.h"

//default the graph is undirected graph

#define _DEBUG_

struct Graph* buildGraph(char* _datasetPath){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    FILE* fptr = fopen(_datasetPath, "r");
    if(fptr == NULL){
        printf("Error: Open file\n");
        exit(1);
    }
    char row[10];
    int val1, val2 = 0;
    fgets(row, 10, fptr);
    getRowData(row, &val1, &val2);

    #ifdef _DEBUG_
    printf("nodeNum = %d, edgeNum = %d\n", val1, val2);
    #endif

    graph->nodeNum = val1;
    graph->edgeNum = val2;
    
    //read first edge to check 0 or 1 is start index.
    fgets(row, 10, fptr);
    getRowData(row, &val1, &val2);
    if(val1 == 0 || val2 == 0){
        #ifdef _DEBUG_
        printf("Graph start with 0\n");
        #endif

        graph->startAtZero = yes;
        graph->vertices = (struct adjList*)malloc(sizeof(struct adjList) * graph->nodeNum);
        for(int i = 0 ; i < graph->nodeNum ; i ++){
            graph->vertices[i].neighbors = InitvVector();
        }
    }
    else{
        #ifdef _DEBUG_
        printf("Graph start with 1\n");
        #endif

        graph->startAtZero = no;
        graph->vertices = (struct adjList*)malloc(sizeof(struct adjList) * (graph->nodeNum + 1));
        for(int i = 0 ; i < graph->nodeNum + 1 ; i ++){
            graph->vertices[i].neighbors = InitvVector();
        }
    }

    //append first edge into adjlist
    vAppend(graph->vertices[val1].neighbors, val2);
    vAppend(graph->vertices[val2].neighbors, val1);

    //run over all remain edges
    for(int i = 1 ; i < graph->edgeNum ; i ++){
        fgets(row, 10, fptr);
        getRowData(row, &val1, &val2);
        vAppend(graph->vertices[val1].neighbors, val2);
        vAppend(graph->vertices[val2].neighbors, val1);
    }
}

void showAdjList(struct Graph* _graph){
    if(_graph->startAtZero == yes){
        for(int i = 0 ; i < _graph->nodeNum ; i ++){
            printf("AA");
        }
    }
    else{
        for(int i = 1 ; i < _graph->nodeNum + 1 ; i ++){
            printf("Hi");
        }
    }
}