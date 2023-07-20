# Compile.sh
```bash
#if perform compile.sh then got error : permission denied
#go to the folder that contain the compile.sh and use the command below
$ chmod u+x *.sh
```

# Sequential BFS
## Complie and run example.c in the folder "SequentialBFS"
```bash
#Compile example.c in the folder "SequentailBFS"
$ gcc example.c SequentialBFS.c ../Lib/qQueue/qQueue.c ../Lib/AdjList/AdjList.c ../Lib/vVector/vVector.c ../Lib/FileReader/FileReader.c -o a
#即可生成 可執行檔 "a"

#執行a要搭配Dataset
#./a <datasetPath> <startNode>
$./a karate.txt 2
```

# Parallel BFS