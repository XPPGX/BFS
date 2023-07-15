#include "SequentialBFS.h"

#define _DEBUG_

void seqBFS(struct Graph* _graph, int _startNode){
    struct qQueue* queue = InitqQueue();
    int currentNode = -1;
    int* visited;
    if(_graph->startAtZero == yes){
        visited = (int*)calloc(_graph->nodeNum, sizeof(int));
    }
    else{
        visited = (int*)calloc(_graph->nodeNum + 1, sizeof(int));
    }

    qPushBack(queue, _startNode);
    int neighborNode = -1;
    while(!qIsEmpty(queue)){
        currentNode = qPopFront(queue);
        visited[currentNode] = 1;
        
        #ifdef _DEBUG_
        printf("%d, ", currentNode);
        #endif

        for(int neighborIndex = 0 ; neighborIndex <= _graph->vertices[currentNode].neighbors->tail ; neighborIndex ++){
            neighborNode = _graph->vertices[currentNode].neighbors->dataArr[neighborIndex];
            if(visited[neighborNode] == 0){
                visited[neighborNode] = 1;
                qPushBack(queue, neighborNode);
            }
        }
    }
    printf("\n");
}