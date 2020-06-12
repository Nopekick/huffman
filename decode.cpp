#include "decode.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <vector>
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

    string encodedFile = "";
    bitset<8> bts;
    
    // stringstream sstr;
    // while(infile >> sstr.rdbuf());
    // cout << sstr.str() << endl;
    // char c;
    // while (infile.get(c)){
    //     for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
    //         cout << ((c >> i) & 1);
    // }
    char a;
    vector<char> fileContents((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    for(vector<char>::iterator it = fileContents.begin(); it != fileContents.end(); it++){
        a = *it;    
        bitset<8> x(a);
        encodedFile += x.to_string();
    }
    cout << encodedFile << endl;


}
    
void Decoder::decode(){

}