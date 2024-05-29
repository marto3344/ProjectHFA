#include<cstring>
#include<fstream>
#include"state.h"
#include"utilities.h"
  State::State(const std::string &_name,bool _final,bool _initial):stateName(_name),final(_final),initial(_initial){}
  State::State()
  {
    stateName=" ";
    initial=0;
     final=0;
  }
  State::State(const State& other)
  {
    stateName=other.stateName;
    final=other.final;
     initial=other.initial;
  }
  State::State(State &&rhs)
  {
    stateName=std::move(rhs.stateName);
    final=rhs.final;
    initial=rhs.initial;
  }
  State& State::operator=(State&&rhs)
  {
    if(this==&rhs)
    {
      return *this;
    }
    stateName=std::move(rhs.stateName);
    final=rhs.final;
    initial=rhs.initial;
    return *this;
    
  }
  bool State::operator==(const State &other) const
  {
      return stateName==other.stateName&&initial==other.initial&&final==other.final;
  }
  const std::string &State::getStateName() const
  {
    return stateName;
  }
  void State::setStateName(const std::string &name)
  {
    if(!Utilities::IsValidStateName(name))
    {
      throw "Invalid state name!";
    }
    stateName=name;
  }

  bool State::isFinal() const
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
  State& State:: operator=(const State&other)
  {
     if (this==&other)
     {
        return *this;
     }
     final=other.final;
     initial=other.initial;
     stateName=other.stateName;
     return *this;
     
  }
 std::ostream&  operator<<(std::ostream& out,const State&other)
 {
    out<<other.stateName<<" ["<<other.final<<","<<other.initial<<"]";
    return out;
 }
std::istream& operator>>(std::istream& in, State& state)
{
   std::string stateName;
   std::string stateValues;
   in>>stateName;
   in>>stateValues;
   state.stateName=stateName;
   state.final=stateValues[1]-'0';
   state.initial=stateValues[3]-'0';
   return in;
}