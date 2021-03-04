#ifndef TRUNK_H
#define TRUNK_H

#include <string>

struct Trunk
{
    Trunk *previous;
    std::string str;

    Trunk(Trunk *previous, std::string str)
    {
        this->previous = previous;
        this->str = str;
    }
};

void printTrunk(Trunk *pointer);

#endif //TRUNK_H