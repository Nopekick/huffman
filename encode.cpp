#include "encode.h"
#include "node.h"
#include <unordered_map>
#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void recHelper(Node* node, string built); 

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
        Node* temp = new Node(it->first, it->second);
        this->list.push_back(temp);
    }
    sort(this->list.begin(), this->list.end(), comp);
    vector<Node*> tempList(this->list);

    while(tempList.size() > 1){
        Node* least1 = tempList.back();
        tempList.pop_back();
        Node* least2 = tempList.back();
        tempList.pop_back();
        Node* parent = new Node(least1->frequency + least2->frequency);
        parent->left = least2;
        parent->right = least1;
        tempList.push_back(parent);

        sort(tempList.begin(), tempList.end(), comp);
    }
    Node* root = tempList.back();
    this->head = root;

    recHelper(this->head, "");

    //Print (char: bit string) pairs
    // for(unordered_map<char, string>::iterator it = this->bitmap.begin(); it != this->bitmap.end(); it++){
    //     cout << it->first << " : " << it->second << endl;
    // }
}
    
void Encoder::encode(){
    ifstream infile(this->inputFileName);
    
    if(!infile){
        cerr << "Could not open input file: " << this->inputFileName << endl;
        exit(1);
    }

    char c;
    string encodedFile = "";
    while(infile.get(c)){
        encodedFile += this->bitmap[c];
    }
    infile.close();

    ofstream outfile(this->outputFileName, ios::binary);
    string firstByte;

    //first 8 bits (1 byte) of file will be number of encoded Node structs
    //this means the input document can have at most 255 different characters
    int numLeafs = this->list.size();
    string bin = bitset<8>(numLeafs).to_string(); 
    unsigned long dec = bitset<8>(bin).to_ulong();
    outfile.write((const char*)&dec, 1);

    //encoded char (character):int (frequency) pairs
    for(vector<Node*>::iterator it = this->list.begin(); it != this->list.end(); it++){
        Node temp = **it;
        char c[] = {temp.character};
        int fr = temp.frequency;
        bin = bitset<32>(fr).to_string(); 
        dec = bitset<32>(bin).to_ulong();
        outfile.write((char*)&c[0], sizeof(char));
        outfile.write((char*)&dec, sizeof (int));
    }

    //next 8 bits of file will be length of padding of last byte written to file
    int difference = 8 - (encodedFile.length() % 8);
    string binary = bitset<8>(difference).to_string(); 
    unsigned long decimal = bitset<8>(binary).to_ulong();
    outfile.write((const char*)&decimal, 1);
    
    //write file contents to binary file, 8 bits (1 byte) at a time
    while(encodedFile.length() > 0){
        if(encodedFile.length() >= 8){
            firstByte = encodedFile.substr(0,8);
            encodedFile = encodedFile.substr(8);
        } else {
            firstByte = encodedFile.substr(0, encodedFile.length());
            encodedFile = "";
        }
        
        bitset<8> bits(firstByte);
        unsigned long binary_value = bits.to_ulong();
        outfile.write((const char*)&binary_value, 1);
    }

    outfile.close();
}

void Encoder::recHelper(Node* node, string built){
    if(node->left == nullptr && node->right == nullptr){
        this->bitmap[node->character] = built;
    }
    if(node->left != nullptr){
        recHelper(node->left, built+"0");
    }
    if(node->right != nullptr){
        recHelper(node->right, built+"1");
    }
}
