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

void Decoder::recoverTree(){
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
        //cout << character << " : " << frequency << endl;
        list.push_back(new Node(character, frequency));
    }
    
    sort(list.begin(), list.end(), comp);

    Node* least1, *least2;
    while(list.size() > 1){
        least1 = list.back();
        list.pop_back();
        least2 = list.back();
        list.pop_back();
        Node* parent = new Node(least1->frequency + least2->frequency);
        parent->left = least2;
        parent->right = least1;
        list.push_back(parent);

        sort(list.begin(), list.end(), comp);
    }
    Node* root = list.back();
    this->head = root;

    //get padding length
    char pad;
    infile.read((char*)&pad, sizeof(char));
    bitset<8> padd(pad); 
    this->padding = padd.to_ulong();

    //build binary string of compressed file contents
    string file = "";
    char byte;
    while(infile){
        infile.read((char*)&byte, sizeof(char));
        bitset<8> reader(byte);
        file += reader.to_string();
    }
    this->content = file;
    infile.close();
}

void Decoder::decode(){
    string buildOutput, content;


    string lastByte = this->content.substr(this->content.length()-8);
    lastByte = lastByte.substr(this->padding);
    content = this->content.substr(0, this->content.length()-8) + lastByte;


    int pos = 0;
    Node* temp = this->head;
    while(pos < content.length()){
        if(content[pos] == '0'){
            if(temp->left != nullptr){
                temp = temp->left;
                if(temp->left == nullptr && temp->right == nullptr){
                    buildOutput += temp->character;
                    temp = this->head;
                }
            }
        } else if(content[pos] == '1'){
            if(temp->right != nullptr){
                temp = temp->right;
                if(temp->left == nullptr && temp->right == nullptr){
                    buildOutput += temp->character;
                    temp = this->head;
                }
            }
        }
        pos++;
    }

    ofstream outfile(this->outputFileName);
    outfile << buildOutput;
    outfile.close();

    freeHelper(this->head);
}

void Decoder::freeHelper(Node* temp){
    if(temp->left != nullptr)
        freeHelper(temp->left);
    if(temp->right != nullptr)
        freeHelper(temp->right);
    
    delete temp;
}