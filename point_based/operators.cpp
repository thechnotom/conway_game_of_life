#ifndef OPERATORS_CPP
#define OPERATORS_CPP

#include "Point.h"

struct ptrComp {
    bool operator() (const Point* lhs, const Point* rhs) const {
        return lhs->hash() < rhs->hash();
    }
};

#endif