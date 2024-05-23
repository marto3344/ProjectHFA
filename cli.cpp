#include<iostream>
#include<vector>
#include<fstream>
#include<exception>
#include<string>
#include"CLI.h"
#include"utilities.h"
CommandInterface* CommandInterface::interface=nullptr;
bool CommandInterface::fileIsOpened=0;
CommandInterface::~CommandInterface()
{
  cleanMemory();
}
CommandInterface& CommandInterface:: Initialize()
{
  if(interface!=nullptr)
  {
    return *interface;
  }
  interface= new CommandInterface();
  return *interface;   
}
void CommandInterface::Run()
{
  std::cout << "Welcome! Type help to see the list of commands!\n";
  std::string inputStr;
  std::getline(std::cin,inputStr);
  while (true)
  {
    if(inputStr=="exit")
    {
      Exit();
    }
    else if(inputStr=="close")
    {
      if(fileIsOpened)
      {
       Close();
      }
    }
    else if(inputStr=="help")
    {
      Help();
    }
    else if(GetCommand(inputStr)=="open")
    {
       std::string filename;
      for (size_t i = 5; i < inputStr.size(); i++)
      {
          filename+=inputStr[i];
      }
      try
      {
        Open(filename);
      }
      catch(const std::string str)
      {
        std::cout<<str;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
    }
   inputStr.clear();
   std::getline(std::cin,inputStr);
  }
 
}

void CommandInterface::Open(const std::string &filename)
{
        std::ifstream in;
        in.open(filename);
        if (in.is_open())
        {
          Deserialize(in);
          openedfile = filename;
          fileIsOpened = true;
          std::cout<<"Successfully opened "<<filename<<'\n';
        }
        else throw "coudn't open the file";
}

void CommandInterface::Close()
{
    std::cout<<"Are you sure you want to close the file? Your unsaved changes will be lost!\nType y/n to confirm!\n";
    char conf;
    std::cin>>conf;
    if(conf=='n')
    {
      return;
    }
    
    automatas.clear();
    openedfile="";
    fileIsOpened=0;
}
void CommandInterface::Exit()const
{
    std::cout<<"Are you sure you want to exit the program? Your unsaved changes will be lost!\nType y/n to confirm!\n";
    char conf;
    std::cin>>conf;
    if(conf=='n')
    {
      return;
    }
    std::cout<<"Exiting the program!";
    exit(0);
}

void CommandInterface::Help() const
{
  std::cout<<"The following commands are supported:\n";
  std::cout<<"open <file> - opens file\n";
  std::cout<<"close - closes currently opened file\n";
  std::cout<<"save - saves the opened file\n";
  std::cout<<"save <id> <filename> - saves the automata in the file with <filename>!\n";
  std::cout<<"save as <file> - saves the currently opened file in <file>\n";
  std::cout<<"help - prints this information\n";
  std::cout<<"exit - exists the program\n";
  std::cout<<"list - prints the id-s of all read automatas\n";
  //TODO::cout the rest of commands
  

}

void CommandInterface::cleanMemory()
{
  for (Automata *automata : automatas)
  {
    delete[] automata;
  }
}

void CommandInterface::List() const
{
  for(Automata* automata:automatas)
  {
     automata->Print();
  }
}

void CommandInterface::Deserialize(std::ifstream& in)
{
   while (!in.eof())
   {
     Automata* a=new Automata();
     in>>*a;
     automatas.push_back(a);
   }
}

const std::string CommandInterface::GetCommand(const std::string input)
{
    std::string command;
    for (char c:input)
    {
      if(c==' ')
      {
        return command;
      }
      command+=c;
    }
    return command;
}
