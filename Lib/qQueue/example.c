#include "qQueue.h"

int main(){
    struct qQueue* queue = InitqQueue();
    for(int i = 0 ; i < 10 ; i ++){
        qPushBack(queue, i * 10);
    }
    showAllElement(queue);
}