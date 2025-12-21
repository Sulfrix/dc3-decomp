#pragma once
#include "obj/Object.h"
#include "utl/Str.h"

class SkeletonIdentifier : public Hmx::Object {
public:
    SkeletonIdentifier();
    virtual ~SkeletonIdentifier();

    void Init();
    void Poll();
    String GetPlayerName(int) const;
};

extern SkeletonIdentifier *TheSkeletonIdentifier;
