#include "decode.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <stdio.h>
#include <vector>
#include <algorithm> 
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
    vector<Node*> list;
    list.reserve(numNodes);
    for(int i = 0; i < numNodes; i++){
        infile.read((char*)&ch, sizeof(char));
        bitset<8> chbit(ch);
        unsigned long temp = chbit.to_ulong(); 
        character = static_cast<unsigned char>(temp);
        
        infile.read((char*)&fr, sizeof(int));
        bitset<32> frbit(fr);
        frequency = frbit.to_ulong();
        cout << character << " : " << frequency << endl;
        list.push_back(new Node(character, frequency));
    }
    
    sort(list.begin(), list.end(), comp);

    while(list.size() > 1){
        Node* least1 = list.back();
        list.pop_back();
        Node* least2 = list.back();
        list.pop_back();
        Node* parent = new Node(least1->frequency + least2->frequency);
        parent->left = least2;
        parent->right = least1;
        list.push_back(parent);

        sort(list.begin(), list.end(), comp);
    }
    Node* root = list.back();
    this->head = root;

    infile.close();
}