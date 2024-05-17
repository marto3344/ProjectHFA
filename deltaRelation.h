#pragma once
#include"State.h"
#include<vector>


class DeltaRelation
{
   public:
   DeltaRelation(const  State &_start, const State &_end, char _label);
   DeltaRelation();
   DeltaRelation(const DeltaRelation&other);
   ~DeltaRelation();
   DeltaRelation& operator=(const DeltaRelation &other);
   char getLabel()const;
   State* getStart()const;
   State* getEnd()const;
   

   friend std::ostream& operator<<(std::ostream& out, const DeltaRelation &relation);


   private:
    State* start;
    State* end;
    char label;
};


