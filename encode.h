#include <string>
#include <unordered_map>
#include <vector> 
struct Node;

class Encoder {
public:
    Encoder(std::string inputFile, std::string outputfile);
    void generateTree();
    void encode();

private:
    std::string inputFileName;
    std::string outputFileName;
    Node* head;
    std::unordered_map<char, int> frequency;
    std::vector<Node> list;
};

struct Node {
    Node(char ch, int freq){
        left = nullptr;
        right = nullptr;
        character = ch;
        freq = frequency;
    }

    char character;
    int frequency;
    Node* left;
    Node* right;  

    bool operator<(const Node& n){
        return this->frequency < n.frequency;
    }  
};