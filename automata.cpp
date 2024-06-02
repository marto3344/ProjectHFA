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
   edges=std::move(other.edges);
   

}
Automata& Automata::operator=(Automata &&other)
{
    if (this == &other)
    {
        return *this;
    }
    id = other.id;
    edges=std::move(other.edges);
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
        std::string resultStart=other.edges[i]->getStart()->getStateName();
        std::string resultEnd=other.edges[i]->getEnd()->getStateName();
        while (other.ContainsStateName(resultStart)||this->ContainsStateName(resultStart))
        {
            resultStart+='0';
        }
        while (other.ContainsStateName(resultEnd)||this->ContainsStateName(resultEnd))
        {
            resultEnd+='0';
        }
        State resultStartState= State(*other.edges[i]->getStart());
        resultStartState.setStateName(resultStart);
        State resultEndState=State(*other.edges[i]->getEnd());
        resultEndState.setStateName(resultEnd);
        resultEdges[edges.size()+i]=new DeltaRelation(resultStartState,resultEndState,other.edges[i]->getLabel());     
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
                    result.states[states.size()+j]->setInitial(false);
                    result.edges.push_back(new DeltaRelation(*result.states[i],*result.states[states.size()+j],'~'));
                }                
            }           
        }
        
    }
    result.CalculateStates();
    return result;   
 }
 Automata Automata::Un() const
 {
     Automata result = Automata(*this);
     for (size_t i = 0; i < states.size(); i++)
     {
         if (result.states[i]->isFinal())
         {
             for (size_t j = 0; j < states.size(); j++)
             {
                 if (result.states[j]->isInitial())
                 {
                     result.edges.push_back(new DeltaRelation(*result.states[i], *result.states[j], '~'));
                 }
             }
         }
     }
     result.CalculateStates();
     return result;
 }

 Automata Automata::KleeneStar() const
 {
    Automata result(this->Un());
    std::string epsiloneStateName="e";//We need a state that recognizes empty word
    while (result.ContainsStateName(epsiloneStateName))
    {
        epsiloneStateName+='e';
    }
    State epsiloneState = State(epsiloneStateName,1,1);
    result.edges.push_back(new DeltaRelation(epsiloneState,epsiloneState,'~'));
    result.CalculateStates();
    return result;
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

 void Automata::draw()
 {
   std::ofstream out;
   out.open("Automata.dot",std::ios::app);
   if(out.is_open())
   {
    CalculateStates();
    std::vector<State*>initialStates=getInitialStates();
    std::vector<State*>finialStates=getFinalStates();
     out<<"digraph Automata_"<<id<<"{\n";
     for (size_t i = 0; i <initialStates.size(); i++)//Print pointing arrow to the initial states
     {
           out<<" hiddenNode[shape=none,label=\"\"]"<<"\n";
           out<<" hiddenNode->"<<initialStates[i]->getStateName()<<"[arrowtail=none]"<<"\n";
     }
     for (size_t i = 0; i < finialStates.size(); i++)//Format it as double circle if state is final;
     {
        out<<" "<<finialStates[i]->getStateName()<<"[shape=doublecircle]\n";
     }
     
     for (size_t i = 0; i < edges.size(); i++)
     {
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
       if(!IsFromAlphabet(word[i]))
       {
          return false;
       }
    }
    
    return true;
 }
 bool Automata::IsOperator(const char c)
 {
   return (c=='.'||c=='*'||c=='+');
 }
 bool Automata::IsBracket(const char c)
 {
     return c=='('||c==')';
 }
 bool Automata::IsFromAlphabet(const char c)
 {
     return (c>='a'&&c<='z')||(c>='0'&&c<='9')||(c=='~');
 }
 bool Automata::DeltaContainsState(const std::vector<DeltaRelation *> &deltaRel, const std::string &stateName)
 {
     for (DeltaRelation* delta:deltaRel)
     {
        if(delta->getStart()->getStateName()==stateName||delta->getEnd()->getStateName()==stateName)
        {
            return true;
        }
     } 
     return false;
 }
 bool Automata::ExpressionIsValid(const std::string &expression) // Recursively validate if regulatr expression matches the format
 {
    unsigned int bracketsCount =0;
    std::string expSubstr;
    expSubstr=expression.substr(1,expression.length()-2);
    if(WordIsValid(expSubstr))
    {
        return true;
    }
    for (size_t i = 0; i < expSubstr.length(); i++)
    {

        if(!IsBracket(expSubstr[i])&&!IsFromAlphabet(expSubstr[i])&&!IsOperator(expSubstr[i]));
        {
            return false;
        }
        if(expSubstr[i]=='(')
        {
         ++bracketsCount;
        }
        if(expSubstr[i]==')')
        {
          -- bracketsCount;
        }
        if(bracketsCount==0)
        {
            if(expSubstr[i]=='*')
            {
               return ExpressionIsValid(expSubstr.substr(0,i));
            }
            if((expSubstr[i]=='.')||(expSubstr[i]=='+'))
            {
               return ExpressionIsValid(expSubstr.substr(0,i))&&ExpressionIsValid(expSubstr.substr(i+1,expSubstr.length()-i-1));
            }
        }    
    }
    return false;
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
 
 void Automata::RemoveEpsilones() 
 {
    std::vector<State*>epsStates=FindStatesThatHaveEps();
    std::vector<State*>states;
    for (State* state:epsStates)
    {
        EpsiloneClosure(state,states);
    }    
 }
 void Automata::EpsiloneClosure(State* state,std::vector<State*>&states)
 {
    if(!VecContainsState(state,states))
    {
        states.push_back(state);
        FindConnWithEps(state,states);
    }
    else{//if the states vector contains state that means we have already made epsilone closure in this state
        return;
    }
    std::string stateName;
    for (State* state:states)//Calculating new state name
    {
        stateName+=state->getStateName();
    }
    while (ContainsStateName(stateName))
    {
        stateName+='0';
    }
    State s1(stateName,vecHasFinal(states),vecHasInitial(states));
    std::vector<DeltaRelation*>newEdges;
    for (DeltaRelation *delta : edges) // Calculate new DeltaRelation
    {
        if (!VecContainsState(delta->getStart(), states) && !VecContainsState(delta->getEnd(), states)) // if the relation is not
        {                                                                                               // from the current e-closure we add the relation
            newEdges.push_back(delta);
        }
        if (VecContainsState(delta->getStart(),states));
        {
           if(VecContainsState(delta->getEnd(),states)&&delta->getLabel()!='~')//Check if we have loop
           { 
             newEdges.push_back(new DeltaRelation(s1,s1,delta->getLabel()));
           }
           else if(delta->getLabel()!='~'){
             newEdges.push_back(new DeltaRelation(s1,*delta->getEnd(),delta->getLabel()));
           }
        }
    }
    freeMemory();
    this->edges=std::move(newEdges);
    this->states.clear();
    CalculateStates();
   
 }

 void Automata::FindConnWithEps(State *state, std::vector<State*>&states)
 {
    for (DeltaRelation*delta:edges)
    {
        if(*state==*delta->getStart()&&delta->getLabel()=='~'&&!VecContainsState(delta->getEnd(),states))//&& states ne sudurja end
        {
           states.push_back(delta->getEnd());
           FindConnWithEps(delta->getEnd(),states);
        }
    }
    
    
 }

 std::vector<State *> Automata::FindStatesThatHaveEps() const
 {
    std::vector<State*>result;
    for (DeltaRelation*delta:edges)
    {
        if(delta->getLabel()=='~')
        {
            result.push_back(delta->getStart());
        }
    }
    return result;
 }

 bool Automata::VecContainsState(const State * state, const std::vector<State *> &states)
 {
     for (State* vecState:states)
     {
        if(*state==*vecState)
        {
            return true;
        }
     }
     
     return false;
 }

 bool Automata::vecHasFinal(const std::vector<State *> states)
 {
    for (State*state:states)
    {
        if(state->isFinal())
        {
            return true;
        }
    }
    return false;
 }

 bool Automata::vecHasInitial(const std::vector<State *> states)
 {
    for (State* state:states)
    {
        if(state->isInitial())
        {
            return true;
        }
    }
    return false;
 }
