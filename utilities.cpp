#include "utilities.h"

void Utilities::MoveElementsRValue(std::vector<State*>&destination,std::vector<State*>&&source)
{
    for (size_t i = 0; i < source.size(); i++)
    {
        destination.push_back(source[i]);
    }
    
}