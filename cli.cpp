#include<iostream>
#include<vector>
#include<fstream>
#include<exception>
#include<string>
#include"CLI.h"
#include"utilities.h"
CommandInterface* CommandInterface::interface=nullptr;
bool CommandInterface::fileIsOpened=0;
std::string CommandInterface::NoOpenedFileMessage="Error! There is no file opened\n";
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
      else
      {
        std::cout<<NoOpenedFileMessage;
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
        if(!fileIsOpened)
        {
         Open(filename);
        }
        else
        {
         std::cout<<"File "<<openedfile<<"is already opened! Please close it before opening another\n";
        }
      }
      catch(const char* str)
      {
        std::cout<<str;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
    }
    else if(GetCommand(inputStr)=="recognize")
    {
      if(!fileIsOpened)
      {
        std::cout<<NoOpenedFileMessage;
      }
      else{

      }

    }
    else if(GetCommand(inputStr)=="deterministic")
    {
      if (!fileIsOpened)
      {
        std::cout << NoOpenedFileMessage;
      }
      else
      {
        std::string automataId;
        for (size_t i = 14; i < inputStr.size(); i++)
        {
          automataId += inputStr[i];
        }
        size_t id=std::stoi(automataId);
        if(id<0||id>=automatas.size())
        {
          std::cout<<"No automata with this id! Type list to see all available automatas!\n";
        }
        else
        {
         std::cout << std::boolalpha << automatas[id]->Deterministic() << '\n';
        }
      }
    }
    else if(GetCommand(inputStr)=="empty")
    {
      if (!fileIsOpened)
      {
        std::cout << NoOpenedFileMessage;
      }
      else
      {
        std::string automataId;
        for (size_t i = 5; i < inputStr.size(); i++)
        {
          automataId += inputStr[i];
        }
        size_t id=std::stoi(automataId);
        if(id<0||id>=automatas.size())
        {
          std::cout<<"No automata with this id! Type list to see all available automatas!\n";
        }
        else
        {
         std::cout << std::boolalpha << automatas[id]->Empty() << '\n';
        }
      }
    }
    else if(GetCommand(inputStr)=="save"&&inputStr.size()!=4)
    {
      if (!fileIsOpened)
      {
        std::cout << NoOpenedFileMessage;
      }
      else
      {
        std::string automataId;
        for (size_t i = 5; i < inputStr.size(); i++)//TODO:Parse filename
        {
          automataId += inputStr[i];
        }
        size_t id=std::stoi(automataId);
        if(id<0||id>=automatas.size())
        {
          std::cout<<"No automata with this id! Type list to see all available automatas!\n";
        }
        else
        {
           try
           {
            automatas[id]->Save(openedfile);
            std::cout<<"Successfully saved automata with id "<<id<<" into "<<openedfile<<'\n';
           }
           catch(const std::exception& e)
           {
            std::cerr << e.what() << '\n';
           }
           
          
        }
        
      }
    }
    else if (inputStr == "save")
    {
      if (!fileIsOpened)
      {
        std::cout << NoOpenedFileMessage;
      }
      else
      {
        try
        {
          Save(openedfile);
        }
        catch (const char* err)
        {
          std::cout << err;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << '\n';
        }
      }
    }
    else if(GetCommand(inputStr)=="saveas")
    {
      std::string fileName;
      fileName=inputStr.substr(7,inputStr.size()-7);
      std::cout<<fileName<<'\n';
      try
      {
        Save(fileName);
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      

    }
    else if(inputStr=="list")
    {
      if(!fileIsOpened)
      {
        std::cout<<NoOpenedFileMessage;
      }
      else
      {
       List();
      }
    }
    else if(GetCommand(inputStr)=="print")
    {
      if(!fileIsOpened)
      {
        std::cout<<NoOpenedFileMessage;
      }
      else
      {
       unsigned automataId;
       automataId=std::stoi(inputStr.substr(6,inputStr.size()-6));
       PrintAutomata(automataId);
      }
    }
    else if(GetCommand(inputStr)=="union")
    {

    }
    else if(GetCommand(inputStr)=="concat")
    {

    }
    else if(GetCommand(inputStr)=="un")
    {

    }
    else if(GetCommand(inputStr)=="reg")
    {
      
    }
   inputStr.clear();
   std::getline(std::cin,inputStr);
  }
 
}

void CommandInterface::Open(const std::string &filename)
{
        std::fstream in;
        in.open(filename,std::ios::in);
        if (in.is_open())
        {
          Deserialize(in);
          openedfile = filename;
          fileIsOpened = true;
          in.close();
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
    else if(conf=='y')
    {
     cleanMemory();
     automatas.clear();
     fileIsOpened=0;
     std::cout<<openedfile<<" closed successfully!\n";
     openedfile="";
    }
    else
     std::cout<<"Invalid argument please try again!\n";
}
void CommandInterface::Exit()
{
    std::cout<<"Are you sure you want to exit the program? Your unsaved changes will be lost!\nType y/n to confirm!\n";
    char conf;
    std::cin>>conf;
    if(conf=='n')
    {
      return;
    }
    else if(conf=='y')
    {
     std::cout<<"Exiting the program!";
     cleanMemory();
     exit(0);
    }
    std::cout<<"Invalid argument. Please try again!";
}

void CommandInterface::Help() const
{
  using std::cout;
  cout<<"The following commands are supported:\n";
  cout<<"open <file> - opens file\n";
  cout<<"close - closes currently opened file\n";
  cout<<"save - saves the opened file\n";
  cout<<"save <id> <filename> - saves the automata in the file with <filename>!\n";
  cout<<"save as <file> - saves the currently opened file in <file>\n";
  cout<<"help - prints this information\n";
  cout<<"exit - exists the program\n";
  cout<<"list - prints the id-s of all read automatas\n";
  //TODO::cout the rest of commands
  

}

void CommandInterface::cleanMemory()
{
  for (Automata *automata : automatas)
  {
    delete automata;
  }
}

void CommandInterface::List() const
{
   std::cout<<"There are "<<automatas.size()<<" read automatas with id from 0 to "<<automatas.size()<<'\n';
}

void CommandInterface::Save(const std::string& fileName) const
{
  std:: ofstream out;
  out.open(fileName,std::ios::trunc);
  if(out.is_open())
  {
    for (Automata*automata:automatas)
    {
      out<<*automata;
    }
    out.close();
    std::cout<<"Successfully saved "<<fileName<<'\n';
  }
  else throw "Coud't save the file!";
}

void CommandInterface::PrintAutomata(unsigned const id) const
{
  if(id<0||id>=automatas.size())
  {
    std::cout<<"Error! There is no automata with this id.\n";
    return;
  }
  automatas[id]->Print();
}

void CommandInterface::Deserialize(std::istream& in)
{
  in.ignore();
  while (!in.eof())
   {
     Automata* a=new Automata();
     in>>*a;
     a->setId(automatas.size());
     automatas.push_back(a);
   }
}

void CommandInterface::Draw(unsigned id) const
{
  if(id<0||id>=automatas.size())
  {
    std::cout<<"Error! There is no automata with this id.\n";
    return;
  }
  automatas[id]->draw();
  std::cout<<"Automata with id: "<<id<<" was drawed successfully. Check Automata.dot file.\n";
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
