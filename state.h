#pragma once
#include<string>
#include<fstream>

class State{
  public:
  State(std::string _name,bool _final,bool _initial);
  State();
  State(const State &other);
  State(const State &&rhs);
  ~State()=default;
  State&  operator=(const State&other);
  State& operator=(const State&&rhs);
  const std::string getStateName()const;
  void setStateName(const std::string name);
  bool isFinal()const;
  bool isInitial()const;
  void setFinal(bool const value);
  void setInitial(bool const value);
  friend std::ostream& operator<<(std::ostream& out,const State&other);
  friend std::ifstream& operator>>(std::ifstream& in, State&);
  
  private:
  std::string stateName;
  bool initial=0;
  bool final=0;

};