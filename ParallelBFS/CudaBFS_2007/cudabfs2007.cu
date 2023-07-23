/***
 * @brief The code sites https://github.com/siddharths2710/cuda_bfs/blob/master/cuda_bfs/kernel.cu
 * @author XPPGX
 * @date 2023/07/21
*/
#ifndef COMMON
#define COMMON
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//content

//include C library
extern "C"{
    #ifndef cCSR
    #define cCSR
    #include "../../Lib/CSR/CSR.h"
    #endif

    #ifndef tTime
    #define tTime
    #include "../../Lib/tTime/tTime.h"
    #endif
}

//define
// #define showCost
// #define _DEBUG_
typedef enum{
    no,
    yes
}bBool;

//include cuda library
#include <cuda_runtime.h>

__global__ void cudaBfsKernel(int* _csrV, int* _csrE, bBool* _frontier, bBool* _visited, int* _cost, bBool* _done, int _nodeSize, int level){
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int neighbor = -1;
    if(tid < _nodeSize){
        if(_frontier[tid] == yes && _visited[tid] == no){
            
            #ifdef _DEBUG_
            printf("%d, ", tid); // tid == nodeID
            #endif

            _frontier[tid] = no;
            _visited[tid] = yes;
            _cost[tid] = level;
            __syncthreads();

            //visit neighbor
            for(int neighborIndex = _csrV[tid] ; neighborIndex < _csrV[tid + 1] ; neighborIndex ++){
                neighbor = _csrE[neighborIndex];
                if(_visited[neighbor] == no){
                    _frontier[neighbor] = yes;
                    *_done = no;
                }
            }
        }
    }
}

int main(int argc, char* argv[]){
    char* datasetPath = argv[1];
    int startNode = atoi(argv[2]);

    double time1 = 0;
    double time2 = 0;
    double startTime = 0;
    
    double timeBuildAdjlist = 0;
    double timeBuildCSR = 0;
    double timeCopyData = 0;
    double timeParallelBFS = 0;
    double timeTotal = 0;

    //Time counter start
    startTime = seconds();
    struct Graph* adjlist = buildGraph(datasetPath);
    time1 = seconds();
    timeBuildAdjlist = time1 - startTime;
    //compute the time of buliding Adjlist
    time1 = seconds();
    struct CSR* csr = createCSR(adjlist);
    printf("neighbor[34] = {");
    for(int neighborIndex = csr->csrV[34] ; neighborIndex < csr->csrV[35] ; neighborIndex ++){
        printf("%d, ", csr->csrE[neighborIndex]);
    }
    printf("}\n");
    time2 = seconds();
    timeBuildCSR = time2 - time1;
    //compute the time of create csr
    int nodeSize = csr->csrVSize - 1; //actual node size, csr format here will add one space to put the final edge offset.
    // showCSR(csr);
    printf("\n\n");
    // printf("csr->csrVSize = %d, csr->csrESize = %d\n", csr->csrVSize, csr->csrESize);

    int dev = 0;
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);
    #ifdef _DEBUG_
    printf("device %d : %s\n", dev, deviceProp.name);
    #endif
    
#pragma region threadLayout
    dim3 block(32, 1);
    dim3 grid((nodeSize + block.x - 1) / block.x, 1);
    printf("block(x,y) = (%d,%d), grid(x,y) = (%d,%d)\n", block.x, block.y, grid.x, grid.y);
#pragma endregion

    //compute time
#pragma region copyData
    time1 = seconds();
    //可以寫個kernel看資料到底有沒有複製到GPU裡面
    int* cudaCsrV;
    cudaMalloc((void**)&cudaCsrV, sizeof(int) * csr->csrVSize);
    cudaMemcpy(cudaCsrV, csr->csrV, sizeof(int) * csr->csrVSize, cudaMemcpyHostToDevice);


    int* cudaCsrE;
    cudaMalloc((void**)&cudaCsrE, sizeof(int) * csr->csrESize);
    cudaMemcpy(cudaCsrE, csr->csrE, sizeof(int) * csr->csrESize, cudaMemcpyHostToDevice);
    

    bBool* hostFrontier = (bBool*)calloc(csr->csrVSize, sizeof(bBool));
    hostFrontier[startNode] = yes;
    bBool* cudaFrontier;
    cudaMalloc((void**)&cudaFrontier, sizeof(bBool) * csr->csrVSize);
    cudaMemcpy(cudaFrontier, hostFrontier, sizeof(bBool) * csr->csrVSize, cudaMemcpyHostToDevice);

    bBool* hostVisited = (bBool*)calloc(csr->csrVSize, sizeof(bBool));
    bBool* cudaVisited;
    cudaMalloc((void**)&cudaVisited, sizeof(bBool) * csr->csrVSize);
    cudaMemcpy(cudaVisited, hostVisited, sizeof(bBool) * csr->csrVSize, cudaMemcpyHostToDevice);
    

    int* hostCost = (int*)calloc(csr->csrVSize, sizeof(int));
    int* cudaCost;
    cudaMalloc((void**)&cudaCost, sizeof(int) * csr->csrVSize);
    cudaMemcpy(cudaCost, hostCost, sizeof(int) * csr->csrVSize, cudaMemcpyHostToDevice);
    
    bBool* hostDone = (bBool*)malloc(sizeof(bBool));
    *hostDone = no;
    bBool* cudaDone;
    cudaMalloc((void**)&cudaDone, sizeof(bBool));
    cudaMemcpy(cudaDone, hostDone, sizeof(bBool), cudaMemcpyHostToDevice);
    int count = 0;

    time2 = seconds();

    timeCopyData = time2 - time1;
#pragma endregion

#pragma region algo
    time1 = seconds();

    #ifdef _DEBUG_
    printf("BFS order : ");
    #endif

    while(*hostDone == no){
        *hostDone = yes;

        #ifdef _DEBUG_
        printf("\ncount = %d, { ", count);
        #endif

        cudaMemcpy(cudaDone, hostDone, sizeof(bBool), cudaMemcpyHostToDevice);
        cudaBfsKernel<<<grid, block>>>(cudaCsrV, cudaCsrE, cudaFrontier, cudaVisited, cudaCost, cudaDone, csr->csrVSize, count);
        cudaMemcpy(hostDone, cudaDone, sizeof(bBool), cudaMemcpyDeviceToHost);
        
        #ifdef _DEBUG_
        printf("}");
        #endif

        count ++;
    }
    printf("\n");

    time2 = seconds();
    timeParallelBFS = time2 - time1;
#pragma endregion

#pragma region copyData2
    time1 = seconds();
    cudaMemcpy(hostCost, cudaCost, sizeof(int) * csr->csrVSize, cudaMemcpyDeviceToHost);
    time2 = seconds();
    timeCopyData = timeCopyData + (time2 - time1);
#pragma endregion

    printf("Iteration times = %d\n", count);

    #ifdef showCost
    printf("Cost :\n");
    int nodeId = 0;
    if(csr->startAtZero == 0){nodeId = 1;}
    for(; nodeId < csr->csrVSize - 1 ; nodeId ++){
        printf("cost[%d] = %d\n", nodeId, hostCost[nodeId]);
    }
    #endif
    //compute whole time
    cudaDeviceReset();
    time1 = seconds();
    timeTotal = time1 - startTime;
    
    printf("============================================================\n");
    printf("[Execution Time] Build Adjlist    = %9f\n", timeBuildAdjlist);
    printf("[Execution Time] Build CSR        = %9f\n", timeBuildCSR);
    printf("[Execution Time] Copy Data        = %9f\n", timeCopyData);
    printf("[Execution Time] ParallelBFS algo = %9f\n", timeParallelBFS);
    printf("[Execution Time] TotalTime        = %9f\n", timeTotal);
    printf("============================================================\n");
}