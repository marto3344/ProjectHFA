#include"automata.h"
#include<iostream>

Automata::Automata(unsigned _id, std::vector<State> _states, std::vector<DeltaRelation> _edges) : id(_id), states(_states), edges(_edges){};

unsigned Automata::getId() const
{
    return id;
}

void Automata::Print() const
{
    for (DeltaRelation delta : edges)
    {
        std::cout<<delta;
    }
}