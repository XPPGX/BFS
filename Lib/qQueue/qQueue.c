#include "qQueue.h"

#define _DEBUG_

struct qQueue* InitqQueue(){
    struct qQueue* queue = (struct qQueue*)malloc(sizeof(struct qQueue));
    queue->dataArr = (int*)malloc(sizeof(int) * 5);
    queue->front = 0;
    queue->rear = -1;
    queue->size = 5;
    return queue;
}

void qPushBack(struct qQueue* _queue, int _val){
    if(qSpaceFull(_queue)){
        
        #ifdef _DEBUG_
        printf("Q is full, queue->front = %d, queue->rear = %d\n", _queue->front, _queue->rear);
        #endif

        _queue->size = _queue->size * 2;
        int* newSpace = (int*)malloc(sizeof(int) * _queue->size);
        memcpy(newSpace, (_queue->dataArr) + _queue->front,  sizeof(int) * (_queue->rear - _queue->front + 1));
        free(_queue->dataArr);
        _queue->dataArr = newSpace;

        //re-assign index
        _queue->rear = _queue->rear - _queue->front;
        _queue->front = 0;
    }
    _queue->rear++;
    _queue->dataArr[_queue->rear] = _val;

    #ifdef _DEBUG_
    printf("queue->dataArr[%d] = %d, qPushBack Success\n", _queue->rear, _queue->dataArr[_queue->rear]);
    #endif
}

bool qSpaceFull(struct qQueue* _queue){
    return (_queue->rear + 1) == _queue->size;
}

bool qIsEmpty(struct qQueue* _queue){
    return _queue->front > _queue->rear;
}

void showAllElement(struct qQueue* _queue){
    for(int i = 0 ; i <= _queue->rear ; i ++){
        printf("queue[%d] = %d\n", i, _queue->dataArr[i]);
    }
}

int qPopFront(struct qQueue* _queue){
    if(qIsEmpty(_queue)){
        printf("Queue is empty\n");
        return -1;
    }
    _queue->front++;
    return _queue->dataArr[_queue->front - 1];
}