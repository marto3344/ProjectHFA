#pragma once
#include<string>
#include<fstream>

class CommandInterface{

  public:
  void Run()const;
  CommandInterface();
  private:
  std::string openedfile;
  std::ofstream* streamPtr;//nullptr
  
  void Open(const std::string&);
  void Close();
  void Exit()const;


};