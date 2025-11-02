#pragma once
#include "utl/Symbol.h"

class PhysMemTypeTracker {
public:
    PhysMemTypeTracker(Symbol);
    ~PhysMemTypeTracker();
};

int PhysicalUsage();
void PhysicalFree(void *);
int ForceLinkXMemFuncs();
