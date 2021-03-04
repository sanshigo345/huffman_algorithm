#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <map>
#include <vector>
#include "TreeNode.h"
#include "Trunk.h"

class HuffmanCoding {
public:

    TreeNode* createNode(char character, int frequency, TreeNode* left, TreeNode* right);
    // struct comp
    bool isLeaf(TreeNode* root);
    void encodeHelper(TreeNode* root, std::string str, std::map<char, std::string> &huffmanCode);
    void decodeHelper(TreeNode* root, int &counter, std::string str);
    void encode(std::string text);
    void getCharacterCoding(std::string character);
    void decode(std::string encodedString);
    void printTreeHelper(TreeNode *root, Trunk *prev, bool isLeft);
    void printTree();
};


#endif //HUFFMANCODING_H
