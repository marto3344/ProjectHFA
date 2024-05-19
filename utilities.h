#pragma once
#include<vector>
#include<string>
#include "state.h"

class Utilities
{
   public:
   static void MoveElementsRValue(std::vector<State*>&destination,  std::vector<State*>&&);
   static bool IsValidStateName(const std::string);
   static int ConvertChartToInt(const char c);
};
