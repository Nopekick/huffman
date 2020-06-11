#include "encode.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

Encoder::Encoder(string inputFile, string outputFile){
    this->inputFileName = inputFile;
    this->outputFileName = outputFile;
}

void Encoder::generateTree(){
    ifstream infile(this->inputFileName);
    
    if(!infile){
        cerr << "Could not open input file: " << this->inputFileName << endl;
        exit(1);
    }

    char c;
    while(infile.get(c)){
        if(this->frequency.find(c) == this->frequency.end()){
            this->frequency[c] = 1;
        } else {
            this->frequency[c]++;
        }
    }
    infile.close();

    for(unordered_map<char, int>::iterator it = this->frequency.begin(); it != this->frequency.end(); it++){
        Node a(it->first, it->second);
        this->list.push_back(a);
    }
    sort(this->list.begin(), this->list.end());

    
}
    
void Encoder::encode(){

}