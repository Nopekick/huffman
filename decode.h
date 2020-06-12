#include <string>
#include <unordered_map>

struct Node;

class Decoder {
public:
    Decoder(std::string inputFile, std::string outputFile);
    void recoverTree();
    void decode();

private:
    std::string inputFileName;
    std::string outputFileName;
    Node* head;
};
