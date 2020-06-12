#ifndef ENCODE_H
#define ENCODE_H

#include <string>
#include <unordered_map>
#include <vector> 
struct Node;

class Encoder {
public:
    Encoder(std::string inputFile, std::string outputfile);
    void generateTree();
    void encode();
    void freeHelper(Node* temp);

private:
    void recHelper(Node* node, std::string built);
    std::string inputFileName;
    std::string outputFileName;
    Node* head;
    std::unordered_map<char, int> frequency;
    std::unordered_map<char, std::string> bitmap;
    std::vector<Node*> list;
};

#endif