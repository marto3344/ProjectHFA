#pragma once
#include"State.h"
#include"deltaRelation.h"
#include<vector>

class Aoutomata{


    private:
    unsigned int id;
    std::vector<State>states;
    std::vector<DeltaRelation>edges;
};