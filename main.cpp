#include <iostream>
#include <stdlib.h> 
#include <string>
#include "decode.h"
#include "encode.h"
using namespace std;

void printUsage();

int main(int argc, char* argv[])
{
    if(argc != 4){
        printUsage();
    }
    string inputFile = argv[2];
    string outputFile = argv[3];

    if(strcmp(argv[1],"-e") == 0){
        Encoder e(inputFile, outputFile);
        e.generateTree();
        e.encode();
    } else if(strcmp(argv[1],"-d") == 0){

    } else {
        printUsage();
    }
}

void printUsage(){
    cerr << "Usage: -e/-d input-file output-file" << endl;
    cerr << "-e: encode the input-file, put encoded result into output file" << endl;
    cerr << "-d: decode the input-file, put decoded result into output file" << endl;
    exit(1);
}