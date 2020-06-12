#include "decode.h"
#include "encode.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
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
    
    //retrieve number of nodes
    int numNodes;
    unsigned char b;
    // bitset<8> num(fileContents.at(0));
    // numNodes = num.to_ulong();
    infile.read(reinterpret_cast<char *>(&b), 1);
    bitset<8> z(b);
    numNodes = z.to_ulong();

    //retrieve nodes from infile
    unsigned char ch;
    unsigned char fr;
    int frequency;
    char character;
    Node* arr = new Node[numNodes];
    for(int i = 0; i < numNodes; i++){
        infile.read((char*)&ch, sizeof(char));
        infile.read((char*)&fr, sizeof (int));
        bitset<8> chbit(ch);
        bitset<32> frbit(fr);
        frequency = frbit.to_ulong();
        // character = chbit.to_string();
        cout << chbit.to_string() << " : " << frequency << endl;
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