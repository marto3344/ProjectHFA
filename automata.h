#pragma once
#include"State.h"
#include"deltaRelation.h"
#include<vector>
#include<string>
class Automata{
    public:
    Automata(unsigned _id,std::vector<DeltaRelation> _edges);
    Automata(std::string regex);
    ~Automata()=default;

    const std::vector<State> getStates();
    
    unsigned getId()const;

    void Print() const;
    void Save(std::string filename)const;
    bool Empty()const;
    bool Finite()const;
    bool Deterministic()const;
    bool Recognize(std::string word)const;
    Automata Union(const Automata &other)const;
    Automata Concat(const Automata &other)const;
    Automata Un(const Automata &other)const;
    


    private:
    unsigned int id;
    std::vector<State>states;
    std::vector<DeltaRelation>edges;
    void CalculateStates();
    bool ContainsStateName(const std::string)const;
    public:
    Automata getUniqueStates(const Automata&other);
};