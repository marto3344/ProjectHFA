#include"automata.h"
#include<iostream>
Automata::Automata(unsigned _id, std::vector<DeltaRelation> _edges) : id(_id), edges(_edges){

  CalculateStates();

};
Automata::~Automata()
{
    for (State* state:states)
    {
        delete state;
    }
    
}
unsigned Automata::getId() const
{
    return id;
}
const std::vector<State*> Automata:: getStates()
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

 Automata Automata:: getUniqueStates(const Automata&other)
 {  
    std::vector<DeltaRelation>resultEdges=std::vector<DeltaRelation>(edges.size()+other.edges.size());
    for (size_t i = 0; i < edges.size(); i++)
    {
       resultEdges[i]=edges[i];
    }
    for (size_t i = 0; i < other.edges.size(); i++)
    {
        std::string resultStart=other.edges[i].getStart()->getStateName();
        std::string resultEnd=other.edges[i].getEnd()->getStateName();
        while (other.ContainsStateName(resultStart))
        {
            resultStart="{"+resultStart+"}";
        }
        while (other.ContainsStateName(resultEnd))
        {
            resultEnd="{"+resultEnd+"}";
        }
        State * resultStartState=new State(*other.edges[i].getStart());
        resultStartState->setStateName(resultStart);
        State* resultEndState=new State(*other.edges[i].getEnd());
        resultEndState->setStateName(resultEnd);
        resultEdges[edges.size()+i]=DeltaRelation(*resultStartState,*resultEndState,other.edges[i].getLabel());    
    }
   
    Automata result(0,resultEdges);
    //result.CalculateStates();
    return result;
 }
void Automata:: CalculateStates(){

    for (DeltaRelation delta:edges)
    {
        if (!ContainsStateName(delta.getStart()->getStateName()))
        {
            states.push_back(delta.getStart());
        }
        if (!ContainsStateName(delta.getEnd()->getStateName()))
        {
            states.push_back(delta.getEnd());
        }
        
    }
    
};

bool Automata:: ContainsStateName(const std::string name)const
{
    if(states.empty())
    {
        return false;
    }
    for(State* state:states)
    {
        if(state->getStateName()==name)
        {
            return true;
        }
    }
    return false;
}