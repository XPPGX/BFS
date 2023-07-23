#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]){
    string datasetReadPath = argv[1];
    string datasetWritePath = argv[2];
    
    ifstream reader;
    reader.open(datasetReadPath);
    ofstream writer;
    writer.open(datasetWritePath);
    
    set<int> allNodeID;
    int nodeNum = 0;
    int edgeNum = 0;
    int node1 = 0;
    int node2 = 0;
    reader >> nodeNum >> edgeNum;
    vector<int> leftColumn;
    vector<int> rightColumn;
    while(!reader.eof()){
        reader >> node1 >> node2;

        allNodeID.insert(node1);
        allNodeID.insert(node2);

        leftColumn.push_back(node1);
        rightColumn.push_back(node2);
    }
    printf("allNodeID size = %ld\n", allNodeID.size());
    map<int, int> mapping;
    int convertID = 0;
    for(const auto &node : allNodeID){
        convertID ++;
        mapping[node] = convertID;
    }
    printf("mapping[%d] = %d\n", 548551, mapping[548551]);
    
    //output converted dataset
    writer << nodeNum << " " << edgeNum;
    for(int i = 0 ; i < edgeNum ; i ++){
        node1 = mapping[leftColumn[i]];
        node2 = mapping[rightColumn[i]];

        writer << endl;
        writer << node1 << " " << node2;
    }
    writer.close();
    reader.close();
}