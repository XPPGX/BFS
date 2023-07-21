/***
 * @brief This sites https://github.com/siddharths2710/cuda_bfs/blob/master/cuda_bfs/kernel.cu
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
    #include "../../Lib/CSR/CSR.h"
}

//define bBool;
typedef enum{
    no,
    yes
}bBool;

//include cuda library
#include <cuda_runtime.h>

__global__ void cudaBfsKernel(int* _csrV, int* _csrE, bBool* _frontier, bBool* _visited, int* _cost, bBool* _done, int _nodeSize){
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    // printf("tid = %d", tid);
    int neighbor = -1;
    if(tid <= _nodeSize){
        if(_frontier[tid] == yes && _visited[tid] == no){
            printf("%d, ", tid); // tid == nodeID
            _frontier[tid] = no;
            _visited[tid] = yes;
            __syncthreads();

            //visit neighbor
            for(int neighborIndex = _csrV[tid] ; neighborIndex < _csrV[tid + 1] ; neighborIndex ++){
                neighbor = _csrE[neighborIndex];
                if(_visited[neighbor] == no){
                    _cost[neighbor] = _cost[tid] + 1;
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
//start time 
    struct Graph* adjlist = buildGraph(datasetPath);
    //compute the time of buliding Adjlist
    struct CSR* csr = createCSR(adjlist);
    //compute the time of create csr
    int nodeSize = csr->csrVSize - 1; //actual node size, csr format here will add one space to put the final edge offset.
    showCSR(csr);
    printf("\n\n");
    printf("csr->csrVSize = %d, csr->csrESize = %d\n", csr->csrVSize, csr->csrESize);

    int dev = 0;
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);
    printf("device %d : %s\n", dev, deviceProp.name);
    
    //compute time
#pragma region copyData
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
#pragma endregion

#pragma region threadLayout
    dim3 block(32, 1);
    dim3 grid((nodeSize + block.x - 1) / block.x, 1);
    printf("block(x,y) = (%d,%d), grid(x,y) = (%d,%d)\n", block.x, block.y, grid.x, grid.y);
#pragma endregion

    bBool* hostDone = (bBool*)malloc(sizeof(bBool));
    *hostDone = no;
    bBool* cudaDone;
    cudaMalloc((void**)&cudaDone, sizeof(bBool));
    cudaMemcpy(cudaDone, hostDone, sizeof(bBool), cudaMemcpyHostToDevice);
    int count = 0;

    printf("BFS order : ");
    while(*hostDone == no){
        count ++;
        *hostDone = yes;
        cudaMemcpy(cudaDone, hostDone, sizeof(bBool), cudaMemcpyHostToDevice);
        cudaBfsKernel<<<block, grid>>>(cudaCsrV, cudaCsrE, cudaFrontier, cudaVisited, cudaCost, cudaDone, csr->csrVSize);
        cudaMemcpy(hostDone, cudaDone, sizeof(bBool), cudaMemcpyDeviceToHost);
    }
    printf("\n");
    cudaMemcpy(hostCost, cudaCost, sizeof(int) * csr->csrVSize, cudaMemcpyDeviceToHost);
    printf("Iteration times = %d\n", count);
    printf("Cost : ");
    for(int i = 0 ; i < csr->csrVSize ; i ++){
        printf("cost[%d] = %d\n", i, hostCost[i]);
    }
    //compute whole time
    cudaDeviceReset();
}