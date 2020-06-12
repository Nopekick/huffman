#ifndef NODE_H
#define NODE_H

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

static bool comp(const Node* n, const Node* n1){
        return n1->frequency < n->frequency;
}

#endif