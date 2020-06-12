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
    void recHelper(Node* node, std::string built);
    std::string inputFileName;
    std::string outputFileName;
    Node* head;
    std::unordered_map<char, int> frequency;
    std::unordered_map<char, std::string> bitmap;
    std::vector<Node*> list;
};

struct Node {
    Node(char ch, int freq){
        left = nullptr;
        right = nullptr;
        character = ch;
        frequency = freq;
    }

    Node(int freq){
        left = nullptr;
        right = nullptr;
        frequency = freq;
    }

    Node(){
        left = nullptr;
        right = nullptr;
    }

    char character;
    int frequency;
    Node* left;
    Node* right;  
};