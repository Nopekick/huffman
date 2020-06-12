#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <unordered_map>

struct Node;

class Decoder {
public:
    Decoder(std::string inputFile, std::string outputFile);
    void recoverTree();
    void decode();
    void freeHelper(Node* temp);

private:
    std::string inputFileName;
    std::string outputFileName;
    Node* head;
    std::string content;
    int padding;
};

#endif