#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    string datasetReadPath = argv[1];
    string datasetWritePath = argv[2];
    //Delete k lines which are leading lines in the dataset.
    int leadingLineNumber = atoi(argv[3]);
    //The information which will be written at head of the dataset.
    int nodeNum = atoi(argv[4]);
    int edgeNum = atoi(argv[5]);

    cout << datasetReadPath << endl;

    ifstream reader(datasetReadPath);
    ofstream writer(datasetWritePath);
    string tempLine;
    for(int i = 0 ; i < leadingLineNumber ; i ++){
        getline(reader, tempLine);
    }
    writer << nodeNum << " " << edgeNum;
    int k = 0;
    int node1 = 0;
    int node2 = 0;
    while(!reader.eof()){
        reader >> node1 >> node2;
        writer << endl;
        writer << node1 << " " << node2;
        k ++;
    }
    writer.close();
    reader.close();
}