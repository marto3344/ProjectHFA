#pragma once
#include"State.h"
#include"deltaRelation.h"
#include<vector>
#include<string>
class Automata{
    public:
    Automata(unsigned _id,const std::vector<DeltaRelation>& _edges);
    Automata(const Automata&other);
    Automata(std::string regex);
    ~Automata();

    const std::vector<State*> getStates();
    
    unsigned getId()const;

    void Print() const;
    void Save(std::string filename)const;
    bool Empty();
    bool Finite();
    bool Deterministic()const;
    bool Recognize(std::string word);
    Automata Union(const Automata &other)const;
    Automata Concat(const Automata &other)const;
    Automata Un()const;
    


    private:
    unsigned int id;
    std::vector<State*>states;
    std::vector<DeltaRelation>edges;
    void CalculateStates();
    bool ContainsStateName(const std::string)const;
    void RemoveEpsilons();
    std::vector<State*> EpsiloneClosure(const State &other);
   
    std::vector<State*>getFinalStates();
    std::vector<State*>TraversalWithChar(const std::vector<State*>&, const char c);
    std::vector<State*>getInitialStates();
    public:
    Automata getUniqueStates(const Automata&other)const;
    
};