#pragma once
#include<vector>
#include<fstream>
#include"State.h"

class DeltaRelation
{
   public:
   DeltaRelation(const  State &_start, const State &_end, char _label);
   DeltaRelation(State &&start,State &&end, char _label);
   DeltaRelation();
   DeltaRelation(const DeltaRelation&other);
   DeltaRelation(DeltaRelation&&other);
   ~DeltaRelation();
   DeltaRelation& operator=(const DeltaRelation &other);
   DeltaRelation& operator=(DeltaRelation &&other);
   char getLabel()const;
   State* getStart()const;
   State* getEnd()const;
   

   friend std::ostream& operator<<(std::ostream& out, const DeltaRelation &relation);
   friend std::istream& operator>>(std::istream& in, DeltaRelation& relation);

   private:
    State* start;
    State* end;
    char label;
};


