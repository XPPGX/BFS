#include "SequentialBFS.h"
#include <stdbool.h>
//#define _DEBUG_

void seqBFS_Adjlist(struct Graph* _graph, int _startNode){
    printf("[Start] Sequentail BFS, version = \"Adjlist\"\n");
    struct qQueue* queue = InitqQueue();
    int currentNode = -1;
    bool* visited;
    if(_graph->startAtZero == 1){
        visited = (bool*)calloc(_graph->nodeNum, sizeof(bool));
    }
    else{
        visited = (bool*)calloc(_graph->nodeNum + 1, sizeof(bool));
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
                qPushBack(queue, neighborNode);
            }
        }
    }
    printf("\n");
    printf("[Finished Successfully] Sequential BFS, version = \"Adjlist\"\n\n");
}

void seqBFS_CSR(struct CSR* _csr, int _startNode){
    printf("[Start] Sequential BFS, version = \"CSR\"\n");
    struct qQueue* queue = InitqQueue();
    int currentNode = -1;
    bool* visited;
    if(_csr->startAtZero == 1){
        visited = (bool*)calloc(_csr->csrVSize - 1, sizeof(bool));
    }
    else{
        visited = (bool*)calloc(_csr->csrVSize, sizeof(bool));
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
                qPushBack(queue, neighborNode);
            }
        }
    }
    printf("\n");
    printf("[Finished Successfully] Sequential BFS, version = \"CSR\"\n");
}