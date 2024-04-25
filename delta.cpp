#include "deltaRelation.h"

DeltaRelation:: DeltaRelation(State _start,State _end, char _label):start(_start),end(_end),label(_label){}

std::ostream& operator<<(std::ostream out, const DeltaRelation &relation){
    out<<"("<<relation.start.getStateName()<<","<<relation.end.getStateName()<<")";
    return out;
}