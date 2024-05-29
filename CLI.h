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
  static std::string NoOpenedFileMessage;
  CommandInterface()=default;
  ~CommandInterface();

  void Open(const std::string&);
  void Close();
  void Exit();
  void Help()const;
  void List()const;
  void Save(const std::string&filename)const;
  void PrintAutomata(unsigned const id)const;
  public:
  void Deserialize(std::istream&);
  void Draw(unsigned)const;
  static const std::string GetCommand(const std::string);
  void cleanMemory();

};