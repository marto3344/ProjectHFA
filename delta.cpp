#include<fstream>
#include "deltaRelation.h"

DeltaRelation:: DeltaRelation(const State &_start, const State &_end, char _label){
  start=new State(_start);
  end=new State(_end);
  label=_label;
}
DeltaRelation::DeltaRelation()
{
    start=nullptr;
    end=nullptr;
    label=0;
}
DeltaRelation::DeltaRelation(const DeltaRelation&other)
{
   start=new State( *other.start);
   end=new State( *other.end);
   label=other.label;
}
DeltaRelation::DeltaRelation(DeltaRelation &&other)
{
    start=other.start;
    end=other.end;
    label=other.label;
    other.start=nullptr;
    other.end=nullptr;
}
DeltaRelation& DeltaRelation:: operator=(const DeltaRelation &other)
{
    if (this==&other)
    {
        return *this;
    }
    start=new State( *other.start);
    end=new State( *other.end);
    label=other.label;
    return *this;
    

}
DeltaRelation& DeltaRelation::operator=(DeltaRelation &&other)
{
    if(this==&other)
    {
        return *this;
    }
    delete start;
    delete end;
    start=other.start;
    end=other.end;
    label=other.label;
    other.start=nullptr;
    other.end=nullptr;
    return *this;
}
DeltaRelation::~DeltaRelation()
{
    if(start!=nullptr)
    {
        delete start;
    }
    if(end!=nullptr)
    {
        delete end;
    }
}
char DeltaRelation::getLabel() const
{
    return label;
}
State* DeltaRelation:: getStart()const
{
    return start;
}
State* DeltaRelation:: getEnd()const
{ 
    return end;
}
std::ostream& operator<<(std::ostream& out, const DeltaRelation &delta){
    out<< *delta.getStart()<< " "<<delta.getLabel()<<" "<< *delta.getEnd();
    return out;
}
std::istream& operator>>(std::istream& in, DeltaRelation& relation){
    if(relation.start!=nullptr)
    {
        delete []relation.start;
    }
    if(relation.end!=nullptr)
    {
        delete[]relation.end;
    }
    State* start=new State();
    State* end=new State();
    char c;
    in>>*start;
    in>>c;
    in>>*end;
    relation.start=start;
    relation.end=end;
    relation.label=c;
    return in;
}