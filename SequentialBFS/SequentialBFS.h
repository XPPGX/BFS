#ifndef COMMON
#define COMMON
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#ifndef ADJLIST
#define ADJLIST
#include "../Lib/AdjList/AdjList.h"
#endif

#ifndef QQueue
#define QQueue
#include "../Lib/qQueue/qQueue.h"
#endif

#ifndef cCSR
#define cCSR
#include "../Lib/CSR/CSR.h"
#endif
//content
int* seqBFS_Adjlist(struct Graph* _graph, int _startNode);
int* seqBFS_CSR(struct CSR* _csr, int startNode);