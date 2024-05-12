#pragma once
#include<vector>
#include "state.h"

class Utilities
{
   public:
   static void MoveElementsRValue(std::vector<State*>&destination,  std::vector<State*>&&);
};
