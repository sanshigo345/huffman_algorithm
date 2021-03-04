#include <iostream>
#include <fstream>
#include "HuffmanCoding.h"

using namespace std;

int main(int argc, char* argv[]) {
    HuffmanCoding huffmanCoding;
    string argu1 = argv[1];
    if (argu1 == "-i") {
        string argu3 = argv[3];
        if (argu3 == "-encode") {
            string argu2 = argv[2];
            ifstream inputEncode(argu2);
            string text; // text that not encoded yet.
            getline(inputEncode, text); // reading input file which will be encoded
            huffmanCoding.encode(text);
            return 0;
        } else {
            string argu2 = argv[2];
            ifstream inputDecode(argu2);
            string EncodedText; // text that encoded.
            getline (inputDecode, EncodedText);
            huffmanCoding.decode(EncodedText);
            return 0;
        }
    } else if (argu1 == "-s") {
        string argu2 = argv[2];
        huffmanCoding.getCharacterCoding(argu2);
        return 0;
    } else if (argu1 == "-l") {
        huffmanCoding.printTree();
        return 0;
    }

    return 0;
}
