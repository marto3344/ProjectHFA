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

 Automata Automata:: getUniqueStates(const Automata&other)const
 {
    std::vector<State> resultStates=std::vector<State>(states.size()+other.states.size());
    for (size_t i = 0; i < states.size(); i++)
    {
       resultStates[i]=states[i];
    }
    for (size_t i = 0; i < other.states.size(); i++)
    {
        resultStates[states.size()+i]=other.states[i];    
    }
    std::vector<DeltaRelation>resultEdges=std::vector<DeltaRelation>(edges.size()+other.edges.size());
    for (size_t i = 0; i < edges.size(); i++)
    {
       resultEdges[i]=edges[i];
    }
    for (size_t i = 0; i < other.edges.size(); i++)
    {
        resultEdges[edges.size()+i]=other.edges[i];    
    }
    for (size_t i = 0; i < resultStates.size(); i++)
    {
       resultStates[i].setStateName(std::to_string(i));
    }
    Automata result(0,resultStates,resultEdges);
    return result;
 }