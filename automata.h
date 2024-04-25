#pragma once
#include"State.h"
#include"deltaRelation.h"
#include<vector>
#include<string>
class Automata{
    public:
    Automata(unsigned _id,std::vector<State> _states,std::vector<DeltaRelation> _edges);
    Automata(std::string regex);
    ~Automata()=default;
    
    unsigned getId()const;

    void Print() const;
    void Save(std::string filename)const;
    bool Empty()const;
    bool Finite()const;
    bool Deterministic()const;
    bool Recognize(std::string word)const;
    Automata& Union(const Automata &other)const;
    Automata& Concat(const Automata &other)const;
    Automata& Un(const Automata &other)const;
    


    private:
    unsigned int id;
    std::vector<State>states;
    std::vector<DeltaRelation>edges;

    std::vector<State> getUniqueStates(const Automata&other)const;
};