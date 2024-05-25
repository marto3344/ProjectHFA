#include<iostream>
#include<cstring>
#include "utilities.h"

void Utilities::MoveElementsRValue(std::vector<State*>&destination,std::vector<State*>&&source)
{
    for (size_t i = 0; i < source.size(); i++)
    {
        destination.push_back(source[i]);
    }
    
}
bool Utilities::IsValidStateName(const std::string name)
{
    for (size_t i = 0; i < name.size(); i++)
    {
        if(name[i]==' ')
        {
            return false;
        }
    }
    return true;
}