#include"State.h"


  State::State(std::string _name,bool _final,bool _initial):stateName(_name),final(_final),initial(_initial){}
 

  const std::string State::getStateName()const
  {  
    return stateName;
  }
  bool State:: ifFinal()const
  {
    return final;
  }
  bool State:: isInitial()const
  {
    return initial;
  }
  void State:: setFinal(bool const value)
  {
    final=value;
  }
  void State:: setInitial(bool const value)
  {
    initial=value;
  }
 std::ostream&  operator<<(std::ostream& out,const State&other)
 {
    out<<"{"<<other.stateName<<"}";
    return out;
 }