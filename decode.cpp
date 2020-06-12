#include "decode.h"
#include "encode.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

Decoder::Decoder(string inputFile, string outputFile){
    this->inputFileName = inputFile;
    this->outputFileName = outputFile;
}

void Decoder::decode(){
    ifstream infile(this->inputFileName, ios::binary);

    if(!infile){
        cerr << "Could not open input file: " << this->inputFileName << endl;
        exit(1);
    }

    // string encodedFile = "";
    // vector<char> fileContents((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    // bitset<8> x(fileContents.at(6));
    // cout << static_cast<unsigned char>(x.to_ulong()) << endl;
    // infile.seekg(0);

    //retrieve number of nodes
    int numNodes;
    unsigned char first;
    infile.read(reinterpret_cast<char *>(&first), 1);
    bitset<8> f(first);
    numNodes = f.to_ulong();

    
    //retrieve nodes from infile
    unsigned char ch, fr;
    int frequency;
    char character;
    Node* arr = new Node[numNodes];
    for(int i = 0; i < numNodes; i++){
        infile.read((char*)&ch, sizeof(char));
        bitset<8> chbit(ch);
        unsigned long temp = chbit.to_ulong(); 
        character = static_cast<unsigned char>(temp);
        
        infile.read((char*)&fr, sizeof(int));
        bitset<32> frbit(fr);
        frequency = frbit.to_ulong();
        
        
        cout << character << " : " << frequency << endl;
        //cout << character << " : " << temp << " : " << ch << " : " << chbit.to_string() << endl;
        // cout << frbit.to_string() << endl;
    }
    
    
    // char a;
    // for(vector<char>::iterator it = fileContents.begin() + 1; it != fileContents.end(); it++){
    //     a = *it;    
    //     bitset<8> x(a);
    //     encodedFile += x.to_string();
    // }
    //cout << encodedFile << endl;

    infile.close();
}