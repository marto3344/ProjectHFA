#include"CLI.h"
#include<iostream>
#include<vector>
CommandInterface* CommandInterface::interface=nullptr;
bool CommandInterface::fileIsOpened=0;
CommandInterface& CommandInterface:: Initialize()
{
  if(interface!=nullptr)
  {
    return *interface;
  }
  interface= new CommandInterface();
  return *interface;   
}
void CommandInterface::Run() const
{
  std::string command = "";
  std::cout << "Welcome! Type help to see the list of commands!\n";
  std::cin >> command;
  while (true)
  {
    if(command=="exit")
    {
      Exit();
    }
    std::cin >> command;
  }
 
}
void CommandInterface::Open(const std::string &filename) 
{
 
   std::ofstream os;
   os.open(filename);
   if (os.is_open())
   {
     std::cout<<"Successfully opened file "<<filename;
     openedfile=filename;
     fileIsOpened=true;
     os.close();
   }
   throw "Error! Coudn't open the file "+filename;
}

void CommandInterface::Close()
{
    std::cout<<"Are you sure you want to close the file! Your unsaved changes will be lost!\nType y/n to confirm!\n";
    char conf;
    std::cin>>conf;
    if(conf=='n')
    {
      return;
    }
    for (Automata* automata:automatas)
    {
      delete[]automata;
    }
    automatas.clear();
    openedfile="";
    fileIsOpened=0;
}
void CommandInterface::Exit()const
{
    std::cout<<"Are you sure you want to exit the program! Your unsaved changes will be lost!\nType y/n to confirm!\n";
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
  std::cout<<"list - prints the id-s of all read automatas";
  //TODO::cout the rest of commands


}

void CommandInterface::List() const
{
  for(Automata* automata:automatas)
  {
     automata->Print();
     std::cout<<'\n';
  }
}

void CommandInterface::Serialize()
{
  //TODO:Serialize automatas
}
