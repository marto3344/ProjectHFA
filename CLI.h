#pragma once
#include<string>
#include<fstream>
#include<vector>
#include"automata.h"
class CommandInterface{

  public:
  void Run();
  static CommandInterface& Initialize();

  CommandInterface(const CommandInterface&)=delete;
  CommandInterface(const CommandInterface&&)=delete;
  CommandInterface& operator=(const CommandInterface&)=delete;
  CommandInterface& operator=(const CommandInterface&&)=delete;

  private:
  
  static CommandInterface* interface;
  static bool fileIsOpened;
  std::vector<Automata*>automatas;
  std::string openedfile;
  
  CommandInterface()=default;
  ~CommandInterface()=default;

  void Open(const std::string&);
  void Close();
  void Exit()const;
  void Help()const;
  void List()const;
  void Deserialize(std::fstream&);
  static const std::string GetCommand(const std::string);

};