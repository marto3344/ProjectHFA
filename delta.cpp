#include "deltaRelation.h"

DeltaRelation:: DeltaRelation(State _start,State _end, char _label):start(_start),end(_end),label(_label){}
char DeltaRelation:: getLabel()const
{
    return label;
}
const State& DeltaRelation:: getStart()const
{
    return start;
}
const State& DeltaRelation:: getEnd()const
{ 
    return end;
}
std::ostream& operator<<(std::ostream& out, const DeltaRelation &delta){
    out<< "(" << delta.getStart().getStateName() << ","<<delta.getLabel()<<","<< delta.getEnd().getStateName() << ")"<< " ";
    return out;
}