#include"automata.h"
#include<iostream>
Automata::Automata(unsigned _id, std::vector<DeltaRelation> _edges) : id(_id), edges(_edges){};

unsigned Automata::getId() const
{
    return id;
}
const std::vector<State> Automata:: getStates()
{
   CalculateStates();
   return states;
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
    //Dokato ima state sus sushtoto ime dobavqme { ime}
    std::vector<DeltaRelation>resultEdges=std::vector<DeltaRelation>(edges.size()+other.edges.size());
    for (size_t i = 0; i < edges.size(); i++)
    {
       resultEdges[i]=edges[i];
    }
    for (size_t i = 0; i < other.edges.size(); i++)
    {

        resultEdges[edges.size()+i]=other.edges[i];    
    }
   
    Automata result(0,resultEdges);
    return result;
 }
void Automata:: CalculateStates(){

    for (DeltaRelation delta:edges)
    {
        if (!ContainsStateName(delta.getStart().getStateName()))
        {
            states.push_back(delta.getStart());
        }
        if (!ContainsStateName(delta.getEnd().getStateName()))
        {
            states.push_back(delta.getEnd());
        }
        
    }
    
};

bool Automata:: ContainsStateName(const std::string name)const
{
    for(State state:states)
    {
        if(state.getStateName()==name)
        {
            return true;
        }
    }
    return false;
}