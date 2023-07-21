# Compile.sh
```bash
#if got error after performing compile.sh : permission denied
#go to the folder that contain the compile.sh and use the command below
$ chmod u+x *.sh
```

# Sequential BFS
## Complie and run example.c in the folder "SequentialBFS"
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
# Reference
1. In "ParallelBFS/CudaBFS_2007/cudabfs2007.cu" https://github.com/siddharths2710/cuda_bfs/blob/master/cuda_bfs/kernel.cu