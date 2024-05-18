#pragma once
#include<string>
#include<fstream>
#include<vector>
#include"automata.h"
class CommandInterface{

  public:
  void Run()const;
  static CommandInterface& Initialize();

  CommandInterface(const CommandInterface&)=delete;
  CommandInterface(const CommandInterface&&)=delete;
  CommandInterface& operator=(const CommandInterface&)=delete;
  CommandInterface& operator=(const CommandInterface&&)=delete;

  private:
  static CommandInterface* interface;
  std::vector<Automata*>automatas;
  std::string openedfile;
  std::ofstream* streamPtr;
  CommandInterface();
  ~CommandInterface();
  void Open(const std::string&);
  void Close();
  void Exit()const;


};