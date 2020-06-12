#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <string>
#include "decode.h"
#include "encode.h"
using namespace std;

void printUsage();
void printFileSize(string in, string out);

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

        printFileSize(inputFile, outputFile);
    } else if(strcmp(argv[1],"-d") == 0){
        Decoder dc(inputFile, outputFile);
        dc.recoverTree();
        dc.decode();
    } else {
        printUsage();
    }
}

void printUsage(){
    cerr << "Usage: -e/-d input-file output-file" << endl;
    cerr << "-e: encode the input-file, put encoded result into output-file" << endl;
    cerr << "-d: decode the input-file, put decoded result into output-file" << endl;
    exit(1);
}

void printFileSize(string in, string out){
    int compSize;
    int normSize; 
    ifstream infile(in, ios::binary);
    infile.seekg(0, ios::end);
    normSize = infile.tellg();
    infile.close();

    ifstream infile2(out, ios::binary);
    infile2.seekg(0, ios::end);
    compSize = infile2.tellg();
    infile2.close();

    cout << "Original file size: " << normSize << endl;
    cout << "Compressed file size: " << compSize << endl;
}