#include<iostream>
#include<fstream>
#include"automata.h"
#include"utilities.h"
Automata::Automata(unsigned _id,const std::vector<DeltaRelation>& _edges){
  id=_id;
  edges=_edges;
  CalculateStates();

};
Automata::Automata(const Automata &other)
{
    id=other.id;
    edges=other.edges;
    CalculateStates();
}
Automata::~Automata()
{
    // //std::cout<<"~Automata";
    // for (State* state:states)
    // {
    //     if(state!=nullptr)
    //     {
    //         delete[]state;
    //     }
    // }
    
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
        std::cout<<delta<<"\n";
    }
}

 Automata Automata:: getUniqueStates(const Automata&other)const
 {  
    std::vector<DeltaRelation>resultEdges=std::vector<DeltaRelation>(edges.size()+other.edges.size());
    for (size_t i = 0; i < edges.size(); i++)
    {
       resultEdges[i]=edges[i];
    }
    for (size_t i = 0; i < other.edges.size(); i++)
    {
        std::string resultStart="{"+other.edges[i].getStart()->getStateName()+"}";
        std::string resultEnd="{"+other.edges[i].getEnd()->getStateName()+"}";
        while (other.ContainsStateName(resultStart)||this->ContainsStateName(resultStart))
        {
            resultStart="{"+resultStart+"}";
        }
        while (other.ContainsStateName(resultEnd)||this->ContainsStateName(resultEnd))
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
    result.CalculateStates();
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
    for(State* state:states)
    {
        if(state->getStateName()==name)
        {
            return true;
        }
    }
    return false;
}


 Automata Automata:: Union(const Automata &other)const
 {
    Automata result=this->getUniqueStates(other);
    return result;
 }
 Automata Automata::Concat(const Automata &other)const{
    Automata result=this->getUniqueStates(other);
    for (size_t i = 0; i < states.size(); i++)
    {
        if (result.states[i]->isFinal())
        {
            result.states[i]->setFinal(false);
            for (size_t j = 0; j < other.states.size(); j++)
            {
                if (other.states[j]->isInitial())
                {
                    result.edges.push_back(DeltaRelation(*result.states[i],*other.states[j],'~'));
                    other.states[j]->setInitial(false);
                }                
            }           
        }
        
    }
    return result;   
 }
 Automata Automata:: Un()const
 {
    Automata result=Automata(*this);
    for (size_t i = 0; i < states.size(); i++)
    {
        if (result.states[i]->isFinal())
        {
           for (size_t j = 0; j < states.size(); j++)
           {
              if (result.states[j]->isInitial())
              {
                result.edges.push_back(DeltaRelation(*result.states[i],*result.states[j],'~'));
              }
              
           }
           
        }
        
    }
    return result;   
 }
 std::vector<State*> Automata::EpsiloneClosure(const State&other)
 {
    std::vector<State*>resultStates;
    for (DeltaRelation delta:edges)
    {
       if (delta.getStart()==&other &&delta.getLabel()=='~')
       {
          resultStates.push_back(delta.getEnd());
       }
          
    }
    return resultStates;


 }
 const std::vector<State *> Automata::FindConnectedStated(const State &start) const
 {
    std::vector<State*> result;
    for (DeltaRelation delta:edges)
    {
        if (start==*delta.getStart())
        {
            result.push_back(delta.getEnd());
        }
        
    }
     return result;
 }

 void Automata::RemoveEpsilons()
 {

 }
 const std::vector<State*>Automata::getInitialStates() const
 {
    std::vector<State*>result;
    for (State* state:states)
    {
        if (state->isInitial())
        {
            result.push_back(state);
        }
    
    }
    return result;
    std::cout<<"End of Initial";
 }

 const std::vector<State *> Automata::getFinalStates() const
 {
    std::vector<State*>result;
    for (State* state:states)
    {
        if (state->isFinal())
        {
            result.push_back(state);
        }
    
    }
    return result;

 }

 bool Automata:: Empty()const
 {
   if(getFinalStates().empty()|| getInitialStates().empty())
   {
      return true;
   }
   std::vector<State*>visited;
   const std::vector<State*>initialStates=getInitialStates();
   for (State* state:initialStates)
   {
     if (FindPaths(*state,visited))
     {
        return true;
     }
     
   }
   
     
   
   return false;
 }


 std::vector<State*> Automata::TraversalWithChar(const std::vector<State*>&currStates, const char c)
 {
   std::vector<State*>result;
   for (size_t i = 0; i < currStates.size(); i++)
   {
     for (size_t j = 0; j < edges.size(); j++)
     {
        if (*currStates[i]==*edges[j].getStart()&&edges[j].getLabel()==c)
        {
            result.push_back(edges[j].getEnd());
        }       
     }
     
   }
   return result;
 }

 bool Automata::FindPaths(const State &start,  std::vector<State *> &visitedStates) const
 {
    if (FindConnectedStated(start).empty()||ConnectedStatesAreVisited(start,visitedStates))
    {
        if(start.isFinal())
        {
            return true;
        }
        else return false;
    }
    for (DeltaRelation delta:edges)
    {
        if (start==*delta.getStart()&&!ContainsState(start,visitedStates))
        {
            visitedStates.push_back(delta.getEnd());
            return FindPaths(*delta.getEnd(),visitedStates);
        }
        
    }
    if(start.isFinal())
    {
     return true;
    }
    return false;
 }

 bool Automata::ContainsState(const State &state, const std::vector<State *> &vec)
 {
    for (State* vecState:vec)
    {
        if (state==*vecState)
        {
            return true;
        }
    }
    
     return false;
 }

 void Automata::draw() const
 {
   std::ofstream out;
   out.open("Automata.dot");
   if(out.is_open())
   {
     out<<"digraph Automata_"<<id<<"{\n";
     for (size_t i = 0; i < edges.size(); i++)
     {
        if(edges[i].getStart()->isInitial())
        {
           out<<" hiddenNode[shape=none,label=\"\"]"<<"\n";
           out<<" hiddenNode->"<<edges[i].getStart()->getStateName()<<"[arrowtail=none]"<<"\n";
        }
        if(edges[i].getEnd()->isInitial())
        {
           
           out<<" hiddenNode[shape=none,label=\"\"]"<<"\n";
           out<<" hiddenNode->"<<edges[i].getEnd()->getStateName()<<"[arrowtail=none]"<<"\n";
        }
        if(edges[i].getStart()->isFinal())
        {
           out<<" "<<edges[i].getStart()->getStateName()<<"[shape=doublecircle]\n";
        }
        else{
            out<<" "<<edges[i].getStart()->getStateName()<<"[shape=circle]\n";
        }
        if(edges[i].getEnd()->isFinal())
        {
           out<<" "<<edges[i].getEnd()->getStateName()<<"[shape=doublecircle]\n";
        }
        else{
            out<<" "<<edges[i].getEnd()->getStateName()<<"[shape=circle]\n";
        }
        out<<" "<<edges[i].getStart()->getStateName();
        out<<"->"<<edges[i].getEnd()->getStateName();
        out<<"[label=\""<<edges[i].getLabel()<<"\"]"<<"\n" ;  
     }
     out<<"}";
     out.close();
   }
   else throw "coudn't draw the automata";
   
 }

 void Automata::setId(unsigned _id)
 {
    id=_id;
 }

 bool Automata::Recognize(std::string word)
 {
     std::vector<State *> currStates;
     Utilities::MoveElementsRValue(currStates, TraversalWithChar(getInitialStates(), word[0]));
     for (size_t i = 1; i < word.size(); i++)
     {
         if (currStates.empty())
             return false;
         Utilities::MoveElementsRValue(currStates, TraversalWithChar(currStates, word[i]));
     }
     for (State *state : currStates)
     {
         if (state->isFinal())
         {
             return true;
         }
     }
     return false;
  }
  void Automata:: Save(std::string filename)const
  {
    std::ofstream os;
    os.open(filename,std::ios::app);
    os<<edges.size()<<'\n';
    for (DeltaRelation delta:edges)
    {
        os<<delta<<'\n';
    }
    os.close();
  }
  std::istream& operator>>(std::istream& in, Automata& automata)
  {
    size_t relationsCount;
    in>>relationsCount;
    for (size_t i = 0; i <relationsCount; i++)
    {
        DeltaRelation* delta=new DeltaRelation();
        in>>*delta;
        automata.edges.push_back(*delta);
    }
    automata.CalculateStates();
    return in;
  }
bool Automata::Deterministic()const
{
    if(getInitialStates().size()>1)
    {
        return false;
    }
    const size_t alphabet_size=36;
    bool alphabet[alphabet_size]={0,};
    for (State* state:states)
    {
        for (DeltaRelation delta:edges)
        {
            if (*state == *delta.getStart())
            {
                if (delta.getLabel() >= 48 && delta.getLabel() <= 57) // if the char is digit
                {
                    if (alphabet[delta.getLabel()-48])
                    {
                        return false;
                    }
                    alphabet[delta.getLabel()-48] = true;
                }
                if(delta.getLabel()>=97&&delta.getLabel()<=122)//if the char is small letter
                {
                    if(alphabet[delta.getLabel()-87])
                    {
                        return false;
                    }
                    alphabet[delta.getLabel()-87]=true;

                }
            }
        }
        
    }
    return true;
}
 bool Automata::ConnectedStatesAreVisited(const State&start,const std::vector<State*>&visited)const
 {
     for (State* state:FindConnectedStated(start))
     {
        if (!ContainsState(*state,visited))
        {
            return false;
        }       
     }   
     return true;
 }