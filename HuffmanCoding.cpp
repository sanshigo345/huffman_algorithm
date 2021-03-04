#include <iostream>
#include <queue>
#include <fstream>
#include <map>
#include "HuffmanCoding.h"

// This function creates, initializes and returns TreeNode.
TreeNode* HuffmanCoding::createNode(char character, int count, TreeNode *left, TreeNode *right) {
    TreeNode* treeNode = new TreeNode();

    treeNode->character = character;
    treeNode->count = count;
    treeNode->right = right;
    treeNode->left = left;

    return treeNode;
}

// This comparison object help us to sort priority queue.
struct compare
{
    bool operator() (TreeNode* left, TreeNode* right)
    {
        // Characters with lowest count will have highest priority in queue
        if (left->count > right->count) {
            return true;
        }
        else {
            return false;
        }
    }
};

// Utility function to check if given node is leaf or not
bool HuffmanCoding::isLeaf(TreeNode* treeNode) {
    if (treeNode->left == nullptr && treeNode-> right == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

/* This function starts with empty string and traverses the tree. If branch is going to the left it adds 0 to string.
 * and adds 1 for the right branches until it traverses all of the tree. It also modifies huffmanCode map too according
 * to leaf nodes and character encodings.
*/
void HuffmanCoding::encodeHelper(TreeNode* root, std::string encodedString,
                                 std::map<char, std::string> &charsAndHuffmanCodes)
{
    if (root == nullptr) { // base case for recursion
        return;
    }

    // found a leaf node
    if (isLeaf(root)) {
        if (encodedString != "") {
            charsAndHuffmanCodes[root->character] = encodedString;
        } else {
            charsAndHuffmanCodes[root->character] = "1";
        }
    }

    encodeHelper(root->left, encodedString + "0", charsAndHuffmanCodes);
    encodeHelper(root->right, encodedString + "1", charsAndHuffmanCodes);
}

void HuffmanCoding::encode(std::string text) {
    if (text == "") { // if text is empty gives an error
        std::cout << "There is no text!\n";
        return;
    }

    // checks all characters in text and store them in map with counts.
    std::map<char, int> charsAndCounts;
    for (char ch: text) {
        charsAndCounts[ch]++;
    }

    // saving chars and counts of them to txt file to decode later
    std::ofstream charsAndCountsOutput("charsAndCounts.txt");
    for (auto pair: charsAndCounts) {
        charsAndCountsOutput << pair.first << pair.second << std::endl;
    }
    charsAndCountsOutput.close();

    // Priority queue for storing sorted TreeNodes
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, compare> TreeNodesPQ;

    // Creating leaf node for every character and pushing them to PQ
    for (auto pair: charsAndCounts) {
        TreeNodesPQ.push(createNode(pair.first, pair.second, nullptr, nullptr));
    }

    /* This while loop creates a parent node for two characters leaf nodes and removes them from priority queue. Created
     * parent node also get pushed back to the priority queue. While creating parent nodes it uses huffman algorithm
     * which created parent node count is equal to the sum of child node's counts. Loops this until priority queue size
     * reaches one.
    */
    while (TreeNodesPQ.size() != 1)
    {
        TreeNode *left = TreeNodesPQ.top();
        TreeNodesPQ.pop();
        TreeNode *right = TreeNodesPQ.top();
        TreeNodesPQ.pop();

        int sum = left->count + right->count;
        TreeNodesPQ.push(createNode('\0', sum, left, right));
    }

    // Last element of priority queue becomes root of tree.
    TreeNode* root = TreeNodesPQ.top();

    // encodes with helper function and also stores characters and their respective HuffmanCodes to map.
    std::map<char, std::string> charsAndHuffmanCodes;
    encodeHelper(root, "", charsAndHuffmanCodes);

    // writing Huffman encodings to .txt file to store them.
    std::ofstream huffmanEncodingOutput("CharacterEncodings.txt");
    for (auto pair: charsAndHuffmanCodes) {
        huffmanEncodingOutput << pair.first << pair.second << std::endl;
    }
    huffmanEncodingOutput.close();

    // For every character in given text get their Huffman codes.
    std::string finalEncodedString;
    for (char ch: text) {
        finalEncodedString += charsAndHuffmanCodes[ch];
    }

    // print encoded result
    std::cout << finalEncodedString;
    return;
}

// outputs the encoding of given character. Uses program created (encode part) CharacterEncodings.txt to find encodings.
void HuffmanCoding::getCharacterCoding(std::string character) {
    std::ifstream huffmanCharacterEncodings("CharacterEncodings.txt");
    std::string tempText;

    while (getline (huffmanCharacterEncodings, tempText)) {
        if (character[0] == tempText[0]) {
            tempText.erase(0, 1);
            std::cout << tempText;
            return;
        }
    }
    std::cout << "Can't find character " << character << " as encoded character." << std::endl;
}

// decoding huffman tree with recursion
void HuffmanCoding::decodeHelper(TreeNode* root, int &counter, std::string str)
{
    // Base case for recursion
    if (root == nullptr) {
        return;
    }

    // when found a leaf code print it.
    if (isLeaf(root)) {
        std::cout << root->character;
        return;
    }

    counter++;

    if (str[counter] == '0') {
        decodeHelper(root->left, counter, str);
    } else {
        decodeHelper(root->right, counter, str);
    }
}

void HuffmanCoding::decode(std::string encodedString) {
    if (encodedString == "") {
        std::cout << "This encode cannot be decoded - no encoded string" << std::endl;
    return;
    }

    // get characters and counts from .txt
    std::ifstream charsAndCountsInput("charsAndCounts.txt");
    std::string tempText;
    std::string tempText2;
    std::map<char, int> charsAndCounts;

    // getting data from txt to map
    while (getline (charsAndCountsInput, tempText)) {
        tempText2 = tempText;
        tempText.erase(0, 1);
        charsAndCounts[tempText2.at(0)] = stoi(tempText);
    }

    // creating Huffman tree to traverse and decode given text file (same algorithms which used in encode function)
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, compare> TreeNodesPQ;

    for (auto pair: charsAndCounts) {
        TreeNodesPQ.push(createNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (TreeNodesPQ.size() != 1)
    {
        TreeNode *left = TreeNodesPQ.top();
        TreeNodesPQ.pop();
        TreeNode *right = TreeNodesPQ.top();
        TreeNodesPQ.pop();

        int sum = left->count + right->count;
        TreeNodesPQ.push(createNode('\0', sum, left, right));
    }

    TreeNode* root = TreeNodesPQ.top();

    if (isLeaf(root))
    {
        while (root->count--) {
            std::cout << root->character;
        }
    }
    else
    {
        int counter = -1;
        while (counter < (int)encodedString.size() - 1) {
            decodeHelper(root, counter, encodedString);
        }
    }
}

void HuffmanCoding::printTreeHelper(TreeNode *root, Trunk *previous, bool isLeft) {
    if (root == nullptr) {
        return;
    }

    std::string previousStr = "    ";
    Trunk *trunk = new Trunk(previous, previousStr);

    printTreeHelper(root->left, trunk, true);

    if (!previous)
        trunk->str = "===";
    else if (isLeft)
    {
        trunk->str = "*===";
        previousStr = "   |";
    }
    else
    {
        trunk->str = "*===";
        previous->str = previousStr;
    }

    printTrunk(trunk);
    std::cout << root->character << std::endl;

    if (previous)
        previous->str = previousStr;
    trunk->str = "   |";

    printTreeHelper(root->right, trunk, false);
}

void HuffmanCoding::printTree() {
    // get characters and frequencies from .txt
    std::ifstream charsAndFreqs("charsAndCounts.txt");
    std::string tempText;
    std::string tempText2;
    std::map<char, int> charsAndCounts;

    // getting data from txt to map
    while (getline (charsAndFreqs, tempText)) {
        tempText2 = tempText;
        tempText.erase(0, 1);
        charsAndCounts[tempText2.at(0)] = stoi(tempText);
    }

    // same algorithm to create tree as decode and encode.
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, compare> TreeNodesPQ;

    for (auto pair: charsAndCounts) {
        TreeNodesPQ.push(createNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (TreeNodesPQ.size() != 1)
    {
        TreeNode *left = TreeNodesPQ.top();
        TreeNodesPQ.pop();
        TreeNode *right = TreeNodesPQ.top();
        TreeNodesPQ.pop();

        int sum = left->count + right->count;
        TreeNodesPQ.push(createNode('\0', sum, left, right));
    }

    TreeNode* root = TreeNodesPQ.top();

    printTreeHelper(root ,nullptr, false);
}