#ifndef qQ
#define qQ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    no,
    yes
}bool;

struct qQueue{
    int* dataArr;
    int front;
    int rear;
    int size;
};

struct qQueue* InitqQueue();
void qPushBack(struct qQueue* _queue, int _val);
bool qIsFull(struct qQueue* _queue);
bool qIsEmpty(struct qQueue* _queue);
void showAllElement(struct qQueue* _queue);
int qPopFront(struct qQueue* _queue);
#endif