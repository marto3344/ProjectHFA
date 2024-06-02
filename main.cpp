#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"deltaRelation.h"
#include"state.h"
#include "automata.h"
#include"CLI.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
TEST_SUITE("Testing logical methods"){
  TEST_CASE("testEmpty")
  {
    State state1("state1",0,1);
    State state2("s2",0,0);
    State state3("s15",0,0);
    DeltaRelation rel(state1,state2,'a');
    DeltaRelation rel2(state2,state3,'b');
    DeltaRelation rel3(state3,state3,'b');
    std::vector<DeltaRelation*>edges;
    edges.push_back(&rel);
    edges.push_back(&rel2);
    edges.push_back(&rel3);
    Automata a(0,edges);
    CHECK(a.Empty()==true);
  }
  TEST_CASE("Test deterministic")
  {
    State state1("0",0,1);
    State state2("1",0,0);
    State state3("2",0,0);
    DeltaRelation rel(state1,state2,'a');
    DeltaRelation rel2(state2,state3,'b');
    DeltaRelation rel3(state3,state3,'b');
    std::vector<DeltaRelation*>edges;
    edges.push_back(&rel);
    edges.push_back(&rel2);
    edges.push_back(&rel3);
    Automata a(0,edges);
    CHECK(a.Deterministic()==true);
  }
  TEST_CASE("test finite")
  {
    State state1("0",0,1);
    State state2("1",0,0);
    State state3("2",1,0);
    DeltaRelation rel(state1,state2,'a');
    DeltaRelation rel2(state2,state3,'b');
    DeltaRelation rel3(state3,state3,'b');
    std::vector<DeltaRelation*>edges;
    edges.push_back(&rel);
    edges.push_back(&rel2);
    edges.push_back(&rel3);
    Automata a(0,edges);
    CHECK(a.Finite()==true);
  }
  TEST_CASE("test regex balanced brackets validation")
  {
    std::string validRegex="(((abc)*)+(bc))";
    std::string invalidRegex="(abc)+(bc))";
    Automata::ExpressionIsValid(validRegex);
    CHECK(Automata::ExpressionIsValid(invalidRegex)==false);
    CHECK(Automata::ExpressionIsValid(validRegex)==true);
  }
  TEST_CASE("test recognize")
  {
      State state1("0",0,1);
      State state2("1",0,0);
      State state3("2",1,0);
      DeltaRelation rel(state1,state2,'a');
      DeltaRelation rel2(state2,state3,'b');
      DeltaRelation rel3(state2,state1,'b');
      DeltaRelation rel4(state3,state3,'b');
      std::vector<DeltaRelation*>edges;
      edges.push_back(&rel);
      edges.push_back(&rel2);
      edges.push_back(&rel3);
      edges.push_back(&rel4);
      Automata a(0,edges);
      CHECK(a.Recognize("abbb")==true);
      CHECK(a.Recognize("cd")==false);

  }
}

int main(){
  doctest::Context().run();
  //CommandInterface& Interface=CommandInterface::Initialize();
  //Interface.Run();
 }
