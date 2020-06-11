#include "encode.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void recHelper(Node* node, string built);
bool comp(const Node* n, const Node* n1){
        return n1->frequency < n->frequency;
} 

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

    while(this->list.size() > 1){
        Node* least1 = this->list.back();
        this->list.pop_back();
        Node* least2 = this->list.back();
        this->list.pop_back();
        Node* parent = new Node(least1->frequency + least2->frequency);
        parent->left = least2;
        parent->right = least1;
        this->list.push_back(parent);

        sort(this->list.begin(), this->list.end(), comp);
    }
    Node* root = this->list.back();
    this->head = root;

    recHelper(this->head, "");

    for(unordered_map<char, string>::iterator it = this->bitmap.begin(); it != this->bitmap.end(); it++){
        cout << it->first << " : " << it->second << endl;
    }
}
    
void Encoder::encode(){

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
