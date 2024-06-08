#pragma once
#include"State.h"
#include"deltaRelation.h"
#include<vector>
#include<string>
class Automata{
    public:
    Automata()=default;
    Automata(unsigned _id,const std::vector<DeltaRelation*>& _edges);
    Automata(const Automata&other);
    Automata& operator=(const Automata&other);
    Automata(Automata &&other);
    Automata& operator=(Automata &&other);
    ~Automata();

    const std::vector<State*> getStates();
    
    unsigned getId()const;

    void Print() const;
    void Save(std::string filename)const;
    bool Empty() const;
    bool Finite();
    bool Deterministic()const;
    void draw();
    void setId(unsigned);
    bool Recognize(std::string word);
    Automata Union(const Automata &other)const;
    Automata Concat(const Automata &other)const;
    Automata Un()const;
    Automata KleeneStar()const;
    friend std::istream& operator>>(std::istream& in, Automata& automata);
    friend std::ostream& operator<<(std::ostream& out,const Automata& automata);
    
    static Automata createAutomataByWord(const std::string &word);
    static Automata createAutomataByRegex(const std::string &regex);
    static bool ExpressionIsValid(const std::string &expression);
    void Determinize();

    private:
    unsigned int id;
    std::vector<State*>states;
    std::vector<DeltaRelation*>edges;
    void CalculateStates();
    bool ContainsStateName(const std::string)const;
    const std::vector<State*>FindConnectedStated(const State& start,const std::vector<State*>&visited)const;
    std::vector<State*>TraversalWithChar(const std::vector<State*>&, const char c);
    bool FindPaths(const State& start, std::vector<State*>& visitedStates)const;
    bool static ContainsState(const State& state,const std::vector<State*>&vec);
    bool HasSuccCyclePath(const State& start,std::vector<State*>& visitedStates,std::vector<State*>& visitedPath)const;
    bool StateFormsCycle(const State& state,const std::vector<State*>&visitedStates,unsigned &cycleStart)const;
    const std::vector<State*>getFinalStates()const;
    const std::vector<State*>getInitialStates() const;

    static bool WordIsValid(const std::string& word);
    static bool IsOperator(const char c);
    static bool IsBracket(const char c);
    static bool IsFromAlphabet(const char c);
    static bool DeltaContainsState(const std::vector<DeltaRelation*>&deltaRel, const std::string&stateName);
    Automata getUniqueStates(const Automata &other) const;
    
    std::vector<State*> ConnectedStates(std::vector<State*>&states, const char label);
    State ConvertClosureToState(const std::vector<State*>&closure);
    void EpsiloneClosure(std::vector<State*>& states);
    void FindConnWithEps(State* state, std::vector<State*>& states);
    static bool VecContainsState(const State*, const std::vector<State*>& states);
    void freeMemory();
    void copy(const Automata &other);
    
};