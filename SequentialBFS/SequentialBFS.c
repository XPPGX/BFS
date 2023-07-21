#include "SequentialBFS.h"
#include <stdbool.h>
//#define _DEBUG_

int* seqBFS_Adjlist(struct Graph* _graph, int _startNode){
    printf("[Start] Sequentail BFS, version = \"Adjlist\"\n");
    struct qQueue* queue = InitqQueue();

    int currentNode = -1;
    bool* visited;
    int* cost;
    if(_graph->startAtZero == 1){
        visited = (bool*)calloc(_graph->nodeNum, sizeof(bool));
        cost = (int*)calloc(_graph->nodeNum, sizeof(int));
    }
    else{
        visited = (bool*)calloc(_graph->nodeNum + 1, sizeof(bool));
        cost = (int*)calloc(_graph->nodeNum + 1, sizeof(int));
    }

    qPushBack(queue, _startNode);
    int neighborNode = -1;
    while(!qIsEmpty(queue)){
        currentNode = qPopFront(queue);
        visited[currentNode] = true;
        
        #ifdef _DEBUG_
        printf("%d, ", currentNode);
        #endif

        for(int neighborIndex = 0 ; neighborIndex <= _graph->vertices[currentNode].neighbors->tail ; neighborIndex ++){
            neighborNode = _graph->vertices[currentNode].neighbors->dataArr[neighborIndex];
            if(visited[neighborNode] == false){
                visited[neighborNode] = true;
                cost[neighborNode] = cost[currentNode] + 1;
                qPushBack(queue, neighborNode);
            }
        }
    }
    printf("\n");
    printf("[Finished Successfully] Sequential BFS, version = \"Adjlist\"\n\n");
    return cost;
}

int* seqBFS_CSR(struct CSR* _csr, int _startNode){
    printf("[Start] Sequential BFS, version = \"CSR\"\n");
    struct qQueue* queue = InitqQueue();

    int currentNode = -1;
    bool* visited;
    int* cost;
    if(_csr->startAtZero == 1){
        visited = (bool*)calloc(_csr->csrVSize - 1, sizeof(bool));
        cost = (int*)calloc(_csr->csrVSize - 1, sizeof(int));
    }
    else{
        visited = (bool*)calloc(_csr->csrVSize, sizeof(bool));
        cost = (int*)calloc(_csr->csrVSize, sizeof(int));
    }
    qPushBack(queue, _startNode);
    int neighborNode = -1;
    while(!qIsEmpty(queue)){
        currentNode = qPopFront(queue);
        visited[currentNode] = true;

        #ifdef _DEBUG_
        printf("%d, ", cuurentNode);
        #endif

        for(int neighborIndex = _csr->csrV[currentNode] ; neighborIndex < _csr->csrV[currentNode + 1] ; neighborIndex ++){
            neighborNode = _csr->csrE[neighborIndex];
            if(visited[neighborNode] == false){
                visited[neighborNode] = true;
                cost[neighborNode] = cost[currentNode] + 1;
                qPushBack(queue, neighborNode);
            }
        }
    }
    printf("\n");
    printf("[Finished Successfully] Sequential BFS, version = \"CSR\"\n");
    return cost;
}