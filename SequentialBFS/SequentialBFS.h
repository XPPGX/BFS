#ifndef COMMON
#define COMMON
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#ifndef BOOL
#define BOOL
typedef enum{
    no,
    yes
}bool;
#endif

#ifndef ADJLIST
#define ADJLIST
#include "../Lib/AdjList/AdjList.h"
#endif

#ifndef QQueue
#define QQueue
#include "../Lib/qQueue/qQueue.h"
#endif

//content
void seqBFS(struct Graph* _graph, int _startNode);