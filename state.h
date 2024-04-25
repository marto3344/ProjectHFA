#pragma once
#include<string>
#include<ostream>

class State{
  public:
  State(std::string _name,bool _final,bool _initial);
  ~State()=default;

  const std::string getStateName()const;
  bool ifFinal()const;
  bool isInitial()const;
  void setFinal(bool const value);
  void setInitial(bool const value);
  friend std::ostream& operator<<(std::ostream& out,const State&other);
 
  private:
  std::string stateName;
  bool initial=0;
  bool final=0;

};