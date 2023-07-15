#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#include "AdjList.h"

int main(){
    struct Graph* graph = buildGraph("karate.txt");
    showAdjList(graph);
}