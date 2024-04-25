#pragma once
#include"State.h"
#include<vector>


class DeltaRelation
{
   public:
   DeltaRelation(State _start,State _end, char _label);
   ~DeltaRelation()=default;
   friend std::ostream& operator<<(std::ostream out, const DeltaRelation &relation);
   private:
    State start;
    State end;
    char label;
};


