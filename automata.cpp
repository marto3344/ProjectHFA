#include<iostream>
#include<fstream>
#include<exception>
#include"automata.h"
#include"utilities.h"
Automata::Automata(unsigned _id,const std::vector<DeltaRelation*>& _edges){
  id=_id;
  for (size_t i = 0; i < _edges.size(); i++)
  {
    edges.push_back(new DeltaRelation(*_edges[i]));
  }
  
  CalculateStates();

};
Automata::Automata(const Automata &other)
{
    id=other.id;
    copy(other);
    CalculateStates();
}
Automata& Automata::operator=(const Automata &other)
{
    if(this==&other)
    {
        return *this;
    }
    freeMemory();
    copy(other);
    CalculateStates();
    return *this;
}
Automata::Automata(Automata &&other)
{
   id=other.id;
   for (size_t i = 0; i < other.edges.size(); i++)
   {
      edges[i]=other.edges[i];
      other.edges[i]=nullptr;
   }
   

}
Automata& Automata::operator=(Automata &&other)
{
    if (this == &other)
    {
        return *this;
    }
    id = other.id;
    for (size_t i = 0; i < other.edges.size(); i++)
    {
        *edges[i] = std::move(*other.edges[i]);
    }
    return *this;
}
Automata::~Automata()
{
  freeMemory();  
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
    for (DeltaRelation* delta : edges)
    {
        std::cout<<*delta<<"\n";
    }
}

 Automata Automata:: getUniqueStates(const Automata&other)const
 {  
    std::vector<DeltaRelation*>resultEdges=std::vector<DeltaRelation*>(edges.size()+other.edges.size());
    for (size_t i = 0; i < edges.size(); i++)
    {
       resultEdges[i]=new DeltaRelation (*edges[i]);
    }
    for (size_t i = 0; i < other.edges.size(); i++)
    {
        std::string resultStart="{"+other.edges[i]->getStart()->getStateName()+"}";
        std::string resultEnd="{"+other.edges[i]->getEnd()->getStateName()+"}";
        while (other.ContainsStateName(resultStart)||this->ContainsStateName(resultStart))
        {
            resultStart="{"+resultStart+"}";
        }
        while (other.ContainsStateName(resultEnd)||this->ContainsStateName(resultEnd))
        {
            resultEnd="{"+resultEnd+"}";
        }
        State * resultStartState=new State(*other.edges[i]->getStart());
        resultStartState->setStateName(resultStart);
        State* resultEndState=new State(*other.edges[i]->getEnd());
        resultEndState->setStateName(resultEnd);
        resultEdges[edges.size()+i]=new DeltaRelation(*resultStartState,*resultEndState,other.edges[i]->getLabel());    
    }
   
    Automata result;
    result.id=0;
    result.edges=std::move(resultEdges);
    result.CalculateStates();
    return result;
 }
 void Automata::CalculateStates()
 {
     for (DeltaRelation* delta : edges)
     {
         if (!ContainsStateName(delta->getStart()->getStateName()))
         {
             states.push_back(delta->getStart());
         }
         if (!ContainsStateName(delta->getEnd()->getStateName()))
         {
             states.push_back(delta->getEnd());
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
                    result.edges.push_back(new DeltaRelation(*result.states[i],*result.states[i+j],'~'));//Da se fiksne s move Constructor
                    result.states[i+j]->setInitial(false);
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
                result.edges.push_back(new DeltaRelation(*result.states[i],*result.states[j],'~'));
              }
              
           }
           
        }
        
    }
    result.CalculateStates();
    return result;   
 }
 Automata Automata::KleeneStar() const
 {
    //Automata result;
    //result=this->Un();
     State e("e",1,1);//State that recognizes epsilone
     //result.states.push_back(&e);
     return this->Un();
 }
 const std::vector<State *> Automata::FindConnectedStated(const State &start, const std::vector<State *> &visited) const
 {
    std::vector<State*> result;
    for (DeltaRelation* delta:edges)
    {
        if (start==*delta->getStart()&&!ContainsState(*delta->getEnd(),visited))
        {
            result.push_back(delta->getEnd());
        }
        
    }
     return result;
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
   { visited.push_back(state);
     if (FindPaths(*state,visited))
     {
        return false;
     }
     visited.clear();
     
   } 
   return true;
 }

 bool Automata::Finite()
 {
   if(getFinalStates().empty()|| getInitialStates().empty())
   {
      return true;
   }
   std::vector<State*>visitedStates;
   std::vector<DeltaRelation*>visitedEdges;
   const std::vector<State*>initialStates=getInitialStates();
   bool hasCycle;

   for (State* state:initialStates)
   {
      hasCycle=0;
      visitedStates.push_back(state);
      if(HasSuccCyclePath(*state,visitedStates,hasCycle))//If we find successfull path that has cycle->language is not finite
      {
        return false;
      }
      visitedStates.clear();
      visitedEdges.clear();
   }
   
   return true;
 }

 std::vector<State*> Automata::TraversalWithChar(const std::vector<State*>&currStates, const char c)
 {
   std::vector<State*>result;
   for (size_t i = 0; i < currStates.size(); i++)
   {
     for (size_t j = 0; j < edges.size(); j++)
     {
        if (*currStates[i]==*edges[j]->getStart()&&edges[j]->getLabel()==c)
        {
            result.push_back(edges[j]->getEnd());
        }       
     }
     
   }
   return result;
 }

 bool Automata::FindPaths(const State &start,  std::vector<State *> &visitedStates) const
 {
    if(start.isFinal())
    {
      return true;
    }
    if (FindConnectedStated(start,visitedStates).empty()&&!start.isFinal())
    {
      return false;
    }
    for (DeltaRelation* delta:edges)
    {
        if (start==*delta->getStart()&&!ContainsState(*delta->getEnd(),visitedStates))
        {
            visitedStates.push_back(delta->getEnd());
            return FindPaths(*delta->getEnd(),visitedStates);
        }
        
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

 bool Automata::HasSuccCyclePath(const State &start, std::vector<State *> visitedStates, bool hasCycle) const
 {
    // if (StateFormsCycle(start,visitedStates))
    // {
      
    //   hasCycle=1;

    // }
    if (FindConnectedStated(start,visitedStates).empty())
    {
        std::cout<<"Return here";
        return hasCycle;
    }
    
    for (DeltaRelation* delta:edges)
    {
        if (start==*delta->getStart()&&!ContainsState(*delta->getEnd(),visitedStates))
        {
            for (State* state:visitedStates)
            {
                std::cout<<"visited: "<<state->getStateName()<<'\n';
            }
            
            std::cout<<"state: "<<start.getStateName()<<"\n";
            visitedStates.push_back(delta->getEnd());
           
            
            if(StateFormsCycle(*delta->getEnd(),visitedStates))
            {
                if(delta->getEnd()->isFinal())
                {
                    hasCycle=true;
                    return true;
                }
                hasCycle=true;
            }
            return HasSuccCyclePath(*delta->getEnd(),visitedStates,hasCycle);
        }
        
    }
     return false;
 }

 void Automata::draw() const
 {
   std::ofstream out;
   out.open("Automata.dot",std::ios::app);
   if(out.is_open())
   {
     out<<"digraph Automata_"<<id<<"{\n";
     for (size_t i = 0; i < edges.size(); i++)
     {
        if(edges[i]->getStart()->isInitial())
        {
           out<<" hiddenNode[shape=none,label=\"\"]"<<"\n";
           out<<" hiddenNode->"<<edges[i]->getStart()->getStateName()<<"[arrowtail=none]"<<"\n";
        }
        if(edges[i]->getEnd()->isInitial())
        {
           
           out<<" hiddenNode[shape=none,label=\"\"]"<<"\n";
           out<<" hiddenNode->"<<edges[i]->getEnd()->getStateName()<<"[arrowtail=none]"<<"\n";
        }
        if(edges[i]->getStart()->isFinal())
        {
           out<<" "<<edges[i]->getStart()->getStateName()<<"[shape=doublecircle]\n";
        }
        else{
            out<<" "<<edges[i]->getStart()->getStateName()<<"[shape=circle]\n";
        }
        if(edges[i]->getEnd()->isFinal())
        {
           out<<" "<<edges[i]->getEnd()->getStateName()<<"[shape=doublecircle]\n";
        }
        else{
            out<<" "<<edges[i]->getEnd()->getStateName()<<"[shape=circle]\n";
        }
        out<<" "<<edges[i]->getStart()->getStateName();
        out<<"->"<<edges[i]->getEnd()->getStateName();
        out<<"[label=\""<<edges[i]->getLabel()<<"\"]"<<"\n" ;  
     }
     out<<"}\n";
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
    os<<*this;
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
        automata.edges.push_back(delta);
    }
    automata.CalculateStates();
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const Automata &automata)
  {
     out<<'\n'<<automata.edges.size()<<'\n';
    for (size_t i=0;i<automata.edges.size()-1;++i)
    {
        out<<*automata.edges[i]<<'\n';
    }
    out<<*automata.edges[automata.edges.size()-1];
     
     return out;
  }
  bool Automata::Deterministic() const
  {
      if (getInitialStates().size() > 1)
      {
          return false;
      }
      const size_t alphabet_size = 36;
      size_t states_count = 1;
      states_count = states.size();
      bool alphabet[states_count][alphabet_size] = {
          0,
      };
      for (size_t i = 0; i < states_count; ++i)
      {
          for (DeltaRelation *delta : edges)
          {
              if (delta->getLabel() == '~') // Check if there are epsilon transitions
              {
                  return false;
              }

              if (*states[i] == *delta->getStart())
              {

                  if (delta->getLabel() >= 48 && delta->getLabel() <= 57) // if the char is digit
                  {
                      if (alphabet[i][delta->getLabel() - 48])
                      {
                          return false;
                      }
                      alphabet[i][delta->getLabel() - 48] = true;
                  }
                  if (delta->getLabel() >= 97 && delta->getLabel() <= 122) // if the char is small letter
                  {
                      if (alphabet[i][delta->getLabel() - 87])
                      {
                          return false;
                      }
                      alphabet[i][delta->getLabel() - 87] = true;
                  }
              }
          }
      }
      return true;
}
bool Automata:: StateFormsCycle(const State& state,const std::vector<State*>&visitedStates)const
{
    for (DeltaRelation*delta:edges)
    {
       if (state==*delta->getStart()&&ContainsState(*delta->getEnd(),visitedStates));
       {
         return true;
       }
    }
    return false;

}
bool Automata::EdgeIsVisited(const DeltaRelation * delta, std::vector<DeltaRelation *> &visitedEdges) const
 {
    for (DeltaRelation* deltaRel:visitedEdges)
    {
        if (delta==deltaRel)
        {
            return true;
        }   
    }
     return false;
 }

 bool Automata::WordIsValid(const std::string& word)
 {
    for (size_t i = 0; i < word.size(); i++)
    {
       if((word[i]<'a'||word[i]>'z')&&(word[i]<'0'||word[i]>'9'))
       {
          return false;
       }
    }
    
    return true;
 }
 Automata Automata::createAutomataByWord(const std::string &word)
 {
    if(!WordIsValid(word))
    {
        throw "Word is not from (Sigma)* !";
    }
    Automata automata;
    State start("s",0,1);
    for (size_t i = 0; i < word.size()-1; i++)
    {
      State end(std::to_string(i),0,0);
      DeltaRelation delta(start,end,word[i]);
      automata.edges.push_back(new DeltaRelation(start,end,word[i]));
      start=end;
    }
    State final("f",1,0);
    automata.edges.push_back(new DeltaRelation(start,final,word[word.size()-1]));
    automata.CalculateStates();
     return automata;
 }

 Automata Automata::createAutomataByRegex(const std::string &regex)//The idea about recursive tree parsing is from seminar
 {
    //ValidateRegex
    std::string regxWithoutBrackets=regex.substr(1,regex.size()-2);
    unsigned bracketsCount=0;
    size_t strLen=regxWithoutBrackets.size();
    if (WordIsValid(regxWithoutBrackets))
    {
        return Automata::createAutomataByWord(regxWithoutBrackets);
    }
    for (size_t i = 0; i < regxWithoutBrackets.size(); i++)
    {
        if(regxWithoutBrackets[i]=='(')
         bracketsCount++;
        else if(regxWithoutBrackets[i]==')')
         bracketsCount--;
        if (bracketsCount==0)
        {
            if(regxWithoutBrackets[i]=='*')
            {
                return Automata::createAutomataByRegex(regxWithoutBrackets.substr(0,i)).KleeneStar();
            }
            else if(regxWithoutBrackets[i]=='+')
            {
              return Automata::createAutomataByRegex(regxWithoutBrackets.substr(0,i)).Union(Automata::createAutomataByRegex(regxWithoutBrackets.substr(i+1,strLen-i-1)));
            }
            else if(regxWithoutBrackets[i]=='.')
            {
              return Automata::createAutomataByRegex(regxWithoutBrackets.substr(0,i)).Concat(Automata::createAutomataByRegex(regxWithoutBrackets.substr(i+1,strLen-i-1)));  
            }
        }
              
    }
     return Automata();
 }
 void Automata::freeMemory()
 {
    for (DeltaRelation* delta:edges)
    {
        delete delta;
    }
    
 }
 void Automata::copy(const Automata &other)
 {
    id=other.id;
    for (size_t i = 0; i < other.edges.size(); i++)
    {
      edges.push_back(new DeltaRelation(*other.edges[i]));
    }
    
 }


