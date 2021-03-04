#include <iostream>
#include "Trunk.h"

// Helper function to print branches of the huffman tree
void printTrunk(Trunk *pointer)
{
    if (pointer == nullptr)
        return;

    printTrunk(pointer->previous);

    std::cout << pointer->str;
}