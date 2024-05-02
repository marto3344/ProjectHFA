#include "deltaRelation.h"

DeltaRelation:: DeltaRelation(State _start,State _end, char _label):start(&_start),end(&_end),label(_label){}
DeltaRelation::DeltaRelation()
{
    start=nullptr;
    end=nullptr;
    label=0;
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
char DeltaRelation:: getLabel()const
{
    return label;
}
const State& DeltaRelation:: getStart()const
{
    return *start;
}
const State& DeltaRelation:: getEnd()const
{ 
    return *end;
}
std::ostream& operator<<(std::ostream& out, const DeltaRelation &delta){
    out<< "(" << delta.getStart().getStateName() << ","<<delta.getLabel()<<","<< delta.getEnd().getStateName() << ")"<< " ";
    return out;
}