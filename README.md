# BFS
1. ### [Compile.sh](#compilesh)
2. ### [Sequential BFS](#sequential-bfs)
3. ### [Parallel BFS](#parallel-bfs)
    - [CudaBFS_2007](#cudabfs_2007)

# Compile.sh
```bash
#if got error after performing compile.sh : permission denied
#go to the folder that contain the compile.sh and use the command below
$ chmod u+x *.sh
```

# Sequential BFS
```bash
#Compile example.c in the folder "SequentailBFS"
$ ./complie.sh
#It will create a executable file "a".

#execute "a" should go with the parameters like : datasetPath, mode, startNode, whereas the mode = 1 represent adpating CSR, mode = 0 adapting Adjlist.
#./a <datasetPath> <mode> <startNode>
$./a karate.txt 1 10 #an example of the command to perform sequential BFS
```

# Parallel BFS
- Note
    - In cuda file(*.cu), if we want to use the library written by ourself, it should be included as the form below.<br>
        ```c
        //example
        extern "C"{
            #include "../../Lib/CSR/CSR.h"
        }
        ```
- ### CudaBFS_2007
    ```bash
    #Compile cudabfs2007.cu in the folder CudaBFS_2007
    $ ./compile.sh
    #It will create a executable file "a".

    #execute "a" should go with the parameters like : datasetPath, startNode.
    #./a <datasetPath> <startNode>
    $./a ../../Datasets/dblp.txt 10 #an example of the command to perform CudaBFS_2007.
    ```
    #### Experiments
    ![Alt text](image.png)
    #### Reference(with hyperlink)
    1. [cuda_bfs](https://github.com/siddharths2710/cuda_bfs/blob/master/cuda_bfs/kernel.cu)
    2. [Paper](https://www.nvidia.com/content/cudazone/CUDABrowser/downloads/Accelerate_Large_Graph_Algorithms/HiPC.pdf)

# Environment
- CPU : Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
- GPU : GeForce GTX 1060 6GB