#include"CLI.h"
#include<iostream>
#include<vector>
CommandInterface* CommandInterface::interface=nullptr;
CommandInterface& CommandInterface:: Initialize()
{
  if(interface!=nullptr)
  {
    return *interface;
  }
  interface= new CommandInterface();
  return *interface;   
}
CommandInterface::CommandInterface(){}
CommandInterface::~CommandInterface()
{
  std::cout<<"~Interface";
//     if(streamPtr!=nullptr)
//     {
//         delete[]streamPtr;
//     }
//     for (Automata* automata:automatas)
//     {
//        delete[] automata;
//     }
    
}
void CommandInterface::Run()const
{
    std::string command="";
    std::cout<<"Welcome! Type help to see the list of commands!\n";
    std::cin>>command;
   while (command!="exit")
   {
      
     
      std::cin>>command; 
   }
   Exit();
   
}
void CommandInterface::Open(const std::string &filename) 
{
   openedfile=filename;
   std::ofstream os;
   os.open(filename);
   if (os.is_open())
   {
     std::cout<<"Successfully opened file "<<filename;
     streamPtr=&os;
   }
   //throw->exep
}

void CommandInterface::Close()
{
    streamPtr=nullptr;
    openedfile="";
}
void CommandInterface::Exit()const
{
    std::cout<<"Exiting the program!";
    exit(0);
}